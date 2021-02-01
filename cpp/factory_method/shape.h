#ifndef _SHAPE_H
#define _SHAPE_H

// abstract shape
class CShape
{
public:
	virtual void save(FILE *stream) = 0;
	virtual void load(FILE *stream) = 0;
	virtual ~CShape()
	{
	}
};

#endif  // _SHAPE_H
