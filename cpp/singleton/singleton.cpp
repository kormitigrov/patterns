#include <iostream>

using namespace std;

class CZoo
{
private:
	// a private static variable that holds the only 
	// existing copy of CZoo 
	static CZoo *_zoo;
protected:
	// protected constructor (not available to everyone)
	CZoo()
	{
		cout << "CZoo::CZoo()\n";
	}
public:
	// a function, returning the only existing copy of CZoo
	static CZoo *getInstance()
	{
		if (_zoo == nullptr)
			_zoo = new CZoo();
		return _zoo;
	}
	// just a function
	void doSomething()
	{
		cout << "CZoo::doSomething()\n";
	}
};
// a static variable is initialized to nullptr
CZoo *CZoo::_zoo = nullptr;

//----------------------------

void main()
{
	// we can not create objects of class CZoo,
	// so we can not by mistake create several copies
	//CZoo *zoo1 = new CZoo(); // error! not available
	//CZoo *zoo2 = new CZoo(); // error! not available
	
	// instead, we can use can use getInstance(), that\
	// always creates the same copy of CZoo,
	// note that is was created here with the first call
	CZoo::getInstance()->doSomething();
	
	// note that is was NOT created here again, only accessed
	CZoo::getInstance()->doSomething();

	system("pause");
}