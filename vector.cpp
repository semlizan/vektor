#include<iostream>

using namespace std;

template <typename T>//шаблонный класс вектор
class Vector{
	T * array;
	int size;
	int capacity;
public:
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
};
int main(){

}
