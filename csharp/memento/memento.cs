using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Memento
{

	// a memento - something that be used to store and retrieve a state of CPoint
	class CMemento
	{
		// actual storage of CPoint data
		private int _x,_y;
		// a method to set the state of the memento
		public void setState(int x, int y)
		{
			_x = x;
			_y = y;
		}
		// a method to get the state of the memento
		public void getState(ref int x, ref int y)
		{
			x = _x;
			y = _y;
		}
		public CMemento()
		{
			_x = 0; _y = 0;
		}
	};

	// an CPoint, whos state we will change and unchange back
	class CPoint
	{
		// data of CPoint
		private int _x,_y;
		public CPoint(int x, int y)
		{
			_x = x; _y = y;
		}
		// a method to change the state of the object
		public void move(int dx, int dy)
		{
			_x = _x + dx; _y = _y + dy;
		}
		// a method to report the state of the object
		public void report()
		{
			Console.WriteLine(string.Format("CPoint is: {0} {1}\n", _x, _y));
		}
		// we can ask a point to write its current state
		// into new memento object and return it to us
		public CMemento createMemento()
		{
			// create a new memento
			CMemento memento = new CMemento();
			// store actual data inside it
			memento.setState(_x, _y);
			// and return it
			return memento;
		}
		// we can give the object a memento it has created
		// a long time ago, and to ask it to read its state from memento
		public virtual void updateFromMemento(CMemento memento)
		{
			// read actual data from memento
			memento.getState(ref _x, ref _y);
		}
	};
	
	class memento
	{
		static void Main(string[] args)
		{
			// create a CPoint
			CPoint p = new CPoint(10, 20);
			// ask a CPoint to report its current state
			p.report();

			// ask a CPoint to create its current memento
			CMemento memento = p.createMemento();

			// now we can change a point to another destination
			p.move(5, 5);
			// ask a CPoint to report its current state
			p.report();

			// however, having a memento object, we can always ask CPoint
			// to return back to the state it was when memento was created
			p.updateFromMemento(memento);
			// ask a CPoint to report its current state
			p.report();

			Console.ReadKey();
		}
	}
}
