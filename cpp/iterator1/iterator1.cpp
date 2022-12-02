#include <iostream>
#include <stdio.h>
#include <list>

using namespace std;

// a container is something that contains values.
// when we are working with many containers (arrays, lists, trees,
// hash tables, etc.), it is useful to have one common interface
// to access them all. lets define such an interface and call it CIterator

// an abstract iterator - something, that allows to retrieve 
// values from any container sequentially
class CIterator {
public:
	// move to the first element
	virtual void first() = 0;
	// get current element
	virtual int getCurrentItem() = 0;
	// set current element
	virtual void setCurrentItem(int item) = 0;
	// move to the next element
	virtual void next() = 0;
	// have we moved out of the elements in the container?
	virtual bool isEOL() = 0;
	virtual ~CIterator() { }
};

// a real concrete container, an array in this case.
// note, it actuall has its own interface for accessing data
// (methods getCount, getValue and setValue), but we want to 
// access it using methods CIterator, so we'll make our program 
// more flexible to future changes (if in the future we would need
// to replace and array with, say, a hash table).
class CArray {
private:
	int *_values;
	int _size;
public:
	CArray(int size) {
		_size = size;
		_values = new int[_size];
	}
	int getCount() {
		return _size;
	}
	int getValue(int index) {
		return _values[index];
	}
	void setValue(int index, int item) {
		_values[index] = item;
	}
	// one way would be just to derive CArray from CIterator and to
	// implement methods of CIterator here, but it's not the best way.
	// an array may have MULTIPLE iterators. Thus we teach an array to
	// supply us an appropriate iterator, given the type we want.
	CIterator *createIterator(string);
	virtual ~CArray() {
		delete[] _values;
	}
};

// an array may have multiple iterators, to iterate values in the array 
// in many different ways: in direct order, in reversed order, etc.  

// CRegularArrayIterator is an iterator, that iterates all possible 
// values in the array, while

// CPositiveOnlyArrayIterator iterates only possible values in the 
// array


// iterator that returns all values in the array
class CRegularArrayIterator : public CIterator {
private:
	// an array iterator holds a link to CArray
	CArray *_arr;
	// and an internal counter of the current element
	int _current_index;
public:
	CRegularArrayIterator(CArray *arr) {
		_arr = arr;
		_current_index = 0;
	}
	void first() override {
		_current_index = 0;
	}
	int getCurrentItem() override {
		if (!isEOL())
			return _arr->getValue(_current_index);
		else
			return 0;
	}
	void setCurrentItem(int item) override {
		if (!isEOL())
			_arr->setValue(_current_index, item);
	}
	void next() override {
		if (!isEOL())
			_current_index++;
	}
	bool isEOL() override {
		return _current_index == _arr->getCount();
	}
};

// iterator that returns only positive values in the array
class CPositiveOnlyArrayIterator : public CIterator {
private:
	// an array iterator holds a link to CArray
	CArray *_arr;
	// and an internal counter of the current element
	int _current_index;
public:
	CPositiveOnlyArrayIterator(CArray *arr) {
		_arr = arr;
		_current_index = 0;
	}
	void first() override {
		_current_index = 0;
		while (!isEOL() && getCurrentItem() < 0) {
			_current_index++;
		}
	}
	int getCurrentItem() override {
		if (!isEOL())
			return _arr->getValue(_current_index);
		else
			return 0;
	}
	void setCurrentItem(int item) override {
		if (!isEOL())
			_arr->setValue(_current_index, item);
	}
	void next() override {
		if (!isEOL())
			_current_index++;
		while (!isEOL() && getCurrentItem() < 0) {
			_current_index++;
		}
	}
	bool isEOL() override {
		return _current_index == _arr->getCount();
	}
};

// an implementation for CArray :: createIterator method:
// depending on the string 'type' given, create either
// one iterator, or another
CIterator* CArray :: createIterator(string type) {
	if (type == "REGULAR")
		return new CRegularArrayIterator(this);
	else if (type == "POSITIVEONLY")
		return new CPositiveOnlyArrayIterator(this);
	else
		throw "Wrong iterator type!";
}

void main() {
	
	// lets create an array
	CArray arr(10);

	// we have created a container, lets work with it:

	// lets fill the array with values:
	for (int i = 0; i < arr.getCount(); i++) {
		arr.setValue(i, rand() - RAND_MAX / 2);
	}

	// we have used specific methods of an array,
	// getCount and setValue. It's not very good, because it we
	// replace array with a tree, or with a hash table, we'll
	// have to rewrite the code that works with the array.

	// a much better way of working with an array would be to
	// ask it to create an iterator, for instance, CRegularArrayIterator:

	CIterator *it = arr.createIterator("REGULAR");
	
	// now we may use standard methods of CIterator to access 
	// elements of our container; 
	for(it->first(); !it->isEOL(); it->next()) {
		printf("%d ", it->getCurrentItem());
	}
	printf("\n");
	
	// but we can also create another iterator, if we want to access
	// values in the array in some other way; for instance, we may
	// want to iterate values in the array in reversed order (from
	// last to first), or we may want to iterate through only positive
	// values in the array:

	CIterator *it2 = arr.createIterator("POSITIVEONLY");
	
	// again, iterate and access
	for(it2->first(); !it2->isEOL(); it2->next()) {
		printf("%d ", it2->getCurrentItem());
	}
	printf("\n");

	// delete iterators
	delete it;
	delete it2;

	//list<int> values(10);
	//list<int>::iterator i;
	//for (i = values.begin(); i != values.end(); i++)
	//	*i = rand();

	system("pause"); 
}