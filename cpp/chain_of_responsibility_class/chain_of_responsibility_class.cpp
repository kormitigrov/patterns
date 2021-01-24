#include <iostream>
#include <stdio.h>

using namespace std;

class Handler
{
public:
	virtual bool handle(int request) = NULL;
};

class DefaultHandler : public Handler
{
public:
	bool handle(int request)
	{
		printf("%d is prime\n", request);
		return false;
	}
};

class DivisionChecker2 : public DefaultHandler
{
public:
	bool handle(int request)
	{
		if ((request % 2 == 0) && (request != 2))
			return true;
		else
			return DefaultHandler::handle(request);
	}
};

class DivisionChecker3 : public DivisionChecker2
{
public:
	bool handle(int request)
	{
		if ((request % 3 == 0) && (request != 3))
			return true;
		else
			return DivisionChecker2::handle(request);
	}
};

class DivisionChecker5 : public DivisionChecker3
{
public:
	bool handle(int request)
	{
		if ((request % 5 == 0) && (request != 5))
			return true;
		else
			return DivisionChecker3::handle(request);
	}
};

class DivisionChecker7 : public DivisionChecker5
{
public:
	bool handle(int request)
	{
		if ((request % 7 == 0) && (request != 7))
			return true;
		else
			return DivisionChecker5::handle(request);
	}
};

class DivisionChecker11 : public DivisionChecker7
{
public:
	bool handle(int request)
	{
		if ((request % 11 == 0) && (request != 11))
			return true;
		else
			return DivisionChecker7::handle(request);
	}
};

void main()
{
	Handler *queue = new DivisionChecker11();

	for (int i = 2; i < 100; i++)
		queue->handle(i);

	system("pause");
}
