#ifndef _SHAPE_ARRAY_H
#define _SHAPE_ARRAY_H

// shape array includes only shape.h, so it knows about
// abstract factory and abstract shape, but it DOES NOT
// know anything about CCircle or CPoint
#include "shape.h"

// class that contains an array of abstract shapes, some
// of which could be CCircles or CPoints, but CShapeArray
// knows them only as CShapes
class CShapeArray
{
private:
	CShape **_shapes;
public:
	// a function that loads an array of shapes from file
	// it requires a filename - AND a factory:
	// CShapeArray CAN NOT create CCircles and CPoints, it
	// does not know about them. So it requires an object
	// that KNOWS how to create CCircles and CPoints.
	// that mechanism is a factory.
	void loadShapes(char *filename, CShapeFactory *factory)
	{
		FILE *stream;
		// open the file for reading
		if ((stream = fopen(filename, "r" )) != NULL)
		{
			int count;
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
				// ask the factory to create the object
				// by the code from the file
				_shapes[i] = factory->createShape(code);
				// the factory will in fact create either
				// CCircle or CPoint, but here we do not
				// know the concrete type, because we receive
				// it as a pointer to CShape
				if (_shapes[i] != NULL)
				{
					// if the object has been created, ask it
					// to read itself from the file
					_shapes[i]->load(stream);
				}
			}
			fclose(stream);
		}
	}
};

#endif  // _SHAPE_ARRAY_H
