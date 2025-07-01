#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<memory>
using namespace std;

template<class target_itor,class source_itor>
target_itor copy_(source_itor first, source_itor last, target_itor dest)
{
	while (first != last)
	{
		new (dest) typename std::iterator_traits<OutputIt>::value_type(*first);
		//*res = *first;
		dest++; first++;
	}
	return dest;
}

template<typename T>
class Vector_Queue
{
private:
	//vector<T> Queue;
	T* data = nullptr;
	size_t capacity=1;
	int head = 0;
	int tail = 0;
	int count = 0;
	void resize()
	{
		size_t new_capacity = 2 * capacity;
		T* new_data=static_cast<T*>(operator new[](new_capacity * sizeof(T)));
		if (!empty())
		{
			if (head < tail)
			{
				copy_(data + head, data + tail, new_data);

			}
			else
			{
				T* intern = copy_(data + head, data + capacity, intern);
				copy_(data,data+tail,intern+capacity-head)
			}
			
		}
		for (int i = 0; i < count; i++)
		{
			data[(i + head) % capacity].~T();

		}
		operator delete[](data);
		data = new_data;
		capacity = new_capacity;
		head = 0;
		tail = count;


	}
	
public:
	Vector_Queue()
	{
		data = static_cast<T*>(operator new[](capacity * sizeof(T)));
	}
	~Vector_Queue()
	{
		for (int i = 0; i < count; i++)
		{
			data[(i + head) % capacity].~T();

		}
		operator delete[](data);
	}
	void pop()
	{
		if(empty)
		{
			throw out_of_range("queue is empty");
		}
		data[head].~T();
		head=(head+1)%capacity;
		--count;
	}
	void push(T& new_in)
	{
		if(count==capacity)
		{
			resize();
			data[tail+1]=new_in;
			count++;
		}
		else
		{
			data[tail+1]=new_in;
			count++;
		}
		

	}
	T& get_front()
	{
		if(empty)
		{
			throw out_of_range("queue is empty");
		}
		return data[head];
	}
	T& get_end()
	{
		if(empty)
		{
			throw out_of_range("queue is empty");
		}
		return data[tail];
	}
	bool empty()
	{
		return count==0;
	}
	bool full()
	{
		return count==capacity;
	}
	size_t size()
	{
		return count;
	}
};
