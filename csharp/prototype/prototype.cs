using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prototype
{
	abstract class CAnimal
	{
		// абстрактная функция для клонирования объектов
		public abstract CAnimal clone();
	};

	class CDog : CAnimal
	{
		public CDog() 
		{
			Console.WriteLine(string.Format("CDog::CDog()"));
		}
		// перекрытая функция клонирования, создающая новую копию CDog
		public override CAnimal clone()
		{
			Console.WriteLine(string.Format("CDog::clone()"));
			return new CDog();
		}
	};

	class CCat : CAnimal
	{
		public CCat() 
		{
			Console.WriteLine(string.Format("CCat::CCat()"));
		}
		// перекрытая функция клонирования, создающая новую копию CCat
		public override CAnimal clone()
		{
			Console.WriteLine(string.Format("CCat::clone()"));
			return new CCat();
		}
	};
	
	class Program
	{
		static void Main(string[] args)
		{
			// создаем массив прототипов
			CAnimal[] cage = new CAnimal[] {new CCat(), new CDog()};

			// в другой части программы мы не знаем, какой конкретный объект
			// находится в какой ячейке, но можем легко создавать их копии

			CAnimal newAnimal1 = cage[0].clone(); // создается CCat
			CAnimal newAnimal2 = cage[1].clone(); // создается CDog

			Console.ReadKey(); 
		}
	}
}
