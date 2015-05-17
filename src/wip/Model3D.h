#pragma once
#include "OpenGL.h"

class WIPModel3D
{
public:
	WIPModel3D();
	~WIPModel3D();
	void renderer(int glmode);
	//ע���������unsigned short��ΪOpenGL���������������ͣ�����unsigned short�����ֵΪ65535������
	//����65535�������ģ�ͼ��ػ��������
	bool load(const char* file);
	bool load_weight(const char* file);
	bool attach_bone();
	//
	inline GLuint get_vbo()
	{
		return _vbo;
	}
	inline GLuint get_vao()
	{
		return _vao;
	}
	inline GLuint get_ebo()
	{
		return _ebo;
	}
	inline int get_vert_count()
	{
		return _vert_count;
	}
	inline int get_index_count()
	{
		return _index_count;
	}
	inline int get_index_size()
	{
		return _index_size;
	}
	inline int get_vert_size()
	{
		return _vert_size;
	}
protected:

private:
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _bbo;
	GLuint _nbo;
	GLuint _tbo;
	int _vert_count;
	int _index_count;
	int _vert_size;
	int _index_size;
};