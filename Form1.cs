using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public enum ControlParseCase
        {
            None,
            Name,
            Money
        }
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)     //폼 로드
        {
            lblTime.Text = DateTime.Now.ToString("yyyy.M.");
            lvwOutgo.View = View.Details;
            lvwOutgo.Columns.Add("Name", "이름");
            lvwOutgo.Columns.Add("Money", "지출");
            lvwOutgo.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
            lvwOutgo.Columns["Money"].TextAlign = HorizontalAlignment.Center;
            lvwIncome.View = View.Details;
            lvwIncome.Columns.Add("Name", "이름");
            lvwIncome.Columns.Add("Money", "지출");
            lvwIncome.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
            lvwIncome.Columns["Money"].TextAlign = HorizontalAlignment.Center;
            lvwIncome.Items.Clear();
            lvwOutgo.Items.Clear();
            string directory_path = "Data";
            if (!Directory.Exists(directory_path))
            {
                Directory.CreateDirectory(directory_path);
            }

            if (File.Exists("Data\\" + lblTime.Text + "수입.txt") || File.Exists("Data\\" + lblTime.Text + "지출.txt"))
            {   
                LoadData();
            }
        }

        private void btnPrev_Click(object sender, EventArgs e)      //이전달 버튼 클릭
        {
            DateTime t = DateTime.Parse(lblTime.Text);
            t = t.AddMonths(-1);
            lblTime.Text = t.ToString("yyyy.M.");
            lvwIncome.Items.Clear();
            lvwOutgo.Items.Clear();
            if (File.Exists("Data\\" + lblTime.Text + "수입.txt") || File.Exists("Data\\" + lblTime.Text + "지출.txt"))
            {
                LoadData();
            }
            clearControlsI();
            clearControlsO();
            EvalOutgo();
            EvalIncome();
            Total();
        }

        private void btnNext_Click(object sender, EventArgs e)          //다음달 버튼 클릭
        {
            DateTime t = DateTime.Parse(lblTime.Text);
            t = t.AddMonths(1);
            lblTime.Text = t.ToString("yyyy.M.");
            lvwIncome.Items.Clear();
            lvwOutgo.Items.Clear();
            if (File.Exists("Data\\" + lblTime.Text + "수입.txt") || File.Exists("Data\\" + lblTime.Text + "지출.txt"))
            {
                LoadData();
            }
            clearControlsO();
            clearControlsI();
            EvalOutgo();
            EvalIncome();
            Total();
        }

        private void clearControlsO()           //지출 내용입력 박스 클리어
        {

            tbOutMoney.Clear();
            tbOutName.Clear();
        }
        private ControlParseCase GetControlParseCaseO()
        {
            if (string.Equals(tbOutMoney.Text, String.Empty)) return ControlParseCase.Money;
            else if (string.Equals(tbOutName.Text, String.Empty)) return ControlParseCase.Name;
            return ControlParseCase.None;
        }
        private Dictionary<string,string> GetControlParseDictO()
        {
            return new Dictionary<string, string>()
            {
                { "Name", tbOutName.Text },
                {"Money", tbOutMoney.Text }
            };

        }
        private void btnAddO_Click(object sender, EventArgs e)      //지출 추가 버튼 클릭
        {
            if (GetControlParseCaseO() != ControlParseCase.None) return;
            for(int i = 0; i < tbOutMoney.TextLength; i++)
            {
                if (!Char.IsDigit(tbOutMoney.Text[i]))
                {
                    MessageBox.Show("지출 금액은 숫자만 입력해 주세요!");
                    tbOutMoney.Clear();
                    return;
                }
            }
            var lvwItem = new ListViewItem(new string[lvwOutgo.Columns.Count]);

            for (int i = 0; i < lvwOutgo.Columns.Count; i++)
                lvwItem.SubItems[i].Name = lvwOutgo.Columns[i].Name;

            var controlParseDict = GetControlParseDictO();
            foreach (string item in controlParseDict.Keys)
                lvwItem.SubItems[item].Text = controlParseDict[item];

            lvwOutgo.Items.Add(lvwItem);

            clearControlsO();

            EvalOutgo();

            Total();
        }

        private void btnDelO_Click(object sender, EventArgs e)      //지출 삭제 버튼 클릭
        {
            if (lvwOutgo.FocusedItem == null) return;
            lvwOutgo.FocusedItem.Remove();
            EvalOutgo();
            Total();
        }
        private void EvalOutgo()                               //총 지출 계산
        {
            int sum = 0;
            for (int i = 0; i < lvwOutgo.Items.Count; i++)
            {
                var lvwitems = new ListViewItem(new string[lvwOutgo.Columns.Count]);
                lvwitems = lvwOutgo.Items[i];
                sum += Int32.Parse(lvwitems.SubItems["money"].Text);
            }
            lblOutgo.Text = "총 지출 : " + sum + "원";
        }
        private void clearControlsI()               //수입 내용입력 박스 클리어
        {
            tbInMoney.Clear();
            tbInName.Clear();
        }                       
        private ControlParseCase GetControlParseCaseI()
        {
            if (string.Equals(tbInMoney.Text, String.Empty)) return ControlParseCase.Money;
            else if (string.Equals(tbInName.Text, String.Empty)) return ControlParseCase.Name;
            return ControlParseCase.None;
        }
        private Dictionary<string, string> GetControlParseDictI()
        {
            return new Dictionary<string, string>()
            {
                { "Name", tbInName.Text },
                {"Money", tbInMoney.Text }
            };

        }
        private void btnAddI_Click(object sender, EventArgs e)      //수입 추가 버튼 클릭
        {
            if (GetControlParseCaseI() != ControlParseCase.None) return;

            for (int i = 0; i < tbInMoney.TextLength; i++)
            {
                if (!Char.IsDigit(tbInMoney.Text[i]))
                {
                    MessageBox.Show("수입 금액은 숫자만 입력해 주세요!");
                    tbInMoney.Clear();
                    return;
                }
            }

            var lvwItem = new ListViewItem(new string[lvwIncome.Columns.Count]);

            for (int i = 0; i < lvwIncome.Columns.Count; i++)
                lvwItem.SubItems[i].Name = lvwIncome.Columns[i].Name;

            var controlParseDict = GetControlParseDictI();
            foreach (string item in controlParseDict.Keys)
                lvwItem.SubItems[item].Text = controlParseDict[item];

            lvwIncome.Items.Add(lvwItem);
            clearControlsI();
            EvalIncome();
            Total();
        }

        private void btnDelI_Click(object sender, EventArgs e)      //수입 삭제 버튼 클릭
        {
            if (lvwIncome.FocusedItem == null) return;
            lvwIncome.FocusedItem.Remove();
            EvalIncome();
            Total();
        }
        private void EvalIncome()               //총 수입 계산
        {
            int sum = 0;
            for (int i = 0; i < lvwIncome.Items.Count; i++)
            {
                var lvwitems = new ListViewItem(new string[lvwIncome.Columns.Count]);
                lvwitems = lvwIncome.Items[i];
                sum += Int32.Parse(lvwitems.SubItems["Money"].Text);
            }

            lblIncome.Text = "총 수입 : " + sum + "원";
        }
        private void Total()                    //총 자산 계산
        {
            int total = 0;
 
            for (int i = 0; i < lvwIncome.Items.Count; i++)
            {
                var lvwitems = new ListViewItem(new string[lvwIncome.Columns.Count]);
                lvwitems = lvwIncome.Items[i];
                total += Int32.Parse(lvwitems.SubItems["money"].Text);
            }
            for (int i = 0; i < lvwOutgo.Items.Count; i++)
            {
                var lvwitems = new ListViewItem(new string[lvwOutgo.Columns.Count]);
                lvwitems = lvwOutgo.Items[i];
                total -= Int32.Parse(lvwitems.SubItems["money"].Text);
            }
            lblSum.Text = ("총 자산 : "+total+"원");
        }
        
        private void LoadData()                 //파일 읽어오기
        {
            LoadOutgo();
            LoadIncome();
        }
        public void LoadOutgo()                 //파일 읽어오기_지출
        {
            string FileName = "Data\\" + lblTime.Text + "지출.txt";
            if (!File.Exists(FileName))
            {
                return;
            }
            else
            {
                StreamReader sr = new StreamReader(FileName);
                while (true)
                {
                    string read = sr.ReadLine();
                    if (read == null)
                        break;

                    string name = null;
                    string money = null;
                    string[] list = read.Split(':');
                    string[] list2 = list[1].Split(' ');

                    name = list2[1];
                    money = list[2].Trim();

                    var lvwItem = new ListViewItem(new string[lvwOutgo.Columns.Count]);

                    for (int i = 0; i < lvwOutgo.Columns.Count; i++)
                        lvwItem.SubItems[i].Name = lvwOutgo.Columns[i].Name;

                    lvwItem.SubItems["Name"].Text = name;
                    lvwItem.SubItems["Money"].Text = money;

                    lvwOutgo.Items.Add(lvwItem);
                }
                sr.Close();
                EvalIncome();
                EvalOutgo();
                Total();
            }
        }
        public void LoadIncome()                //파일 읽어오기_수입
        {
            string FileName = "Data\\" + lblTime.Text + "수입.txt";
            if (!File.Exists(FileName))
            {
                return;
            }
            else
            {
                StreamReader sr = new StreamReader(FileName);
                while (true)
                {
                    string read = sr.ReadLine();
                    if (read == null)
                        break;

                    string name = null;
                    string money = null;
                    string[] list = read.Split(':');
                    string[] list2 = list[1].Split(' ');

                    name = list2[1];
                    money = list[2].Trim();

                    var lvwItem = new ListViewItem(new string[lvwIncome.Columns.Count]);

                    for (int i = 0; i < lvwIncome.Columns.Count; i++)
                        lvwItem.SubItems[i].Name = lvwIncome.Columns[i].Name;

                    lvwItem.SubItems["Name"].Text = name;
                    lvwItem.SubItems["Money"].Text = money;

                    lvwIncome.Items.Add(lvwItem);
                }
                sr.Close();
                EvalIncome();
                EvalOutgo();
                Total();
            }
        }
        private void btnSave_Click(object sender, EventArgs e)      //가계부 저장버튼 클릭
        {
            SaveData();
        }
        private void SaveData()                 //가계부 저장
        {
            try
            {
                string FileName = "Data\\" + lblTime.Text + "지출.txt";
                StreamWriter sw = new StreamWriter(FileName);
                for (int i = 0; i < lvwOutgo.Items.Count; i++)
                {
                    var lvwitems = new ListViewItem(new string[lvwOutgo.Columns.Count]);
                    lvwitems = lvwOutgo.Items[i];

                    sw.WriteLine("Name : " + lvwitems.SubItems["Name"].Text + " Money : " + lvwitems.SubItems["Money"].Text);
                }
                sw.Close();
            }
            catch
            {
                MessageBox.Show("지출 파일 저장 실패.");
            }
            try
            {
                string FileName = "Data\\" + lblTime.Text + "수입.txt";
                StreamWriter sw = new StreamWriter(FileName);
                for (int i = 0; i < lvwIncome.Items.Count; i++)
                {
                    var lvwitems = new ListViewItem(new string[lvwIncome.Columns.Count]);
                    lvwitems = lvwIncome.Items[i];

                    sw.WriteLine("Name : " + lvwitems.SubItems["Name"].Text + " Money : " + lvwitems.SubItems["Money"].Text);
                }
                sw.Close();
            }
            catch
            {
                MessageBox.Show("수입 파일 저장 실패.");
            }
            MessageBox.Show("저장 완료.");
        }
    }
}
