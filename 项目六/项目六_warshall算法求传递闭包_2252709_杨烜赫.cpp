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
	cout << "����������������";
	cin >> row;
	cout << endl;
	cout << "��������������(�뱣֤������������ͬ)��";
	cin >> col;
	cout << endl;
	cout << "�������ϵ����" << endl;
	for (int i = 0; i < row; i++)
	{
		cout << endl << "����������" << i << "��(�Կո�ָ�)��" << endl;
		for (int j = 0; j < col; j++)
		{
			string errorTips = "��";
			errorTips += char(i + '0');
			errorTips += "��";
			errorTips += char(j + '0');
			errorTips += "�����������Ӵ˴���ʼ�������뱾��Ԫ��:";
			errorTips += '\n';// �õ���ǰ����Ԫ����������Ӧ��ʾ
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
	cout << endl << "��ʼ����������ǰ����Ϊ��" << endl;
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

	cout << endl << "�����ϵ�հ�Ϊ��" << endl;
	display_matrix(result_matrix);
}
int main()
{
	input();
	Warshall();
	system("pause");
	return 0;
}