#include<iostream>

using namespace std;

template <typename T>//шаблонный класс вектора
class Vector{//класс вектора 
	T * array;//массив может быть любого типа
	int size;//размер
	int capacity;//вместимость
public:
	typedef T* iterator;//объявляем итератор именем типа
	iterator begin() { return array; }//указатеь на первый элемент
	iterator end() { return array + size; }//указатель на воображаемый несуществующий элемент,следующий за последним

	Vector() : capacity(0), size(0) {//конструктор по умолчанию
		array = (T*)(operator new (0));//выделяется память для массива
	}
	Vector(int size) : Vector(size, T()){}//конструктор позволяющий задать размерность вектора, но не являющимся конструктором преобразования

	Vector(int _size, const T& value)//конструктор копирования из одного вектора в другой
	{
		size = 0;//задаем размер массива
		capacity = size;//задаем вместимость 
		array = (T*)(operator new (sizeof(T)* capacity));//выделяем память для массива,с размером и вместимостью
		for (int i = 0; i < size; i++){
			new (array + i)T(value);//кладем в массив значения
		}
	};
	Vector<T> & pushBack(const T& value){//добавление элемента
		if (size == capacity)
			reserve(size + 1);//увеличиваем массив

		array[size++] = value;
		return *this;//указатель на текущий вектор
	}
	unsigned int _size() const {//возвращаем размер
		return (unsigned int)size;
	}
	unsigned int _capaciy() const {//возвращае вместимость, чтоб небыло отрицательных значений
		return (unsigned int)capacity;
	}
	Vector<T> & popBack()//удаление элемента
	{
		(array + —size)->~T();//вызываем конструктор для конкрутного элемента и сдвигаем  
		return *this;
	}
	Vector<T> & clear(){//удаляем массив
		for (int i = 0; i < size; i++)
			(array + i)->~T();//удаляем элемент

		operator delete(array);//удаляем массив

		array = (T*)(operator new (0));//выделяем пустой массив
		size = capacity = 0;
		return *this;
	}

	~Vector(){//деструктор на удаление любого элемента
		delete[] array;
	}

	T& operator[] (int i){//обращение по индексу
		return array[i];
	};
	bool empty() const{
		return size == 0;//обнуляем размер
	}

	void erase(iterator it){//удаление одного элемента
		if (it < begin() || end() <= it)
			throw nullptr;//бросаем 0
		int i = (int)(it - array);//получаем указатель на элемент который нужно удалить
		array[i].~T();
		for (; i < size - 1; i++){
			array[i] = array[i + 1]; //сдвигаем
		}
		size--;

	}

	void erase(iterator it, int n)//удаление н элементов по одному
	{
		if (n == 1)
		{
			erase(it);//удаление одного элемента 
			return;
		}
		else if (it > begin() || it <= end())		{
			int i = (int)(it - array);//получаем указатель на элемент который нужно удалить
			for (int j = i; j < n; j++){
				array[j].~T();
			}
			for (int j = i; j < size; j++){
				array[j] = array[j + n];
			}
			size -= n;
		}
	};


	void erase(iterator it_begin, iterator it_end)
	{
		if (it_begin < begin() || it_begin > end())//итератор должен находится посередине
			throw nullptr;

		if (it_end < begin() || it_end > end())
			throw nullptr;

		int i = (int)(it_begin - array);//вычитаем указатели
		int	j = (int)(it_end - array);//вычитаем указатели

		if (i == j)//конец и начало (якобы)
		{
			erase(it_begin); // удаление одного элемента
			return;
		}
		j++;

		while (j < size)
		{
			*(array + i) = *(array + j);//стираем элементы с двух сторон 
			i++;
			j++;

			size--;
		}
	}

	void insert(const iterator it, T value)//вставка
	{
		if (it < begin() || end() <= it)
			throw nullptr;

		Vector<T>::iterator it1 = it;//новывй итератор
		if (size == capacity)
		{
			int i = (int)(it1 - array);//вычитаем указатели
			reserve();//добавляем памяти
			it1 = array + i;
		}

		new (end())T();//новый итератор

		for (Vector<T>::iterator i = end(); i != it1; i--)
			*i = *(i - 1);//

		*it1 = value;//кладем в вектор значение с пмощью вектора
		size++;
		return;
	}

	void reserve(int _capacity)//увеличиваем массив
	{
		if (capacity >= _capacity)//сравниваем текущую вместимость и которая вообще может быть
			return;
		T *newArray = (T*)(operator new (sizeof(T)* _capacity));//создали новывй массив
		size = _size();
		if (capacity == 0){//если вместимость = 0 то надо увелисить
			capacity = 2;
		}
		else capacity *= 2;//увеличиваю в 2 раза

		for (int i = 0; i < size; i++)
			new(newArray + i)T(array[i]);//заполняем новый массив элементами

		for (int i = 0; i < size; i++){
			array[i].~T();//удаляем элементы старого массива
		}
		int sz = size;//переопределяем для нового массива
		clear();
		size = sz;
		capacity = _capacity;
		array = newArray;//приравниваем массивы
	}
	void swap(Vector<T>& vector)//меняем местами
	{
		swap(array, vector.array);
		swap(size, vector.size);
		swap(capacity, vector.capacity);
	}

	T sum(Vector<T>& vector)
	{
		T sum = 0;
		int i = 0;
		for (i; i < size; i++){
			sum += array[i] + vector.array[i];
		}
		return sum;
	}
};

int main(){
	Vector<int> vect1(10);
	/*
	Vector<int> vect2(10);
	*/
	for (int i = 0; i < 10; ++i)
	{
		vect1.pushBack(i);
	}
	/*
	for (int i = 0; i < 10; ++i)
	{
	vect2.pushBack(i);
	};
	*/
	//system("pause");

	//cout << vect1[2];
	cout << vect1._size() << endl;
	//vect1.erase(vect1.begin()+1,2);

	vect1.erase(vect1.begin() + 1, vect1.begin() + 4);

	cout << vect1._size() << endl;
	system("pause");
	//cout << vect2.sum(vect1);
}