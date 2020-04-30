#pragma once

struct RefCount
{
	int smartPtr;
	int weakPtr;
	RefCount(int i_smartPtr, int i_weakPtr)
		:smartPtr(i_smartPtr),
		 weakPtr(i_weakPtr)
	{
	}
};

template <class T>
class SmartPtr
{
public:
	explicit SmartPtr(T* i_object):
		object(i_object),
		count(new RefCount(1,0))
	{
	}

	explicit SmartPtr(WeakPtr& i_other):
		object(i_other.object),
		count(i_other.count)
	{
		*(count->smartPtr)++;
	}
	
	SmartPtr(SmartPtr& i_other):
		object(i_other.object),
		count(i_other.count)
	{
		(*count->smartPtr)++;
	}

	SmartPtr& operator=(SmartPtr& i_other)
	{
		if (this != &i_other)
		{
			Release();
			object = i_other.object;
			count = i_other.count;
			(*count->smartPtr)++;
		}
	}
	
	void operator=(std::nullptr_t i_nullptr)
	{
		Release();
	}

	T* operator->()
	{
		return object;
	}

	T& operator*()
	{
		return *(object);
	}

	operator bool()
	{
		return object != nullptr;
	}
	 
	~SmartPtr()
	{
		Release();
	}

private:
	void Release()
	{
		if (--(*count->smartPtr) == 0)
		{
			delete object;
		}
	}

private:
	T* object;
	RefCount* count;
};

template <class T>
class WeakPtr
{
public:
	WeakPtr(SmartPtr& i_other):
		object(i_other.object),
		count(i_other.count)
	{
		*(count->weakPtr)++;
	}

	WeakPtr(WeakPtr& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		(*count->weakPtr)++;
	}

	WeakPtr& operator=(WeakPtr& i_other)
	{
		if (this != &i_other)
		{
			Release();
			object = i_other.object;
			count = i_other.count;
			(*count->weakPtr)++;
		}
	}
	SmartPtr<T> Acquire()
	{
		return SmartPtr<T>(*this);
	}
	operator bool()
	{
		return count->smartPtr > 0;
	}

	void operator=(std::nullptr_t i_nullptr)
	{
		Release();
	}


	~WeakPtr()
	{
		Release();
	}

private:
	void Release()
	{
		if (--(*count->weakPtr) == 0)
		{
			delete count;
		}
	}

private:
	T* object;
	RefCount* count;
};
