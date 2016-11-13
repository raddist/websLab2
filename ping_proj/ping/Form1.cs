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
            System.Object[] ItemObject1 = new System.Object[16];
            for (int i = 0; i < 16; i++)
            {
                ItemObject1[i] = i;
            }
            typeComboBox.Items.AddRange(ItemObject1);
            typeComboBox.SelectedIndex = 8;

            System.Object[] ItemObject2 = new System.Object[3];
            for (int i = 0; i < 3; i++)
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

            validateAndSet(prefsSet);

            resBody.Text = "Sending is processing";

            // resultLbl.Text = Marshal.PtrToStringAnsi((IntPtr)Imports.sendPacket((char*)"sad", "fd", 8, 0));
            //int srcAddress = BitConverter.ToInt32(IPAddress.Parse(srcAddrTxtBox.Text).GetAddressBytes(), 0);
            //int dstAddress = BitConverter.ToInt32(IPAddress.Parse(dstAddrTxtBox.Text).GetAddressBytes(), 0);
            //resultLbl.Text = typeComboBox.SelectedItem.ToString() + " ";
            Imports.sendPacket(prefsSet.GetSrcAddress(),
                                prefsSet.GetDstAddress(),
                                prefsSet.GetPacType(),
                                prefsSet.GetCode(),
                                prefsSet.GetVolume(),
                                prefsSet.GetDelay());
        }

        private void validateAndSet(Preferences set)
        {
            int srcAddress = BitConverter.ToInt32(IPAddress.Parse(srcAddrTxtBox.Text).GetAddressBytes(), 0);
            int dstAddress = BitConverter.ToInt32(IPAddress.Parse(dstAddrTxtBox.Text).GetAddressBytes(), 0);

            //prepare nPackets
            int count = 0;
            try
            {
                count = Convert.ToInt32(volumeTxtBox.Text);
            }
            catch (Exception except)
            {
                volumeTxtBox.Text = set.GetVolume().ToString();
            }

            //prepare nPackets
            double delay = 0;
            try
            {
                delay = Convert.ToDouble(delayTxtBox.Text);
            }
            catch (Exception except)
            {
                delayTxtBox.Text = set.GetDelay().ToString();
            }

            //prepare type and code
            int type = Convert.ToInt32(typeComboBox.SelectedItem);
            int code = Convert.ToInt32(codeComboBox.SelectedItem);
            //map(type, code);

            set.setPreferences(srcAddress,
                                dstAddress,
                                type,
                                code,
                                count,
                                delay);
        }
    }

    public unsafe class Imports
    {
        [DllImport("../../../Debug/connectionLib.dll")]
        public static extern int sendPacket(int srcAddr, int dstAddr, int type, int code, int count, double delay);
    }
}