#include <iostream>

using namespace std;

class Animal
{
public:
	// virtual function clone, which clones nothing
	virtual Animal *clone() = 0;
	virtual ~Animal() { };
};

class Dog : public Animal
{
public:
	// virtual function clone, which returns a copy of Dog
	Animal *clone() override
	{
		cout << "Dog::clone()\n";
		return new Dog(*this);
	}
};

class Cat : public Animal
{
public:
	// virtual function clone, which returns a copy of Cat
	Animal *clone() override
	{
		cout << "Cat::clone()\n";
		return new Cat(*this);
	}
};

void main()
{
	// creating prototypes
	Animal *cages[2] = {new Cat(), new Dog()};

	// some time after ... we do not know which concrete object
	// resides in which cage, but we can create a copy of each

	Animal *newAnimal1 = cages[0]->clone(); // Cat created
	Animal *newAnimal2 = cages[1]->clone(); // Dog created

	delete newAnimal1;
	delete newAnimal2;

	delete cages[0];
	delete cages[1];

	system("pause");
}