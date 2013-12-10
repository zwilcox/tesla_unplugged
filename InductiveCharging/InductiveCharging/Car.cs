﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveCharging
{
    public class Car
    {
        public string carID { get; set; }
        public string radioID { get; set; }
        public PadColor pad1Color { get; set; }
        public PadColor pad2Color { get; set; }
        public PadColor pad3Color { get; set; }

        public Car (string _carID, string _radioID)
        {
            carID = _carID;
            radioID = _radioID;
            pad1Color = new PadColor();
            pad2Color = new PadColor();
            pad3Color = new PadColor();

        }
    }
}
