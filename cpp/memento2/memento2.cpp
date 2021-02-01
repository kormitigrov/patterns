#include <iostream>
#include <stdio.h>

using namespace std;

// an abstract class, that _encapsulates_ a 'state' of the abstract shape
class CShapeState
{
public:
	virtual ~CShapeState() 
	{
	};
};

// an abstract memento - something that be used to store and retrieve
// a state of the object
class CShapeMemento
{
public:
	virtual ~CShapeMemento() 
	{
	};
};

// an abstract object, whos state we will change and unchange back
class CShape
{
public:
	// a virtual method, to ask an object to write its current state
	// into new memento object and return it to us
	virtual CShapeMemento *createShapeMemento() = 0;
	// a virtual method, to give the object a memento it has created
	// a long time ago, and to ask it to read its state from memento
	virtual void updateFromMemento(CShapeMemento *memento) = 0;
	virtual ~CShape()
	{
	}
};

// a concrete class that _encapsulates_ a state of a point 
class CPointState : public CShapeState
{
private:
	// it is a friend of a CPoint class, thus CPoint
	// can access its private arrtibutes
	friend class CPoint;
	int _x,_y;
};

// a concrete memento - something that be used to store and retrieve
// a state of CPoint
class CPointMemento : public CShapeMemento
{
private:
	// it is a friend of a CPoint class, thus CPoint
	// can access its private arrtibutes
	friend class CPoint;
	// a memento stores a pointer to the object, that
	// actually stores all data of the state
	CPointState _state;
	// we can retrieve the state from every memento
	CPointState getState()
	{
		// in this case we just return the state that is stored inside
		return _state;
	}
public:
	// CPointMemento has only two public methods, thus data inside
	// is invisible for anybody, but its friend, CPoint
	CPointMemento(CPointState state)
	{
		printf("CPointMemento(CPointState state)\n");
		_state = state;
	}
	~CPointMemento()
	{
		printf("~CPointMemento()\n");
	};
};

// an concrete CPoint, whos state we will change and unchange back
class CPoint : public CShape
{
private:
	CPointState state;
public:
	CPoint(int x, int y)
	{
		printf("CPoint(int x, int y)\n");
		state._x = x; state._y = y;
	};
	// a method to change the state of the object
	void move(int dx, int dy)
	{
		state._x = state._x + dx; state._y = state._y + dy;
	};
	// a method to report the state of the object
	void report()
	{
		printf("CPoint is: %d %d\n", state._x, state._y);
	}
	// we can ask a point to write its current state
	// into new memento object and return it to us
	CShapeMemento *createShapeMemento() override
	{
		// create a new memento
		CPointMemento *memento = new CPointMemento(state);
		// and return it
		return memento;
	}
	// we can give the object a memento it has created
	// a long time ago, and to ask it to read its state from memento
	void updateFromMemento(CShapeMemento *memento) override
	{
		// if it is our own memento (of class CPointMemento)
		CPointMemento *ownmemento = dynamic_cast<CPointMemento*>(memento);
		if (ownmemento != nullptr)
			// get the state from memento 
			state = ownmemento->getState();
		else
			printf("CPoint::updateFromMemento(memento) error: memento is not of CPointMemento class\n");
	}
	~CPoint()
	{
		printf("~CPoint()\n");
	}
};

void main()
{

	// create a CPoint
	CPoint *p = new CPoint(10,20);
	// ask a CPoint to report its current state
	p -> report();
	
	// ask a CPoint to create its current memento
	CShapeMemento *memento = p -> createShapeMemento();
	
	// now our memento object stores the current state of the CPoint object.
	// note, CShapeMemento has NO public methods, thus we know NOTHING
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