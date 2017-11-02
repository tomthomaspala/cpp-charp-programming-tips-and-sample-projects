using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CallbackDLLLib;

namespace CallbacktestApp
{
    public partial class Form1 : Form , _ICallbackTestEvents , CallbackEvents
    {
        private ICallbackTest m_CallbackTest;
        private int cookie;
        private IConnectionPoint icp;
        public Form1()
        {
            InitializeComponent();
           
        }

        private void buttonInit_Click(object sender, EventArgs e)
        {
            listBoxStatusLog.Items.Clear();
            IConnectionPointContainer icpc = (IConnectionPointContainer)m_CallbackTest;


            Guid _ICallbackGUID = typeof(_ICallbackTestEvents).GUID;

            icpc.FindConnectionPoint(ref _ICallbackGUID, out icp);
            icp.Advise(this, out cookie);
            m_CallbackTest.INIT();
        }

        private void buttonInitEx_Click(object sender, EventArgs e)
        {
            listBoxStatusLog.Items.Clear();
           
            m_CallbackTest.INITEx((CallbackEvents)this);
           
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            m_CallbackTest.STOP();
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            m_CallbackTest = new CallbackTest();
        }

       
        public void OnStatusChangeEx(CallbackParam Param)
        {
            string strData = "Values : " + Param.Param1.ToString() + " ," + Param.Param2.ToString();
            listBoxStatusLog.Items.Add(strData);
        }
        
        public void OnStatusChange(CallbackParam Data)
        {
            try
            {
                string strData = "Values : " + Data.Param1.ToString() + " ," + Data.Param2.ToString();
                listBoxStatusLog.Items.Add(strData);
            }
            catch(Exception Ex)
            {
                MessageBox.Show(Ex.Message);
            }
        }
    }
}
