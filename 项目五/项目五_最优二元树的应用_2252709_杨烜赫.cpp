// ReSharper disable All

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ������������Ľڵ�ṹ��
struct huffman_node {
    int weight = 0;       // �ڵ��Ȩ��
    int leftchild = -1;   // ���ӽڵ������
    int rightchild = -1;  // ���ӽڵ������
    int parent = -1;      // ���ڵ������
    int index = -1;       // �ڵ��ԭʼ���������ڸ��ٽڵ��˳��
};

// ����������
class huffman_tree {
public:
    huffman_tree() {
        root = nullptr;
    }

    ~huffman_tree() {
        delete[] mock;
        delete[] huffmancode;
        delete root;
    }

    void init_huffmantree();
    void create_huffmancode();
    void display_code();

private:
    int node_num = 0;             // Ҷ�ӽڵ������
    vector<int> node;             // �洢Ҷ�ӽڵ��Ȩ��
    huffman_node* root = nullptr; // ָ����������ĸ��ڵ��ָ��
    huffman_node* mock;           // ָ����������ڵ������ָ��
    string* huffmancode;          // �洢���ɵĹ���������

    void select(int n, int& s1, int& s2); // ѡ������δʹ�õ���СȨ�ؽڵ�
};

// ��ʼ����������
void huffman_tree::init_huffmantree() {
    cout << "������Ҷ�ڵ������";
    cin >> node_num;
    node.resize(node_num);
    cout << "����������Ҷ�ڵ�Ȩֵ��" << endl;
    for (int i = 0; i < node_num; i++) {
        cin >> node[i];
    }

    int all_node = 2 * node_num - 1;
    mock = new huffman_node[all_node]; // Ϊ����������������ռ�
    for (int i = 0; i < node_num; i++) {
        mock[i].weight = node[i];
        mock[i].index = i; // ����ԭʼ����
    }

    int s1, s2; // ���ڴ洢������СȨ�ؽڵ������
    // ������������
    for (int i = node_num; i < all_node; i++) {
        select(i, s1, s2);
        mock[s1].parent = i;
        mock[s2].parent = i;
        mock[i].leftchild = s1;
        mock[i].rightchild = s2;
        mock[i].weight = mock[s1].weight + mock[s2].weight;
    }
}

// ��mock������ѡ������δʹ�õ���СȨ�ؽڵ�
void huffman_tree::select(int n, int& s1, int& s2) {
    int min1 = -1, min2;
    for (int i = 0; i < n; ++i) {
        if (mock[i].parent == -1) {
            if (min1 == -1 || mock[i].weight < mock[min1].weight ||
                (mock[i].weight == mock[min1].weight && mock[i].index < mock[min1].index)) {
                min2 = min1;
                min1 = i;
            }
            else if (min2 == -1 || mock[i].weight < mock[min2].weight ||
                (mock[i].weight == mock[min2].weight && mock[i].index < mock[min2].index)) {
                min2 = i;
            }
        }
    }
    s1 = min1;
    s2 = min2;
}

// ��������������
void huffman_tree::create_huffmancode() {
    huffmancode = new string[node_num];
    for (int i = 0; i < node_num; i++) {
        string code = "";
        int j = i;
        // ��Ҷ�ӽڵ����ϱ��������ڵ㣬��������������
        while (mock[j].parent != -1) {
            int p = mock[j].parent;
            code = (mock[p].leftchild == j ? "0" : "1") + code;
            j = p;
        }
        huffmancode[mock[i].index] = code; // ʹ��ԭʼ�����������
    }
}

// ��ʾ����������
void huffman_tree::display_code() {
    for (int i = 0; i < node_num; i++) {
        cout << mock[i].weight << "��" << huffmancode[mock[i].index] << endl;
    }
}

int main() {
    huffman_tree Huffman;
    Huffman.init_huffmantree();
    Huffman.create_huffmancode();
    Huffman.display_code();
    system("pause");
    return 0;
}
