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

#endif  // _SHAPE_H
