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
		return new Dog();
	}
};

class Cat : public Animal
{
public:
	// virtual function clone, which returns a copy of Cat
	Animal *clone() override
	{
		cout << "Cat::clone()\n";
		return new Cat();
	}
};

void main()
{
	// creating prototypes
	Animal *cage[2] = {new Cat(), new Dog()};

	// some time after ... we do not know which concrete object
	// resides in which cage, but we can create a copy of each

	Animal *newAnimal1 = cage[0]->clone(); // Cat created
	Animal *newAnimal2 = cage[1]->clone(); // Dog created

	delete newAnimal1;
	delete newAnimal2;

	delete cage[0];
	delete cage[1];

	system("pause");
}