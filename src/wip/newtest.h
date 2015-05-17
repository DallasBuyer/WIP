#include<iostream>
void* operator new[](size_t size)  
{  
    std::cout<<"call global new[] size: "<<size<<std::endl;  
    return malloc(size);  
}  
class Time
{
private:
 int hrs,mins,secs;//ʱ,��,��
public:
 Time(int hrs=19,int mins=35,int secs=20);//Ĭ�ϲ����Ĵ��ι��캯��
 ~Time();//��������
 void showTime()const;
 Time operator ++();//����ǰ׺���������,++x
 Time operator ++(int);//���غ�׺�������㷨,x++
 bool operator ==(const Time &)const;//��������������
 Time & operator =(const Time &);//���ظ�ֵ�����
 void * operator new(size_t size);//����new()�����,��:int * pInt=new int(0);
 void operator delete(void * ptr);//����delete()�����,��:delete pInt;
 void * operator new[](size_t size);//����new[]()�����,�Է�������
 void operator delete[](void * ptr);//����delete[]()�����,��ȥ������,�ͷ�������ռ�ڴ�
};
Time::Time(int hrs,int mins,int secs)
{
 this->hrs=hrs;
 this->mins=mins;
 this->secs=secs;
 std::cout<<"Time��Ĭ�ϲ����Ĵ��ι��캯�� "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl;
}

Time::~Time()
{
 std::cout<<"Time���������� "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl; 
}

void Time::showTime()const
{
 std::cout<<"Time��showTime()const���� "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl;
}
Time Time::operator ++()//����ǰ׺���������,++x
{
 secs++;
 if(secs>=60)
 {
  secs=0;
  mins++;
  if(mins>=60)
  {
   mins=0;
   hrs++;
   if(hrs>=24)
   {
    hrs=0;
   }
  }
 }
 return Time(hrs,mins,secs);//����������ʱ����
}
Time Time::operator ++(int)//���غ�׺�������㷨,x++
{
 Time temp(hrs,mins,secs);//������ʱ����,�����г�ʼ��
 ++secs;
 if(secs>=60)
 {
  secs=0;
  mins++;
  if(mins>=60)
  {
   mins=0;
   hrs++;
   if(hrs>=24)
   {
    hrs=0;
   }
  }
 }
 return temp;
}
bool Time::operator ==(const Time & aTime)const//��������������
{
 return ((hrs==aTime.hrs)&&(mins==aTime.mins)&&(secs==aTime.secs));
}
Time & Time::operator =(const Time & aTime)//���ظ�ֵ�����
{
 hrs=aTime.hrs;
 mins=aTime.mins;
 secs=aTime.secs;
    std::cout<<"Time�ำֵ��������� "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl;
 return (*this);//���ص�ǰ���������
}
void * Time::operator new(size_t size)//����new()�����,��:int * pInt=new int();
{
 std::cout<<"operator new() is called.Object size is "<<size<<std::endl;
 return malloc(size);//?//�����ɴ洢�з����ڴ�
}
void Time::operator delete(void * ptr)//����delete()�����,��:delete pInt;
{
 std::cout<<"operator delete() is called"<<std::endl;
 free(ptr);//�����ɴ洢���ͷ��ڴ�
}
void * Time::operator new[](size_t size)//����new[]()�����,�Է�������
{ 
 std::cout<<"operator new[]() is called.Object size is "<<size<<std::endl;
 return malloc(size);//?//�����ɴ洢�з����ڴ�
}
void Time::operator delete[](void * ptr)//����delete[]()�����,��ȥ������,�ͷ�������ռ�ڴ�
{ 
 std::cout<<"operator delete[]() is called"<<std::endl;
 free(ptr);//�����ɴ洢���ͷ��ڴ�
}

int main()
{
 Time * pTime;
 pTime=new Time;//����new()�����,����Ĭ�Ϲ��캯��
 pTime->showTime();
 delete pTime;//����delete()�����
 pTime=new Time[3];//����new[]()�����,�Է�������,����Ĭ�Ϲ��캯��
 delete [] pTime;//����delete[]()�����,��ȥ������,�ͷ�������ռ�ڴ�
 getchar();
 return 0;
}