#include <vector>
#include <iostream>

class UnionFind {
private:
    std::vector<int> parent;  // 父节点数组
    std::vector<int> rank;    // 树的秩（高度）

public:
    // 构造函数，初始化并查集，n 为元素总数
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = -1; // 初始时，每个元素的父节点是它自己
        }
    }

    // 查找操作，找到元素x的根节点（代表元素）
    int find(int x) {
        if (parent[x] != x) { // 路径压缩
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并操作，将元素x和元素y所在的集合合并
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) { // 如果x和y不在同一个集合中
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX; // 将秩较小的树的根节点指向秩较大的树的根节点
            } else {
                parent[rootX] = rootY;
                if (rank[rootX] == rank[rootY]) {
                    rank[rootY]++; // 如果两棵树的高度相同，则合并后的树高度+1
                }
            }
        }
    }

    // 演示函数：展示并查集的工作方式
    void demo() {
        std::cout << "Initially, parent array is: ";
        for (int i = 0; i < parent.size(); i++) {
            std::cout << parent[i] << " ";
        }
        std::cout << "\nAfter some union operations:\n";

        unionSets(1, 2);
        unionSets(2, 3);
        unionSets(4, 5);

        for (int i = 0; i < parent.size(); i++) {
            std::cout << "Element " << i << " belongs to set: " << find(i) << "\n";
        }
    }
};

int main() {
    UnionFind uf(6); // 假设有6个元素
    uf.demo();

    return 0;
}
