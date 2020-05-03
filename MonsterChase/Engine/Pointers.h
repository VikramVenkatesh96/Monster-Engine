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
	{
	}

	explicit SmartPtr(T* i_object) :
		object(i_object),
		count((i_object) ? new RefCount(1, 0) : nullptr)
	{
	}

	explicit SmartPtr(WeakPtr<T>& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		if (count)
		{
			(count->smartPtr)++;
		}
	}

	template<class U>
	SmartPtr(const SmartPtr<U>& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		if (count)
		{
			(count->smartPtr)++;
		}
	}

	template<class U>
	SmartPtr(const SmartPtr<U>& i_other, T* i_ptr)
	{
		if (i_other.count)
		{
			(i_other.count->smartPtr)++;
		}
		object = i_ptr;
		count = i_other.count;
	}

	SmartPtr(const SmartPtr& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		if (count)
		{
			(count->smartPtr)++;
		}
	}

	SmartPtr& operator=(const SmartPtr& i_other)
	{
		if (this != &i_other)
		{
			Release();
			object = i_other.object;
			count = i_other.count;
			if (count)
			{
				(count->smartPtr)++;
			}
		}
		return *this;
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
	
	T* Get() const
	{
		return object;
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
		if (count)
		{
			(count->weakPtr)++;
		}
	}

	WeakPtr(WeakPtr& i_other) :
		object(i_other.object),
		count(i_other.count)
	{
		if (count)
		{
			(count->weakPtr)++;
		}
	}

	WeakPtr& operator=(WeakPtr& i_other)
	{
		if (this != &i_other)
		{
			Release();
			object = i_other.object;
			count = i_other.count;
			if (count)
			{
				(count->weakPtr)++;
			}
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

namespace Pointers
{
	template <class T, class U>
	SmartPtr<T> Cast(const SmartPtr<U>& i_original)
	{
		if (auto x = dynamic_cast<T*>(i_original.Get()))
		{
			SmartPtr<T> obj(i_original, x);
			return obj;
		}

		return SmartPtr<T>(nullptr);
	}
}