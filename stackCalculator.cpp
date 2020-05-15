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
	operand2 = numbers.top();//이항계산 10+2 처럼
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();
	switch (operations.top())//배열 문자열 비교
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
		//1 숫자 입력
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
			ins >> symbol;//+-/*가 들어갔는데 아래는 이제 따져줘야지

			if (strchr("+-", symbol) != NULL)//operation stack에 +- 전에 */이면 전의 */ 부터 계산
			{
				while (!operations.empty() && strchr("*/", operations.top()) != NULL)//위가 */일때 즉,+-가 나왔을때 
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
		//3 괄호
		else if (ins.peek() == RIGHT_PARENTHESIS) //오른쪽 괄호가 들어올때 계산 peek는 꺼내오는 것 )
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
		//괄호 에러문 출력
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
	cout.precision(3);//소수점3까지 제한
	
		while (1) {

			read_and_evaluate(cin);
			cin.ignore();
		}
		return 0;
	}

//우선순위를 정하자 +_-, /*, 괄호 등등 입력된것을 infix postfix형태로 바꾸어 나타내자
//+-가 나왔는데 앞에 */가 있으면 앞에 꺼먼저 계산해주기 마지막 조건 while(operation.empty)일때 까지 number.top
//*/({[는 먼저 하고
