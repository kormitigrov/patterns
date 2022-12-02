#include <iostream>

using namespace std;

// исходная ситуация: два класса с почти идентичным методом
class BeforeX {
public:
	void TemplateMethod() {
		printf("1\n");
		printf("2\n");
		printf("hello\n");
		printf("4\n");
		printf("5\n");
	}
};
class BeforeY {
public:
	void TemplateMethod() {
		printf("1\n");
		printf("2\n");
		printf("world\n");
		printf("4\n");
		printf("5\n");
	}
};
class BeforeZ {
public:
	void TemplateMethod() {
		printf("1\n");
		printf("2\n");
		printf("!!!\n");
		printf("4\n");
		printf("5\n");
	}
};
// решение проблемы повторяемого кода - вынесение шаблонного метода в 
// родительский класс и выделение изменяемой части в отдельный метод
class AfterBase {
public:
	virtual void doSpecific() { }
	void TemplateMethod() {
		printf("1\n");
		printf("2\n");
		this->doSpecific();
		printf("4\n");
		printf("5\n");
	}
};

class AfterX : public AfterBase {
public:
	void doSpecific() override {
		printf("hello\n");
	}
};
class AfterY : public AfterBase {
public:
	void doSpecific() override {
		printf("world\n");
	}
};
class AfterZ : public AfterBase {
public:
	void doSpecific() override {
		printf("!!!\n");
	}
};

void main() {
	printf("\nBEFORE\n");
	BeforeX *bx = new BeforeX();
	BeforeY *by = new BeforeY();
	BeforeZ *bz = new BeforeZ();
	bx->TemplateMethod();
	by->TemplateMethod();
	bz->TemplateMethod();

	printf("\nAFTER\n");
	AfterX *ax = new AfterX();
	AfterY *ay = new AfterY();
	AfterZ *az = new AfterZ();
	ax->TemplateMethod();
	ay->TemplateMethod();
	az->TemplateMethod();

	delete bx;
	delete by;
	delete bz;
	delete ax;
	delete ay;
	delete az;

	system("pause");
}