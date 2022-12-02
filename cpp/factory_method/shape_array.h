#ifndef _SHAPE_ARRAY_H
#define _SHAPE_ARRAY_H

// shape array includes only shape.h, so it knows only
// about abstract abstract shape, but it DOES NOT
// know anything about CCircle or CPoint
#include "shape.h"
#include <vector>

using namespace std;

// class that contains an array of abstract shapes, some
// of which could be CCircles or CPoints, but CShapeArray
// knows them only as CShapes
class CShapeArray {
private:
	vector<CShape*> shapes;
public:
	// A virtual function that knows how to create objects 
	// by their code. That is indeed a factory method. It 
	// is empty here, so CShapeArray can NOT create CCircles 
	// and CPoints. However, if a DESCENDANT class CShapeArrayMy
	// overrides this function with the one, that knows how
	// to create CCircles and CPoints, method loadShapes
	// will automatically be able to load them
	virtual CShape *createShape(char code) {
		return nullptr;
	}
	// a function that loads an array of shapes from file
	// it requires a filename only. It uses a method createShape
	// that SHOULD know how to create CCircles and CPoints.
	void loadShapes(string filename) {
		FILE *stream;
		int count;
		// open the file for reading
		if ((stream = fopen(filename.c_str(), "r")) != nullptr) {
			char code;
			CShape *shape;
			// read the number of objects in the file
			fscanf(stream, "%d\n", &count);
			
			// for every shape to read
			for (int i = 0; i < count; i++) {
				// read the code, the line that explains
				// what concrete object (CCircle or CPoint)
				// should be read from the file
				fscanf(stream, "%c\n", &code);
				// ask the factory method to create the object
				// by the code from the file
				shape = createShape(code);
				// the factory method will in fact create either
				// CCircle or CPoint, but here we do not
				// know the concrete type, because we receive
				// it as a pointer to CShape
				if (shape != nullptr) {
					// if the object has been created, ask it
					// to read itself from the file and push it to the vector
					shape->load(stream);
					shapes.push_back(shape);
				}
			}
			fclose(stream);
		}
	}
	virtual ~CShapeArray() {
		for (const auto &s : shapes)
			delete s;
	}
};

#endif  // _SHAPE_ARRAY_H
