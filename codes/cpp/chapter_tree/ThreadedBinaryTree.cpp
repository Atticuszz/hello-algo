#include <iostream>
using namespace std;

// 定义二叉树节点结构体
struct TreeNode {
    int val;
    TreeNode *left, *right;
    bool lTag, rTag; // 标记是否为线索
    TreeNode(int x) : val(x), left(NULL), right(NULL), lTag(false), rTag(false) {}
};

class ThreadedBinaryTree {
public:
    TreeNode *root;
    TreeNode *prev = NULL; // 用于中序遍历时，记录前一个节点

    ThreadedBinaryTree() : root(NULL) {}

    // 初始化线索化过程
    void createInorderThread() {
        prev = NULL;
        inorderThread(root);
        // note: the final prev to set true if right is None
        if(prev->right==NULL){
            prev->rTag = true;
        }
    }
    void createPreorderThread() {
        prev = NULL;
        preorderThread(root);
        if(prev->right==NULL){
            prev->rTag = true;
        }
    }
    // 中序线索化
    void inorderThread(TreeNode* &node) {
        if (node == NULL) return;
        
        // 线索化左子树
        inorderThread(node->left);

        // 左空指针指向前驱
        if (node->left == NULL) {
            node->left = prev;
            node->lTag = true; // 标记为线索
        }

        // 前一个节点的右空指针指向当前节点（当前节点的前驱）
        if (prev != NULL && prev->right == NULL) {
            prev->right = node;
            prev->rTag = true; // 标记为线索
        }

        prev = node; // 更新prev为当前节点

        // 线索化右子树
        inorderThread(node->right);
    }

    // 前序线索化
    void preorderThread(TreeNode* &node) {
        if (node == NULL) return;
        
        // 如果左子节点为空，设置前驱线索
        if (node->left == NULL) {
            node->left = prev;
            node->lTag = true;
        }
        
        // 如果前一个节点的右子节点为空，设置后继线索
        if (prev != NULL && prev->right == NULL) {
            prev->right = node;
            prev->rTag = true;
        }
        
        prev = node; // 更新prev为当前节点
        
        // 注意避开线索，递归左右子树！！
        if (!node->lTag) preorderThread(node->left);
        if (!node->rTag) preorderThread(node->right);
    }

    

    // 添加节点的辅助函数（非主要实现，只为构建测试树）
    void insert(int val) {
        if (!root) {
            root = new TreeNode(val);
            return;
        }
        insertNode(root, val);
    }

private:
    void insertNode(TreeNode* node, int val) {
        if (val < node->val) {
            if (node->left) {
                insertNode(node->left, val);
            } else {
                node->left = new TreeNode(val);
            }
        } else {
            if (node->right) {
                insertNode(node->right, val);
            } else {
                node->right = new TreeNode(val);
            }
        }
    }
};

int main() {
    // 示例
    ThreadedBinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.createInorderThread();

    // 中序遍历线索化二叉树的代码可以根据需要添加
    // 注意这里的中序遍历和常规中序遍历有所不同，需要利用线索进行遍历

    return 0;
}
