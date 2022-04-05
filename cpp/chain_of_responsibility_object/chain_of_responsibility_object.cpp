#include <iostream>
#include <stdio.h>

using namespace std;

class Handler
{
public:
	virtual bool handle(int request) = 0;
	virtual ~Handler() 
	{
	}
};

class DivisionChecker : public Handler
{
private:
	int value;
	Handler *next;
public:
	DivisionChecker(int _value, Handler *_next) : value(_value), next(_next)
	{
	}
	bool handle(int request) override
	{
		if (request % value == 0)
			return true;
		else
			return next->handle(request);
	}
	~DivisionChecker() override
	{
		if (next != nullptr)
			delete next;
	}
};

class DefaultHandler : public Handler
{
public:
	bool handle(int request) override
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

	delete queue;
	
	system("pause");
}
