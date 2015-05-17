#include "ResourceManager.h"
#include "FreeImage.h"
#include <iostream>
#include "Utilities/Utilities.h"
#include "Assertion.h"
#include "SoundHelper.h"
#include "PathTool.h"
#include <al.h>
#include <alc.h>
#include <alext.h>
#include <alut.h>
int g_size = 0;


WIPResourceManager* WIPResourceManager::_instance = 0;

WIPResourceManager::WIPResourceManager()
{

}

WIPResourceManager::~WIPResourceManager()
{

}

WIPResourceManager* WIPResourceManager::get_instance()
{
	if(!_instance)
		_instance = new WIPResourceManager();
	return _instance;
}

bool WIPResourceManager::startup()
{
	return true;
}

void WIPResourceManager::shutdown()
{
	free_all();
}

//return NULL if fail
ResHandler* WIPResourceManager::load_resource(const char* filename,WIPResourceType type)
{

	file2ptr_map::iterator it = _map.find(filename);
	if(_map.end() != it)
	{
		add_ref(it->second);
		return it->second;
	}
	ResHandler* res = alloc(filename,type);

	


	if(!res)
	{
		
		return NULL;
	}
	_map[filename] = res;
	return res;

	/*
	char* file = _map.find(filename)->first;
	void* file_ptr = _map.find(filename)->second;
	*/

}

ResHandler* WIPResourceManager::clone(ResHandler* handler)
{
	handler->nref ++;
	return handler;
}

void WIPResourceManager::free_all()
{
	ResHandler* handler;
	file2ptr_map::iterator it;
	for(it=_map.begin();it!=_map.end();++it)
	{
		handler = it->second;
		free_resource(handler);
		//::free(it->second);
	}
	_map.clear();
	_ref.clear();

}


int WIPResourceManager::free(ResHandler* file,int size)
{
	//remove_ref(file);
	if(file==NULL)
		return SUCC_RELEASE;
	int ret = FAIL;
	unsigned int & ref_num = file->nref;
	if(ref_num>0)
	{
		ref_num--;
		ret = SUCC_SUB;
	}
	if(ref_num<=0)
	{

		_map.erase(file->file_name);
		free_resource(file);
		ret = SUCC_RELEASE;
	}
	return ret;
}

void WIPResourceManager::add_ref(ResHandler* file)
{
	file->nref++;
}

void WIPResourceManager::remove_ref(ResHandler* file)
{
	unsigned int& ref_num =file->nref;
	if(ref_num>0)
		ref_num--;
}

void WIPResourceManager::set_ref(ResHandler* file,int num)
{
	if(num>=0)
		_ref[file] = num;
}

void WIPResourceManager::delete_handler(ResHandler* handler)
{

	delete handler;
	//useless
	//handler = NULL;
}

void WIPResourceManager::free_resource(ResHandler* handler)
{
	switch (handler->type)
	{
	case TEXT:
		{
			delete (std::string*)handler->ptr;
			delete (TextData*)handler->extra;
			//delete_handler(handler);
		}
		break;
	case TEXTURE:
		//FreeImage_Unload((FIBITMAP*)handler->ptr_1);
		delete [] (unsigned char*)handler->ptr;
		delete (TextureData *)handler->extra;
		//delete_handler(handler);
		break;
	case SOUND:
		{

		alGetError();
		string exe = WIPPathTool::get_file_extension(handler->file_name);
		alDeleteBuffers(1,&((SoundData*)(handler->extra))->buffer_index);
		int e = alGetError();
		if ( e!= AL_NO_ERROR)
		{
			printf("alDeleteBuffers failed!:%d\n",e);
			getchar();
			exit(0);
		}
		/*
		if (exe=="wav")
		{
			WIPSoundHelper::unload_sound(handler->ptr,
				((SoundData*)(handler->extra))->al_format,
				((SoundData*)(handler->extra))->size,
				((SoundData*)(handler->extra))->frequency,
				SoundOutFormat::WAV
				);
		}
		else if(exe=="ogg")
		{
			
			WIPSoundHelper::unload_sound(handler->ptr,
				((SoundData*)(handler->extra))->al_format,
				((SoundData*)(handler->extra))->size,
				((SoundData*)(handler->extra))->frequency,
				SoundOutFormat::OGG
				);
				
		}
		*/
		delete (SoundData *)handler->extra;
		//delete_handler(handler);
		break;
		}
	default:
		break;
	}
	delete_handler(handler);
}

//!!!be sure to release memory before return null
ResHandler* WIPResourceManager::alloc(const char* filename,WIPResourceType type)
{
	ResHandler* res = new ResHandler;
	switch (type)
	{
	case TEXT:
		{
			TextData *data = new TextData;
			std::string* str_data = new std::string;
			read_text_file(filename,*str_data);
			res->extra = data;
			res->file_name = filename;
			res->nref = 1;
			res->ptr = str_data;
			res->size = str_data->size();
			res->type = TEXT;
			return res;
		}
		break;
	case TEXTURE:
		{
			TextureData *data = new TextureData;
			//��ʼ��FreeImage
			FreeImage_Initialise(TRUE);

			FIBITMAP* bmpConverted = NULL;
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			fif = FreeImage_GetFileType(filename);
			if(fif == FIF_UNKNOWN)
				fif  =  FreeImage_GetFIFFromFilename(filename);
			if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif))
			{

				FIBITMAP *dib = FreeImage_Load(fif, filename);

				if(!dib)
				{
					printf("[fatal error]: \"%s\" load error!\n",filename);
					delete data;
					delete_handler(res);
					return NULL;
				}

				// we are top left, FIBITMAP is bottom left
				FreeImage_FlipVertical(dib);
				//get infomation
				FREE_IMAGE_TYPE imgType = FreeImage_GetImageType(dib);
				FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(dib);
				unsigned int bpp = FreeImage_GetBPP(dib);

				data->bpp = bpp;
				data->color_type = colorType;
				data->image_type = imgType;
				data->channel = 4;

				int x,y;
				RGBQUAD m_rgb;

				//��ȡͼƬ����
				int width = (int)FreeImage_GetWidth(dib);
				int height = (int)FreeImage_GetHeight(dib);

				unsigned char* imgBuf = new unsigned char[width*height*4];

				//��ȡͼƬ����
				//��RGBA��ʽ���浽������
				for(y=0;y<height;y++)
				{
					for(x=0;x<width;x++)
					{
						//��ȡ����ֵ
						FreeImage_GetPixelColor(dib,x,y,&m_rgb);

						if(FreeImage_IsLittleEndian())
						{
							imgBuf[y*width*4+x*4+0] = m_rgb.rgbRed;
							imgBuf[y*width*4+x*4+1] = m_rgb.rgbGreen;
							imgBuf[y*width*4+x*4+2] = m_rgb.rgbBlue;
							//�ж��Ƿ�͸��ͼƬ
							//����Ǿ�ȡalphaֵ����
							if(FreeImage_IsTransparent(dib))
								imgBuf[y*width*4+x*4+3] = m_rgb.rgbReserved;
							else
								imgBuf[y*width*4+x*4+3] = 255;
						}
						else
						{
							//��˾���!
							//Big Endian Warnning!
							printf("Note:This is a Big endian!\n");
						}
					}
				}

				
				data->width = width;
				data->height = height;
				data->size = height*width*4;


				FreeImage_Unload(dib);

				res->file_name = filename;
				res->extra = data;
				res->nref = 1;
				res->ptr = imgBuf;
				res->size =  width*height*4;
				res->type = TEXTURE;

				_map[filename] = res;

				return res;
			}
		}
		break;
		
	case SOUND:
		{
			//clear error
			//alGetError();
		SoundData* data = new SoundData();
		WIPSoundHelper::load_sound((char*)filename,&data->al_format,&res->ptr,&data->size,&data->frequency,&data->loop);
		alGenBuffers(1,&data->buffer_index);
		int e = alGetError();
		if ( e!= AL_NO_ERROR)
		{
			printf("alGenBuffers failed!:%d\n",e);
			getchar();
			exit(0);
		}
		alBufferData(data->buffer_index,data->al_format,res->ptr,data->size,data->frequency);
		string exe = WIPPathTool::get_file_extension(filename);
		if(exe=="wav")
		{
			alutUnloadWAV(data->al_format,res->ptr,data->size,data->frequency);
		}
		else if(exe=="ogg")
		{
			::free(res->ptr);
		}
		res->ptr = 0;
		e = alGetError();
		if (e != AL_NO_ERROR)
		{
			printf("alBufferData failed!:%d\n",e);
			getchar();
			exit(0);
		}
		res->file_name = filename;
		res->extra = data;
		res->nref = 1;
		res->size = data->size;
		res->type = SOUND;


		return res;
		break;
		}
	default:
		return res;
		break;
	}
	delete_handler(res);
	return NULL;
}

WIPResourceManager* g_res_manager = WIPResourceManager::get_instance();