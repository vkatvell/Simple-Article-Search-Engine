//
// Created by Noah Henson on 6/23/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_AVLTREE_H
#define INC_22SU_SEARCH_ENGINE_AVLTREE_H
#include <iostream>
#include <string>
using std::cin;
using std::cout;

template <typename K, typename V>
class AVLTree {
private:
    class AVLNode {
    public:
        K key;
        V value;
        AVLNode* left = nullptr;
        AVLNode* right = nullptr;
        int height = 0;
        AVLNode();
        AVLNode(K key, V value, AVLNode* left, AVLNode* right, int height);
    };

    AVLNode* root = nullptr;

    void print(AVLNode* curr);

    int getHeight(AVLNode* curr);

    void insert(AVLNode*& curr, const K& x, const V& v);

    int max(int a, int b);

    void rotateWithRightChild(AVLNode*& k1);

    void doubleWithRightChild(AVLNode*& k1);

    void rotateWithLeftChild(AVLNode*& k2);

    void doubleWithLeftChild(AVLNode*& k3);

    AVLNode* nodeCopy (AVLNode* curr);

public:
    //default constructor
    AVLTree();
    //copy constructor
    AVLTree(const AVLTree&);
    //destructor
    void deleteTree(AVLNode*&);
    ~AVLTree();
    //print tree using in order
    void print();
    //insert a value into the tree
    void insert(const K& k, const V& v);

    V& searchTree(AVLNode*, const K& k);
};

template<typename K, typename V>
AVLTree<K, V>::AVLNode::AVLNode() = default;

template<typename K, typename V>
AVLTree<K, V>::AVLNode::AVLNode(K givenKey, V givenValue, AVLTree::AVLNode *leftNode, AVLTree::AVLNode *rightNode, int ht) {
    this->key = givenKey;
    this->value = givenValue;
    this->left = leftNode;
    this->right = rightNode;
    this->height = ht;
}

template <typename K, typename V>
int AVLTree<K,V>::getHeight(AVLNode* curr) {
    if(curr == nullptr)
        return -1;
    else
        return curr->height;
}

template <typename K, typename V>
void AVLTree<K,V>::print(AVLNode* curr) {
    if(curr != nullptr) {
        print(curr->left);
        cout << curr->key << " ";
        print(curr->right);
    }
}

template <typename K, typename V>
void AVLTree<K,V>::insert(AVLTree<K,V>::AVLNode*& curr, const K& x, const V& v) {
    //if curr does not exist, create a new node
    if(curr == nullptr) {
        curr = new AVLNode;
        curr->key = x;
        curr->value = v;
    }else if(x.compare(curr->key) < 0) { //go left (x < curr->key)
        insert(curr->left, x, v);
        //cool balancing stuff
        if(getHeight(curr->left) - getHeight(curr->right) == 2) { // if avl tree does not match avl rules
            if(x < curr->left->key) {
                rotateWithLeftChild(curr);
            }else {
                doubleWithLeftChild(curr);
            }
        }
    }else if(curr->key.compare(x) < 0) { //go right (curr->key < x)
        if(getHeight(curr->right) - getHeight(curr->left) == 2) {
            if(curr->right->key < x) {
                rotateWithRightChild(curr); //case 4
            }else {
                doubleWithRightChild(curr); //case 3
            }
        }
        insert(curr->right, x, v);
    }else {
        ; //handle duplicates
        curr->height = max(getHeight(curr->left), getHeight(curr->right));
    }
}

template <typename K, typename V>
int AVLTree<K,V>::max(int a, int b) {
    if(a < b)
        return b;
    else
        return a;
}

template <typename K, typename V>
void AVLTree<K,V>::rotateWithRightChild(AVLNode *&k1) { //k1 is alpha
    AVLNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1; //one level deeper than the max of the two children
    k2->height = max(getHeight(k2->right), k1->height) + 1;
    k1 = k2; //passed in a reference pointer, so now k2 is pointed to as the root instead of k1
}

template <typename K, typename V>
void AVLTree<K,V>::doubleWithRightChild(AVLNode *&k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template <typename K, typename V>
void AVLTree<K,V>::rotateWithLeftChild(AVLNode *&k2) {
    AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    //update heights
    k2->height = max(getHeight(k2->right), getHeight(k2->left)) + 1;
    k1->height = max(getHeight(k1->left), k2->height + 1);
    k2 = k1;
}

template <typename K, typename V>
void AVLTree<K,V>::doubleWithLeftChild(AVLNode *&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

//default constructor
template <typename K, typename V>
AVLTree<K,V>::AVLTree(): root(nullptr) {}

//copy constructor
template <typename K, typename V>
AVLTree<K,V>::AVLTree(const AVLTree& arg){
    root = nodeCopy(arg.root);
}

//destructor
template <typename K, typename V>
void AVLTree<K,V>::deleteTree(AVLNode*& curr){
    if(curr != nullptr){
        deleteTree(curr->left);
        deleteTree(curr->right);
        delete curr;
        curr = nullptr;
    }
}

//starts deleting the tree from the root via a recursive function
template <typename K, typename V>
AVLTree<K,V>::~AVLTree(){
    deleteTree(root);
    if(root == nullptr) {std::cout << "root cleared";}
}

template <typename K, typename V>
void AVLTree<K,V>::print() {
    print(root);
}

template <typename K, typename V>
void AVLTree<K,V>::insert(const K& k, const V& v) {
    insert(root, k, v);
}

//copies the nodes of the tree using recursion
template<typename K, typename V>
typename AVLTree<K,V>::AVLNode* AVLTree<K, V>::nodeCopy(AVLTree<K,V>::AVLNode *curr) {
    if(curr != nullptr) {
        AVLNode* left = nodeCopy(curr->left);
        AVLNode* right = nodeCopy(curr->right);
        return new AVLNode(curr->key, curr->value, left, right, curr->height);
    }else
        return nullptr;
}

template<typename K, typename V>
V &AVLTree<K, V>::searchTree(AVLTree::AVLNode * curr, const K& k) {
    if(curr == nullptr || curr->key == k) {
        return curr->value;
    }

    if(curr->key < k) {
        return search(curr->right, k);
    }
    else
        return search(curr->left, k);
}

#endif //INC_22SU_SEARCH_ENGINE_AVLTREE_H