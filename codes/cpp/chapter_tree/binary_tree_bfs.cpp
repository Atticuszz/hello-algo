/**
 * File: binary_tree_bfs.cpp
 * Created Time: 2022-11-25
 * Author: krahets (krahets@163.com)
 */

#include "../utils/common.hpp"

/* 层序遍历 */
vector<int> levelOrder(TreeNode *root) {
    // 初始化队列，加入根节点
    queue<TreeNode *> queue;
    queue.push(root);
    // 初始化一个列表，用于保存遍历序列
    vector<int> vec;
    while (!queue.empty()) {
        TreeNode *node = queue.front();
        queue.pop();              // 队列出队
        vec.push_back(node->val); // 保存节点值
        if (node->left != nullptr)
            queue.push(node->left); // 左子节点入队
        if (node->right != nullptr)
            queue.push(node->right); // 右子节点入队
    }
    return vec;
}

/*layer output*/
/**
 * https://leetcode.cn/problems/binary-tree-level-order-traversal/
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
vector<vector<int>> layerLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root){
        return res;
    }
    queue<TreeNode*> my_queue;
    my_queue.push(root);
    
    while(!my_queue.empty()){
        // for layers collector ,separate the traversal into  layers via my_queue.size()
        vector<int> layer;
        int nodes_in_layer = my_queue.size();
        for(int i=0;i<nodes_in_layer;i++){
            TreeNode* cur = my_queue.front();
            layer.push_back(cur->val);
            my_queue.pop();
            if(cur->left){
                my_queue.push(cur->left);
            }
            if(cur->right){
                my_queue.push(cur->right);
            }
        }
        res.push_back(layer);
    }
    return res;
}
/*layer output from bottom*/

/**
 * https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(!root){
            return {};
        }
        vector<vector<int>> res;
        queue<TreeNode*> my_queue;
        my_queue.push(root);
        while(!my_queue.empty()){
            vector<int> layer;
            int num_of_layer = my_queue.size();

            for(int i=0;i<num_of_layer;i++){
                TreeNode* cur = my_queue.front();
                // add to cur layer
                layer.push_back(cur->val);
                my_queue.pop();

                // prepare for next layer
                if(cur->left){
                    my_queue.push(cur->left);
                }
                if(cur->right){
                    my_queue.push(cur->right);
                }
            }
            res.push_back(layer);
        }
        std::reverse(res.begin(),res.end());
        return res;
    }
};

/* Driver Code */
int main() {
    /* 初始化二叉树 */
    // 这里借助了一个从数组直接生成二叉树的函数
    TreeNode *root = vectorToTree(vector<int>{1, 2, 3, 4, 5, 6, 7});
    cout << endl << "初始化二叉树\n" << endl;
    printTree(root);

    /* 层序遍历 */
    vector<int> vec = levelOrder(root);
    cout << endl << "层序遍历的节点打印序列 = ";
    printVector(vec);

    return 0;
}
