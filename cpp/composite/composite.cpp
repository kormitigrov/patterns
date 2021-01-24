#include <iostream>
#include <stdio.h>

using namespace std;

// an abstract object - a shape: every shape can move and draw itself 
class CShape
{
public:
	virtual void move(int dx, int dy) = NULL;
	virtual void draw() = NULL;
	~CShape() {};
};

// a specific object - a point, descends from abstract CShape
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
		printf("CPoint::draw() : drawing at (%d, %d)\n", _x, _y);
	}
};

// another specific object - a group of CShapes,
// note, that it descends from CShape, thus it IS a CShape itself
class CGroup : public CShape
{
private:
	// the maximun number of shapes in the group
	int _maxcount;
	// current number of shapes in the group
	int _count;
	// actual pointers storage array
	CShape **_shapes;
public:
	// constructor
	CGroup(int maxcount)
	{
		printf("CGroup::CGroup(%d)\n", maxcount);
		_maxcount = maxcount; _count = 0;
		_shapes = new CShape*[_maxcount];
		for (int i = 0; i < _maxcount; i++)
			_shapes[i] = NULL;
	}
	// destructor
	~CGroup()
	{
		printf("start CGroup::~CGroup()\n");
		// iterate through all objects and delete them
		for (int i = 0; i < _count; i++)
			delete (_shapes[i]);
		// deallocate the memory
		delete [] _shapes;
		printf("finish CGroup::~CGroup()\n");
	}
	// function to add a shape to the group
	bool addShape(CShape *shape)
	{
		if (_count >= _maxcount)
			return false;
		
		_count++;
		_shapes[_count - 1] = shape;
		return true;
	}
	
	// as CGroup is in the same time CShape, it MUST propose 
	// its own implementation for virtual void move(int dx, int dy)
	virtual void move(int dx, int dy)
	{
		printf("CGroup::move(%d, %d)\n", dx, dy);
		// iterate though all objbects and call move()
		for (int i = 0; i < _count; i++)
			_shapes[i] -> move(dx, dy);
	}
	// as CGroup is in the same time CShape, it MUST propose 
	// its own implementation for virtual void draw()
	virtual void draw()
	{
		printf("CGroup::draw()\n");
		// iterate though all objbects and call draw()
		for (int i = 0; i < _count; i++)
			_shapes[i] -> draw();
	}
};

// ------------------------------------------------------------

void main()
{
	// create a group
	CGroup *shapes = new CGroup(3);
	// assign two first elements with new points
	shapes -> addShape(new CPoint(1,1));
	shapes -> addShape(new CPoint(2,2));
		
		// create another group
		CGroup *childshapes = new CGroup(2);
		// add two new points to the newly created child group
		childshapes -> addShape(new CPoint(3,3));
		childshapes -> addShape(new CPoint(4,4));

	// now assign the third element of the main group with child group
	shapes -> addShape(childshapes);

	// here we can treat 'shapes' as a regular CShape, for instance,
	// calling methods move() or draw(). It looks just like CShape,
	// though it is something more complex inside. That's composite
	shapes -> move(10,10);
	shapes -> draw();

	// delete the main group
	delete shapes;

	system("pause");
}