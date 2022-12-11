#include <cstddef>

template <typename T>
class Array
{
	// Список операций:
	//
public:
	explicit Array(size_t size, const T& value = T()) : size_(size)
	{
		data_ = static_cast<T*>(operator new[](size_ * sizeof(T)));
		for (size_t i = 0; i != size_; ++i) 
		{ 
			new (data_ + i) T(value);
		}
	}
	//   конструктор класса, который создает
	//   Array размера size, заполненный значениями
	//   value типа T. Если у класса нет конструктора
	//   по умолчанию, то второй аргумент этого конструктора
	//   обязателен.
	//
	Array() : size_(0), data_(NULL)
	{}
	//   конструктор класса, который можно вызвать
	//   без параметров. Должен создавать пустой
	//   Array.
	Array(const Array&  other)
	{
		this->~Array();
		this->size_ = other.size_;
		this->data_ = static_cast<T*>(operator new[](size_ * sizeof(T)));
		for (size_t i = 0; i != size_; ++i)
		{
			new (data_ + i) T(other.data_[i]);
		}
	}
	//   конструктор копирования, который создает
	//   копию параметра. Для типа T оператор
	//   присваивания не определен.
	//
	~Array()
	{
		for (size_t i = 0; i != size_; ++i)
		{
			data_[i].~T();
		}
		operator delete[] (data_);
	}
	//   деструктор, если он вам необходим.
	//

	//   оператор присваивания.
	//
	size_t size() const
	{
		return size_;
	}
	//   возвращает размер массива (количество
	//                              элементов).
	//
	T& operator[](size_t sz)
	{
		return data_[sz];
	}
	const T& operator[](size_t sz) const
	{
		return data_[sz];
	}
	//   две версии оператора доступа по индексу.
	Array& operator=(const Array& other)
	{
		if (this != &other)
		{
			
			this->~Array();
			this->size_ = other.size_;
			this->data_ = static_cast<T*>(operator new[](size_ * sizeof(T)));
			for (size_t i = 0; i != size_; ++i)
			{
				new (data_+i) T(other.data_[i]);
			}

		}

		return *this;
	}
public:
	size_t size_;
	T* data_;
};

template <typename U, typename Comp>
U minimum(Array<U> & arr, Comp func)
{
	U min_val = arr[0];
	for (size_t i = 1; i < arr.size(); ++i)
	{	
		if (func(arr[i], min_val))
		{
			min_val = arr[i];
		}
	}
	return min_val;
}

unt main()
{
	bool less(int a, int b) { return a < b; }
	struct Greater { bool operator()(int a, int b) const { return b < a; } };
	Array<int> ints(3);
	ints[0] = 10;
	ints[1] = 2;
	ints[2] = 15;
	int min = minimum(ints, less); // min should be 2
	int max = minimum(ints, Greater()); //  max should be 15
}