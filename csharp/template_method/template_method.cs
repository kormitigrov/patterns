using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateMethod
{

    // исходная ситуация: два класса с почти идентичным методом
    public class BeforeX
    {
        public void TemplateMethod()
        {
            Console.WriteLine(string.Format("1"));
            Console.WriteLine(string.Format("2"));
            Console.WriteLine(string.Format("hello"));
            Console.WriteLine(string.Format("4"));
            Console.WriteLine(string.Format("5"));
        }
    };
    public class BeforeY
    {
        public void TemplateMethod()
        {
            Console.WriteLine(string.Format("1"));
            Console.WriteLine(string.Format("2"));
            Console.WriteLine(string.Format("world"));
            Console.WriteLine(string.Format("4"));
            Console.WriteLine(string.Format("5"));
        }
    };

    // решение проблемы повторяемого кода - вынесение шаблонного метода в 
    // родительский класс и выделение изменяемой части в отдельный метод
    public class AfterZ
    {
        public virtual void doSpecific()
        {
        }
        public void TemplateMethod()
        {
            Console.WriteLine(string.Format("1"));
            Console.WriteLine(string.Format("2"));
            doSpecific();
            Console.WriteLine(string.Format("4"));
            Console.WriteLine(string.Format("5"));
        }
    };
    public class AfterX: AfterZ
    {
        public override void doSpecific()
        {
            Console.WriteLine(string.Format("hello"));
        }
    };
    public class AfterY: AfterZ
    {
        public override void doSpecific()
        {
            Console.WriteLine(string.Format("world"));
        }
    };


    class template_method
    {
        static void Main(string[] args)
        {
            Console.WriteLine(string.Format("\nBEFORE"));
            BeforeX bx = new BeforeX();
            BeforeY by = new BeforeY();
            bx.TemplateMethod();
            by.TemplateMethod();

            Console.WriteLine(string.Format("\nAFTER"));
            AfterX ax = new AfterX();
            AfterY ay = new AfterY();
            ax.TemplateMethod();
            ay.TemplateMethod();

            Console.ReadKey(); 
        }
    }
}
