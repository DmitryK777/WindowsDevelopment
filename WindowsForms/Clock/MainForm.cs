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
			LabelTime.BackColor = Color.AliceBlue;
			this.Location = new Point
				(
					(Screen.PrimaryScreen.Bounds.Width - this.Width)/2, (Screen.PrimaryScreen.Bounds.Height - this.Height) / 2
				);

		}

		void SetVisibility(bool visible)
		{
			checkBoxShowDate.Visible = visible;
			checkBoxShowWeekDay.Visible = visible;
			buttonHideControls.Visible = visible;
			this.FormBorderStyle = visible ? FormBorderStyle.FixedDialog : FormBorderStyle.None;
			this.ShowInTaskbar = visible;
			this.TransparencyKey = visible ? Color.Empty : this.BackColor;
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

			notifyIcon.Text = 
				$"{DateTime.Now.ToString("hh:mm:ss")}\n" +
				$"{DateTime.Now.ToString("yyyy:MM:dd")}\n" +
				$"{DateTime.Now.DayOfWeek}";
		}

		private void buttonHideControls_Click(object sender, EventArgs e)
		{
			SetVisibility(false);
		}

		private void LabelTime_DoubleClick(object sender, EventArgs e)
		{
			SetVisibility(true);
		}
	}
}
