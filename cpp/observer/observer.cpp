#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

// a subject is something being observed
class CSubject;

// a simple object - an observer: someone, who should be
// notified when the something changes 
class CObserver
{
public:
	virtual void onSubjectChanged(CSubject *who) = NULL;
};

// a simple object, that allows to be observed
class CSubject
{
private:
	// a private vector of current observers
	vector<CObserver*> *_observers;
public:
	// a constructor
	CSubject()
	{
		// create an empty collection of observers (nobody is watching)
		_observers = new vector<CObserver*>;
	}
	// a method to register an observer - that is, to say that a new observer 
	// now wants to be notified when the object changes
	void addObserver(CObserver *o)
	{
		_observers -> push_back(o);
	}
	// a method that notifies all current observers
	void notifyEveryone()
	{
		 for (vector<CObserver*>::iterator i = _observers->begin(); i != _observers->end(); i++)
			(*i) -> onSubjectChanged(this);
	}
};

// an example of a subject - an Animal in the Zoo,
class CAnimal : public CSubject
{
public:
	// last said phrase
	char *lastsound;
	// animal name
	char *name;
	// constructor
	CAnimal(char *aname)
	{
		name = aname;
		lastsound = "";
	}
	// animal performs an action, and every observer is notified
	void say(char *sound)
	{
		lastsound = sound;
		printf("\nCAnimal %s : '%s'\n", name, sound);
		// notify every observer that is watching
		notifyEveryone();
	}
};

// an example of an observer - a child in the zoo, watching animals
class CChild : public CObserver
{
public:
	// child name
	char *name;
	// constructor
	CChild(char *cname)
	{
		name = cname;
	}
	// a method which is called for a child when the animal changes,
	// the animal actually calls this method, passing itself as a parameter,
	// so the child not only knows THAT something has changed, but
	// also knows WHO was changed
	void onSubjectChanged(CSubject *who)
	{
		printf("CChild %s : 'Hurray! %s had just said : %s'\n", name, ((CAnimal*)who) -> name, ((CAnimal*)who) -> lastsound);
	}
};

void main()
{
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