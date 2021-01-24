#ifndef _SHAPE_H
#define _SHAPE_H

// abstract shape
class CShape
{
public:
	// 
	virtual void save(FILE *stream) = NULL;
	virtual void load(FILE *stream) = NULL;
};

// an abstract factory - something, that can create shapes by the code
class CShapeFactory
{
public:
	// a abstract function, that can be used to create
	// a shape, given its code 
	virtual CShape *createShape(char code) = NULL;
};

#endif  // _SHAPE_H
