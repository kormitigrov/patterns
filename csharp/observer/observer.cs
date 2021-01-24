using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Observer
{
	// наблюдатель - кто-то, кто хочет, чтобы его уведомили, 
	// когда что-то произойдет 
	abstract class CObserver
	{
		public abstract void onSubjectChanged(CSubject who);
	};

	// наблюдаемый объект - кто-то, кто позволяет за собой следить 
	class CSubject
	{
		// список текущих наблюдателей этого наблюдаемого объекта
		private List<CObserver> _observers;
		public CSubject()
		{
			// создаем пустой список наблюдателей - пока никто не наблюдает
			_observers = new List<CObserver>();
		}
		// метод для регистрации нового наблюдателя, с помощью которого наблюдатель
		// подписывается на уведомления о том, что наблюдаемый объект изменился
		public void addObserver(CObserver o)
		{
			_observers.Add(o);
		}
		// метод, который уведомляет всех подписанных наблюдателей о том, что что-то изменилось
		public void notifyEveryone()
		{
			// проходим по всем наблюдателям и вызываем у каждого его метод onSubjectChanged
			foreach (CObserver o in _observers)
				o.onSubjectChanged(this);
		}
	};

	// пример наблюдаемого объекта - животное в зоопарке
	class CAnimal : CSubject
	{
		// последняя сказанная фраза
		public string lastsound;
		// имя животного
		public string name;
		public CAnimal(string aname)
		{
			name = aname;
			lastsound = "";
		}
		// животное выполняет действие, и каждый наблюдатель получает уведомление
		public void say(string sound)
		{
			lastsound = sound;
			Console.WriteLine(string.Format("\nCAnimal {0} : '{1}'", name, sound));
			// вызываем уведомление каждого наблюдателя
			notifyEveryone();
		}
	};

	// пример наблюдателя - ребенок в зоопарке, наблюдающий за животными
	class CChild : CObserver
	{
		// имя ребенка
		public string name;
		public CChild(string cname)
		{
			name = cname;
		}
		// метод ребенка, вызываемый тогда, когда наблюдаемый им объект изменяется, 
		// животное вызывает этот метод, передавая самого себя как параметр,
		// поэтому ребенок не только получает уведомление о том, что кто-то изменился,
		// но и знает, кто изменился
		public override void onSubjectChanged(CSubject who)
		{
			Console.WriteLine(string.Format("CChild {0} : 'Hurray! {1} had just said : {2}'", name, 
					 (who as CAnimal).name, (who as CAnimal).lastsound));
		}
	};

	class observer
	{
		static void Main(string[] args)
		{
			// создаем животных
			CAnimal cat = new CAnimal("Zorra");
			CAnimal dog = new CAnimal("Tortilla");
			CAnimal unknown = new CAnimal("Cheburashka");
	
			// создаем детей
			CChild vasya = new CChild("Vasya");
			CChild petya = new CChild("Petya");
			CChild kolya = new CChild("Kolya");
	
			// прописываем, кто наблюдает за кем
			cat.addObserver(vasya);
			cat.addObserver(petya);
			dog.addObserver(kolya);
	
			// заметьте, когда животное изменяется, его наблюдатели уведомляются, 
			// таким образом, объекты могут уведомлять друг друга, причем эта связь
			// может возникать во время работы программы, а не прописываться жестко
			// до запуска программы
			cat.say("mew-mew!");
			dog.say("wow-wow!");
			cat.say("wow-wow!");
			dog.say("mew-mew!");
			unknown.say("nobody cares about me");

			Console.ReadKey();
		}
	}
}
