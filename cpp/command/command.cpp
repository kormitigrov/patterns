#include <conio.h>
#include <map>
#include <stack>

using namespace std;

// an CPoint, whos state we will change and unchange back
class CPoint
{
private:
	// data of CPoint
	int _x,_y;
public:
	CPoint(int x, int y)
	{
		printf("CPoint::CPoint(int x, int y)\n");
		_x = x; _y = y;
	}
	// a method to change the state of the object
	void move(int dx, int dy)
	{
		_x = _x + dx; _y = _y + dy;
	}
	// a method to report the state of the object
	void report()
	{
		printf("CPoint is: %d %d\n", _x, _y);
	}
	virtual ~CPoint()
	{
	}
};

// an abstract command, that may be performed on a selected CPoint
class Command
{
public:
	// every command has a main method 'execute'
	// that should perform an action on the selected CPoint
	virtual void execute(CPoint *selection) = 0;
	// every point has as well the method 'unexecute'
	// that should undo an action
	virtual void unexecute() = 0;
	// every command can be cloned
	virtual Command *clone() = 0;
	virtual ~Command() 
	{
	};
};

// a concrete command, that moves the point
class MoveCommand : public Command
{
private:
	// the command remembers the selection (the point) it was performed for
	CPoint *_selection;
	// the command also remembers where the point was moved
	int _dx; int _dy;
	// these two properties are all information necessary to undo the command
public:
	// the command is created with dx and dy - that's because we do not
	// want to create distinct commands MoveLeftCommand, MoveRightCommand,
	// MoveUpCommand and MoveDownCommand, - though, we could have.
	MoveCommand(int dx, int dy) 
	{
		printf("MoveCommand::MoveCommand(%d, %d)\n", dx, dy);
		_dx = dx;
		_dy = dy;
		_selection = nullptr;
	}
	// when the command executes, it moves the selection
	virtual void execute(CPoint *selection)
	{
		printf("MoveCommand::execute(CPoint *selection)\n");
		// remember the selection the command was applied to
		_selection = selection;
		// if it is not empty, call method move of the point
		if (_selection != nullptr)
		{
			_selection -> move(_dx, _dy);
		}
	}
	// when the command should be undone, it just inverse-moves the
	// selection back
	virtual void unexecute()
	{
		printf("MoveCommand::unexecute()\n");
		if (_selection != nullptr)
		{
			_selection -> move(-_dx, -_dy);
		}
	}
	// cloning means creating new instance of the same command
	virtual Command *clone()
	{
		printf("MoveCommand::clone()\n");
		return new MoveCommand(_dx, _dy);
	}
	~MoveCommand() override
	{
		printf("MoveCommand::~MoveCommand()\n");
	}
};

// ------------------------------------------------------------

void main()
{
	printf("Move the point with keys: 'a', 'd', 'w', 's'\n");
	printf("Undo last action with key: 'z'\n\n");

	// lets create the list of commands, that is going to be an
	// associative array (map), which maps a key pressed (a char)
	// to the particular command
	map<char,Command*> commands;
	commands['a'] = new MoveCommand(-10,0);
	commands['d'] = new MoveCommand(10,0);
	commands['w'] = new MoveCommand(0,-10);
	commands['s'] = new MoveCommand(0,10);

	// create a CPoint
	CPoint *selection = new CPoint(0,0);
	// ask a CPoint to report its current state
	selection -> report();
	
	// to do 'undo' we also need a history of commands performed,
	// that will be a stack - the last command performed would be 
	// the first command to undo
	stack<Command*> history;
	
	char key;
	do
	{
		// get the next key pressed
		key = _getch(); 
		// take the command, associated with key, if there is one
		Command *command = commands[key];
		// if there IS a command, associated with a key
		if (command != nullptr)
		{
			// clone a command - we need to add it to history stack,
			// so we need a copy of the original command
			Command *newcommand = command->clone();
			// execute a command on a current selection
			newcommand->execute(selection);
			// push a command into a history stack
			history.push(newcommand);
		}
		
		// if the key 'z' is pressed and history stack is not empty
		// we should undo the last command performed
		if (key == 'z' && !history.empty())
		{
			// get the last command
			Command *lastcommand = history.top();
			// unexecute it
			lastcommand -> unexecute();
			// delete it (it was a copy)
			delete lastcommand;
			// remove it from the stack
			history.pop();
		}
		
		// ask a CPoint to report its current state
		selection -> report();

	} while (key != 27);

	while (!history.empty())
	{
		delete history.top();
		history.pop();
	}

	delete commands['a'];
	delete commands['d'];
	delete commands['w'];
	delete commands['s'];

	delete selection;

	system("pause");
}