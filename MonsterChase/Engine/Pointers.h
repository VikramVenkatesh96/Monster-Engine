#pragma once
#include <cstddef>
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
class WeakPtr;

template <class T>
class SmartPtr
{
	friend WeakPtr<T>;

	template <class U>
	friend class SmartPtr;
public:
	
	SmartPtr()
	{}

	explicit SmartPtr(T* i_object) :
		object(i_object),
		count((i_object) ? new RefCount(1, 0) : nullptr)
	{
	}

	explicit SmartPtr(WeakPtr<T>& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		(count->smartPtr)++;
	}

	template<class U>
	SmartPtr(const SmartPtr<U>& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		(count->smartPtr)++;
	}

	SmartPtr(const SmartPtr& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		(count->smartPtr)++;
	}

	SmartPtr& operator=(const SmartPtr& i_other)
	{
		if (this != &i_other)
		{
			Release();
			object = i_other.object;
			count = i_other.count;
			(count->smartPtr)++;
		}

		return *this;
	}

	template <class U>
	SmartPtr<T> Cast(const SmartPtr<U>& i_other)
	{
		if (dynamic_cast<T*>(i_other.object))
		{
			return SmartPtr<T>(dynamic_cast<T*>(i_other.object));
		}
		else
		{
			return SmartPtr<T>(nullptr);
		}
	}
	
	bool operator==(SmartPtr<T> i_other)
	{
		return (object == i_other.object);
	}

	SmartPtr& operator=(std::nullptr_t i_nullptr)
	{
		Release();
		return *this;
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
		if (count)
		{
			if (--(count->smartPtr) == 0)
			{
				delete object;
			}
		}
	}

private:
	T* object;
	RefCount* count;
};


template <class T>
class WeakPtr
{
	template <class T>
	friend class SmartPtr;
public:
	WeakPtr(SmartPtr<T>& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		(count->weakPtr)++;
	}

	WeakPtr(WeakPtr& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		(count->weakPtr)++;
	}

	WeakPtr& operator=(WeakPtr& i_other)
	{
		if (this != &i_other)
		{
			Release();
			object = i_other.object;
			count = i_other.count;
			(count->weakPtr)++;
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
		if (count)
		{
			if (--(count->weakPtr) == 0)
			{
				delete count;
			}
		}
	}

private:
	T* object;
	RefCount* count;
};