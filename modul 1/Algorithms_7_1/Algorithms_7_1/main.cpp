/*
«адача 7_1. јтлеты.
	¬ город N приехал цирк с командой атлетов. 
	ќни хот€т удивить горожан города N Ч выстроить из своих тел башню максимальной высоты. 
	Ѕашн€ Ч это цепочка атлетов, первый стоит на земле, второй стоит у него на плечах, 
третий стоит на плечах у второго и т.д.
	 аждый атлет характеризуетс€ силой si (kg) и массой mi (kg). 
	—ила Ч это максимальна€ масса, которую атлет способен держать у себ€ на плечах.
	  сожалению ни один из атлетов не умеет программировать, так как всю жизнь они 
	занимались физической подготовкой, и у них не было времени на изучение €зыков программировани€. 
	ѕомогите им, напишите программу, котора€ определит максимальную высоту башни, которую они могут составить.
	»звестно, что если атлет т€желее, то он и сильнее:
		если mi>mj, то si > sj.
	јтлеты равной массы могут иметь различную силу.
*/

#include <iostream>
#include <cstdlib>

struct Athlete {
	int mass;
	int strength;

	Athlete(int m = 0, int s = 0) : mass(m), strength(s) {};

	Athlete& operator = (Athlete& rhs) {
		if (this == &rhs)
			return (*this);
		this->mass = rhs.mass;
		this->strength = rhs.strength;
	}

	/*friend std::ostream & operator << (std::ostream & out, const Athlete & obj) {
	out << obj.mass << " " << obj.strength;
	}*/
};

template <typename T>
class Vector {
private:
	T *pMas;
	int size;
	int top;
public:
	//  default and init constructor
	Vector(int _size = 16) : pMas(nullptr), size(_size), top(-1) {
		pMas = new T[size];
	}
	//  destructor
	~Vector() {
		delete[] pMas;
	}

	int getSize() { return size; }
	int getTop() { return top; }
	void push_back(T value);
	T& operator [] (int n);

	/*friend std::ostream & operator << (std::ostream & out, Vector<T> & obj) {
	for (int i = 0; i < obj.top; i ++) {
	out << obj[i] << "\n";
	}
	}*/
};

template <typename T>
void Vector<T>::push_back(T value) {
	if (top == size - 1) {
		int sizeNew = size * 2;
		T *pMasNew = new T[sizeNew];
		std::copy(pMas, pMas + top + 1, pMasNew);
		pMas = pMasNew;
		size = sizeNew;
	}
	pMas[++top] = value;
}

template <typename T>
T& Vector<T>::operator[] (int n) {
	if (n <= top && n >= 0)
		return pMas[n];
}

int compare(const void *x1, const void *x2) {
	Athlete a1 = *(Athlete*)x1;
	Athlete a2 = *(Athlete*)x2;
	return (a1.strength - a2.strength);
}

template <typename T>
void printVector(Vector<T> &vec) {
	for (int i = 0; i < vec.getTop() + 1; i++) {
		std::cout << vec[i].mass << " " << vec[i].strength << std::endl;;
	}
	std::cout << std::endl;
}

template <typename T>
int calculate(Vector<T> &vec) {
	int sumM = vec[0].mass;
	int i = 1;
	int count = 1;
	int vecTop = vec.getTop();
	while (i < (vecTop + 1)) {
		if (sumM <= vec[i].strength) {
			sumM += vec[i].mass;
			count++;
		}
		i++;
	}
	return count;
}

int main() {
	Vector<Athlete> vec;
	int m = 0, s = 0;
	while (std::cin >> m >> s) {
		Athlete athlete(m, s);
		vec.push_back(athlete);
	}
	//std::cout << "HEY" << std::endl;
	//printVector(vec);
	qsort(&vec[0], vec.getTop() + 1, sizeof(Athlete), compare);
	//printVector(vec);
	std::cout << calculate(vec) << std::endl;
	return 0;
}