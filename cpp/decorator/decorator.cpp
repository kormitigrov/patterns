#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class CShape
{
public:
	virtual void draw() = NULL;
	virtual ~CShape() {};
};

class CPoint : public CShape
{
private:
	int _x, _y;
public:
	CPoint(int x, int y)
	{
		printf("CPoint::CPoint(%d, %d)\n", x, y);
		_x = x;	_y = y;
	}
	~CPoint()
	{
		printf("CPoint::~CPoint() : deleting (%d, %d)\n", _x, _y);
	}
	virtual void move(int dx, int dy)
	{
		printf("CPoint::move(%d, %d)\n", dx, dy);
		_x = _x + dx; _y = _y + dy;
	}
	virtual void draw()
	{
		printf("(%d, %d)", _x, _y);
	}
};

class CDecorator : public CShape
{
private:
	CShape *_shape;
public:
	CDecorator(CShape *shape)
	{
		printf("CDecorator::CDecorator(CShape *shape)\n");
		_shape = shape;
	}
	~CDecorator()
	{
		printf("CDecorator::~CDecorator()\n");
		delete _shape;
	}
	virtual void draw()
	{
		printf("*");
		_shape->draw();
		printf("*");
	}
};

void main()
{
	vector<CShape*> shapes(3);

	shapes[0] = new CPoint(1, 1);  
	shapes[1] = new CDecorator(new CPoint(2, 2));
	shapes[2] = new CDecorator(new CDecorator(new CPoint(3, 3)));

	for (vector<CShape*>::iterator i = shapes.begin(); i != shapes.end(); i++)
		if (*i != NULL)
		{
			(*i)->draw();
			printf("\n");
		}

	system("pause");
}

