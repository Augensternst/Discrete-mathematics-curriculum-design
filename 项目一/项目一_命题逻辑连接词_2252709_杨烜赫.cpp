
#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	int p = -1;
	int q = -1;
	tt:cout << "***************************************" << endl;  //标语
	cout<<"**                                   **"<<endl;
	cout << "**        欢迎进入逻辑运算程序       **" << endl;
	cout << "**                                   **" << endl;
	cout<<"***************************************"<<endl;
	cout << endl;
	cout << "请输入P的值（0或1）,以回车结束:";
	while(true)
	{
		cin >> p;
		if(!cin.good()||p!=0&&p!=1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "P的值输入有误,请重新输入!" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	cout << "请输入Q的值（0或1）,以回车结束:";
	while(true)
	{
		cin >> q;
		if(!cin.good()||q!=0&&q!=1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Q的值输入有误,请重新输入!" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	cout << endl;
	cout << endl;
    cout << "  合取:\n       P/\\Q = " << (p & q) << endl; // 合取式p∧q，在变量运算中为 p & q
    cout << "  析取:\n       P\\/Q = " << (p | q) << endl; // 析取式p∨q，在变量运算中为 p | q
    cout << "  条件:\n       P→Q = " << ((!p) | q) << endl; // 条件运算式p→q，即(!p)∨q，在变量运算中为(!p)|q
    cout << "  双条件:\n       P<->Q = " << (((!p) | q) & ((!q) | p)) << endl; // 双向条件运算p↔q，即(p→q)∧(q→p)，在变量运算中表示为((!p) | q) & ((!q) | p)

	cout << endl;
	cout << endl;
	cout << "是否重新开始进行新的运算，y表示同意，n表示结束：";
	char command;
	while(true)
	{
		cin >> command;
		if(command == 'y')
		{
			cin.clear();
			cin.ignore(1024, '\n');
			system("cls");
			goto tt;
		}
		if(command=='n')
		{
			break;
		}
		else
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;

		}
	}
	cout << endl;
	cout << "程序结束，完结撒花!!!" << endl;
	return 0;


}