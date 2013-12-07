using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveCharging
{
    public class Car
    {
        string carID { get; set; }
        string radioID { get; set; }
        public PadColor pad1Color { get; set; }
        public PadColor pad2Color { get; set; }
        public PadColor pad3Color { get; set; }

        public Car (string _carID, string _radioID)
        {
            carID = _carID;
            radioID = _radioID;
        }
    }
}
