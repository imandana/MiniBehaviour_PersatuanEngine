using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using PersatuanEngine;

class Jump : MiniBehaviour
{
    public Jump()
    {
        Console.WriteLine("In ctor JumpJumpJumpJump!!!!!!");
    }
    public Jump(int v, byte[] array)
    {
        Console.WriteLine("In ctor JUMMMMMMAPAPAP!!!!!! (int, byte[]) got value: {0}, array len: {1}", v, array.Length);
    }

}
