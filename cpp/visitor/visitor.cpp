#include <iostream>
#include <stdio.h>

using namespace std;

class CPoint;
class CGroup;

class CHandler
{
public:
	virtual void handlePoint(CPoint *p) = 0;
	virtual void handleGroup(CGroup *g) = 0;
	virtual ~CHandler()
	{
	}
};

class CShape
{
public:
	virtual void Apply(CHandler *Handler) = 0;
	virtual ~CShape() 
	{
	};
};

class CPoint : public CShape
{
public:
	int _x, _y;
public:
	CPoint(int x, int y) : _x(x), _y(y) {};
	void Apply(CHandler *Handler) override
	{
		Handler->handlePoint(this);
	}
};

class CGroup : public CShape
{
public:
	int _maxcount;
	int _count;
	CShape **_shapes;
public:
	CGroup(int maxcount)
	{
		_maxcount = maxcount; _count = 0;
		_shapes = new CShape*[_maxcount];
		for (int i = 0; i < _maxcount; i++)
			_shapes[i] = nullptr;
	}
	~CGroup()
	{
		for (int i = 0; i < _count; i++)
			delete (_shapes[i]);
		delete[] _shapes;
	}
	bool addShape(CShape *shape)
	{
		if (_count >= _maxcount)
			return false;

		_count++;
		_shapes[_count - 1] = shape;
		return true;
	}
	void Apply(CHandler *Handler) override
	{
		Handler->handleGroup(this);
	}
};

class CDrawer : public CHandler
{
	void handlePoint(CPoint *p) override
	{
		printf("CPoint drawing at (%d, %d)\n", p->_x, p->_y);
	}
	void handleGroup(CGroup *g) override
	{
		for (int i = 0; i < g->_count; i++)
			g->_shapes[i]->Apply(this);
	}
};

class CMover : public CHandler
{
private:
	int _dx, _dy;
public:
	CMover(int dx, int dy) : _dx(dx), _dy(dy) {};
	void handlePoint(CPoint *p) override
	{
		printf("CPoint moving on (%d, %d)\n", _dx, _dy);
		p->_x = p->_x + _dx; p->_y = p->_y + _dy;
	}
	void handleGroup(CGroup *g) override
	{
		for (int i = 0; i < g->_count; i++)
			g->_shapes[i]->Apply(this);
	}
};

void main()
{
	CGroup *shapes = new CGroup(3);
	shapes->addShape(new CPoint(1, 1));
	shapes->addShape(new CPoint(2, 2));
	CGroup *childshapes = new CGroup(2);
	childshapes->addShape(new CPoint(3, 3));
	childshapes->addShape(new CPoint(4, 4));
	shapes->addShape(childshapes);

	CDrawer dr;
	CMover mv(10, 10);

	shapes->Apply(&dr);
	shapes->Apply(&mv);
	shapes->Apply(&dr);

	delete shapes;

	system("pause");
}
