using System;
using System.Data;
using System.Linq;
using System.Windows.Forms;
using System.IO.Ports;


namespace CSharp
{
    public partial class Form1 : Form
    {
        string[] ports = SerialPort.GetPortNames();

        public Form1()
        {
            InitializeComponent();

            CheckForIllegalCrossThreadCalls = false;
        }

        string data;
        int[] frekans;
        int MaxFreq = 8000;


        private void Form1_Load(object sender, EventArgs e)
        {

            string[] ports = SerialPort.GetPortNames();  //Seri portları diziye ekleme
            foreach (string port in ports)
            {
                cbSeriPorts.Items.Add(port);//Seri portları comboBox1'e ekleme
            }
            cbSeriPorts.SelectedIndex = 0;
            cbBaudRate.SelectedIndex = 2;

            ////chart1.ChartAreas[0].AxisX.Minimum = 0;
            ////chart1.ChartAreas[0].AxisX.Maximum = 10000;
            //chart1.ChartAreas[0].AxisX.IntervalType = DateTimeIntervalType.Auto;
            ////chart1.ChartAreas[0].AxisX.Interval = 50;
            //chart1.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;
            //chart1.ChartAreas[0].AxisX.MinorGrid.IntervalType = DateTimeIntervalType.Auto;
            ////chart1.ChartAreas[0].AxisX.MinorGrid.Interval = 2;
            //chart1.ChartAreas[0].AxisX.MinorGrid.LineColor = Color.LightGray;
            //chart1.ChartAreas[0].AxisX.MinorGrid.Enabled = true;
            chart1.ChartAreas[0].AxisX.Title = "Frekans(kHz)";
            //chart1.ChartAreas[0].AxisX.TitleFont = new System.Drawing.Font("", 10);
            //chart1.ChartAreas[0].AxisY.Minimum = 0;
            chart1.ChartAreas[0].AxisY.Maximum = 1000;
            //chart1.ChartAreas[0].AxisY.IntervalType = DateTimeIntervalType.Auto;
            ////cahrtHistogram.ChartAreas[0].AxisY.Interval = 500;
            //chart1.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.DarkGray;
            //chart1.ChartAreas[0].AxisY.MinorGrid.IntervalType = DateTimeIntervalType.Auto; ;
            ////chart1.ChartAreas[0].AxisY.MinorGrid.Interval = 5;
            //chart1.ChartAreas[0].AxisY.MinorGrid.LineColor = Color.LightGray;
            //chart1.ChartAreas[0].AxisY.MinorGrid.Enabled = true;
            //chart1.ChartAreas[0].AxisY.Title = "Genlik ";
            //chart1.ChartAreas[0].AxisY.TitleFont = new System.Drawing.Font("", 10);
            //chart1.ChartAreas[0].AxisX.IntervalType = DateTimeIntervalType.Auto;
            ////chart1.ChartAreas[0].AxisX.Interval = 50;
            //chart1.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;
            //chart1.ChartAreas[0].AxisX.MinorGrid.IntervalType = DateTimeIntervalType.Auto;
            ////chart1.ChartAreas[0].AxisX.MinorGrid.Interval = 2;

            chart2.ChartAreas[0].AxisY.Maximum = 4096;
            chart2.ChartAreas[0].AxisX.Title = "Analog";
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(SerialPort1_DataReceived); //DataReceived eventini oluşturma                   
        }

        private void SerialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
           
            Console.WriteLine(data);
            try
            {
                data = serialPort1.ReadLine();  //Veriyi al
                frekans = data.Split(',').Select(int.Parse).ToArray();
                
                for (int i = 0; i < frekans.Length-1; i++)
                {
                    if (frekans[i].GetType() != typeof(int)) frekans[i] = 0;                   
                }
                
            }
            catch (Exception)
            {

            }

            // data = serialPort1.ReadByte().ToString();
            this.BeginInvoke(new EventHandler(displayData_event));
        }

        private void displayData_event(object sender, EventArgs e)
        {
            double perBarFreq = (double)MaxFreq / 1000;
            perBarFreq /= frekans.Length-1;

            try
            {
                chart2.Series["Series1"].Points.Clear();
                chart1.Series["Series1"].Points.Clear();

                for (int i = 1; i <= frekans.Length - 1; i++)
                {
                    this.chart1.Series["Series1"].Points.AddXY(perBarFreq * i, frekans[i-1]);                    
                }

                chart2.Series["Series1"].Points.AddY(frekans[frekans.Length-1]);
            }
            catch (Exception)
            {
            }
           
        }        

        private void baslat_Click(object sender, EventArgs e)
        {
            if (btnBaslat.Text == "BAŞLAT")
            {
                serialPort1.PortName = cbSeriPorts.Text;  //ComboBox1'de seçili nesneyi port ismine ata
                serialPort1.BaudRate = Convert.ToInt32(cbBaudRate.Text);       //BaudRate 9600 olarak ayarla
                serialPort1.Open();                       //Seri portu aç      
                serialPort1.DiscardInBuffer();
                btnBaslat.Text = "DURDUR";
            }
            else if (btnBaslat.Text == "DURDUR")
            {
                btnBaslat.Text = "BAŞLAT";
                serialPort1.Close();        //Seri Portu kapa
            }          
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort1.IsOpen) serialPort1.Close();    //Seri port açıksa kapat
        }


        private void trackBarZoom_ValueChanged(object sender, EventArgs e)
        {
            chart1.ChartAreas[0].AxisY.Maximum = trackBarZoom.Value;
        }

        private void btnSetFreq_Click(object sender, EventArgs e)
        {
            int presc = 0;
            string strpresc;
            //freq = timer_freq /( prescaler+1-1 * (period +1-1))
            MaxFreq = Convert.ToInt32(textBox1.Text);
            presc = 7200000 / MaxFreq;
            strpresc = presc.ToString().PadLeft(7,'0');
                    
            serialPort1.WriteLine(strpresc);
        }
    }
}
