#include<iostream>

using namespace std;

template <typename T>//��������� ����� ������
class Vector{
	T * array;
	int size;
	int capacity;
public:
	Vector() : capacity(0), size(0) {//����������� �� ���������
		array = (T*)(operator new (0));
	}
	Vector(int size) : Vector(size, T())//�����������, ����������� ������������������� �������, �� �� ���������� ������������� ��������������
                                 
	{}
	Vector(int _size, const T& value)//����������� ����������� �� ������ ������� � ������ 
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
		(array + �size)->~T();
		return *this;
	}
};
int main(){

}
