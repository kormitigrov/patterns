#include <iostream>
#include <stdio.h>

#include "shape.h"
#include "shape_array.h"

using namespace std;

// a concrete object - a point,
// descends from abstract CShape
class CPoint : public CShape
{
private:
	int _x,_y;
public:
	CPoint(int x, int y)
	{
		printf("CPoint::CPoint(int x, int y)\n");
		_x = x;
		_y = y;
	}
	// saving function first puts the line with
	// the code of the object, and then information
	void save(FILE *stream) override
	{
		printf("CPoint::save(FILE *stream)\n");
		
		fprintf(stream, "P\n");
		fprintf(stream, "%d %d\n", _x, _y);
	}
	// loading function reads the line with information
	// (line with the code of object should have been 
	// already read by that time by the factory)
	void load(FILE *stream) override
	{
		printf("CPoint::load(FILE *stream)\n");
		
		fscanf(stream, "%d %d\n", &_x, &_y);
		printf("_x=%d _y=%d\n", _x, _y);
	}
};

// a concrete object - a circle,
// descends from abstract CShape
class CCircle : public CShape
{
private:
	int _x,_y,_r;
public:
	CCircle(int x, int y, int r)
	{
		printf("CCircle::CCircle(int x, int y, int r)\n");
		_x = x;
		_y = y;
		_r = r;
	}
	// saving function first puts the line with
	// the code of the object, and then information
	void save(FILE *stream) override
	{
		printf("CCircle::save(FILE *stream)\n");
		fprintf(stream, "C\n");
		fprintf(stream, "%d %d %d\n", _x, _y, _r);
	}
	// loading function reads the line with information
	// (line with the code of object should have been 
	// already read by that time by the factory)
	void load(FILE *stream) override
	{
		printf("CCircle::load(FILE *stream)\n");
		fscanf(stream, "%d %d %d\n", &_x, &_y, &_r);
		printf("_x=%d _y=%d _r=%d\n", _x, _y, _r);
	}
};

// an extended version of CMyShapeArray, that inherits
// loadShapes, but OVERRIDES createShape. Thus this
// extended version will use inherited (old) version
// of method loadShapes. But when method loadShapes
// will call createShape (old one), that old createShape
// will call NOT the old version CShapeArray::createShape, 
// but the new version CMyShapeArray::createShape.
// Thus it will be able to load CCircles and CPoints
class CMyShapeArray : public CShapeArray
{
public:
	CShape *createShape(char code) override
	{
		CShape *shape = nullptr;
		switch (code)
		{
			case 'P':
				shape = new CPoint(0,0);
				break;
			case 'C':
				shape = new CCircle(0,0,0);
				break;
			default:;
		}
		return shape;
	}
};

void main()
{
	char *filename = "d:\\data.txt";
	FILE *stream;
	CShape *shape;

	// first, lets prepare the file with two objects

	if ((stream = fopen(filename, "w" )) != nullptr)
	{
		// write to the file the number of objects: 2
		fprintf(stream, "%d\n", 2);
		// create a shape, ask it to save itself
		// to the file and then delete it
		shape = new CPoint(10,20);
		shape->save(stream);
		delete shape;
		// create another shape, ask it to save itself
		// to the file and then delete it
		shape = new CCircle(30,40,5);
		shape->save(stream);
		delete shape;

		fclose(stream);
	}
	
	// now we are ready to test the reading of objects

	// create an array of shapes, but - THE KEY! - not
	// the old CShapeArray, but the new CMyShapeArray
	CMyShapeArray shapeArray;

	// ask the array of shapes to read shapes from the
	// file, using the factory to create them
	shapeArray.loadShapes(filename); 

	system("pause"); 
}