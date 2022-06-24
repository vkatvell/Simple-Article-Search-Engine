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
    };

    AVLNode* root = nullptr;

    void print(AVLNode* curr);

    int getHeight(AVLNode* curr);

    void insert(AVLNode*& curr, K x);

    int max(K a, K b);

    void rotateWithRightChild(AVLNode*& k1);

    void doubleWithRightChild(AVLNode*& k1);

    void rotateWithLeftChild(AVLNode*& k2);

    void doubleWithLeftChild(AVLNode*& k3);

public:
    void print();
    void insert(K x);
};

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
void AVLTree<K,V>::insert(AVLNode*& curr, K x) {
    //if curr does not exist, create a new node
    if(curr == nullptr) {
        curr = new AVLNode;
        curr->key = x;
    }else if(x.compare(curr->key) < 0) { //go left (x < curr->key)
        insert(curr->left, x);
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
        insert(curr->right, x);
    }else {
        ; //handle duplicates
        curr->height = max(getHeight(curr->left), getHeight(curr->right));
    }
}

template <typename K, typename V>
int AVLTree<K,V>::max(K a, K b) {
    (a < b) ? b : a;
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

template <typename K, typename V>
void AVLTree<K,V>::print() {
    print(root);
}

template <typename K, typename V>
void AVLTree<K,V>::insert(K x) {
    insert(root, x);
}

#endif //INC_22SU_SEARCH_ENGINE_AVLTREE_H
