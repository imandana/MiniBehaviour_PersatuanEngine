using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using PersatuanEngine;

public class ScriptMove : MiniBehaviour
{
    public ScriptMove()
    {
        Console.WriteLine("In ctor ScriptMove!!!!!!");
    }
    public ScriptMove(int v, byte[] array)
    {
        Console.WriteLine("In ctor ScriptMove!!!!!! (int, byte[]) got value: {0}, array len: {1}", v, array.Length);
    }

    int delay = 0;

    void Start()
    {
        Console.WriteLine("MOVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
    }

    void Update()
    {
        if (delay > 40)
        {
            Console.WriteLine("UPDATEEEE _______ MOVE");
            delay = 0;
        }
        delay++;
    }

}