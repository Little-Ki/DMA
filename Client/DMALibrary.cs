using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Client
{

    class DMALibrary
    {
        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 CreateDMA();

        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool InitializeDMA(UInt32 id);

        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CloseDMA(UInt32 id);

        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool OpenProcess(UInt32 id, string processName);

        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern float ReadFloat(UInt32 id, IntPtr address);

        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool WriteFloat(UInt32 id, IntPtr address, float value);

        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ReadInt(UInt32 id, IntPtr address);

        [DllImport("dma.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool WriteInt(UInt32 id, IntPtr address, int value);

    }
}
