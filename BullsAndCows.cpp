	#include "std_lib_facilities.h"
//1.램덤숫자 출력(예외함수)
//2.내가쓴 숫자 나오게(예외함수)
//예외함수
//try catch 함수아니라 자료형 예외처리
//3.결과함수
//게임함수: 내가쓴숫자랑 1,2 램덤숫자 넣어서 bulls and cows 결과함수 출력
vector<int>v(4);	//v=my input num
vector<int>v1(4);//v1=random num

void Random()
{
	for (int i = 0; i < 4; i++)
	{
		v1[i] = (randint(9));
		for (int a = 0; a < i; a++)

			if (v1[i] == v1[a] && i != a)
				i--;
	}
	
}
void mynum()
{
		cout << "press the number1~9:" << " ";
		cin >> v[0] >> v[1] >> v[2] >> v[3];
		
		
		if (!cin)
			error("It's not number");
		if (v[0] < 0 || v[0]>9 ||
			v[1] < 0 || v[1]>9 ||
			v[2] < 0 || v[2]>9 ||
			v[3] < 0 || v[3]>9
			)
		{
			error("number is out of range");
		}
		if (v[0] == v[1] || v[0] == v[2] ||
			v[0] == v[3] || v[1] == v[2] ||
			v[1] == v[3] || v[2] == v[3])
		{
			error("number is same");
		}
		



	//}
}
bool playagain()
{
	char choice;
	cout << "Do you want to play again??:(y/n)" << endl;
	cin >> choice;
	
	switch (choice)
	{
	case 'y':
		return true;
	case 'n':
		return false;
	}
}

void bullsandcows()
{
	int a, b;
	int bulls = 0;
	int cows = 0;
	int count = 0;
	bool yn = true;

	while (yn)
	{
		while (count < 10)
		{
			mynum();
			bulls = 0, cows = 0;
			for (b = 0; b < 4; b++)
			{
				for (a = 0; a < 4; a++)
					if (v1[b] == v[a])
						if (a == b)
							bulls++;
						else//a!==b;
							cows++;
			}

			//확인 결과를 출력
			if (bulls > 0 || cows > 0)
				cout << "bulls" << bulls << " cows:" << cows << endl << endl;
			else if (bulls == 0 && cows == 0)//no bulls no cows
				cout << "no match" << endl << endl;
			else
				cout << "error" << endl;


			if (bulls == 4)//if all num is right
			{
				cout << " victory!!" << endl << endl;
				count = 0;
				break;

			}
			if (count == 9)// you used all your chances defeated
			{
				cout << "you lost:" << endl;
				count = 0;
				break;
			}
			count++;
		}
		yn = playagain();
	}
}

	
int main()
{
	cout << "start the game bulls and cows" << " ";

	try {
		Random();
		bullsandcows();
	}catch(runtime_error& e)
	{
		cerr << "Error:" << e.what() << endl;
	}
		
	keep_window_open();
	

	return 0;
}