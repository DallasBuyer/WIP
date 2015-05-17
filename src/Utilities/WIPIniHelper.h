#include "SimpleIni.h"


class WIPIniHelper
{
public:
	//�����趨��ǰӰ���ini�ļ�
	static bool reset_ini_file(const char* filename);
//��ȡһ��ָ������name��ֵ��ŵ�des��û�д���Ŀ����false.
static bool get_int(char*section_name,char* name,int& des);
static bool get_float(char*section_name,char* name,float& des);
static bool get_string(char*section_name,char* name,std::string& des);

/*д��һ��ָ��������ô��ֵ���������Ŀ������д�Ǹ�ֵ�����������:
 *section_name==NULL �򴴽�һ��section��Ϊ[NULL],����һsection�����½���ֵ��д��
 *���� ����ָ��section_name�����½���ֵ��д��
*/
static void set_int(char* name,int val,char* section_name=NULL);
static void set_float(char* name,float val,char* section_name=NULL);
static void set_string(char* name,std::string val,char* section_name=NULL);
//������һ��sectionΪnew_name
//���section����������ĩβ�½�
static void rename_section(char* section_name,char* new_name);

static void close();
private:
	static CSimpleIniA _ini;
	static std::string _filename;
	//static bool _binit;
};