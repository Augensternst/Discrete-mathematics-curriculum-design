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
	void dfs(int u, int v);//dfs��������
	void display_matrix(int arr[100][100]);
public:
	matrix();
	~matrix() {};
	int root_matrix[100][100];
	int result_matrix[100][100];
	int choice;
	void menu();
	void input();
	void reflexive_closure();//�Է��հ�
	void symmetric_closure();//�ԳƱհ�
	void transitive_closure();//���ݱհ�
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
	cout << endl << "�������ѡ���Ӧ�㷨��" << endl;
	cout << "1.�Է��հ�" << endl;
	cout << "2.�ԳƱհ�" << endl;
	cout << "3.���ݱհ�" << endl;
	cout << "4.�˳�" << endl;
	cout << "�����룺";
	while(true)
	{
		choice = 0;
		cin >> choice;
		if(choice<1||choice>4||!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룡" << endl;
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

	cout << "����������������";
	cin >> row;
	cout << endl;
	cout << "��������������(�뱣֤������������ͬ)��";
	cin >> col;
	cout << endl;
	cout << "�������ϵ����" << endl;
	for(int i=0;i<row;i++)
	{
		cout << endl << "����������" << i << "��(�Կո�ָ�)��";
		for(int j=0;j<col;j++)
		{
			string errorTips = "��";
			errorTips += char(i + '0');
			errorTips += "��";
			errorTips += char(j + '0');
			errorTips += "�����������Ӵ˴���ʼ�������뱾��Ԫ��:";
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
	cout << endl << "��ʼ����������ǰ����Ϊ��" << endl;
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
	cout << endl << "�����ϵ�հ�Ϊ��" << endl;
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
	cout << endl << "�����ϵ�հ�Ϊ��" << endl;
	display_matrix(result_matrix);
}

void matrix::transitive_closure()
{
	// ����ԭʼ���󵽽������
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result_matrix[i][j] = root_matrix[i][j];
		}
	}
	// ���´��ݱհ�
	for (int k = 0; k < row; k++) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (result_matrix[i][k] && result_matrix[k][j]) {
					result_matrix[i][j] = 1;
				}
			}
		}
	}
	cout << endl << "�����ϵ�հ�Ϊ��" << endl;
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
			cout << "�����������лʹ�ã�" << endl;
			break; // ѡ���˳�ʱ������0��������
		default:
			cout << "��Ч��ѡ�������ѡ��" << endl;
		}
		system("pause");
	return 0;
}
