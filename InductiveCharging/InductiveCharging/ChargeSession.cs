using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveCharging
{
    // Keeps track of ongoing charge sessions information
    class ChargeSession
    {
        public string radioID { get; set; }
        public string sessionID { get; set; }
        public string padID { get; set; }
        public long chargeBeginTime { get; set;}
        public PowerAverager padPower;
        public PowerAverager carPower;

        public ChargeSession()
        {
            padPower = new PowerAverager();
            carPower = new PowerAverager();
        }


    }
}
