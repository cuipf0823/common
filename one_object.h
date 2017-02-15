/*
	ʵ�ּ������������ɶ��������
*/
#ifndef ONE_OBJECT_H
#define ONE_OBJECT_H

namespace one_object
{

//����1�� ˽�л����졢�����������������ṩΨһ�Ĵ����ӿ�
class Printer
{
public:
	void Print(){}
private:
	Printer(){}
	~Printer(){}
	Printer(const Printer&){}
public:
	friend Printer& PrinterInstance();
};

Printer& PrinterInstance()
{
	static Printer p;
	return p;
}

//����2���ͷ���1��ȣ����ṩ�Ĵ����ӿڷ�װ������ڲ�
class PrinterIn
{
public:
	void Print(){}
	static PrinterIn& PrinterInstance();
private:
	PrinterIn(){}
	~PrinterIn(){}
	PrinterIn(const PrinterIn&){}
};

PrinterIn& PrinterIn::PrinterInstance()
{
	static PrinterIn p;
	return p;
}

//����3 �Աȷ���1 ���ǰѴ����ӿ�
namespace PrintingStuff
{
	class Printer
	{
	public:
		void Print(){}
	private:
		Printer(){}
		~Printer(){}
		Printer(const Printer&){}
	public:
		friend Printer& PrinterInstance();
	};

	Printer& PrinterInstance()
	{
		static Printer p;
		return p;
	}
}

//����4�����ƴ�������ĸ���������ֱ���׳��쳣
class PrinterToo
{
public:
	Printer()
	{
		if (num_objects_ >= 1)
		{
			throw TooManyObjects();
		}
		++num_objects_;
	}
	~Printer()
	{
		--num_objects_;
	}

	void Print(){}
	class TooManyObjects{};
private:
	Printer(const Printer&){}
	static size_t num_objects_;

};

size_t PrinterToo::num_objects_ = 0;

}




#endif


