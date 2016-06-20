#include<iostream>

using namespace std;

template <typename T>//шаблонный класс вектор
class Vector{//класс вектор 
	T * array;//массив может быть любого типа 
	int size;//размер 
	int capacity;//вместимость
public:
	typedef T* iterator;//объявляем итератор именем типа 
	iterator begin() { return array; }//указытель на первый элемент
	iterator end() { return array + size; }//указатель  на воображаемый несуществующий элемент, следующий за последним.

	Vector() : capacity(0), size(0) {//конструктор по умолчанию
		array = (T*)(operator new (0));//выделяет память для массива 
	}
	Vector(int size) : Vector(size, T()){}//Конструктор, позволяющий задавать размерность вектора, но не являющийся конструктором преобразования
	
	Vector(int _size, const T& value)//конструктор копирования из одного вектора в другой 
	{
		size = _size;//задаем размер массива
		capacity = size;//задаем вместимость
		array = (T*)(operator new (sizeof(T)* capacity));//выделяем память для массива, с размером и вместимостью
		for (int i = 0; i < size; i++){
			new (array + i)T(value);//кладем в массив значения
		}
	};
	Vector<T> & pushBack(const T& value){//добавление элементов
		if (size == capacity)
			reserve();//увеличиваем массив

		array[size++] = value;
		return *this;//указатель на текущий вектор 
	}
	unsigned int _size() const {//возвращает размер
		return (unsigned int)size;
	}
	unsigned int _capaciy() const {//возвращает вместимость
		return (unsigned int)capaciy;
	}
	Vector<T> & popBack()//уделение элементов
	{
		(array + —size)->~T();//вызываем диструктор для конкретного элемента
		return *this;
	}
	Vector<T> & clear(){
		for (int i = 0; i < size; i++)
			(array + i)->~T();//удалили элементы

		delete(array);//удалили массив

		array = (T*)(operator new (0));//выделяем пустой массив
		size = capacity = 0;
		return *this;
	}
	~Vector(){//деструктор на удаление массива
		delete (array);
	}
	T& operator[] (int i){//обращение по индексу
		return array[i];
	}
	bool empty() const{//обнуляем размер
		return size == 0;
	}

void erase(iterator it){//удаление одного элементов
		if (it < begin() || end() <= it)
			throw nullptr;//бросает 0
		for (int i = (int)(it - array); i < size; i++)
			array[i] = array[i + 1];//сдвигаем
	}

void erase(iterator it, int n)//удаляем н эелементов
{
	if (n == 1)
	{
		erase(it);//удаление одного элементов
		return;
	}
	int i = 0;
	//for (Vector<T>::iterator iterator1 = it; iterator1 != it; iterator1++, i++);
	for (i; i < n; i++);
	erase(it, array + i);
}

void erase(iterator it_begin, iterator it_end)
{
	if (it_begin < begin() || end() <= it_begin)//итератор должен находится посередине
		throw nullptr;

	if (it_end < begin() || end() <= it_end)
		throw nullptr;

	int i = (int)(it_begin - array);//вычитаем указатели
	int	j = (int)(it_end - array);//вычитаем указатели

	if (i == j)
	{
		erase(it_begin); // удаление одного элементов
		return;
	}
	j++;

	while (j < size)
	{
		*(array + i) = *(array + j);//стираем элементы с двух сторон
		i++;
		j++;
	}
}

void insert(const iterator it, T value)//вставка
{
	if (it < begin() || end() <= it)
		throw nullptr;

	Vector<T>::iterator it1 = it;//новый итератор
	if (size == capacity)
	{
		int i = (int)(it1 - array);//вычитаем указатели
		reserve();//добавляем памяти
		it1 = array + i;
	}

	new (end())T();//новый итератор

	for (Vector<T>::iterator i = end(); i != it1; i--)
		*i = *(i - 1);//стираем с двух концов

	*it1 = value;//кладем в вектор значение с помощью вектора 
	size++;
	return;
}

void reserve()//увеличиваем массива
{
	if (capacity == 0){//если вместимость равна нулю, то надо увеличить
		capacity = 2; 
	}
	else capacity *= 2;
	T *newArray = (T*)(operator new (sizeof(T)* capacity));//создали новый массив

	for (int i = 0; i < size; i++)
		new(newArray + i)T(array[i]);//заполняем новый массив элементами

	for (int i = 0; i < size; i++){
		array[i].~T();//удаляем элементы старого массива
	}
	array = newArray;//приравниваем массивы
}

void swap(Vector<T>& vector)//меняем местами
{
	swap(array, vector.array);
	swap(size, vector.size);
	swap(capacity, vector.capacity);
}


};
int main(){
}
