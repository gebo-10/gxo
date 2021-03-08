using System;
using System.Collections;

namespace Coroutine
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            var t = new Test();
            var itr = t.Co();
            foreach(var i in t)
            {
                Console.WriteLine(i);
            }
            //for(object i=0; itr.MoveNext(); i =itr.Current )
            //{
            //    Console.WriteLine(i);
            //}
        }

       
    }
    public class Test:IEnumerable
    {
        public IEnumerator Co()
        {
            Console.WriteLine("one");
            yield return 1;
            Console.WriteLine("two");
            yield return 2;
            Console.WriteLine("three");
            yield return null;
        }

        public IEnumerator GetEnumerator()
        {
            return Co();
        }
    }
}

