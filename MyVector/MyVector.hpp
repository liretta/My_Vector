#pragma once
#include <utility>
#include <stdexcept>

template <typename T>
class MyVector
{
private:
	T* m_pv;
	int m_size;
	int m_cur_last_index;
	void allocate_new_memory()
	{
		switch (m_size)
		{
		case 0:
			{
				T* buff = new T[m_size + 1];
				delete[] m_pv;
				m_pv = buff;
				m_size += 1;
			}
			break;
		case 1:
			{
				T*buff = new T[m_size +1];
				buff[0] = std::move(m_pv[0]); //if object T has move-constructor, object will move
				delete[] m_pv;
				m_pv = buff;
				m_size += 1;
			}
			break;
		default:
			{
			int new_size = m_size * 2;
				T*buff = new T[new_size];
				for(auto i = 0; i<m_size; ++i)
				{
					buff[i] = std::move(m_pv[i]);
				}
				
				delete[] m_pv;
				m_pv = nullptr;
				
				m_pv = buff;
				m_size *= 2;
			}
			break;
		}
	};
	
public:
	explicit MyVector(const int size=0) : m_pv(nullptr), m_size(size), m_cur_last_index(0)
	{
		if (m_size <= 0)
			m_size = 0;
		else
		{
			m_pv = new T[m_size];
		}
	};

	MyVector(const int size, const T default_value): m_pv(nullptr), m_size(size), m_cur_last_index(size)
	{
		m_pv = new T[size];
		for(auto i = 0; i<m_size; ++i)
		{
			m_pv[i] = default_value;
		}
	};

	~MyVector()
	{
		if(m_pv!=nullptr)
		{
			delete[] m_pv;
			m_size = 0;
			m_cur_last_index = 0;
		}
	}

	//copy-constructor
	MyVector(MyVector const &other_vector) :m_pv(nullptr), m_size(other_vector.m_size), m_cur_last_index(other_vector.m_cur_last_index)
	{
		if (other_vector.m_pv != nullptr)
		{
			m_pv = new T[m_cur_last_index];
			std::copy(other_vector.m_pv, other_vector.m_pv + m_cur_last_index, m_pv);
		}
	};
	
	//copy-move constructor
	MyVector(MyVector &&other_vector) noexcept
	{
		m_pv = nullptr;
		if(other_vector.m_pv == nullptr)
		{
			m_size = 0;
			m_cur_last_index = 0;
		}
		else
		{
			m_size = other_vector.m_size;
			m_cur_last_index = other_vector.m_cur_last_index;
			delete[] m_pv;
			m_pv = other_vector.m_pv;
			other_vector.m_pv = nullptr;
			other_vector.m_size = 0;
			other_vector.m_cur_last_index = 0;
		}
	};

	MyVector& operator=(MyVector const &other_vector)
	{
		if (&other_vector == this)
			return *this;

		m_size = other_vector.m_size;
		m_cur_last_index = other_vector.m_cur_last_index;
		delete[] m_pv;
		m_pv = new T[m_cur_last_index];
		std::copy(other_vector.m_pv, other_vector.m_pv + m_cur_last_index, m_pv);
		return *this;
	};

	MyVector& operator=(MyVector &&other_vector) noexcept
	{
		if(&other_vector == this)
		{
			return *this;
		}
		m_size = other_vector.m_size;
		m_cur_last_index = other_vector.m_cur_last_index;
		if (m_pv != nullptr)
		{
			delete[] m_pv;
		}
		m_pv = other_vector.m_pv;
		other_vector.m_pv = nullptr;
		other_vector.m_size = 0;
		other_vector.m_cur_last_index = 0;
		return *this;
	};

	T& operator [](int index) const
	{
		if (index < 0 || index >= m_cur_last_index)
		{
			throw std::out_of_range("Index is out of range");
		}
		else
		{
			return m_pv[index];
		}
	};

	T& begin() const
	{
		if(m_cur_last_index == 0)
		{
			throw std::out_of_range("The vector is empty");
		}
		else
		{
			return m_pv[0];
		}
	};

	T& end() const //return ref on last element
	{
		if(m_cur_last_index == 0)
		{
			throw std::out_of_range("The vector is empty");
		}
		else
		{
			return m_pv[m_cur_last_index];
		}
	};

	bool empty() const
	{
		return(m_cur_last_index == 0);
	};

	int size() const
	{
		return m_cur_last_index;
	};

	int capacity() const
	{
		return m_size;
	}

	void clear()
	{
		if (m_pv != nullptr)
		{
			delete[] m_pv;
			m_pv = nullptr;
			m_size = 0;
			m_cur_last_index = 0;
		}
	};

	void erase(const int index)
	{
		if(index < 0 || index >=m_size)
		{
			throw std::out_of_range("Index is out of range");
		}
		else
		{
			T* buff = new T[m_cur_last_index];
			for (auto i =0; i<index; ++i)
			{
				buff[i] = std::move(m_pv[i]);
			}

			for(auto i = index; i< m_cur_last_index-1; ++i)
			{
				buff[i] = std::move(m_pv[i + 1]);
			}

			delete [] m_pv;
			m_pv = buff;
			--m_cur_last_index;
		}
	};

	void push_back(T const &new_value)
	{
		if(m_cur_last_index == m_size)
		{
			allocate_new_memory();
		}
		m_pv[m_cur_last_index++] = new_value;	
	};

	void push_back(T &&new_value)
	{
		if(m_cur_last_index == m_size)
		{
			allocate_new_memory();
		}
		m_pv[m_cur_last_index++] = std::move(new_value);
	};

	bool operator ==(MyVector const &other_vector) const
	{
		if(m_cur_last_index != other_vector.m_cur_last_index)
		{
			return false;
		}

		bool result = true;
		for(auto i =0; i<m_cur_last_index; ++i)
		{
			if(m_pv[i] != other_vector.m_pv[i])
			{
				result = false;
			}
		}
		return result;
	};

	bool operator!=(MyVector const &other_vector) const
	{
		return !(this == other_vector);
	};
};