#include <iostream>
#include <stdio.h>

using namespace std;

class MultStrategy {
public:
	virtual double multiply(double *arr, int cnt) = 0;
};

class ForwardMultStrategy: public MultStrategy {
public:
	double multiply(double *arr, int cnt) override {
		double res = 1;
		for (int i = 0; i < cnt; i++)
			res = res * arr[i];
		return res;
	}
};

class BackwardMultStrategy: public MultStrategy {
public:
	double multiply(double *arr, int cnt) override {
		double res = 1;
		for (int i = cnt-1; i >= 0; i--)
			res = res * arr[i];
		return res;
	}
};

class Container {
private:
	int cnt;
	double *values;
public:
	MultStrategy *strategy;
	Container(int _cnt): cnt(_cnt) {
		values = new double[cnt];
		for (int i = 0; i < cnt; i++)
			values[i] = double(rand()) / RAND_MAX + 0.5;
		strategy = nullptr;
	}
	double get_product() {
		if (strategy != nullptr)
			return strategy->multiply(values, cnt);
		else
			return 0;
	}
	virtual ~Container() {
		delete[] values;
	}
};

void main() {
	
	Container container(10);

	container.strategy = new ForwardMultStrategy();
	printf("%f\n", container.get_product());
	delete container.strategy;

	container.strategy = new BackwardMultStrategy();
	printf("%f\n", container.get_product());
	delete container.strategy;

	
	system("pause"); 
}