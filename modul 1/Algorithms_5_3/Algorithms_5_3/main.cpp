/*
Задача 5_3. Прямоугольники.
Дана последовательность N прямоугольников различной ширины и высоты (wi,hi). 
Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо). 
Требуется найти M - площадь максимального прямоугольника (параллельного осям координат), 
который можно вырезать из этой фигуры.
*/

#include <iostream>
#include <assert.h>
#include <algorithm>

struct Rectangle {
	int width;
	int height;
	Rectangle(int _width = 0, int _height = 0) : width(_width), height(_height) {};
	Rectangle(const Rectangle & rec) : width(rec.width), height(rec.height) {};
	int area() { return width*height; }
};

template <typename T>
struct Node {
	T data;
	Node *next;
	Node() : next(nullptr) {};
	Node(const T & _data) : data(_data), next(nullptr) {};
};

template <typename T>
class Stack {
private:
	Node<T> *head;
	int size;
	void free();
public:
	Stack() : head(nullptr), size(0) {};
	~Stack() { free(); }
	bool isEmpty() const { return head == 0; }
	T pop();
	void push(const T & obj);
	const T& getTop() { assert(!isEmpty()); return head->data; }
	int getSize() { return size; }
};

template <typename T>
void Stack<T>::free() {
	while (!isEmpty())
		pop();
}

template <typename T>
T Stack<T>::pop() {
	size--;
	Node<T> *newHead = new Node<T>;
	newHead = head->next;
	T data = getTop();
	delete head;
	head = newHead;
	newHead = nullptr;
	return data;
}

template <typename T>
void Stack<T>::push(const T & obj) {
	size++;
	Node<T> *newHead = new Node<T>(obj);
	newHead->next = head;
	head = newHead;
}

int main() {
	Stack<Rectangle> stack;
	int n = 0;
	int w = 0, h = 0;
	int maxArea = 0;
	std::cin >> n;
	std::cin >> w >> h;
	Rectangle rec(w, h);
	maxArea = w*h;
	stack.push(rec);
	for (int i = 1; i < n; i++) {
		std::cin >> w >> h;
		rec = Rectangle(w, h);

		if (h > stack.getTop().height) {
			maxArea = std::max(maxArea, w*h);
			stack.push(rec);
			continue;
		}

		while (stack.getSize() > 0 && stack.getTop().height >= h) {
			Rectangle newRec = stack.pop();
			Rectangle nextRec = Rectangle(0, 0);
			if (!stack.isEmpty())
				nextRec = stack.getTop();
			if (nextRec.height > h) {
				stack.pop();
				newRec = Rectangle((nextRec.width + newRec.width), nextRec.height);
				stack.push(newRec);
				maxArea = std::max(maxArea, newRec.area());
				continue;
			}
			newRec = Rectangle((w + newRec.width), h);
			//	stack.push(newRec);
			maxArea = std::max(maxArea, newRec.area());
			w = newRec.width;
			h = newRec.height;
		}
		stack.push(Rectangle(w, h));

	}

	//stack.push(Rectangle(5, 0));
	h = 0;
	w = 0;
	while (stack.getSize() > 0 && stack.getTop().height >= h) {
		Rectangle newRec = stack.pop();
		Rectangle nextRec = Rectangle(0, 0);
		if (!stack.isEmpty())
			nextRec = stack.getTop();
		if (nextRec.height > h) {
			stack.pop();
			newRec = Rectangle((nextRec.width + newRec.width), nextRec.height);
			stack.push(newRec);
			maxArea = std::max(maxArea, newRec.area());
			continue;
		}
		newRec = Rectangle((w + newRec.width), h);
		//	stack.push(newRec);
		maxArea = std::max(maxArea, newRec.area());
		w = newRec.width;
		h = newRec.height;
	}
	std::cout << maxArea << std::endl;
}