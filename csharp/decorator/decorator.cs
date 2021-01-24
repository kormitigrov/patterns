using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Decorator
{
	abstract class CShape
	{
	    public abstract void draw();
	};

	class CPoint : CShape
	{
	    private int _x, _y;
	    public CPoint(int x, int y)
		{
			Console.WriteLine(string.Format("CPoint::CPoint(%d, %d)", x, y));
			_x = x;	_y = y;
		}
		public virtual void move(int dx, int dy)
		{
			Console.WriteLine(string.Format("CPoint::move(%d, %d)", dx, dy));
			_x = _x + dx; _y = _y + dy;
		}
		public override void draw()
		{
			Console.Write(string.Format("(%d, %d)", _x, _y));
		}
	};

	class CDecorator : CShape
	{
	    private CShape _shape;
	    public CDecorator(CShape shape)
		{
			Console.WriteLine(string.Format("CDecorator::CDecorator(CShape shape)"));
			_shape = shape;
		}
		public override void draw()
		{
			Console.Write(string.Format("*"));
			_shape.draw();
			Console.Write(string.Format("*"));
		}
	};

    class decorator
    {
        static void Main(string[] args)
        {
		    CShape[] shapes = new CShape[3];
	
		    shapes[0] = new CPoint(1,1);
		    shapes[1] = new CDecorator(new CPoint(2,2));
		    shapes[2] = new CDecorator(new CDecorator(new CPoint(3,3)));

		    foreach(CShape s in shapes)
			{
				s.draw();
				Console.WriteLine("");
			}

            Console.ReadKey();
        }
    }
}
