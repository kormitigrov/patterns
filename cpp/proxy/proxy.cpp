
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class CShape {
public:
	virtual void draw() = 0;
	virtual ~CShape() { };
};

class CPoint : public CShape {
private:
	int _x, _y;
public:
	CPoint(int x, int y) {
		printf("CPoint::CPoint(%d, %d)\n", x, y);
		_x = x;	_y = y;
	}
	~CPoint() {
		printf("CPoint::~CPoint() : deleting (%d, %d)\n", _x, _y);
	}
	virtual void move(int dx, int dy) {
		printf("CPoint::move(%d, %d)\n", dx, dy);
		_x = _x + dx; _y = _y + dy;
	}
	virtual void draw() {
		printf("CPoint::draw() : drawing at (%d, %d)\n", _x, _y);
	}
};


class CProxyPoint : public CShape {
private:
	int _x, _y;
	CPoint *point;
public:
	CProxyPoint(int x, int y) {
		printf("CProxyPoint::CProxyPoint(%d, %d)\n", x, y);
		_x = x;	_y = y;
		point = nullptr;
	}
	virtual void draw() {
		printf("CProxyPoint::draw()\n");

		if (point == nullptr)
			point = new CPoint(_x, _y);

		point->draw();
	}
	~CProxyPoint() {
		printf("CProxyPoint::~CProxyPoint()\n");
		if (point != nullptr)
			delete point;
	}
};

void main() {
	vector<CShape*> shapes(3);
	shapes[0] = new CPoint(1, 1);
	shapes[1] = new CProxyPoint(2, 2);
	shapes[2] = new CPoint(3, 3);

	for (const auto &i : shapes)
		if (i != nullptr)
			i->draw();

	for (vector<CShape*>::iterator i = shapes.begin(); i != shapes.end(); i++)
		if (*i != nullptr)
			delete *i;

	system("pause");
}

