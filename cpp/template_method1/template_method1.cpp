#include <iostream>

using namespace std;

// just an abstract object
class CObject
{
public:
	virtual ~CObject()
	{
	}
};

// just an array to store abstract objects
class CObjectArray
{
public:
	// number of values stored
	int _count;
	// actual pointers storage array
	CObject **_objects;
	// constructor
	CObjectArray(int count)
	{
		_count = count;
		_objects = new CObject*[_count];
		for (int i = 0; i < _count; i++)
			_objects[i] = nullptr;
	}
	// a virtual function to compare two objects, 
	// it is used later by a template method
	virtual int compare(CObject *ob1, CObject *ob2)
	{
		return 0;
	}
	// a template method - a sorting algorithm,
	// that works in terms of primitive operations
	// like 'compare'. It behaves differetly, depending
	// on the actual 'compare' behavior in subclasses,
	// but follows the same 'template'
	void sort()
	{
		CObject *tmp;
		for (int i = 0; i < _count-1; i++)
			for (int j = i+1; j < _count; j++)
				if (compare(_objects[i],_objects[j]) == -1)
				{
					tmp = _objects[i];
					_objects[i] = _objects[j];
					_objects[j] = tmp;
				}
	}
	// destructor
	~CObjectArray()
	{
		// iterate through all objects and delete them
		for (int i = 0; i < _count; i++)
			if (_objects[i] != nullptr)
				delete (_objects[i]);
		// deallocate the memory
		delete[] _objects;
	}
};

// just a number, deriving from CObject
class CNumber : public CObject
{
public:
	int _value;
};

// an array of numbers, deriving from CObjectArray
class CNumberArray : public CObjectArray
{
public:
	// a constructor
	CNumberArray(int count) : CObjectArray(count) {}
	// the actual function compare, that lets CNumberArray to
	// use inherited template method to sort its numbers 
	virtual int compare(CObject *ob1, CObject *ob2)
	{
		if (((CNumber*)ob2)->_value > ((CNumber*)ob1)->_value)
			return 1;
		else if (((CNumber*)ob2)->_value < ((CNumber*)ob1)->_value)
			return -1;
		else
			return 0;
	}
};

void main()
{
	// create an array and fill it
	{ CNumberArray arr(10);

	for (int i = 0; i < arr._count; i++)
	{
		CNumber *number = new CNumber();
		number->_value = rand();
		arr._objects[i] = number;
	}

	// call sorting procedure and check the results
	arr.sort();

	for (int i = 0; i < arr._count; i++)
		printf("%d ", ((CNumber*)arr._objects[i])->_value);
	printf("\n");
	}

	system("pause");
}