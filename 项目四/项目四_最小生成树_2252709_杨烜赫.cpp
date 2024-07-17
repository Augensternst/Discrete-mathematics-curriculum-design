#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
using namespace std;

class Graph {
private:
    struct Edge {
        int from, to, dis;
    };

    vector<Edge> edges;
    vector<int> parent;
    vector<Edge> mstEdges; // ���ڴ洢��С�������еı�
    int n; // �������

public:
    Graph(int n) : n(n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    void addEdge(int from, int to, int dis) {
        edges.push_back({ from, to, dis });
    }

    int findParent(int x) {
        if (parent[x] != x) {
            parent[x] = findParent(parent[x]);
        }
        return parent[x];
    }

    void unionSet(int x, int y) {
        parent[findParent(x)] = findParent(y);
    }

    int kruskal() {
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.dis < b.dis;
            });

        int totalWeight = 0;

        for (const auto& edge : edges) {
            if (mstEdges.size() == n - 1) {
                break;
            }
            if (findParent(edge.from) != findParent(edge.to)) {
                unionSet(edge.from, edge.to);
                totalWeight += edge.dis;
                mstEdges.push_back(edge); // ��ӵ���С�������ı߼���
            }
        }

        return totalWeight;
    }

    const vector<Edge>& getMSTEdges() const {
        return mstEdges;
    }
};

// ���ڶ�ȡ����֤�û�����ĺ���
int getValidInput(int minVal, int maxVal, const string& errorMsg) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < minVal || input > maxVal) {
            cin.clear(); // �������״̬
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Դ�������
            cout << errorMsg;
        }
        else {
            break;
        }
    }
    return input;
}

int main() {
    int n, m;
    cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ���Կո�ָ����������س���������";
    n = getValidInput(1, 5000, "���������������������һ����1��5000֮���������");
    m = getValidInput(0, 5000, "�������������������һ����0��5000֮���������");

    Graph g(n);

    cout << "�����������ߵĽڵ�����Լ����ǵ�Ȩֵ���Կո�ָ�����������" << endl;
    for (int i = 0; i < m; i++) {
        int from, to, dis;
        from = getValidInput(1, n, "����������������һ����1��" + to_string(n) + "֮���������");
        to = getValidInput(1, n, "�յ��������������һ����1��" + to_string(n) + "֮���������");
        dis = getValidInput(0, numeric_limits<int>::max(), "Ȩ���������������һ���Ǹ�������");
        g.addEdge(from, to, dis);
    }

    int totalWeight = g.kruskal();
  
    for (const auto& edge : g.getMSTEdges()) {
        cout << "��С�ķ��ǣ�";
        cout << edge.from << "��" << edge.to << endl;
    }

    cout << "��С����������Ȩ�أ��ܺķѣ�Ϊ��" << totalWeight << endl;
    system("pause");
    return 0;
}
