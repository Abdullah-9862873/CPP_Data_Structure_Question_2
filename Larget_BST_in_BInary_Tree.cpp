/*
Collect following information of each node:
1--> Min of subtree including node
2--> Max of subtree including node
3--> size of subtree including node
4--> size of largest BST    (Single node is always BST so it will be 1 for one node)
5--> isBST

Recursively traverse in a bottom up manner and find out the size of largest BST
*/

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

struct Info{
    int size;
    int min;
    int max;
    int ans;
    bool isBST;
};

Info largestBSTinBT(Node* root){
    if(root == NULL){
        return {0, INT_MAX, INT_MIN, 0, true};
    }

    if(root->left == NULL && root->right == NULL){
        // Leaf node
        return {1, root->data, root->data, 1, true};
    }

    Info leftInfo = largestBSTinBT(root->left);
    Info rightInfo = largestBSTinBT(root->right);

    Info curr;
    curr.size = leftInfo.size + rightInfo.size + 1;

    // left and right nodes exisit of current
    if(leftInfo.isBST && rightInfo.isBST && leftInfo.max < root->data && rightInfo.min > root->data){
        // Condition tells that left is giving a BST and right is giving BST
        curr.min = min(leftInfo.min, min(rightInfo.min, root->data));
        curr.max = max(leftInfo.max, max(rightInfo.max, root->data));

        curr.ans = curr.size;
        curr.isBST = true;

        return curr;
    }
    // No BST is formed at curr
    curr.ans = max(leftInfo.ans, rightInfo.ans);
    curr.min = min(leftInfo.min, min(rightInfo.min, root->data));
    curr.max = max(max(leftInfo.max, rightInfo.max), root->data);
    curr.isBST = false;

    return curr;
}

int main(){
/*
                15
               /  \
              20   30
             /
            5
*/
    Node* root = new Node(15);
    root->left = new Node(20);
    root->left->left = new Node(5);
    root->right = new Node(30);

    cout<<"Largest BST in BT is: "<<largestBSTinBT(root).ans<<endl;

/*
            20
           /  \
          12   21
         /  \    \
        4    13   20
       / \        / \ 
      3   6      2   25
                   /  \
                  7    6
*/

        Node* root2 = new Node(20);
        root2->left = new Node(12);
        root2->right = new Node(21);

        root2->left->left = new Node(4);
        root2->left->right = new Node(13);
        root2->left->left->left = new Node(3);
        root2->left->left->right = new Node(6);

        root2->right->right = new Node(20);
        root2->right->right->left = new Node(2);
        root2->right->right->right = new Node(25);
        root2->right->right->right->left = new Node(7);
        root2->right->right->right->right = new Node(6);

        cout<<"Largest BST in BT2 is: "<<largestBSTinBT(root2).ans<<endl;
    return 0;
}