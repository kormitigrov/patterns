#include <iostream>
#include <stdio.h>

using namespace std;

const int cnt = 10;

class MultStrategy
{
public:
	virtual double multiply(double *arr) = 0;
};

class ForwardMultStrategy: public MultStrategy
{
public:
	double multiply(double *arr) override
	{
		double res = 1;
		for (int i = 0; i < cnt; i++)
			res = res * arr[i];
		return res;
	}
};

class BackwardMultStrategy: public MultStrategy
{
public:
	double multiply(double *arr) override
	{
		double res = 1;
		for (int i = cnt-1; i >= 0; i--)
			res = res * arr[i];
		return res;
	}
};

class Container
{
private:
	double values[cnt];
public:
	MultStrategy *strategy;
	Container()
	{
		for (int i = 0; i < cnt; i++)
			values[i] = double(rand()) / RAND_MAX + 0.5;
		strategy = nullptr;
	}
	double get_product()
	{
		if (strategy != nullptr)
			return strategy->multiply(values);
		else
			return 0;
	}
};

void main()
{
	
	Container container;

	container.strategy = new ForwardMultStrategy();
	printf("%f\n", container.get_product());
	delete container.strategy;

	container.strategy = new BackwardMultStrategy();
	printf("%f\n", container.get_product());
	delete container.strategy;

	
	system("pause"); 
}