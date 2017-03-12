/*
*  һЩʵ�õ��༯��
*/
#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H

#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <initializer_list>
#include <boost/noncopyable.hpp>

//�߳���
class MutexLock : boost::noncopyable
{
public:
	MutexLock()
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~MutexLock()
	{
		pthread_mutex_destroy(&mutex_);
	}
	void Lock()
	{
		pthread_mutex_lock(&mutex_);

	}
	void Unlock()
	{
		pthread_mutex_lock(&mutex_);
	}

	pthread_mutex_t* GetThreadMutex()
	{
		return &mutex_;
	}

private:
	pthread_mutex_t mutex_;
};

class MutexLockGuard : boost::noncopyable
{
public:
	explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex)
	{
		mutex_.Lock();
	}
	~MutexLockGuard()
	{
		mutex_.Unlock();
	}
private:
	MutexLock& mutex_; 
};

/*
* ��������
*/
class Condition : boost::noncopyable
{
public:
	explicit Condition(MutexLock& mutex) :mutex_(mutex)
	{
		pthread_cond_init(&pcond_, NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&pcond_);
	}
	void Wait()
	{
		pthread_cond_wait(&pcond_, mutex_.GetThreadMutex());
	}
	void Notify()
	{
		pthread_cond_signal(&pcond_);
	}
	void NotifyAll()
	{
		pthread_cond_broadcast(&pcond_);
	}

private:
	pthread_cond_t pcond_;
	MutexLock& mutex_;
};

//ʵ���Լ���string��
class String
{
public:
	//string��û�����Ʋ��ܱ��̳У��������ʹ��������
	~String();
	//���캯��
	String();
	String(const char* s);
	String(const char* s, size_t n);
	//�������캯��
	String(const String& str);
	//��ֵ���캯��
	String& operator=(const String& rhs);

	//���������
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	String& operator+=(const String& rhs);

	friend std::istream& operator>>(std::istream& is, String& str);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
public:
	const char* c_str() const
	{
		return data_;
	}

	size_t size() const
	{
		return size_;
	}
private:
	char* data_;
	size_t size_;
};

//���캯�� ���ڳ�ʼ��Ϊ�յĹ��캯��������һ��Ԫ�أ����溯���оͲ���Ҫ��null
String::String() :data_(new char[1]), size_(0)
{
	assert(data_ != nullptr);
	*data_ = '\0';
}

//��������
String::~String()
{
	delete [] data_;
	data_ = nullptr;
	size_ = 0;
}

//���캯��
String::String(const char* s)
{
	if (s != nullptr)
	{
		size_ = strlen(s);
		data_ = new char[strlen(s) + 1];
		assert(data_ != nullptr);
		//strcpy ���Ƶ��ַ�������'\0'
		strcpy(data_, s);
	}
	else
	{
		data_ = new char[1];
		assert(data_ != nullptr);
		*data_ = '\0';
		size_ = 0;
	}
}

//���캯��
String::String(const char* s, size_t n)
{
	if (n > 0)
	{
		data_ = new char[n + 1];
		assert(data_ != nullptr);
		size_ = n;
		strcpy(data_, s);
	}
	else
	{
		data_ = new char[1];
		assert(data_ != nullptr);
		*data_ = '\0';
		size_ = 0;
	}
}

//�������캯��
String::String(const String& str)
{
	if (str.size() > 0)
	{
		data_ = new char[str.size() + 1];
		size_ = str.size();
		assert(data_ != nullptr);
		strcpy(data_, str.c_str());
	}
	else
	{
		data_ = new char[1];
		assert(data_ != nullptr);
		*data_ = '\0';
		size_ = 0;
	}

}

/*
* ��ֵ�����
* 1. ����ֵΪ���͵����ã�ֻ�з������͵����òſ������������ĸ�ֵ
* 2. ����Ϊ������������
* 3. �Ƿ��ͷ��Լ��ڴ棻
* 4. �Ƿ��жϴ��ݲ���������ıȽ�
*/
String& String::operator=(const String& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	delete[] data_;
	data_ = nullptr;
	size_ = 0;
	data_ = new char[rhs.size() + 1];
	assert(data_ != nullptr);
	size_ = rhs.size();
	strcpy(data_, rhs.c_str());
	return *this;
}


/*
* ������index��Ч�ԣ�index��Ч�������ⲿ��֤
*/
char& String::operator[](size_t index)
{
	assert(index < size_ - 1);
    return data_[index];
}

//����������øú���
const char& String::operator[](size_t index) const
{
	assert(index < size_ - 1);
	return data_[index];
}

String& String::operator+=(const String& rhs)
{
	if (rhs.size() > 0)
	{
		size_t length = size_ + rhs.size();
		char* temp = new char[length + 1];
		assert(temp != nullptr);
		strcpy(temp, data_);
		//����ʹ��strcat
		strcpy(temp + size_, rhs.c_str());

		delete [] data_;
		data_ = temp;
		size_ = length;
	}
	return *this;
}


/************************************************************************/
//��������Ϊ��ĳ�Ա����������˵��Ӧ���Ƿǳ�Ա����

/*
* ���������
*/
String operator+(const String& lhs, const String &rhs)
{
	size_t length = lhs.size() + rhs.size();
	char* temp = new char[length + 1];
	assert(temp != nullptr);
	strcpy(temp, lhs.c_str());
	//����ʹ��strcat
	strcpy(temp + lhs.size(), rhs.c_str());
	return String(temp, length);
}

/*
* ������������
* 1. �β�һ��Ҫ����д�����ݣ�����Ϊ�����޷�����һ��ostream��������Ϊ�ǳ������ã�
* 2. �������������ļ��ٸ�ʽ��������
*/
std::ostream& operator <<(std::ostream& os, const String& str)
{
	os << str.data_;
	return os;
}

/*
*  �������������
*/
std::istream& operator>>(std::istream& is, String& str)
{
	char temp[100] = { 0 };
	is >> temp;
	if (is)
	{
		str.data_ = new char[strlen(temp) + 1];
		assert(str.data_ != nullptr);
		strcpy(str.data_, temp);
		str.size_ = strlen(temp);
	}
	else
	{
		//����ʧ�ܸ�ֵΪ��
		str = String();
	}
	return is;
}

//��ϵ���������
bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}
	return strcmp(lhs.c_str(), rhs.c_str()) == 0 ? false : true;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}


/*
 * ���������Ҫ���ڲ����������ֲ�����������
 */

class DInt
{
public:
	DInt(int i):imem_(i)
	{

	}
	//prefix increment �����Ҫ��ֹ++++i������Ϊ�ͷ���const DInt& ����
	DInt& operator++()
	{
		++(this->imem_);
		return *this;
	}

    //prefix decrement
	DInt& operator--()
	{
		--(this->imem_);
		return *this;
	}

	//postfix increment �����Ҫ��ֹi++++������Ϊ�ͷ���const DInt ����
    DInt operator++(int)
    {
        DInt temp = *this;
        ++(*this);
        return temp;
    }

    //postfix decrement
    DInt operator--(int)
    {
        DInt temp = *this;
        --(*this);
        return temp;
    }

    //dereference
    int& operator*() const
    {
        return (int&)(imem_);
    }

    int* operator->() const
    {
        return & this->operator*();
    }

    const int& imem() const
    {
        return imem_;
    }
    //operator ()
    void operator()()
    {
        std::cout << imem_ << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, DInt i);
private:
	int imem_;
};

std::ostream& operator<<(std::ostream& os, DInt i)
{
    os << *i << std::endl;
    return os;
}

/*
std::ostream& operator<<(std::ostream& os, DInt& i)
{
    os << *i << std::endl;
    return os;
}
*/

namespace utility_test
{
	void foo(String x)
	{
	}

	void bar(const String& x)
	{
	}

	String baz()
	{
		String ret("world");
		return ret;
	}
	void TestUtility()
	{
		String s0;
		String s1("hello");
		String s2(s0);
		String s3 = s1;	 //�������캯��
		s2 = s1;		 // ��ֵ���캯��

		foo(s1);
		bar(s1);
		foo("temporary");
		bar("temporary");
		String s4 = baz();
		if (s1 == s2)	
		{
		}
		std::cout << s1 + s2 + s3 << std::endl;
		s0 += s1;
		std::cout << s1 << std::endl;
		std::vector<String> svec;
		svec.push_back(s0);
		svec.push_back(s1);
		svec.push_back(baz());
		svec.push_back("good job");
		std::string str1("123456");
		std::cout << str1.size() << std::endl;
		std::string str2;
		std::cout << str2.size() << std::endl;
		int a = 6;
		int b = 10;
		std::cout << a++ + b << std::endl;
		std::cout << a << std::endl;


        DInt in(10);
        DInt* pin = &in;
        std::cout << in++++ << std::endl;
        std::cout << pin->imem() << std::endl;

        in();
        DInt(10000)();
        int i = 100;
        std::cout << ++i << std::endl;

 	}
}



#endif


