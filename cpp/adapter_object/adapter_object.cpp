#include <iostream>
#include <stdio.h>

using namespace std;

// an interface of an array
class IArray
{
public:
	// get the number of elements
	virtual int getCount() = 0;
	// get an element by index
	virtual int getValue(int index) = 0;
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
	int getCount() override
	{
		return _size;
	}
	int getValue(int index) override
	{
		return _values[index];
	}
	virtual ~CArray()
	{
		delete[] _values;
	}
};

// now, suppose we have another interface, IList
class IList
{
public:
	// move to the first element
	virtual void first() = 0;
	// get current value
	virtual int currentValue() = 0;
	// move to the next element
	virtual void next() = 0;
	// have we moved out of the elements in the list?
	virtual bool isEOL() = 0;
};

// the question is: if our program (a big program by that time) 
// is working with IList (is calling methods first, next, etc),
// and WE ALREADY HAVE an object of class CArray, 
// - can we still teach our program to work with this EXISTING object?

// we have to ADAPT CArray to the interface IList, but a little bit differently:

// an adapter class: it implements IList, AND STORES INSIDE A POINTER TO CArray
// that means, it stores inside a pointer to CArray, but it LOOKS like IList:
class CListAdapter : public IList
{
private:
	int _current_index;
	CArray *_arr;
public:
	CListAdapter(CArray *arr)
	{
		_arr = arr;
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
			return _arr -> getValue(_current_index);
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
		return _current_index == _arr -> getCount();
	}
	virtual ~CListAdapter()
	{
	}
};

void main()
{
	// lets suppose we have an object of CArray
	CArray arr(10);

	// we create CListAdapter and give it a pointer to CArray that we already have!
	// this CListAdapter works with the data, stored inside CArray, 
	// but for the rest of the program it LOOKS like IList
	CListAdapter list(&arr);

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