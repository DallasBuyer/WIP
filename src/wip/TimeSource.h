#pragma once
class TimeSource
{
public:
    virtual ~TimeSource() {};
	//���غ���
    virtual double get_time() const = 0;

};