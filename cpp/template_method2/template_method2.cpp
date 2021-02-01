#include <iostream>

using namespace std;

// исходная ситуация: два класса с почти идентичным методом
class BeforeX
{
public:
	void TemplateMethod()
	{
		printf("1\n");
		printf("2\n");
		printf("hello\n");
		printf("4\n");
		printf("5\n");
	}
};
class BeforeY
{
public:
	void TemplateMethod()
	{
		printf("1\n");
		printf("2\n");
		printf("world\n");
		printf("4\n");
		printf("5\n");
	}
};

// решение проблемы повторяемого кода - вынесение шаблонного метода в 
// родительский класс и выделение изменяемой части в отдельный метод
class AfterZ
{
public:
	virtual void doSpecific()
	{
	}
	void TemplateMethod()
	{
		printf("1\n");
		printf("2\n");
		doSpecific();
		printf("4\n");
		printf("5\n");
	}
};
class AfterX : public AfterZ
{
public:
	void doSpecific()
	{
		printf("hello\n");
	}
};
class AfterY : public AfterZ
{
public:
	void doSpecific()
	{
		printf("world\n");
	}
};

void main()
{
	printf("\nBEFORE\n");
	BeforeX *bx = new BeforeX();
	BeforeY *by = new BeforeY();
	bx->TemplateMethod();
	by->TemplateMethod();

	printf("\nAFTER\n");
	AfterX *ax = new AfterX();
	AfterY *ay = new AfterY();
	ax->TemplateMethod();
	ay->TemplateMethod();

	delete bx;
	delete by;
	delete ax;
	delete ay;

	system("pause");
}