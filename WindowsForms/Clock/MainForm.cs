using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
		}

		private void timer_Tick(object sender, EventArgs e)
		{
			LabelTime.Text = DateTime.Now.ToString("hh:mm:ss tt", System.Globalization.CultureInfo.InvariantCulture);
			//LabelTime.Text = DateTime.Now.ToString("HH:mm:ss");
			if (checkBoxShowDate.Checked) 
			{
				LabelTime.Text += $"\n{DateTime.Now.ToString("yyyy.MM.dd")}";
			}

			if (checkBoxShowWeekDay.Checked)
				LabelTime.Text += $"\n{DateTime.Now.DayOfWeek}";
		}

		private void buttonHideControls_Click(object sender, EventArgs e)
		{

		}
	}
}
