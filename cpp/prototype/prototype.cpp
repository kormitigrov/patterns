#include <iostream>

using namespace std;

class CAnimal
{
public:
	// virtual function clone, which clones nothing
	virtual CAnimal *clone() = NULL;
};

class CDog : public CAnimal
{
public:
	// virtual function clone, which returns a copy of CDog
	virtual CAnimal *clone()
	{
		cout << "CDog::clone()\n";
		return new CDog();
	}
};

class CCat : public CAnimal
{
public:
	// virtual function clone, which returns a copy of CCat
	virtual CAnimal *clone()
	{
		cout << "CCat::clone()\n";
		return new CCat();
	}
};

void main()
{
	// creating prototypes
	CAnimal *cage[2] = {new CCat(), new CDog()};

	// some time after ... we do not know which concrete object
	// resides in which cage, but we can create a copy of each

	CAnimal *newAnimal1 = cage[0]->clone(); // CCat created
	CAnimal *newAnimal2 = cage[1]->clone(); // CDog created

	system("pause");
}