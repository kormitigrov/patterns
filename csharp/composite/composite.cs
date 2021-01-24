using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Composite
{

    // абстрактный объект: фигура - то, что может передвигаться и рисоваться на экране
    public abstract class CShape
    {
        public abstract void move(int dx, int dy);
        public abstract void draw();
        ~CShape()
        {
            Console.WriteLine(string.Format("CShape::~CShape()"));
        }
    };

    // конкретный объект: точка, наследуется от CShape
    public class CPoint : CShape
    {
        private int _x, _y;
        public CPoint(int x, int y)
        {
            Console.WriteLine(string.Format("CPoint::CPoint({0}, {1})", x, y));
            _x = x;	_y = y;
        }
        ~CPoint()
        {
            Console.WriteLine(string.Format("CPoint::~CPoint() : deleting ({0}, {1})", _x, _y));
        }
        public override void move(int dx, int dy)
        {
            Console.WriteLine(string.Format("CPoint::move({0}, {1})", dx, dy));
            _x = _x + dx; _y = _y + dy;
        }
        public override void draw()
        {
            Console.WriteLine(string.Format("CPoint::draw() : drawing at ({0}, {1})", _x, _y));
        }
    };

    // еще один конкретный объект: группа фигур
    // обратите внимание - она наследуется от фигуры, то есть она сама и является фигурой!
    public class CGroup : CShape
    {
        // максимально возможное количество фигур в группе
        private int _maxcount;
        // текущее количество фигур в группе
        private int _count;
        // массив ссылок на хранимые фигусы
        private CShape[] _shapes;
        public CGroup(int maxcount)
        {
            Console.WriteLine(string.Format("CGroup::CGroup({0})", maxcount));
            _maxcount = maxcount; _count = 0;
            _shapes = new CShape[_maxcount];
            for (int i = 0; i < _maxcount; i++)
                _shapes[i] = null;
        }
        ~CGroup()
        {
            Console.WriteLine(string.Format("start CGroup::~CGroup()"));
            // очищаем массив ссылок (они удалятся, если никто их не держит)
            for (int i = 0; i < _count; i++)
                _shapes[i] = null;
            // очищаем сам массив
            _shapes = null;
            Console.WriteLine(string.Format("finish CGroup::~CGroup()"));
        }
        // функция для добавления новой фигуры в массив
        public override bool addShape(CShape shape)
        {
            if (_count >= _maxcount)
                return false;
        
            _count++;
            _shapes[_count - 1] = shape;
            return true;
        }
    
        // раз CGroup является потомком CShape, она обязана 
        // перекрыть функцию move(int dx, int dy)
        public override void move(int dx, int dy)
        {
            Console.WriteLine(string.Format("CGroup::move({0}, {1})", dx, dy));
            // проходим по всем фигурам в массиве и вызываем move()
            for (int i = 0; i < _count; i++)
                _shapes[i].move(dx, dy);
        }
        // раз CGroup является потомком CShape, она обязана 
        // перекрыть функцию draw()
        public override void draw()
        {
            Console.WriteLine(string.Format("CGroup::draw()"));
            // проходим по всем фигурам в массиве и вызываем draw()
            for (int i = 0; i < _count; i++)
            {
                _shapes[i].draw();
            }
        }
    };

    class composite
    {
        static void Main(string[] args)
        {
            // создаем группу их трех элементов
            CShape shapes = new CGroup(3);
            // первые два элемента группы заполняем двумя создаваемыми точками
            (shapes as CGroup).addShape(new CPoint(1,1));
            (shapes as CGroup).addShape(new CPoint(2, 2));
                // создаем новую группу из двух элементов
                CShape childshapes = new CGroup(2);
                // и добавляем еще две создаваемые точки в новую группу
                childshapes.addShape(new CPoint(3,3));
                childshapes.addShape(new CPoint(4,4));
            // саму новую группу добавляем в первую группу третьим элементом
            shapes.addShape(childshapes);

            // Весь массив фигур shapes можно считать одной фигурой CShape, 
            // вызывая методы move() и draw(). Он ведет себя как единый CShape,
            // хотя внутри представляет собой сложную составную структуру. 
            // Это и есть паттерн composite
            shapes.move(10,10);
            shapes.draw();

            Console.ReadKey(); 
        }
    }
}
