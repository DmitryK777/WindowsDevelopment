namespace Clock
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.LabelTime = new System.Windows.Forms.Label();
			this.timer = new System.Windows.Forms.Timer(this.components);
			this.checkBoxShowDate = new System.Windows.Forms.CheckBox();
			this.checkBoxShowWeekDay = new System.Windows.Forms.CheckBox();
			this.buttonHideControls = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// LabelTime
			// 
			this.LabelTime.AutoSize = true;
			this.LabelTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 32.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.LabelTime.Location = new System.Drawing.Point(13, 4);
			this.LabelTime.Name = "LabelTime";
			this.LabelTime.Size = new System.Drawing.Size(118, 51);
			this.LabelTime.TabIndex = 0;
			this.LabelTime.Text = "Time";
			this.LabelTime.DoubleClick += new System.EventHandler(this.LabelTime_DoubleClick);
			// 
			// timer
			// 
			this.timer.Enabled = true;
			this.timer.Tick += new System.EventHandler(this.timer_Tick);
			// 
			// checkBoxShowDate
			// 
			this.checkBoxShowDate.AutoSize = true;
			this.checkBoxShowDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.checkBoxShowDate.Location = new System.Drawing.Point(31, 164);
			this.checkBoxShowDate.Name = "checkBoxShowDate";
			this.checkBoxShowDate.Size = new System.Drawing.Size(132, 29);
			this.checkBoxShowDate.TabIndex = 1;
			this.checkBoxShowDate.Text = "Show date";
			this.checkBoxShowDate.UseVisualStyleBackColor = true;
			// 
			// checkBoxShowWeekDay
			// 
			this.checkBoxShowWeekDay.AutoSize = true;
			this.checkBoxShowWeekDay.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.checkBoxShowWeekDay.Location = new System.Drawing.Point(31, 199);
			this.checkBoxShowWeekDay.Name = "checkBoxShowWeekDay";
			this.checkBoxShowWeekDay.Size = new System.Drawing.Size(175, 29);
			this.checkBoxShowWeekDay.TabIndex = 2;
			this.checkBoxShowWeekDay.Text = "Show weekday";
			this.checkBoxShowWeekDay.UseVisualStyleBackColor = true;
			// 
			// buttonHideControls
			// 
			this.buttonHideControls.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.buttonHideControls.Location = new System.Drawing.Point(31, 257);
			this.buttonHideControls.Name = "buttonHideControls";
			this.buttonHideControls.Size = new System.Drawing.Size(146, 37);
			this.buttonHideControls.TabIndex = 3;
			this.buttonHideControls.Text = "Hide controls";
			this.buttonHideControls.UseVisualStyleBackColor = true;
			this.buttonHideControls.Click += new System.EventHandler(this.buttonHideControls_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Control;
			this.ClientSize = new System.Drawing.Size(279, 321);
			this.Controls.Add(this.buttonHideControls);
			this.Controls.Add(this.checkBoxShowWeekDay);
			this.Controls.Add(this.checkBoxShowDate);
			this.Controls.Add(this.LabelTime);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Clock VPD_311";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label LabelTime;
		private System.Windows.Forms.Timer timer;
		private System.Windows.Forms.CheckBox checkBoxShowDate;
		private System.Windows.Forms.CheckBox checkBoxShowWeekDay;
		private System.Windows.Forms.Button buttonHideControls;
	}
}

