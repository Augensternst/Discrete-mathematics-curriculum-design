// ReSharper disable all
#include <iostream>
#include <windows.h>
#include<iomanip>
#include <string>
#include <cmath>
#include <set>
#include <stack>
using namespace std;
// 计算器Title展示
void PrintMenu()
{
	printf("***************************************\n");
	printf("**                                   **\n");
	printf("**         欢迎进入逻辑运算软件      **\n");
	printf("**   (可运算真值表,主范式,支持括号)  **\n");
	printf("**                                   **\n");
	printf("**              用!表示非            **\n");
	printf("**              用&表示与            **\n");
	printf("**              用|表示或            **\n");
	printf("**             用^表示蕴含           **\n");
	printf("**             用~表示等值           **\n");
	printf("**                                   **\n");
	printf("***************************************\n\n");
	printf("请输入一个合法的命题公式（命题变元名称大小写敏感，请使用英文括号）:\n");

}
// 真值表类
class truth_table
{
public:
	// 构造函数，根据输入的表达式构建
	truth_table(const string a = "");
	// 析构函数，释放内存
	~truth_table() { delete[]variables, delete[]principal_conjunctive_normal_form, delete[]principal_disjunctive_normal_form; };
	// 输出真值表
	void print_truth_table();
	// 输出主范式
	void print_main_paradigm();

	// 变量结构定义
	struct variable
	{
		char name;  // 变量名
		bool value; // 变量值0或1
	};

private:
	variable* variables;  // 存储变量
	int* principal_disjunctive_normal_form;  // 主析取范式
	int* principal_conjunctive_normal_form;  // 主合取范式
	int variable_number = 0;  // 变量数量
	string expression;  // 表达式字符串
	void print_variables_names();  // 打印变量名
	void init_variable_value(int num);  // 初始化变量值
	void print_variable_value();  // 打印变量值
	bool calculate_expression();  // 计算表达式值
	string switch_number();  // 替换数字
	bool calculate_variable(const bool a, const char c, const bool b);  // 计算变量
	int compare(const char a, const char b);  // 比较运算符优先级
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
	cout << "该表达式中变量的个数为：" << num << endl;
	cout << "分别是：";
	for(int i=0;i<num;i++)
	{
		cout << temp_expression[i].name << "  ";
		variables[i] = temp_expression[i];
	}
	cout << endl;
}
void truth_table::print_truth_table()
{
	//先输出各变量名称
	print_variables_names();
	//真值表共2的n次方行
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
	std::set<int> conjunctive_set; // 使用集合来避免重复
	set<int> disjunctive_set;

	for (int i = 0; i < lines_num; i++)
	{
		init_variable_value(i);
		if (calculate_expression())
		{
			// 添加新项到主析取范式集合
			disjunctive_set.insert(i);
		}
		else
		{
			// 添加新项到主合取范式集合
			conjunctive_set.insert(i);
		}
	}
	// 输出主合取范式
	if (!conjunctive_set.empty())
	{
		cout << "该命题公式的主合取范式：" << endl;
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
		cout << "该命题公式不存在主合取范式。" << endl;
	}

	// 输出主析取范式
	if (!disjunctive_set.empty())
	{
		cout << "该命题公式的主析取范式：" << endl;
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
		cout << "该命题公式不存在主析取范式。" << endl;
	}
}
void truth_table::print_variables_names()
{
	for(int i=0;i<variable_number;i++)
	{
		cout << setiosflags(ios::right) << setw(3) << variables[i].name;  // 输出变量名称
	                          // 输出表达式名称
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
		cout << setiosflags(ios::right) << setw(3) << variables[i].value;  // 输出变量的值
	}
	cout << "  " << calculate_expression() << endl << endl;
}
bool truth_table::calculate_expression()
{
	stack<bool> stack1;        // 存放数字的栈
	stack<char> stack2;        // 存放运算符的栈
	string s = switch_number();   // 将字母变量转换为数字后的公式

	// 模拟将表达式整体加括号，以判断结束标志
	s += ')';
	stack2.push('(');
	for (size_t i = 0; i < s.length(); i++) {
		// 表达式该位置为0/1，直接入栈
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
				stack2.pop(); // 左括号出栈
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
	if (c == '&') return a & b;    // 合取 
	if (c == '|') return a | b;    // 析取
	if (c == '^') return (!a) | b; // 蕴涵
	if (c == '~') return a == b;   // 等值
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
	cout << endl << "输出真值表如下：" << endl << endl;
	Truthtable.print_truth_table();
	Truthtable.print_main_paradigm();
	system("pause");
	return 0;
}
