#ifndef _MY_BIJECTION_H
#define _MY_BIJECTION_H

class Bijection
{
protected:
	int *array;
	int *index_in_array;
	int array_size;
	int array_capacity;
public:
	Bijection()
	{
		array = NULL;
		index_in_array = NULL;
		array_size = 0;
		array_capacity = 0;
	}
	Bijection(int sz)
	{
		array_capacity = sz + 2;
		array = new int[array_capacity];
		index_in_array = new int[array_capacity];
		memset(array, 0, sizeof(int) * (array_capacity));
		memset(index_in_array, 0, sizeof(int) * (array_capacity));
		array_size = 0;
	}
	~Bijection()
	{
		delete[] array;
		array = NULL;
		delete[] index_in_array;
		index_in_array = NULL;
		array_size = 0;
		array_capacity = 0;
	}
	void clear()
	{
		//memset(array, 0, sizeof(int) * array_capacity);
		//memset(index_in_array, 0, sizeof(int) * array_capacity);	
		for(int i = 1; i <= array_size; i++)
		{
			index_in_array[array[i]] = 0;
		}
		array_size = 0;	
	}
	void insert_element(int e)
	{
		array[++array_size] = e;
		index_in_array[e] = array_size;
	}
	void delete_element(int e)
	{
		int last_e = array[array_size--];
		int e_pos = index_in_array[e];
		array[e_pos] = last_e;
		index_in_array[last_e] = e_pos;
		index_in_array[e] = 0;
	}
	int index_of(int e)
	{
		return index_in_array[e];
	}
	int element_in(int e)
	{
		return index_in_array[e];
	}
	int size()
	{
		return array_size;
	}
	int at(int i)
	{
		return array[i];
	}
	int begin()
	{
		return 1;
	}
	int end()
	{
		return array_size + 1;
	}
	int rand_element()
	{
		return array[rand() % array_size + 1];
	}
};
#endif
