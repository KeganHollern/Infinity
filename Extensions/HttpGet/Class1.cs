using RGiesecke.DllExport;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace HttpGet
{
    public class DllMain
    {
        [DllExport("RVExtensionVersion", CallingConvention = CallingConvention.Winapi)]
        public static void RvExtensionVersion(StringBuilder output, int outputSize)
        {
            output.Append("1.0.0");
        }

        [DllExport("RVExtension", CallingConvention = CallingConvention.Winapi)]
        public static void RvExtension(StringBuilder output, int outputSize, [MarshalAs(UnmanagedType.LPStr)] string function)
        {
            try
            {
                using (WebClient wc = new WebClient())
                {
                    output.Append(wc.DownloadString(function));
                }
            } catch
            {
                output.Append("failed to access url");
            }
        }
    }
}
