#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

// an abstract object - a shape: every shape can move and draw itself 
class CShape {
public:
	virtual void move(int dx, int dy) = 0;
	virtual void draw() = 0;
	virtual ~CShape() { };
};

// a specific object - a point, descends from abstract CShape
class CPoint : public CShape {
private:
	int _x, _y;
public:
	CPoint(int x, int y) {
		printf("CPoint::CPoint(%d, %d)\n", x, y);
		_x = x;	_y = y;
	}
	void move(int dx, int dy) override {
		printf("CPoint::move(%d, %d)\n", dx, dy);
		_x = _x + dx; _y = _y + dy;
	}
	void draw() override {
		printf("CPoint::draw() : drawing at (%d, %d)\n", _x, _y);
	}
	~CPoint() {
		printf("CPoint::~CPoint() : deleting (%d, %d)\n", _x, _y);
	}
};

// another specific object - a group of CShapes,
// note, that it descends from CShape, thus it IS a CShape itself
class CGroup : public CShape {
private:
	// actual pointers storage array
	vector <CShape*> _shapes;
public:
	// constructor
	CGroup() {
		printf("CGroup::CGroup()\n");
	}
	// function to add a shape to the group
	void addShape(CShape *shape) {
		_shapes.push_back(shape);
	}
	// as CGroup is in the same time CShape, it MUST propose 
	// its own implementation for virtual void move(int dx, int dy)
	void move(int dx, int dy) override {
		printf("CGroup::move(%d, %d)\n", dx, dy);
		// iterate though all objbects and call move()
		for (const auto &shape : _shapes)
			shape->move(dx, dy);
	}
	// as CGroup is in the same time CShape, it MUST propose 
	// its own implementation for virtual void draw()
	void draw() override {
		printf("CGroup::draw()\n");
		// iterate though all objbects and call draw()
		for (const auto &shape : _shapes)
			shape->draw();
	}
	// destructor
	~CGroup() {
		printf("start CGroup::~CGroup()\n");
		// iterate through all objects and delete them
		for (const auto &shape : _shapes)
			delete shape;
		printf("finish CGroup::~CGroup()\n");
	}
};

// ------------------------------------------------------------

void main() {
	// create a group
	CGroup *shapes = new CGroup;
	// assign two first elements with new points
	shapes->addShape(new CPoint(1,1));
	shapes->addShape(new CPoint(2,2));
		
		// create another group
		CGroup *childshapes = new CGroup;
		// add two new points to the newly created child group
		childshapes->addShape(new CPoint(3,3));
		childshapes->addShape(new CPoint(4,4));

	// now assign the third element of the main group with child group
	shapes->addShape(childshapes);

	// here we can treat 'shapes' as a regular CShape, for instance,
	// calling methods move() or draw(). It looks just like CShape,
	// though it is something more complex inside. That's composite
	shapes->move(10,10);
	shapes->draw();

	// delete the main group
	delete shapes;

	system("pause");
}