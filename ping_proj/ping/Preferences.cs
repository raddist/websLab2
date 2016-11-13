using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ping
{
    public  class Preferences
    {
        int srcAddress;
        int dstAddress;
        int type;
        int code;
        int volume;
        double delay;

        public Preferences()
        {
            this.volume = 4;
            this.delay = 1;
        }

        public void setPreferences(int srcAddress,
                            int dstAddress,
                            int type,
                            int code, 
                            int volume, 
                            double delay)
        {
            this.srcAddress = srcAddress;
            this.dstAddress = dstAddress;
            this.type = type;
            this.code = code;
            this.volume = volume;
            this.delay = delay;
        }


        // setters


        public void SetDelay(double delay)
        {
            this.delay = delay;
        }

        public void SetVolume(int volume)
        {
            this.volume = volume;
        }

        //getters
        public int GetVolume()
        {
            return this.volume;
        }

        public int GetSrcAddress()
        {
            return this.srcAddress;
        }

        public int GetDstAddress()
        {
            return this.dstAddress;
        }

        public double GetDelay()
        {
            return this.delay;
        }

        public int GetPacType()
        {
            return this.type;
        }

        public int GetCode()
        {
            return this.code;
        }
    }
}
