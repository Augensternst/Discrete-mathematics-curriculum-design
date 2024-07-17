#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
int row, col;
int root_matrix[100][100];
int result_matrix[100][100];
void display_matrix(int arr[100][100])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << setiosflags(ios::left) << setw(2) << arr[i][j];
		}
		cout << endl;
	}
}
void input()
{
	cout << "请输入矩阵的行数：";
	cin >> row;
	cout << endl;
	cout << "请输入矩阵的列数(请保证行数和列数相同)：";
	cin >> col;
	cout << endl;
	cout << "请输入关系矩阵：" << endl;
	for (int i = 0; i < row; i++)
	{
		cout << endl << "请输入矩阵第" << i << "行(以空格分隔)：" << endl;
		for (int j = 0; j < col; j++)
		{
			string errorTips = "第";
			errorTips += char(i + '0');
			errorTips += "行";
			errorTips += char(j + '0');
			errorTips += "列输入错误，请从此处开始重新输入本行元素:";
			errorTips += '\n';// 得到当前矩阵元素输入错误对应提示
			for (int k = 0; k < j; k++)
			{
				errorTips += char(root_matrix[i][k] + '0');
				errorTips += ' ';
			}
			while (true)
			{
				int n;
				cin >> n;
				if (n != 0 && n != 1 || !cin.good())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << errorTips << endl;
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
void Warshall()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result_matrix[i][j] = root_matrix[i][j];
		}
	}
	for (int k = 0; k < row; k++) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result_matrix[i][j] = result_matrix[i][j] || (result_matrix[i][k] && result_matrix[k][j]);
			}
		}
	}

	cout << endl << "所求关系闭包为：" << endl;
	display_matrix(result_matrix);
}
int main()
{
	input();
	Warshall();
	system("pause");
	return 0;
}