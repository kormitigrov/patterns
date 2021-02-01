#include <iostream>
#include <stdio.h>

using namespace std;

// just a pre-declaration of the class, to be defined later
template <class Item> class CIterator;

// an abstract container - something that contains elements,
// but how it stores them in not defined: the container does not
// expose its structure. the only way to access elements in the
// container is to ask it for an iterator
template <class Item>
class CContainer
{
public:
	// the abstract container can only create an iterator,
	// which can be used to access its elements
	virtual CIterator<Item> *createIterator() = 0;
	virtual ~CContainer()
	{
	}
};

// an abstract iterator - something, that allows to retrieve 
// objects from the container sequentially
template <class Item>
class CIterator
{
public:
	// move to the first element
	virtual void first() = 0;
	// get current element
	virtual Item getCurrentItem() = 0;
	// set current element
	virtual void setCurrentItem(Item item) = 0;
	// move to the next element
	virtual void next() = 0;
	// have we moved out of the elements in the list?
	virtual bool isEOL() = 0;
	virtual ~CIterator()
	{
	}
};


// just a pre-declaration of the class, to be defined later
template <class Item> class CArrayIterator;

// a real concrete container, an array in this case,
// which allows to get the number of elements and to
// access (get or set) random element:
// note, it is NOT the the same way as to access with CIterator 
template <class Item>
class CArray : public CContainer<Item>
{
private:
	Item *_values;
	int _size;
public:
	CArray(int size)
	{
		_size = size;
		_values = new Item[_size];
	}
	virtual int getCount()
	{
		return _size;
	}
	virtual Item getValue(int index)
	{
		return _values[index];
	}
	virtual void setValue(int index, Item item)
	{
		_values[index] = item;
	}
	// of course, we may work with CArray directly through getValue and setValue
	// if we know that it is CArray, and not merely CContainer, but another way
	// to access data is to retrieve an iterator first, and access through it
	virtual CIterator<Item> *createIterator()
	{
		// a CArray known which iterator can access its data and creates it here
		return new CArrayIterator<Item>(this);
	}
	virtual ~CArray()
	{
		delete[] _values;
	}
};

// a concrete array iterator - something, that can retrieve elements from the
// concrete CArray sequentially, the way it is defined by CIterator
template <class Item>
class CArrayIterator : public CIterator<Item>
{
private:
	// an array iterator holds a link to CArray
	CArray<Item> *_arr;
	// and an internal counter of the current element
	int _current_index;
public:
	CArrayIterator(CArray<Item> *arr)
	{
		_arr = arr;
		_current_index = 0;
	}
	void first() override
	{
		_current_index = 0;
	}
	Item getCurrentItem() override
	{
		if (!isEOL())
			return _arr->getValue(_current_index);
		else
			return 0;
	}
	void setCurrentItem(Item item) override
	{
		if (!isEOL())
			_arr->setValue(_current_index, item);
	}
	void next() override
	{
		if (!isEOL())
			_current_index++;
	}
	bool isEOL() override
	{
		return _current_index == _arr->getCount();
	}
};

void main()
{
	// lets create an array of 'ints'
	CArray<int> arr(10);

	// knowing that we have created CArray, we can manually 
	// create an appropriate iterator, that is CArrayIterator:

	// CArrayIterator<int> *i = new CArrayIterator<int>(&arr);

	// but it's not very good, - we'd better ask an array itself
	// to create an appropriate iterator for us - thus we do not
	// have to know to what real container class 'arr' belongs to

	CIterator<int> *i = arr.createIterator();

	// now we may use standard methods of CIterator to access 
	// elements of our container; here we know nothing about
	// exact class of 'arr' and 'i' - for us here it's just
	// an abstract container and abstract class
	for (i->first(); !i->isEOL(); i->next())
	{
		i->setCurrentItem(rand());
	}

	// again, iterate and access
	for (i->first(); !i->isEOL(); i->next())
	{
		printf("%d ", i->getCurrentItem());
	}
	printf("\n");

	// delete iterator
	delete i;

	system("pause");
}