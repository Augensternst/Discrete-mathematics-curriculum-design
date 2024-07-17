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
    vector<Edge> mstEdges; // 用于存储最小生成树中的边
    int n; // 点的数量

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
                mstEdges.push_back(edge); // 添加到最小生成树的边集中
            }
        }

        return totalWeight;
    }

    const vector<Edge>& getMSTEdges() const {
        return mstEdges;
    }
};

// 用于读取并验证用户输入的函数
int getValidInput(int minVal, int maxVal, const string& errorMsg) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < minVal || input > maxVal) {
            cin.clear(); // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入
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
    cout << "请输入所求图的顶点数目和边的数目（以空格分隔各个数，回车结束）：";
    n = getValidInput(1, 5000, "顶点数量输入错误，请输入一个在1到5000之间的整数：");
    m = getValidInput(0, 5000, "边数量输入错误，请输入一个在0到5000之间的整数：");

    Graph g(n);

    cout << "请输入两条边的节点序号以及它们的权值（以空格分隔各个数）：" << endl;
    for (int i = 0; i < m; i++) {
        int from, to, dis;
        from = getValidInput(1, n, "起点输入错误，请输入一个在1到" + to_string(n) + "之间的整数：");
        to = getValidInput(1, n, "终点输入错误，请输入一个在1到" + to_string(n) + "之间的整数：");
        dis = getValidInput(0, numeric_limits<int>::max(), "权重输入错误，请输入一个非负整数：");
        g.addEdge(from, to, dis);
    }

    int totalWeight = g.kruskal();
  
    for (const auto& edge : g.getMSTEdges()) {
        cout << "最小耗费是：";
        cout << edge.from << "和" << edge.to << endl;
    }

    cout << "最小生成树的总权重（总耗费）为：" << totalWeight << endl;
    system("pause");
    return 0;
}
