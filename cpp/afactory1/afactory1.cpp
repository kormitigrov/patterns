#include <iostream>

using namespace std;

// an abstract food
class CFood {
public:
	virtual void prepare() = 0;
	virtual ~CFood() { }
};

// an concrete food - a meat food
class CMeatFood : public CFood {
public:
	CMeatFood() {
		cout << "CMeatFood::CMeatFood()\n";
	}
	void prepare() override {
		cout << "CMeatFood::prepare()\n";
	}
};

// an concrete food - a vegetarian food
class CVegetarianFood : public CFood {
public:
	CVegetarianFood() {
		cout << "CVegetarianFood::CVegetarianFood()\n";
	}
	void prepare() override {
		cout << "CVegetarianFood::prepare()\n";
	}
};

//----------------------------

// an abstract food factory - an object, that can create abstract food
class CFoodFactory {
public:
	virtual CFood *createFood() = 0;
	virtual ~CFoodFactory() { }
};

// a concrete version of abstract food factory - 
// a concrete food factory that creates meat food
class CMeatFoodFactory : public CFoodFactory {
public:
	CMeatFoodFactory() {
		cout << "CMeatFoodFactory::CMeatFoodFactory()\n";
	}
	CFood *createFood() override {
		cout << "CMeatFoodFactory::createFood()\n";
		return new CMeatFood();
	}
};

// another concrete version of abstract food factory - 
// a concrete food factory that creates vegetarian food
class CVegetarianFoodFactory : public CFoodFactory {
public:
	CVegetarianFoodFactory() {
		cout << "CVegetarianFoodFactory::CVegetarianFoodFactory()\n";
	}
	CFood *createFood() override {
		cout << "CVegetarianFoodFactory::createFood()\n";
		return new CVegetarianFood();
	}
};

// just a sample class of a sample animal to feed
class CAnimal {
public:
	CAnimal() {
		cout << "CAnimal::CAnimal()\n";
	}
	virtual void feedWith(CFood *food) {
		cout << "CAnimal::feed()\n";
	}
	virtual ~CAnimal() { }
};

//----------------------------

void main() {
	// creating a factory of food - 
	// either CMeatFoodFactory or CVegetarianFoodFactory 
	CFoodFactory *factory;
	if (rand() % 2 == 0)
		factory = new CMeatFoodFactory();
	else
		factory = new CVegetarianFoodFactory();


	// some time after ... we do not know which concrete factory
	// we have; for us it is an abstract factory: something, that
	// can create food - that's all we know
	
	// so we may ask it to create food, and it will create 
	// either CMeatFood or CVegetarianFood - we do not know 
	// for certain, for us it is just food here
	
	CFood *food = factory->createFood();
	food->prepare();
	
	// lets create an animal and feed it
	CAnimal *student = new CAnimal();
	student->feedWith(food);

	delete food;
	delete factory;
	delete student;

	system("pause");
}