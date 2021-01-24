#include <iostream>
#include <stdio.h>

using namespace std;

// an interface of an array
class IArray
{
public:
	// get the number of elements
	virtual int getCount() = NULL;
	// get an element by index
	virtual int getValue(int index) = NULL;
};

// lets create a real array of ints, that implements IArray
class CArray : public IArray
{
private:
	int *_values;
	int _size;
public:
	CArray(int size)
	{
		_size = size;
		_values = new int[_size];
		for (int i = 0; i < _size; i++)
			_values[i] = rand();
	}
	virtual int getCount()
	{
		return _size;
	}
	virtual int getValue(int index)
	{
		return _values[index];
	}
};

// now, suppose we have another interface, IList
class IList
{
public:
	// move to the first element
	virtual void first() = NULL;
	// get current value
	virtual int currentValue() = NULL;
	// move to the next element
	virtual void next() = NULL;
	// have we moved out of the elements in the list?
	virtual bool isEOL() = NULL;
};

// the question is: if our program (a big program by that time) 
// is working with IList (is calling methods first, next, etc),
// - can we teach it to work with CArray?
// we do not want to rewrite CArray a new, we want to use it's
// functionality.
// we have to ADAPT CArray to the interface IList:

// an adapter class: it implements IList, but privately inherits from CArray
// that means, it is in fact CArray, but it LOOKS like IList:
class CListAdapter : public IList, private CArray
{
private:
	int _current_index;
public:
	CListAdapter(int size) : CArray(size)
	{
		_current_index = 0;
	}
	// all functions of IList are implemented by calling methods of CArray
	virtual void first()
	{
		_current_index = 0;
	}
	// all functions of IList are implemented by calling methods of CArray
	virtual int currentValue()
	{
		if (!isEOL())
			return getValue(_current_index);
		else
			return 0;
	}
	// all functions of IList are implemented by calling methods of CArray
	virtual void next()
	{
		if (!isEOL())
			_current_index++;
	}
	// all functions of IList are implemented by calling methods of CArray
	virtual bool isEOL()
	{
		return _current_index == getCount();
	}
};

void main()
{
	// we create CListAdapter, that means that in fact we are creating CArray
	// but for the rest of the program it LOOKS like IList
	CListAdapter list(10);

	// so we can use methods of IList on list object,
	// it will behave like IList, though inside it
	// is the same old CArray, storing values in a plain array

	for(list.first(); !list.isEOL(); list.next())
		printf("%d ", list.currentValue());
	printf("\n");
	
	list.first();
	for(int i = 0; i < 5; i++)
	{
		printf("%d ", list.currentValue());
		list.next();
	}
	printf("\n");

	system("pause"); 
}