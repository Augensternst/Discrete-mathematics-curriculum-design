// ReSharper disable All
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class matrix
{
private:
	int row;
	int col;
	void dfs(int u, int v);//dfs辅助函数
	void display_matrix(int arr[100][100]);
public:
	matrix();
	~matrix() {};
	int root_matrix[100][100];
	int result_matrix[100][100];
	int choice;
	void menu();
	void input();
	void reflexive_closure();//自反闭包
	void symmetric_closure();//对称闭包
	void transitive_closure();//传递闭包
};

matrix::matrix()
{
	row = 0;
	col = 0;
	memset(root_matrix, 0, sizeof(root_matrix));
	memset(result_matrix, 0, sizeof(result_matrix));
	choice = 0;
}

void matrix::menu()
{
	cout << endl << "输入序号选择对应算法：" << endl;
	cout << "1.自反闭包" << endl;
	cout << "2.对称闭包" << endl;
	cout << "3.传递闭包" << endl;
	cout << "4.退出" << endl;
	cout << "请输入：";
	while(true)
	{
		choice = 0;
		cin >> choice;
		if(choice<1||choice>4||!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入！" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
}

void matrix::input()
{

	cout << "请输入矩阵的行数：";
	cin >> row;
	cout << endl;
	cout << "请输入矩阵的列数(请保证行数和列数相同)：";
	cin >> col;
	cout << endl;
	cout << "请输入关系矩阵：" << endl;
	for(int i=0;i<row;i++)
	{
		cout << endl << "请输入矩阵第" << i << "行(以空格分隔)：";
		for(int j=0;j<col;j++)
		{
			string errorTips = "第";
			errorTips += char(i + '0');
			errorTips += "行";
			errorTips += char(j + '0');
			errorTips += "列输入错误，请从此处开始重新输入本行元素:";
			for(int k=0;k<j;k++)
			{
				errorTips += char(root_matrix[i][k] + '0');
				errorTips += ' ';
			}
			while(true)
			{
				int n;
				cin >> n;
				if(n!=0&&n!=1||!cin.good())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << errorTips ;
					continue;
				}
				else
				{
					root_matrix[i][j] = n;
					break;
				}
			}
		}
	}
	cout << endl << "初始化结束，当前矩阵为：" << endl;
	display_matrix(root_matrix);
}

void matrix::display_matrix(int arr[100][100])
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout << setiosflags(ios::left) << setw(2) << arr[i][j];
		}
		cout << endl;
	}
}

void matrix::reflexive_closure()
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			if (i == j)
				result_matrix[i][j] = 1;
			else
			{
				result_matrix[i][j] = root_matrix[i][j];
			}
		}
	}
	cout << endl << "所求关系闭包为：" << endl;
	display_matrix(result_matrix);
}

void matrix::symmetric_closure()
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			result_matrix[i][j] = root_matrix[i][j] | root_matrix[j][i];

		}
	}
	cout << endl << "所求关系闭包为：" << endl;
	display_matrix(result_matrix);
}

void matrix::transitive_closure()
{
	// 复制原始矩阵到结果矩阵
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result_matrix[i][j] = root_matrix[i][j];
		}
	}
	// 更新传递闭包
	for (int k = 0; k < row; k++) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (result_matrix[i][k] && result_matrix[k][j]) {
					result_matrix[i][j] = 1;
				}
			}
		}
	}
	cout << endl << "所求关系闭包为：" << endl;
	display_matrix(result_matrix);
}

void matrix::dfs(int u, int v)
{
	for (int i = 0; i < row; ++i) {
		if (root_matrix[v][i] == 1 && result_matrix[u][i] == 0) {
			result_matrix[u][i] = 1;
			dfs(v, i);
		}
	}
}

int main()
{
	matrix Matrix;
	int choice;
	
		Matrix.input();
		Matrix.menu();

		choice = Matrix.choice;

		switch (choice) {
		case 1:
			Matrix.reflexive_closure();
			break;
		case 2:
			Matrix.symmetric_closure();
			break;
		case 3:
			Matrix.transitive_closure();
			break;
		case 4:
			cout << "程序结束，感谢使用！" << endl;
			break; // 选择退出时，返回0结束程序
		default:
			cout << "无效的选项，请重新选择。" << endl;
		}
		system("pause");
	return 0;
}
