using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChainOfResponsibility
{
    abstract public class Handler
    {
        public abstract bool handle(int request);
    };


    public class DivisionChecker: Handler
    {
        private int value;
        private Handler next;
        
        public DivisionChecker(int _value, Handler _next)
        {
            value = _value;
            next = _next;
        }
        public override bool handle(int request)
        {
            if (request % value == 0)
            {
                return true;
            }
        
            return next.handle(request);
        }
    };

    public class DefaultHandler: Handler
    {
        public override bool handle(int request)
        {
            Console.WriteLine(string.Format("{0} is prime", request));
            return false;
        }
    };

    class chain_of_responsibility
    {
        static void Main(string[] args)
        {
            Handler queue = new DefaultHandler();

            for (int i = 2; i < 100; i++)
                if (queue.handle(i) == false)
                    queue = new DivisionChecker(i, queue);
            
            Console.ReadKey(); 
        }
    }
}
