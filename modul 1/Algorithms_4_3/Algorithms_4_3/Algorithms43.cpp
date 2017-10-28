/*
	Задача 4_3. 
	Реализовать очередь с помощью двух стеков. 
	Использовать стек, реализованный с помощью динамического буфера.
*/


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <assert.h>

#define VECTOR_SIZE 16
//////////////////////////////////////////
//Класс Vector
////////////////////////////////////////

template <typename T>
class Vector {
	T *pMas;
	int top;
	int size;
public:
	//default constructor
	Vector() : top(-1), size(VECTOR_SIZE) { 
		pMas = new T[size];
	}
	//initialisation constructor
	Vector(int _size) : top(-1), size(_size) {
		pMas = new T[size];
	}
	//destructor
	~Vector() { delete[] pMas; }
	//push value
	void push(T value);
	//pop value
	T pop();
	//isEmpty
	bool isEmpty() { return top == -1; }

};

template <typename T>
void Vector<T>::push(T value) {
	if (top == -1) {
		pMas = new T[VECTOR_SIZE];
		size = VECTOR_SIZE;
	}
	if (top + 1 >= size) { //if no space in vector
		int sizeNew = size * 2;
		T *pMasNew = new T[sizeNew];
		std::copy(pMas, pMas + top + 1, pMasNew);
		pMas = pMasNew;
		size = sizeNew;
	}
	pMas[++top] = value;
}

template <typename T>
T Vector<T>::pop() {
	if (top < (size / 2)) {
		int sizeNew = size / 2 + 1;
		T *pMasNew = new T[sizeNew];
		std::copy(pMas, pMas + top + 1, pMasNew);
		delete[] pMas;
		pMas = pMasNew;
		size = sizeNew;
	}
	if (top != -1)
		return pMas[top--];
	delete[] pMas;
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
//Класс Stack
////////////////////////////////////////////////////////////////////////////
template <typename T>
class Stack {
	Vector<T> vector;
public:
	//default constructor
	Stack() {};
	//initialisation constructor
	Stack(T _size) : vector(_size) {};
	//destructor
	~Stack() {};
	void push(T data);
	T pop();
	bool isEmpty() { return vector.isEmpty(); }
};

template <typename T>
void Stack<T>::push(T data) {
	vector.push(data);
}

template <typename T>
T Stack<T>::pop() {
	return vector.pop();
}

////////////////////////////////////////////////////////////////////////////
//Класс Queue
////////////////////////////////////////////////////////////////////////////
template <typename T>
class Queue {
	Stack<T> left;
	Stack<T> right;
public:
	Queue(T _size = 0): left(_size), right(_size) {};
	~Queue() {};
	void push(T data);
	T pop();
	//void print();
	bool isEmpty() { return (right.isEmpty() && left.isEmpty()); };
};

template <typename T>
void Queue<T>::push(T data) {
	left.push(data);
}

template <typename T>
T Queue<T>::pop() {
	if (right.isEmpty()) {
		while (!left.isEmpty())
			right.push(left.pop());
	}
	if (!right.isEmpty())
		return right.pop();
	return -1;
}

/*template <typename T>
void Queue<T>::print() {
	while (!right->isEmpty())
		std::cout << right->pop() << std::endl;
	while (!left->isEmpty())
		right->push(left->pop());
	while (!right->isEmpty())
		std::cout << right->pop() << std::endl;
}*/

int main() {
	Queue<int> queue(32);
	std::ifstream fin;
	fin.open("input.txt");
	if (!fin.is_open()) { // если файл небыл открыт
		std::cout << "Файл не может быть открыт или создан\n"; // напечатать соответствующее сообщение
		return 1; // выполнить выход из программы
	}

	int countCommand;
	fin >> countCommand;
	//std::cin >> countCommand;
	assert(countCommand > 0);

	for (int i = 0; i < countCommand; i++) {
		int command, value;
		fin >> command >> value;
		//std::cin >> command >> value;
		assert(command > 0);
		assert(command < 5);
		switch (command) {
		case 2: if (value == -1 && queue.isEmpty())
			continue;
			if (value != queue.pop()) {
				std::cout << "NO";
				return 0;
			}
			break;
		case 3: queue.push(value);
			break;
		default:
			assert(false);
		}
	}
	std::cout << "YES";
	return 0;
}
