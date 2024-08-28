using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Client
{

    class DMA
    {
        [DllImport("dma.dll")]
        public static extern bool Initialize([MarshalAs(UnmanagedType.LPStr)] string processName);

        [DllImport("dma.dll")]
        public static extern bool InitKeyboard();

        [DllImport("dma.dll")]
        public static extern bool IsKeyDown(UInt32 vk);

        [DllImport("dma.dll")]
        public static extern float ReadFloat(IntPtr address);

        [DllImport("dma.dll")]
        public static extern bool WriteFloat(IntPtr address, float value);

        [DllImport("dma.dll")]
        public static extern int ReadInt(IntPtr address);

        [DllImport("dma.dll")]
        public static extern bool WriteInt(IntPtr address, int value);

    }
}
