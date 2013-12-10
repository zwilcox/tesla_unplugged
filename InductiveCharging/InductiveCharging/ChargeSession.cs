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
        public DateTime chargeBeginTime { get; set;}

    }
}
