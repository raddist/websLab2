using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Net;

namespace ping
{
    public unsafe partial class Form1 : Form
    {
        bool isSendingStart = false;

        Preferences prefsSet;
        public Form1()
        {
            InitializeComponent();

            // prepare type and code
            System.Object[] ItemObject1 = new System.Object[15];
            int[] values = new int[] {0,3,4,5,8,9,10,11,12,13,14,15,16,17,18 };
            for (int i = 0; i < 15; i++)
            {
                ItemObject1[i] = values[i];
            }
            typeComboBox.Items.AddRange(ItemObject1);
            typeComboBox.SelectedIndex = 4;

            System.Object[] ItemObject2 = new System.Object[16];
            for (int i = 0; i < 16; i++)
            {
                ItemObject2[i] = i;
            }
            codeComboBox.Items.AddRange(ItemObject2);
            codeComboBox.SelectedIndex = 0;

            prefsSet = new Preferences();

            // prepare volume and delay
            volumeTxtBox.Text = prefsSet.GetVolume().ToString();
            delayTxtBox.Text = prefsSet.GetDelay().ToString();
        }

        private void sendBtn_Click(object sender, EventArgs e)
        {
            if (isSendingStart)
            {
                return;
            }

            if (!validateAndSet(prefsSet))
            {
                return;
            }

            resBody.Text = "Sending is processing";

            // resultLbl.Text = Marshal.PtrToStringAnsi((IntPtr)Imports.sendPacket((char*)"sad", "fd", 8, 0));
            //int srcAddress = BitConverter.ToInt32(IPAddress.Parse(srcAddrTxtBox.Text).GetAddressBytes(), 0);
            //int dstAddress = BitConverter.ToInt32(IPAddress.Parse(dstAddrTxtBox.Text).GetAddressBytes(), 0);
            //resultLbl.Text = typeComboBox.SelectedItem.ToString() + " ";
            int result = Imports.sendPacket(prefsSet.GetSrcAddress(),
                                            prefsSet.GetDstAddress(),
                                            prefsSet.GetPacType(),
                                            prefsSet.GetCode(),
                                            prefsSet.GetVolume(),
                                            prefsSet.GetDelay());
            resBody.Text = "Successful sending";
        }

        private bool validateAndSet(Preferences set)
        {
            // validate IP addresses
            int srcAddress = 0;
            try {
                srcAddress = BitConverter.ToInt32(IPAddress.Parse(srcAddrTxtBox.Text).GetAddressBytes(), 0);
            }
            catch (Exception srcIPexc)
            {
                resBody.Text = "Error: incorrect source address";
                return false;
            }

            int dstAddress = 0;
            try {
                dstAddress = BitConverter.ToInt32(IPAddress.Parse(dstAddrTxtBox.Text).GetAddressBytes(), 0);
            }
            catch(Exception dstIPexc)
            {
                resBody.Text = "Error: incorrect destination address";
                return false;
            }

            // validate volume (nymber of packets)
            int volume = 0;
            try
            {
                volume = Convert.ToInt32(volumeTxtBox.Text);
                if (volume < 0)
                {
                    resBody.Text = "Error: incorrect number of packets";
                    return false;
                }
            }
            catch (Exception except)
            {
                //volumeTxtBox.Text = set.GetVolume().ToString();
                resBody.Text = "Error: incorrect number of packets";
                return false;
            }

            //prepare sending delay
            double delay = 0;
            try
            {
                delay = Convert.ToDouble(delayTxtBox.Text);
                if (delay < 0)
                {
                    resBody.Text = "Error: incorrect sending delay";
                    return false;
                }
            }
            catch (Exception except)
            {
                //delayTxtBox.Text = set.GetDelay().ToString();
                resBody.Text = "Error: incorrect sending delay";
                return false;
            }

            //prepare type and code
            int type = Convert.ToInt32(typeComboBox.SelectedItem);
            int code = Convert.ToInt32(codeComboBox.SelectedItem);
            if(!mapTypeCode(type, code))
            {
                resBody.Text = "Error: incorrect code";
                return false;
            }

            set.setPreferences(srcAddress,
                                dstAddress,
                                type,
                                code,
                                volume,
                                delay);

            return true;
        }

        private bool mapTypeCode(int type, int code)
        {
            int[] inds = new int[] {3,5,11,12 };
            if ((code > 0) && (Array.IndexOf(inds, type) < 0))
            {
                return false;
            }
            if ((code > 1) && (type != 3) && (type != 5))
            {
                return false;
            }
            if ((code > 3) && (type != 3))
            {
                return false;
            }
            return true;
        }
    }

    public unsafe class Imports
    {
        [DllImport("../../../Debug/connectionLib.dll")]
        public static extern int sendPacket(int srcAddr, int dstAddr, int type, int code, int count, double delay);
    }
}