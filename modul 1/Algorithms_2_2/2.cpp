/*
«адача 2_2.
	ѕлощадь n-угольника.
	¬ычислить площадь выпуклого n-угольника, заданного координатами своих вершин. 
	¬начале вводитс€ количество вершин, затем последовательно целочисленные координаты всех вершин 
	в пор€дке обхода по часовой стрелке.
	n < 1000, координаты < 10000.
	”казание. ƒл€ вычислени€ площади n-угольника можно посчитать сумму ориентированных площадей трапеций 
	под каждой стороной многоугольника.
*/
#include <iostream>
#include <climits>
#include <assert.h>
#include <cmath>

struct Point {
	int x;
	int y;
};

class CPolygon {
	Point* pPoint;
	int n;
public:
	CPolygon(int _n): n(_n) { pPoint = new Point[n]; };
	void enterPoints();
	~CPolygon(){ delete[] pPoint; };
	double area();
};	

double CPolygon::area() {
	int minX = INT_MAX, minY = INT_MAX, 
		maxX = INT_MIN, maxY = INT_MIN;
	double sumArea = 0;
	for (int i = 0; i < n; i++) { //search for maxX, maxY, minX, minY
		if (pPoint[i].x > maxX)
			maxX = pPoint[i].x;
		if (pPoint[i].x < minX)
			minX = pPoint[i].x;
		if (pPoint[i].y > maxY)
			maxY = pPoint[i].y;
		if (pPoint[i].y < minY)
			minY = pPoint[i].y;
	}

	double rectangleArea = std::abs( (maxX - minX) * (maxY - minY) ); // calculate the area of a rectangle
		
	for (int i = 0; i < n; i++) {
		if (i == (n - 1))
			sumArea += std::abs( ((pPoint[i].x - pPoint[0].x) * (pPoint[i].y - pPoint[0].y) * 0.5) ); //area of a triangle when the coordinates are last and first
		else
			sumArea += std::abs( ((pPoint[i].x - pPoint[i + 1].x) * (pPoint[i].y - pPoint[i + 1].y) * 0.5) ); //area of a triangle
		if (pPoint[i].x > minX && pPoint[i].x < maxX && pPoint[i].y > minY && pPoint[i].y < maxY) //if the dot inside of the rectangle
			if (i == (n - 1)) 
				sumArea += std::abs( (pPoint[0].x - pPoint[i].x) * (pPoint[i - 1].y - pPoint[i].y) );
			else
				sumArea += std::abs( (pPoint[i + 1].x - pPoint[i].x) * (pPoint[i - 1].y - pPoint[i].y) );

	}
	return (rectangleArea - sumArea);
}

void CPolygon::enterPoints() {
	for (int i = 0; i < n; i++) {
		std::cin >> pPoint[i].x >> pPoint[i].y;
	}
}

int main() {
	int n;
	std::cin >> n;
	assert(n > 2);
	CPolygon polygon(n);
	polygon.enterPoints();
	double s = polygon.area();
	std::cout << s << std::endl;
}
