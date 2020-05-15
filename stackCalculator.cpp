//Visual 2019 version

#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <cstring>
#include <math.h>

using namespace std;
void evaluate_stack(stack<double>& numbers, stack<char>& operations)//
{
	double operand1, operand2;
	operand2 = numbers.top();//���װ�� 10+2 ó��
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();
	switch (operations.top())//�迭 ���ڿ� ��
	{
	case '+': numbers.push(operand1 + operand2); break;
	case '-': numbers.push(operand1 - operand2); break;
	case '*': numbers.push(operand1 * operand2); break;
	case '/': numbers.push(operand1 / operand2); break;

	}
	//operands
	operations.pop();
}
void read_and_evaluate(istream& ins)
{
	const char DECIMAL = '.';
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';
	const char BIGRIGHT_PARENTHESIS = '}';
	const char BIGLEFT_PARENTHESIS = '{';
	const char BIGGESTRIGHT_PARENTHESIS = ']';
	const char BIGGESTLEFT_PARENTHESIS = '[';
	stack<double> numbers;
	stack <char> operations;
	double number;
	char symbol;
	int DIVIDE=0;
	char parenthes='P';
	
	while (ins && ins.peek() != '\n')
	{
		//1 ���� �Է�
		if (isdigit(ins.peek()))
		{
			ins >> number;
			numbers.push(number);
		}
		//EOI

		else if (strchr("E", ins.peek()) !=NULL)
		{
			ins >> symbol;
			operations.push(symbol);
		}
		else if (strchr("O", ins.peek()) != NULL)
		{
			ins >> symbol;
			operations.push(symbol);
		}
		else if (strchr("I", ins.peek()) != NULL)
		{
			ins >> symbol;
			operations.push(symbol);
		}


		
		//2
		else if (strchr("+-*/", ins.peek()) != NULL)
		{
			ins >> symbol;//+-/*�� ���µ� �Ʒ��� ���� ���������

			if (strchr("+-", symbol) != NULL)//operation stack�� +- ���� */�̸� ���� */ ���� ���
			{
				while (!operations.empty() && strchr("*/", operations.top()) != NULL)//���� */�϶� ��,+-�� �������� 
				{
					if (strchr("/", operations.top()) != NULL && numbers.top() == 0) {
					
						DIVIDE = 1;
						operations.pop();
					}
					else
						evaluate_stack(numbers, operations);
				}
			}
			else if (strchr("*/", symbol) != NULL)
			{
				while (!operations.empty() && strchr("*/", operations.top()) != NULL)
				{
					if (strchr("/", operations.top() != NULL && numbers.top() == 0))
					{
					
						DIVIDE = 1;
						operations.pop();
					}
					else
						evaluate_stack(numbers, operations);
				}
			}
			operations.push(symbol);
		}
		//3 ��ȣ
		else if (ins.peek() == RIGHT_PARENTHESIS) //������ ��ȣ�� ���ö� ��� peek�� �������� �� )
		{
			ins.ignore();
			while (operations.top() != '(') {
				
					evaluate_stack(numbers, operations);
			}
			
			operations.pop();
		}
		else if (ins.peek() == LEFT_PARENTHESIS)//(
		{
			ins >> symbol;
			operations.push(symbol);
		}
		//
		else if (ins.peek() == BIGRIGHT_PARENTHESIS) //}
		{ 
			{
				ins.ignore();

				while (operations.top() != '{') {
					if (operations.top() == '{')
					{
						cout << "Error unbalanced parentheses" << endl;
						break;
					}
				else if (strchr("/", operations.top()) != NULL && numbers.top() == 0) {
						DIVIDE = 1;
						operations.pop();
					}
				  
						else 
						evaluate_stack(numbers, operations);
				}
				operations.pop();
			}
		}
		else if (ins.peek() == BIGLEFT_PARENTHESIS)//{
		{
			ins >> symbol;
			operations.push(symbol);
		}
		else if (ins.peek() == BIGGESTRIGHT_PARENTHESIS) //]
		{
			{
				ins.ignore();

				while (operations.top() != '[') {
					if (operations.top() == '[')
					{
						cout << "Error unbalanced parentheses" << endl;
						break;
					}
					else if (strchr("/", operations.top()) != NULL && numbers.top() == 0) {
				
						DIVIDE = 1;
						operations.pop();
					}
					
					else evaluate_stack(numbers, operations);
				}
				operations.pop();
			}
		}
		//��ȣ ������ ���
		else if (ins.peek() == BIGGESTLEFT_PARENTHESIS)//[
		{

			ins >> symbol;
			operations.push(symbol);
		}
		
		//
		else
		ins.ignore();
		
	}
	
	while (!operations.empty()) {
		if (strchr("/", operations.top()) != NULL && numbers.top() == 0) {
			
			DIVIDE = 1;
			operations.pop();
		}
		else if (operations.top() == 'I')
		{
			operations.pop();
			if (operations.top() == 'O')
			{
				operations.pop();
				if (operations.top() == 'E')
				{

					cout << "EOI end of input" << "\n";
					exit(1);

				}
			}
		}
		else
			evaluate_stack(numbers, operations);
	}
	if (DIVIDE == 1)
		cout << "Error! divided by 0" << "\n";
	else if (parenthes == 'N')
		cout << "Error! Unbalanced parentheses"<<endl;
	else
		cout << numbers.top() << endl;


}

int main() {
	cout << fixed;
	cout.precision(3);//�Ҽ���3���� ����
	
		while (1) {

			read_and_evaluate(cin);
			cin.ignore();
		}
		return 0;
	}

//�켱������ ������ +_-, /*, ��ȣ ��� �ԷµȰ��� infix postfix���·� �ٲپ� ��Ÿ����
//+-�� ���Դµ� �տ� */�� ������ �տ� ������ ������ֱ� ������ ���� while(operation.empty)�϶� ���� number.top
//*/({[�� ���� �ϰ�
