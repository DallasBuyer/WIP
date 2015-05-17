#pragma once
#include "al.h"
/*
��ȡ��������Դ�İ�����
*/
enum SoundOutFormat
{
	OGG,
	WAV
};
class WIPSoundHelper
{
public:
	//TODO:return void* and length
	static bool load_sound(char* file_path,int* format,void **data,int* size,int* frequency,ALboolean* loop);
	static void unload_sound(void * data,int format,int size,int frequency,SoundOutFormat type);
private:
	static bool load_sound_wav(char* file_path,int* format,void **data,int* size,int* frequency,ALboolean* loop);
	static bool load_sound_ogg(char* file_path,int* format,void **data,int* size,int* frequency,ALboolean* loop);
	static void unload_sound_wav(void * data,int format,int size,int frequency);
	static void unload_sound_ogg(void * data,int format,int size,int frequency);
};