using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    class DMA
    {
        private UInt32 id;

        DMA()
        {
            id = DMALibrary.CreateDMA();
        }

        public bool Initialize()
        {
            return DMALibrary.InitializeDMA(id);
        }

        public void Close()
        {
            DMALibrary.CloseDMA(id);
        }

        public bool OpenProcess(string processName)
        {
            return DMALibrary.OpenProcess(id, processName);
        }

        public float ReadFloat(IntPtr address)
        {
            return DMALibrary.ReadFloat(id, address);
        }
        public bool WriteFloat(IntPtr address, float value)
        {
            return DMALibrary.WriteFloat(id, address, value);
        }

        public int ReadInt(IntPtr address)
        {
            return DMALibrary.ReadInt(id, address);
        }

        public bool WriteInt(IntPtr address, int value)
        {
            return DMALibrary.WriteInt(id, address, value);
        }
    }
}
