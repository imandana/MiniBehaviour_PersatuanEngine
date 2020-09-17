using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class Chiw : Jump
{
    public Chiw()
    {
        Console.WriteLine("In ctor CHIIWWW!!!!!!");
    }
    public Chiw(int v, byte[] array)
    {
        Console.WriteLine("In ctor JUMMMMMMAPAPAP!!!!!! (int, byte[]) got value: {0}, array len: {1}", v, array.Length);
    }

    void Start()
    {
        Console.WriteLine("CHIIWWW");
    }

    void Update()
    {
        Console.WriteLine("UPDATE _____ CHIIWWW");
    }
}
