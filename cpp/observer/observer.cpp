#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

// an object is something being observed
class CObject;

// a simple object - an observer: someone, who should be
// notified when the something changes 
class CObserver {
public:
	virtual void onSubjectChanged(CObject *who) = 0;
	virtual ~CObserver() { }
};

// a simple object, that allows to be observed
class CObject {
private:
	// a private vector of current observers
	vector<CObserver*> _observers;
public:
	// a method to register an observer - that is, to say that a new observer 
	// now wants to be notified when the object changes
	void addObserver(CObserver *o) {
		_observers.push_back(o);
	}
	// a method that notifies all current observers
	void notifyEveryone() {
		for (const auto &o : _observers)
			o->onSubjectChanged(this);
	}
	virtual ~CObject()
	{ }
};

// an example of an object - an Animal in the Zoo,
class CAnimal : public CObject {
public:
	// last said phrase
	string lastsound;
	// animal name
	string name;
	// constructor
	CAnimal(string aname) {
		name = aname;
		lastsound = "";
	}
	// animal performs an action, and every observer is notified
	void say(string sound) {
		lastsound = sound;
		printf("\nCAnimal %s : '%s'\n", name.c_str(), sound.c_str());
		// notify every observer that is watching
		notifyEveryone();
	}
};

// an example of an observer - a child in the zoo, watching animals
class CChild : public CObserver {
public:
	// child name
	string name;
	// constructor
	CChild(string cname) {
		name = cname;
	}
	// a method which is called for a child when the animal changes,
	// the animal actually calls this method, passing itself as a parameter,
	// so the child not only knows THAT something has changed, but
	// also knows WHO was changed
	void onSubjectChanged(CObject *who) {
		printf("CChild %s : 'Hurray! %s had just said : %s'\n", name.c_str(), ((CAnimal*)who)->name.c_str(), ((CAnimal*)who)->lastsound.c_str());
	}
};

void main() {
	// create animals
	CAnimal cat("Zorra");
	CAnimal dog("Tortilla");
	CAnimal unknown("Cheburashka");
	
	// create children
	CChild vasya("Vasya");
	CChild petya("Petya");
	CChild kolya("Kolya");
	
	// assign who is watching (observing) who
	cat.addObserver(&vasya);
	cat.addObserver(&petya);
	dog.addObserver(&kolya);
	
	// check that when the animals change, children get notified;
	// the main idea of observer pattern is that objects can notify each
	// other indirectly, WITHOUT HARDCODING which objects exactly update which 
	cat.say("mew-mew!");
	dog.say("wow-wow!");
	cat.say("wow-wow!");
	dog.say("mew-mew!");
	unknown.say("nobody cares about me");

	system("pause"); 
}