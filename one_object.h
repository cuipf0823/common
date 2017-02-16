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

//����4�����ƴ�������ĸ���������ֱ���׳��쳣 �÷�������ȡ
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


//����5�����ڷ���4�̳У����춼���ܲ������󣬿��ܺ��������ġ�������Ŀ����һ�� �Ż�����
class PrinterMake
{
public:
	class TooManyObjects(){};
	//α���캯��
	static PrinterMake* MakePrinter();
	static PrinterMake* MakePrinter(const PrinterMake& rhs);
private:
	PrinterMake()
	{
		if (num_objects_ >= max_objects_)
		{
			throw TooManyObjects();
		}
	};
	~PrinterMake(){};
	PrinterMake(const PrinterMake& rhs)
	{
		if (num_objects_ >= max_objects_)
		{
			throw TooManyObjects();
		}
	}
	static size_t num_objects_;
	static const size_t max_objects_ = 10;
};

const size_t PrinterMake::max_objects_;
size_t PrinterMake::num_objects_ = 0;

PrinterMake* PrinterMake::MakePrinter()
{
	return new PrinterMake();
}

PrinterMake* PrinterMake::MakePrinter(const PrinterMake& rhs)
{
	return new PrinterMake(rhs);
}

//����6����װ����ʵ���������ܵĻ��ࣻ
template<class BeingCounted>
class Counted
{
public:
	class TooManyObjects{};
	static int ObjectCount()
	{ 
		return num_objects_; 
	}
protected:
	Counted();
	virtual ~Counted()
	{
		--num_objects_;
	}
	Counted(const Counted& rhs);
private:
	static int num_objects_;
	static const size_t max_objects_;
	void init();				      //���⹹�캯����
};
template<class BeingCounted>
Counted<BeingCounted>::Counted()
{
	init();
}
template<class BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted>&)
{
	init();
}
template<class BeingCounted>
void Counted<BeingCounted>::init()
{
	if (num_objects_ >= max_objects_)
	{
		throw TooManyObjects();
	}
	++num_objects_;
}

//ֱ�Ӽ̳м�����ʵ����������
class Printer : private Counted < Printer >
{
public:
	// α���캯��
	static Printer * makePrinter();
	static Printer * makePrinter(const Printer& rhs);
	~Printer();
	using Counted<Printer>::TooManyObjects;
	using Counted<Printer>::TooManyObjects;
private:
	Printer();
	Printer(const Printer& rhs);
}


#endif


