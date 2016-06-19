#include<iostream>

using namespace std;

template <typename T>//шаблонный класс вектор
class Vector{
	T * array;
	int size;
	int capacity;
public:
typedef T* iterator;
	iterator begin() { return array; }
	iterator end() { return array + size; }

	Vector() : capacity(0), size(0) {//конструктор по умолчанию
		array = (T*)(operator new (0));
	}
	Vector(int size) : Vector(size, T())// онструктор, позвол€ющий задаватьразмерность вектора, но не €вл€ющийс€ конструктором преобразовани€
                                 
	{}
	Vector(int _size, const T& value)//конструктор копировани€ из одного вектора в другой 
	{
		sizeA = _size;
		capacity = size;
		array = (T*)(operator new (sizeof(T)* capacity));
		for (int i = 0; i < size; i++){
			new (array + i)T(value);
		}
	};
	Vector<T> & pushBack(const T& value){
		if (size == capacity)
			reserve();

		array[size++] = value;
		return *this;
	}
	unsigned int _size() const {
		return (unsigned int)size;
	}
	unsigned int _capaciy() const {
		return (unsigned int)capaciy;
	}
	Vector<T> & popBack()
	{
		(array + Чsize)->~T();
		return *this;
	}
	Vector<T> & clear(){
		for (int i = 0; i < size; i++)
			(array + i)->~T();

		delete(array);

		array = (T*)(operator new (0));
		size = capacity = 0;
		return *this;
	}
	~Vector(){
		delete (array);
	}
	T& operator[] (int i){
		return array[i];
	}
	bool empty() const{
		return size == 0;
	}

void erase(iterator it){
		if (it < begin() || end() <= it)
			throw nullptr;
		for (int i = (int)(it - array); i < size; i++)
			array[i] = array[i + 1];
		popBack();
	}

void erase(iterator it, int n)
{
	if (n == 1)
	{
		erase(it);
		return;
	}
	int i = 0;
	for (Vector<T>::iterator iterator1 = it; iterator1 != it; iterator1++, i++);
	for (i; i < n; i++);
	erase(it, array + i);
}

void erase(iterator it_begin, iterator it_end)
{
	if (it_begin < begin() || end() <= it_begin)
		throw nullptr;

	if (it_end < begin() || end() <= it_end)
		throw nullptr;

	int i = (int)(it_begin - array),
		j = (int)(it_end - array);

	if (i == j)
	{
		erase(it_begin);
		return;
	}
	j++;

	while (j < size)
	{
		*(array + i) = *(array + j);
		i++;
		j++;
	}

	int _size = i;
	for (i++; i < size; i++)
	{
		(array + i)->~T();
	}

	sizeArray = _size;
}

void insert(const iterator it, T value)
{
	if (it < begin() || end() <= it)
		throw nullptr;

	Vector<T>::iterator it1 = it;
	if (size == capacity)
	{
		int i = (int)(it1 - array);
		reserve();
		it1 = array + i;
	}

	new (end())T();

	for (Vector<T>::iterator i = end(); i != it1; i--)
		*i = *(i - 1);

	*it1 = value;
	size++;
	return;
}

void reserve()
{
	capacity == 0 ? capacity = 2 : capacity *= 2;
	T *newArray = (T*)(operator new (sizeof(T)* capacity));

	for (int i = 0; i < size; i++)
		new(newArray + i)T(array[i]);

	for (int i = 0; i < size; i++){
		array[i].~T();
	}
	array = newArray;
}

void swap(Vector<T>& vector)
{
	swap(array, vector.array);
	swap(size, vector.size);
	swap(capacity, vector.capacity);
}


};
int main(){

}
