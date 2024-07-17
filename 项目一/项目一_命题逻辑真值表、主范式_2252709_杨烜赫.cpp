// ReSharper disable all
#include <iostream>
#include <windows.h>
#include<iomanip>
#include <string>
#include <cmath>
#include <set>
#include <stack>
using namespace std;
// ������Titleչʾ
void PrintMenu()
{
	printf("***************************************\n");
	printf("**                                   **\n");
	printf("**         ��ӭ�����߼��������      **\n");
	printf("**   (��������ֵ��,����ʽ,֧������)  **\n");
	printf("**                                   **\n");
	printf("**              ��!��ʾ��            **\n");
	printf("**              ��&��ʾ��            **\n");
	printf("**              ��|��ʾ��            **\n");
	printf("**             ��^��ʾ�̺�           **\n");
	printf("**             ��~��ʾ��ֵ           **\n");
	printf("**                                   **\n");
	printf("***************************************\n\n");
	printf("������һ���Ϸ������⹫ʽ�������Ԫ���ƴ�Сд���У���ʹ��Ӣ�����ţ�:\n");

}
// ��ֵ����
class truth_table
{
public:
	// ���캯������������ı��ʽ����
	truth_table(const string a = "");
	// �����������ͷ��ڴ�
	~truth_table() { delete[]variables, delete[]principal_conjunctive_normal_form, delete[]principal_disjunctive_normal_form; };
	// �����ֵ��
	void print_truth_table();
	// �������ʽ
	void print_main_paradigm();

	// �����ṹ����
	struct variable
	{
		char name;  // ������
		bool value; // ����ֵ0��1
	};

private:
	variable* variables;  // �洢����
	int* principal_disjunctive_normal_form;  // ����ȡ��ʽ
	int* principal_conjunctive_normal_form;  // ����ȡ��ʽ
	int variable_number = 0;  // ��������
	string expression;  // ���ʽ�ַ���
	void print_variables_names();  // ��ӡ������
	void init_variable_value(int num);  // ��ʼ������ֵ
	void print_variable_value();  // ��ӡ����ֵ
	bool calculate_expression();  // ������ʽֵ
	string switch_number();  // �滻����
	bool calculate_variable(const bool a, const char c, const bool b);  // �������
	int compare(const char a, const char b);  // �Ƚ���������ȼ�
};
truth_table::truth_table(const string a)
{
	variable temp_expression[50];
	int num = 0;
	for(int i=0;i<a.length();i++)
	{
		judge:if(isalpha(a[i]))
		{
			for(int j=0;j<num;j++)
			{
				if(a[i]==temp_expression[j].name)
				{
					i++;
					goto judge;
				}
			}
			temp_expression[num].name = a[i];
			temp_expression[num].value = 0;
			num++;

		}
	}
	variables = new variable[num];
	variable_number = num;
	expression = a;
	principal_conjunctive_normal_form = new int[pow(2, num)];
	principal_disjunctive_normal_form = new int[pow(2, num)];
	cout << "�ñ��ʽ�б����ĸ���Ϊ��" << num << endl;
	cout << "�ֱ��ǣ�";
	for(int i=0;i<num;i++)
	{
		cout << temp_expression[i].name << "  ";
		variables[i] = temp_expression[i];
	}
	cout << endl;
}
void truth_table::print_truth_table()
{
	//���������������
	print_variables_names();
	//��ֵ��2��n�η���
	int lines_num = pow(2, variable_number);
	for(int i=0;i<lines_num;i++)
	{
		init_variable_value(i);
		print_variable_value();
	}
}
void truth_table::print_main_paradigm()
{
	int lines_num = pow(2, variable_number);
	std::set<int> conjunctive_set; // ʹ�ü����������ظ�
	set<int> disjunctive_set;

	for (int i = 0; i < lines_num; i++)
	{
		init_variable_value(i);
		if (calculate_expression())
		{
			// ����������ȡ��ʽ����
			disjunctive_set.insert(i);
		}
		else
		{
			// ����������ȡ��ʽ����
			conjunctive_set.insert(i);
		}
	}
	// �������ȡ��ʽ
	if (!conjunctive_set.empty())
	{
		cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
		for (auto it = conjunctive_set.begin(); it != conjunctive_set.end(); ++it)
		{
			if (it != conjunctive_set.begin())
			{
				cout << "\\/";
			}
			cout << "M(" << *it << ")";
		}
		cout << endl;
	}
	else
	{
		cout << "�����⹫ʽ����������ȡ��ʽ��" << endl;
	}

	// �������ȡ��ʽ
	if (!disjunctive_set.empty())
	{
		cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
		for (auto it = disjunctive_set.begin(); it != disjunctive_set.end(); ++it)
		{
			if (it != disjunctive_set.begin())
			{
				cout << "/\\";
			}
			cout << "M(" << *it << ")";
		}
		cout << endl;
	}
	else
	{
		cout << "�����⹫ʽ����������ȡ��ʽ��" << endl;
	}
}
void truth_table::print_variables_names()
{
	for(int i=0;i<variable_number;i++)
	{
		cout << setiosflags(ios::right) << setw(3) << variables[i].name;  // �����������
	                          // ������ʽ����
	}
	cout << "  " << expression << endl << endl;
}
void truth_table::init_variable_value(int num)
{
	int temp = variable_number;
	while(temp)
	{
		variables[temp - 1].value = num % 2;
		num /= 2;
		temp--;
	}
}
void truth_table::print_variable_value()
{
	for(int i=0;i<variable_number;i++)
	{
		cout << setiosflags(ios::right) << setw(3) << variables[i].value;  // ���������ֵ
	}
	cout << "  " << calculate_expression() << endl << endl;
}
bool truth_table::calculate_expression()
{
	stack<bool> stack1;        // ������ֵ�ջ
	stack<char> stack2;        // ����������ջ
	string s = switch_number();   // ����ĸ����ת��Ϊ���ֺ�Ĺ�ʽ

	// ģ�⽫���ʽ��������ţ����жϽ�����־
	s += ')';
	stack2.push('(');
	for (size_t i = 0; i < s.length(); i++) {
		// ���ʽ��λ��Ϊ0/1��ֱ����ջ
		if (isdigit(s[i])) stack1.push(s[i] - '0');

		else {
			if (s[i] == '(') stack2.push(s[i]);

			else if (s[i] == ')') {
				if (stack2.empty()) continue;

				while (stack2.top() != '(') {
					if (stack2.top() == '!') {
						bool a = stack1.top(); stack1.pop();
						stack1.push(!a);
						stack2.pop();
						i--;
					}
					else {
						bool b = stack1.top(); stack1.pop();
						bool a = stack1.top(); stack1.pop();
						stack1.push(calculate_variable(a, stack2.top(), b));
						stack2.pop();
					}
				}
				stack2.pop(); // �����ų�ջ
			}

			else if (compare(stack2.top(), s[i]) == -1) stack2.push(s[i]);
			else if (compare(stack2.top(), s[i]) == 0) stack2.pop();
			else if (compare(stack2.top(), s[i]) == 1) {
				while (!stack2.empty() && stack2.top() != '(' && compare(stack2.top(), s[i]) >= 1) {
					if (stack2.top() == '!') {
						bool a = stack1.top(); stack1.pop();
						stack1.push(!a);
						stack2.pop();
					}
					else {
						bool b = stack1.top(); stack1.pop();
						bool a = stack1.top(); stack1.pop();
						stack1.push(calculate_variable(a, stack2.top(), b));
						stack2.pop();
					}
				}
				stack2.push(s[i]);
			}
		}
	}
	return stack1.top();
}
string truth_table::switch_number()
{
	string set = expression;
	for (int i = 0; i < expression.length(); i++)
	{
		if(isalpha(expression[i]))
		{
			for(int j=0;j<variable_number;j++)
			{
				if (variables[j].name == expression[i])
				{
					set[i] = variables[j].value + '0';
					break;
				}
			}
		}
    }
	return set;

}
bool truth_table::calculate_variable(const bool a, const char c, const bool  b)
{
	if (c == '&') return a & b;    // ��ȡ 
	if (c == '|') return a | b;    // ��ȡ
	if (c == '^') return (!a) | b; // �̺�
	if (c == '~') return a == b;   // ��ֵ
}
int truth_table::compare(const char a, const char b)
{
	if (a == '!')
	{
		if (b == '(') return -1;
		else if (b == '!') return 0;
		else return 1;
	}
	else if (a == '&')
	{
		if ((b == '(' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '|')
	{
		if ((b == '&' || b == '(' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '^')
	{
		if ((b == '&' || b == '(' || b == '|' || b == '!')) return -1;
		else return 1;
	}
	else if (a == '~')
	{
		if ((b == '~' || b == ')')) return 1;
		else return -1;
	}
	else if (a == '(')  return -1;
}
int main()
{
	PrintMenu();
	string expression;
	cin >> expression;
	truth_table Truthtable(expression);
	cout << endl << "�����ֵ�����£�" << endl << endl;
	Truthtable.print_truth_table();
	Truthtable.print_main_paradigm();
	system("pause");
	return 0;
}
