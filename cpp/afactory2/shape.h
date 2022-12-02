#ifndef _SHAPE_H
#define _SHAPE_H

// abstract shape
class CShape {
public:
	virtual void save(FILE *stream) = 0;
	virtual void load(FILE *stream) = 0;
	virtual ~CShape() { }
};

// an abstract factory - something, that can create shapes by the code
class CShapeFactory {
public:
	// a abstract function, that can be used to create
	// a shape, given its code 
	virtual CShape *createShape(char code) = 0;
	virtual ~CShapeFactory() { }
};

#endif  // _SHAPE_H