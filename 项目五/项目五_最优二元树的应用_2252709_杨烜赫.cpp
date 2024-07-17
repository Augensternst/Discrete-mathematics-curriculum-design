// ReSharper disable All

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 定义哈夫曼树的节点结构体
struct huffman_node {
    int weight = 0;       // 节点的权重
    int leftchild = -1;   // 左子节点的索引
    int rightchild = -1;  // 右子节点的索引
    int parent = -1;      // 父节点的索引
    int index = -1;       // 节点的原始索引，用于跟踪节点的顺序
};

// 哈夫曼树类
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
    int node_num = 0;             // 叶子节点的数量
    vector<int> node;             // 存储叶子节点的权重
    huffman_node* root = nullptr; // 指向哈夫曼树的根节点的指针
    huffman_node* mock;           // 指向哈夫曼树节点数组的指针
    string* huffmancode;          // 存储生成的哈夫曼编码

    void select(int n, int& s1, int& s2); // 选择两个未使用的最小权重节点
};

// 初始化哈夫曼树
void huffman_tree::init_huffmantree() {
    cout << "请输入叶节点个数：";
    cin >> node_num;
    node.resize(node_num);
    cout << "请依次输入叶节点权值：" << endl;
    for (int i = 0; i < node_num; i++) {
        cin >> node[i];
    }

    int all_node = 2 * node_num - 1;
    mock = new huffman_node[all_node]; // 为整个哈夫曼树分配空间
    for (int i = 0; i < node_num; i++) {
        mock[i].weight = node[i];
        mock[i].index = i; // 保存原始索引
    }

    int s1, s2; // 用于存储两个最小权重节点的索引
    // 构建哈夫曼树
    for (int i = node_num; i < all_node; i++) {
        select(i, s1, s2);
        mock[s1].parent = i;
        mock[s2].parent = i;
        mock[i].leftchild = s1;
        mock[i].rightchild = s2;
        mock[i].weight = mock[s1].weight + mock[s2].weight;
    }
}

// 从mock数组中选择两个未使用的最小权重节点
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

// 创建哈夫曼编码
void huffman_tree::create_huffmancode() {
    huffmancode = new string[node_num];
    for (int i = 0; i < node_num; i++) {
        string code = "";
        int j = i;
        // 从叶子节点向上遍历到根节点，构建哈夫曼编码
        while (mock[j].parent != -1) {
            int p = mock[j].parent;
            code = (mock[p].leftchild == j ? "0" : "1") + code;
            j = p;
        }
        huffmancode[mock[i].index] = code; // 使用原始索引保存编码
    }
}

// 显示哈夫曼编码
void huffman_tree::display_code() {
    for (int i = 0; i < node_num; i++) {
        cout << mock[i].weight << "：" << huffmancode[mock[i].index] << endl;
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
