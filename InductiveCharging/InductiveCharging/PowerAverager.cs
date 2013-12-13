using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace InductiveCharging
{
    
    class PowerAverager
    {
        ArrayList voltArray = new ArrayList();
        ArrayList ampArray = new ArrayList();

        private Int64 interval = TimeSpan.TicksPerSecond;

        private Int64 powerLastCaclulated;

        public PowerAverager ()
        {
            powerLastCaclulated = DateTime.Now.Ticks;
        }

        public float addVoltageRead(float volts)
        {
            voltArray.Add(volts);

            return calculatePower();

        }

        public float addCurrentRead(float current)
        {
            ampArray.Add(current);

            return calculatePower();
        }

        private float calculatePower()
        {
            float voltAverage = 0;
            float ampAverage = 0;

            if (DateTime.Now.Ticks < powerLastCaclulated + interval || voltArray.Count < 1 || ampArray.Count < 1)
            {
                return float.MaxValue;
            }

            foreach(float v in voltArray)
            {
                voltAverage += v;
            }
            voltAverage /= voltArray.Count;


            foreach (float a in ampArray)
            {
                ampAverage += a;
            }
            ampAverage /= ampArray.Count;


            powerLastCaclulated = DateTime.Now.Ticks;

            if (ampAverage == 0 || voltAverage == 0)
            {
                return 0;
            }

            ampArray.Clear();
            voltArray.Clear();

            return voltAverage * ampAverage;

        }


    }
}
