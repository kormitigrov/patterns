#include <iostream>
#include <stdio.h>

using namespace std;

class Handler
{
public:
	virtual bool handle(int request) = NULL;
};

class DivisionChecker : public Handler
{
private:
	int value;
	Handler *next;
public:
	DivisionChecker(int _value, Handler *_next)
	{
		value = _value;
		next = _next;
	}
	bool handle(int request)
	{
		if (request % value == 0)
			return true;
		else
			return next->handle(request);
	}
};

class DefaultHandler : public Handler
{
	bool handle(int request)
	{
		printf("%d is prime\n", request);
		return false;
	}
};

void main()
{
	Handler *queue = new DefaultHandler;

	for (int i = 2; i < 100; i++)
		if (queue->handle(i) == false)
			queue = new DivisionChecker(i, queue);

	system("pause");
}
