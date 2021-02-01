#include <iostream>
#include <stdio.h>

using namespace std;

// a memento - something that be used to store and retrieve a state of CPoint
class CMemento
{
private:
	// it is a friend of a CPoint class, thus CPoint
	// can access its private attributes
	friend class CPoint;
	// actual storage of CPoint data
	int _x,_y;
	// a method to set the state of the memento
	void setState(int x, int y)
	{
		_x = x;
		_y = y;
	}
	// a method to get the state of the memento
	void getState(int &x, int &y)
	{
		x = _x;
		y = _y;
	}
public:
	// CPointMemento has only two public methods, thus data inside
	// is invisible to anybody, but to its friend, CPoint
	CMemento()
	{
		_x = 0; _y = 0;
	}
	virtual ~CMemento()
	{
	};
};

// an CPoint, whos state we will change and unchange back
class CPoint
{
private:
	// data of CPoint
	int _x,_y;
public:
	CPoint(int x, int y)
	{
		_x = x; _y = y;
	}
	// a method to change the state of the object
	void move(int dx, int dy)
	{
		_x = _x + dx; _y = _y + dy;
	}
	// a method to report the state of the object
	void report()
	{
		printf("CPoint is: %d %d\n", _x, _y);
	}
	// we can ask a point to write its current state
	// into new memento object and return it to us
	virtual CMemento *createMemento()
	{
		// create a new memento
		CMemento *memento = new CMemento();
		// store actual data inside it
		memento -> setState(_x, _y);
		// and return it
		return memento;
	}
	// we can give the object a memento it has created
	// a long time ago, and to ask it to read its state from memento
	virtual void updateFromMemento(CMemento *memento)
	{
		// read actual data from memento
		memento -> getState(_x, _y);
	}
	virtual ~CPoint()
	{
	}
};

void main()
{

	// create a CPoint
	CPoint *p = new CPoint(10,20);
	// ask a CPoint to report its current state
	p -> report();
	
	// ask a CPoint to create its current memento
	CMemento *memento = p -> createMemento();
	
	// now our memento object stores the current state of the CPoint object.
	// note, CMemento has NO public methods, thus we know NOTHING
	// about memento, we have NO access to its members, but we know that
	// it stores inside information about CPoint

	// now we can change a point to another destination
	p -> move(5,5);
	// ask a CPoint to report its current state
	p -> report();

	// however, having a memento object, we can always ask CPoint
	// to return back to the state it was when memento was created
	p -> updateFromMemento(memento);
	// ask a CPoint to report its current state
	p -> report();
	
	// delete memento and CPoint
	delete memento;
	delete p;
	
	system("pause"); 
}