#pragma once

#pragma warning( disable : 4067)

constexpr auto IS_BUAS_BUILD = true;

//Somehow I can't #if IS_BUAS_BUILD the #include <ostream> please bear with me here, it's for debugging.
#include <ostream>

template <class T>
class List
{
public:
	List()
		: count_(0),
		  capacity_(5)
	{
		array_ = new T[capacity_];
	}

	List(const unsigned int capacity)
		: count_(0),
		  capacity_(capacity)
	{
		array_ = new T[capacity_];
	}

	List(const List<T>& other)
		: count_(other.count_),
		  capacity_(other.capacity_)
	{
		array_ = new T[capacity_];

		for (auto i = 0; i < this->Count(); i++)
		{
			this->array_[i] = other.array_[i];
		}
	}

	List(const unsigned int instances, T default_value) // = nullptr)
		: count_(instances),
		  capacity_(count_ + 5)
	{
		array_ = new T[capacity_];

		for (auto i = 0; i < Count(); i++)
		{
			this->array_[i] = default_value;
		}
	}

	~List()
	{
		delete[] array_;
	}

	void Add(T value)
	{
		if (count_ >= capacity_)
		{
			capacity_ = capacity_ * 2; //(int)(capacity * 1.25f); //Increases size by 25%
			T* new_array = new T[capacity_]; //create new memory reservation

			for (auto i = 0; i < count_; i++)
			{
				new_array[i] = array_[i];
			}

			delete[] array_;
			array_ = new_array;
		}

		array_[count_] = value;
		count_++;
	}

	//AddAt(int index);
	void RemoveAt(const unsigned int index)
	{
		if (index > Count() - 1)
			//if (index >= Count())
		{
			//#if !IS_BUAS_BUILD

			throw std::out_of_range("List<T> operator []: index is out of range");

			//#else

			printf("Index out of range!"); //no STL for exceptions, why must you be so cruel?

			//#endif
		}

		for (int i = index; i <= Count(); i++)
		{
			array_[i] = array_[i + 1];
		}
		count_--;
	}

	void StartForEach()
	{
		for (size_t i = 0; i < Count(); i++)
		{
			array_[i]->Start();
		}
	}

	void UpdateForEach()
	{
		for (size_t i = 0; i < Count(); i++)
		{
			array_[i]->Update();
		}
	}

	void StopForEach()
	{
		for (size_t i = 0; i < Count(); i++)
		{
			array_[i]->Stop();
		}
	}

	unsigned int Count() const
	{
		return count_;
	}

	unsigned int Capacity() const
	{
		return capacity_;
	}

	bool IsEmpty() const
	{
		return count_ == 0;
	}

	T& First()
	{
		return array_[0];
	}

	T& Last()
	{
		return array_[Count() - 1];
	}

	bool operator ==(const List<T>& other) const
	{
		if (this->Count() != other.Count()) return false;
		//If the Lists are of different size, they're not the same.

		for (auto i = 0; i < Count(); i++)
		{
			if (this->array_[i] != other.array_[i])
			{
				return false; //If any element of the Lists differ, they're not the same.
			}
		}

		return true;
	}

	bool operator !=(const List<T>& other) const
	{
		return !(other == *this);
	}

	List& operator =(const List<T>& other)
	{
		if (other.Count() > Count())
		{
			delete[] array_; //The entire array will be overriden anyways.

			this->capacity_ = other.Count() + 5;
			this->array_ = new T[capacity_]();
		}

		for (int i = 0; i < other.Count(); i++)
		{
			this->array_[i] = other.array_[i];
		}

		this->count_ = other.count_;

		return *this;
	}

	T operator [](const unsigned int index)
	{
		if (index > (Count() - 1))
		{
			throw std::out_of_range("List<T> operator []: index is out of range");
		}
		return array_[index];
	}

private:
	T* array_;
	unsigned int count_;
	unsigned int capacity_;
};
