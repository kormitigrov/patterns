#ifndef _SHAPE_ARRAY_H
#define _SHAPE_ARRAY_H

// shape array includes only shape.h, so it knows only
// about abstract abstract shape, but it DOES NOT
// know anything about CCircle or CPoint
#include "shape.h"

// class that contains an array of abstract shapes, some
// of which could be CCircles or CPoints, but CShapeArray
// knows them only as CShapes
class CShapeArray
{
private:
	int count;
	CShape **_shapes;
public:
	// A virtual function that knows how to create objects 
	// by their code. That is indeed a factory method. It 
	// is empty here, so CShapeArray can NOT create CCircles 
	// and CPoints. However, if a DESCENDANT class CShapeArrayMy
	// overrides this function with the one, that knows how
	// to create CCircles and CPoints, method loadShapes
	// will automatically be able to load them
	virtual CShape *createShape(char code)
	{
		return nullptr;
	}
	// a function that loads an array of shapes from file
	// it requires a filename only. It uses a method createShape
	// that SHOULD know how to create CCircles and CPoints.
	void loadShapes(char *filename)
	{
		FILE *stream;
		// open the file for reading
		if ((stream = fopen(filename, "r" )) != nullptr)
		{
			char code;
			
			// read the number of objects in the file
			fscanf(stream, "%d\n", &count);
			// allocate the memory for the array of shapes
			_shapes = new CShape*[count];
			
			// for every shape to read
			for (int i = 0; i < count; i++)
			{
				// read the code, the line that explains
				// what concrete object (CCircle or CPoint)
				// should be read from the file
				fscanf(stream, "%c\n", &code);
				// ask the factory method to create the object
				// by the code from the file
				_shapes[i] = createShape(code);
				// the factory method will in fact create either
				// CCircle or CPoint, but here we do not
				// know the concrete type, because we receive
				// it as a pointer to CShape
				if (_shapes[i] != nullptr)
				{
					// if the object has been created, ask it
					// to read itself from the file
					_shapes[i]->load(stream);
				}
			}
			fclose(stream);
		}
	}
	virtual ~CShapeArray()
	{
		for (int i = 0; i < count; i++)
			delete (_shapes[i]);
		delete[] _shapes;
	}
};

#endif  // _SHAPE_ARRAY_H
