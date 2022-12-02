#include <iostream>

using namespace std;

class Zoo {
protected:
	// protected constructor (not available to everyone)
	Zoo() {
		cout << "Zoo::Zoo()\n";
	}
public:
	// a function, returning the only existing copy of Zoo
	static Zoo &get_instance() {
		static Zoo zoo;
		return zoo;
	}
	// just a function
	void do_something() {
		cout << "Zoo::do_something()\n";
	}
};

void main() {

	// we can not create objects of class Zoo,
	// so we can not by mistake create several copies
	//Zoo *zoo1 = new Zoo(); // error! not available
	//Zoo *zoo2 = new Zoo(); // error! not available
	
	// instead, we can use can use get_instance(), that\
	// always creates the same copy of Zoo,
	// note that is was created here with the first call
	Zoo::get_instance().do_something();
	
	// note that is was NOT created here again, only accessed
	Zoo::get_instance().do_something();

	system("pause");
}