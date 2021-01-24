#include <iostream>
#include <stdio.h>

using namespace std;

// an abstract class, that _encapsulates_ a 'state' of the object
class CState
{
public:
	virtual ~CState() {};
};

// an abstract memento - something that be used to store and retrieve
// a state of the object
class CShapeMemento
{
private:
	friend class CShape;
	// we can retrieve the state from every memento
	virtual CState *getState() = NULL;
	// and we can set state of every memento
	virtual void setState(CState *state) = NULL;
public:
	virtual ~CShapeMemento() {};
};

// an abstract object, whos state we will change and unchange back
class CShape
{
public:
	// a virtual method, to ask an object to write its current state
	// into new memento object and return it to us
	virtual CShapeMemento *createShapeMemento() = NULL;
	// a virtual method, to give the object a memento it has created
	// a long time ago, and to ask it to read its state from memento
	virtual void updateFromMemento(CShapeMemento *memento) = NULL;
};

// ------------------------------------------------------------

// a concrete class that _encapsulates_ a state of a point 
class CPointState: public CState
{
private:
	// it is a friend of a CPoint class, thus CPoint
	// can access its private arrtibutes
	friend class CPoint;
	int _x,_y;
};

// a concrete memento - something that be used to store and retrieve
// a state of CPoint
class CPointMemento: public CShapeMemento
{
private:
	// it is a friend of a CPoint class, thus CPoint
	// can access its private arrtibutes
	friend class CPoint;
	// a memento stores a pointer to the object, that
	// actually stores all data of the state
	CPointState *_state;
	// we can retrieve the state from every memento
	virtual CState *getState()
	{
		// in this case we just return the state that is stored inside
		return _state;
	}
	// and we can set state of every memento
	virtual void setState(CState *state)
	{
		// if the state given is CPointState, we store it inside
		if (dynamic_cast<CPointState*>(state) == NULL)
			printf("CPointMemento::setState(state) error: state is not of CPointState class\n");
		else
			_state = dynamic_cast<CPointState*>(state);
	}
public:
	// CPointMemento has only two public methods, thus data inside
	// is invisible for anybody, but its friend, CPoint
	CPointMemento()
	{
		_state = NULL;
	}
	virtual ~CPointMemento()
	{
		delete _state;
	};
};

// an concrete CPoint, whos state we will change and unchange back
class CPoint: public CShape
{
private:
	int _x,_y;
public:
	CPoint(int x, int y)
	{
		_x = x; _y = y;
	};
	// a method to change the state of the object
	void move(int dx, int dy)
	{
		_x = _x + dx; _y = _y + dy;
	};
	// a method to report the state of the object
	void report()
	{
		printf("CPoint is: %d %d\n", _x, _y);
	}
	// we can ask a point to write its current state
	// into new memento object and return it to us
	virtual CShapeMemento *createShapeMemento()
	{
		// create a new memento
		CPointMemento *memento = new CPointMemento();
		// create a new state object
		CPointState *state = new CPointState();
		// store actual data inside state
		state -> _x = _x; state -> _y = _y;
		// store state inside memento
		memento -> setState(state);
		// and return it
		return memento;
	}
	// we can give the object a memento it has created
	// a long time ago, and to ask it to read its state from memento
	virtual void updateFromMemento(CShapeMemento *memento)
	{
		// if it is our own memento (of class CPointMemento)
		if (dynamic_cast<CPointMemento*>(memento) == NULL)
			printf("CPoint::updateFromMemento(memento) error: memento is not of CPointMemento class\n");
		else
		{
			// typecast memento to our own class
			CPointMemento *ownmemento = dynamic_cast<CPointMemento*>(memento);
			// get the state from memento and typecast it to our own class
			CPointState *state = dynamic_cast<CPointState*>(ownmemento -> getState());
			// read actual data from state
			_x = state -> _x;
			_y = state -> _y;
		}
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