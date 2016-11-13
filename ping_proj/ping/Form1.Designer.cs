namespace ping
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.srcAddrLbl = new System.Windows.Forms.Label();
            this.dstAddrLbl = new System.Windows.Forms.Label();
            this.typeLbl = new System.Windows.Forms.Label();
            this.codeLbl = new System.Windows.Forms.Label();
            this.Header = new System.Windows.Forms.Label();
            this.srcAddrTxtBox = new System.Windows.Forms.TextBox();
            this.dstAddrTxtBox = new System.Windows.Forms.TextBox();
            this.sendBtn = new System.Windows.Forms.Button();
            this.resHeader = new System.Windows.Forms.Label();
            this.typeComboBox = new System.Windows.Forms.ComboBox();
            this.codeComboBox = new System.Windows.Forms.ComboBox();
            this.resBody = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.errHeader = new System.Windows.Forms.Label();
            this.delayTxtBox = new System.Windows.Forms.TextBox();
            this.volumeTxtBox = new System.Windows.Forms.TextBox();
            this.delayLbl = new System.Windows.Forms.Label();
            this.countLbl = new System.Windows.Forms.Label();
            this.prefsHeader = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // srcAddrLbl
            // 
            this.srcAddrLbl.AutoSize = true;
            this.srcAddrLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.srcAddrLbl.Location = new System.Drawing.Point(30, 73);
            this.srcAddrLbl.Name = "srcAddrLbl";
            this.srcAddrLbl.Size = new System.Drawing.Size(136, 16);
            this.srcAddrLbl.TabIndex = 0;
            this.srcAddrLbl.Text = "Enter source address";
            // 
            // dstAddrLbl
            // 
            this.dstAddrLbl.AutoSize = true;
            this.dstAddrLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.dstAddrLbl.Location = new System.Drawing.Point(30, 139);
            this.dstAddrLbl.Name = "dstAddrLbl";
            this.dstAddrLbl.Size = new System.Drawing.Size(160, 16);
            this.dstAddrLbl.TabIndex = 1;
            this.dstAddrLbl.Text = "Enter destination address";
            // 
            // typeLbl
            // 
            this.typeLbl.AutoSize = true;
            this.typeLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.typeLbl.Location = new System.Drawing.Point(30, 207);
            this.typeLbl.Name = "typeLbl";
            this.typeLbl.Size = new System.Drawing.Size(103, 16);
            this.typeLbl.TabIndex = 2;
            this.typeLbl.Text = "Enter ICMP type";
            // 
            // codeLbl
            // 
            this.codeLbl.AutoSize = true;
            this.codeLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.codeLbl.Location = new System.Drawing.Point(30, 268);
            this.codeLbl.Name = "codeLbl";
            this.codeLbl.Size = new System.Drawing.Size(108, 16);
            this.codeLbl.TabIndex = 3;
            this.codeLbl.Text = "Enter ICMP code";
            // 
            // Header
            // 
            this.Header.AutoSize = true;
            this.Header.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Header.Location = new System.Drawing.Point(195, 27);
            this.Header.Name = "Header";
            this.Header.Size = new System.Drawing.Size(160, 20);
            this.Header.TabIndex = 4;
            this.Header.Text = "Enter necessary data";
            // 
            // srcAddrTxtBox
            // 
            this.srcAddrTxtBox.Location = new System.Drawing.Point(211, 73);
            this.srcAddrTxtBox.Name = "srcAddrTxtBox";
            this.srcAddrTxtBox.Size = new System.Drawing.Size(100, 20);
            this.srcAddrTxtBox.TabIndex = 5;
            this.srcAddrTxtBox.Text = "192.168.1.37";
            // 
            // dstAddrTxtBox
            // 
            this.dstAddrTxtBox.Location = new System.Drawing.Point(211, 135);
            this.dstAddrTxtBox.Name = "dstAddrTxtBox";
            this.dstAddrTxtBox.Size = new System.Drawing.Size(100, 20);
            this.dstAddrTxtBox.TabIndex = 6;
            this.dstAddrTxtBox.Text = "192.168.1.37";
            // 
            // sendBtn
            // 
            this.sendBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.sendBtn.Location = new System.Drawing.Point(371, 199);
            this.sendBtn.Name = "sendBtn";
            this.sendBtn.Size = new System.Drawing.Size(148, 82);
            this.sendBtn.TabIndex = 9;
            this.sendBtn.Text = "Send";
            this.sendBtn.UseVisualStyleBackColor = true;
            this.sendBtn.Click += new System.EventHandler(this.sendBtn_Click);
            // 
            // resHeader
            // 
            this.resHeader.AutoSize = true;
            this.resHeader.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.resHeader.Location = new System.Drawing.Point(33, 321);
            this.resHeader.Name = "resHeader";
            this.resHeader.Size = new System.Drawing.Size(52, 20);
            this.resHeader.TabIndex = 10;
            this.resHeader.Text = "State:";
            // 
            // typeComboBox
            // 
            this.typeComboBox.FormattingEnabled = true;
            this.typeComboBox.Location = new System.Drawing.Point(211, 202);
            this.typeComboBox.Name = "typeComboBox";
            this.typeComboBox.Size = new System.Drawing.Size(39, 21);
            this.typeComboBox.TabIndex = 11;
            // 
            // codeComboBox
            // 
            this.codeComboBox.FormattingEnabled = true;
            this.codeComboBox.Location = new System.Drawing.Point(211, 260);
            this.codeComboBox.Name = "codeComboBox";
            this.codeComboBox.Size = new System.Drawing.Size(39, 21);
            this.codeComboBox.TabIndex = 12;
            // 
            // resBody
            // 
            this.resBody.AutoSize = true;
            this.resBody.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.resBody.Location = new System.Drawing.Point(207, 321);
            this.resBody.Name = "resBody";
            this.resBody.Size = new System.Drawing.Size(161, 20);
            this.resBody.TabIndex = 13;
            this.resBody.Text = "Nothing was done yet";
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.errHeader);
            this.panel1.Controls.Add(this.delayTxtBox);
            this.panel1.Controls.Add(this.volumeTxtBox);
            this.panel1.Controls.Add(this.delayLbl);
            this.panel1.Controls.Add(this.countLbl);
            this.panel1.Controls.Add(this.prefsHeader);
            this.panel1.Location = new System.Drawing.Point(12, 364);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(522, 95);
            this.panel1.TabIndex = 14;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(312, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "All is fine now";
            // 
            // errHeader
            // 
            this.errHeader.AutoSize = true;
            this.errHeader.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.errHeader.Location = new System.Drawing.Point(311, 9);
            this.errHeader.Name = "errHeader";
            this.errHeader.Size = new System.Drawing.Size(56, 20);
            this.errHeader.TabIndex = 5;
            this.errHeader.Text = "Errors:";
            // 
            // delayTxtBox
            // 
            this.delayTxtBox.Location = new System.Drawing.Point(198, 61);
            this.delayTxtBox.Name = "delayTxtBox";
            this.delayTxtBox.Size = new System.Drawing.Size(39, 20);
            this.delayTxtBox.TabIndex = 4;
            // 
            // volumeTxtBox
            // 
            this.volumeTxtBox.Location = new System.Drawing.Point(198, 33);
            this.volumeTxtBox.Name = "volumeTxtBox";
            this.volumeTxtBox.Size = new System.Drawing.Size(39, 20);
            this.volumeTxtBox.TabIndex = 3;
            // 
            // delayLbl
            // 
            this.delayLbl.AutoSize = true;
            this.delayLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.delayLbl.Location = new System.Drawing.Point(20, 61);
            this.delayLbl.Name = "delayLbl";
            this.delayLbl.Size = new System.Drawing.Size(149, 16);
            this.delayLbl.TabIndex = 2;
            this.delayLbl.Text = "Delay between packets";
            // 
            // countLbl
            // 
            this.countLbl.AutoSize = true;
            this.countLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.countLbl.Location = new System.Drawing.Point(20, 33);
            this.countLbl.Name = "countLbl";
            this.countLbl.Size = new System.Drawing.Size(172, 16);
            this.countLbl.TabIndex = 1;
            this.countLbl.Text = "Number of sending packets";
            // 
            // prefsHeader
            // 
            this.prefsHeader.AutoSize = true;
            this.prefsHeader.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.prefsHeader.Location = new System.Drawing.Point(16, 9);
            this.prefsHeader.Name = "prefsHeader";
            this.prefsHeader.Size = new System.Drawing.Size(139, 20);
            this.prefsHeader.TabIndex = 0;
            this.prefsHeader.Text = "Extra preferences:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(546, 471);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.resBody);
            this.Controls.Add(this.codeComboBox);
            this.Controls.Add(this.typeComboBox);
            this.Controls.Add(this.resHeader);
            this.Controls.Add(this.sendBtn);
            this.Controls.Add(this.dstAddrTxtBox);
            this.Controls.Add(this.srcAddrTxtBox);
            this.Controls.Add(this.Header);
            this.Controls.Add(this.codeLbl);
            this.Controls.Add(this.typeLbl);
            this.Controls.Add(this.dstAddrLbl);
            this.Controls.Add(this.srcAddrLbl);
            this.Name = "Form1";
            this.Text = "ICMP generator";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label srcAddrLbl;
        private System.Windows.Forms.Label dstAddrLbl;
        private System.Windows.Forms.Label typeLbl;
        private System.Windows.Forms.Label codeLbl;
        private System.Windows.Forms.Label Header;
        private System.Windows.Forms.TextBox srcAddrTxtBox;
        private System.Windows.Forms.TextBox dstAddrTxtBox;
        private System.Windows.Forms.Button sendBtn;
        private System.Windows.Forms.Label resHeader;
        private System.Windows.Forms.ComboBox typeComboBox;
        private System.Windows.Forms.ComboBox codeComboBox;
        private System.Windows.Forms.Label resBody;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label prefsHeader;
        private System.Windows.Forms.TextBox volumeTxtBox;
        private System.Windows.Forms.Label delayLbl;
        private System.Windows.Forms.Label countLbl;
        private System.Windows.Forms.TextBox delayTxtBox;
        private System.Windows.Forms.Label errHeader;
        private System.Windows.Forms.Label label1;
    }
}

