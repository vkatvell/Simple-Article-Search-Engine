//
// Created by Noah Henson on 6/23/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_AVLTREE_H
#define INC_22SU_SEARCH_ENGINE_AVLTREE_H

#include <iostream>
#include <unordered_set>
#include <string>
#include <exception>
using std::cin;
using std::cout;
using std::unordered_set;
#include <utility>

//hash function included to allow unordered sets to include pairs
struct pair_hash
{
    template <class T1, class T2>
    //overload the () operator to allow for a pair of type T1, T2
    std::size_t operator () (std::pair<T1, T2> const &pair) const
    {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);

        return h1 ^ h2;
    }
};

template <typename K, typename V>
class AVLTree {
private:
    class AVLNode {
    public:
        //string being stored
        K key;
        //set of values and the number of times they appeared in that doc
        unordered_set<std::pair<V, int>, pair_hash> value;
        AVLNode* left = nullptr;
        AVLNode* right = nullptr;
        int height = 0;
        //default constructor
        AVLNode();
        //copy constructor
        AVLNode(K key, std::pair<V, int> value, AVLNode* left, AVLNode* right, int height);
    };

    AVLNode* root = nullptr;
    //prints the current node data
    void print(AVLNode* curr);
    //returns the height of the current node
    int getHeight(AVLNode* curr);
    //recursively inserts a node with a key and a value
    void insert(AVLNode*& curr, const K& x, const std::pair<V, int>& v);
    //find the higher value between two numbers
    int max(int a, int b);
    //avl tree rotation functions
    void rotateWithRightChild(AVLNode*& k1);
    void doubleWithRightChild(AVLNode*& k1);
    void rotateWithLeftChild(AVLNode*& k2);
    void doubleWithLeftChild(AVLNode*& k3);

    //return a new copy of the node
    AVLNode* nodeCopy (AVLNode* curr);
    //recursively search the avl tree for a certain key```
    unordered_set<std::pair<V, int>, pair_hash> searchTree(AVLNode*& curr, const K&);
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
    void insert(const K& k, const std::pair<V,int>& v);
    //search the key
    unordered_set<std::pair<V, int>, pair_hash> searchTree(const K& k);
};

//default constructor
template<typename K, typename V>
AVLTree<K, V>::AVLNode::AVLNode() = default;

/**
 * Copy constructor
 * @tparam K data type of key
 * @tparam V data type being stored in pair.first
 * @param givenKey key of new node
 * @param givenValue value pair of new node
 * @param leftNode set value of left ptr
 * @param rightNode set value of right ptr
 * @param ht set height of new node
 */
template<typename K, typename V>
AVLTree<K, V>::AVLNode::AVLNode(K givenKey, std::pair<V, int> givenValue, AVLTree::AVLNode *leftNode, AVLTree::AVLNode *rightNode, int ht) {
    this->key = givenKey;
    this->value.operator=(givenValue); //copy constructor for unordered set
    this->left = leftNode;
    this->right = rightNode;
    this->height = ht;
}

/**
 * Returns the height of the current node
 * @tparam K data type of key
 * @tparam V data type being stored in pair.first
 * @param curr current node
 * @return
 */
template <typename K, typename V>
int AVLTree<K,V>::getHeight(AVLNode* curr) {
    if(curr == nullptr) //if node has a key
        return -1;
    else
        return curr->height;
}

/**
 * Print the data of the current node
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param curr current node
 */
template <typename K, typename V>
void AVLTree<K,V>::print(AVLNode* curr) {
    if(curr != nullptr) {
        print(curr->left);
        cout << curr->key << " ";
        print(curr->right);
    }
}

/**
 * Recursively inserts a node with a key and a value
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param curr current node
 * @param x key
 * @param v value pair
 */
template <typename K, typename V>
void AVLTree<K,V>::insert(AVLTree<K,V>::AVLNode*& curr, const K& x, const std::pair<V,int>& v) {
    //if curr does not exist, create a new node
    if(curr == nullptr) {
        curr = new AVLNode;
        curr->key = x;
        curr->value.insert(v);
    }else if(x.compare(curr->key) < 0) { //go left (x < curr->key)
        insert(curr->left, x, v);
        //balance depending on the case
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
        //handle duplicates
        if(curr->value.find(v) == curr->value.end()) {
            curr->value.insert(v);
        }
        curr->height = max(getHeight(curr->left), getHeight(curr->right));
    }
}

/**
 * Find the higher value between two integers
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param a first integer
 * @param b second integer
 * @return
 */
template <typename K, typename V>
int AVLTree<K,V>::max(int a, int b) {
    if(a < b)
        return b;
    else
        return a;
}

/**
 * Case 4 AVL Tree rotation
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param k1 alpha, point to be rotated
 */
template <typename K, typename V>
void AVLTree<K,V>::rotateWithRightChild(AVLNode *&k1) { //k1 is alpha
    AVLNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1; //one level deeper than the max of the two children
    k2->height = max(getHeight(k2->right), k1->height) + 1;
    k1 = k2; //passed in a reference pointer, so now k2 is pointed to as the root instead of k1
}

/**
 * Case 3 AVL Tree Rotation
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param k1 node
 */
template <typename K, typename V>
void AVLTree<K,V>::doubleWithRightChild(AVLNode *&k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

/**
 * Case 1 AVL Tree Rotation (LL)
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param k2 alpha, node to be rotated
 */
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

/**
 * Case 2 AVL Tree Rotation
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param k3 node
 */
template <typename K, typename V>
void AVLTree<K,V>::doubleWithLeftChild(AVLNode *&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

//default constructor
template <typename K, typename V>
AVLTree<K,V>::AVLTree(): root(nullptr) {}

//copy constructor for avl tree
template <typename K, typename V>
AVLTree<K,V>::AVLTree(const AVLTree& arg){
    root = nodeCopy(arg.root);
}

//destructor
template <typename K, typename V>
void AVLTree<K,V>::deleteTree(AVLNode*& curr){
    //delete tree recursively
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
    //call destructor
    deleteTree(root);
    if(root == nullptr) {std::cout << "root cleared";}
}

//print tree recursively
template <typename K, typename V>
void AVLTree<K,V>::print() {
    print(root);
}

/**
 * Calls recursive insertion of a key and value pair
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param k key
 * @param v value pair
 */
template <typename K, typename V>
void AVLTree<K,V>::insert(const K& k, const std::pair<V,int>& v) {
    insert(root, k, v);
}

/**
 * Copies the nodes of the tree using recursion
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param curr current node
 * @return
 */
template<typename K, typename V>
typename AVLTree<K,V>::AVLNode* AVLTree<K, V>::nodeCopy(AVLTree<K,V>::AVLNode *curr) {
    if(curr != nullptr) { //loop through the tree while the key still exists
        AVLNode* left = nodeCopy(curr->left);
        AVLNode* right = nodeCopy(curr->right);
        return new AVLNode(curr->key, curr->value, left, right, curr->height);
    }else
        return nullptr;
}

/**
 * Calls the function to search the AVL Tree recursively
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param k key to be searched for
 * @return returns an ordered set of pairs stored in that key
 */
template<typename K, typename V>
unordered_set<std::pair<V, int>, pair_hash> AVLTree<K, V>::searchTree(const K& k){
    return searchTree(root, k);
}

/**
 * Recursively search the avl tree for a certain key
 * @tparam K data type of the key
 * @tparam V data type being stored in pair.first
 * @param curr current node
 * @param k key to be searched for
 * @return returns a set of the value pairs being stored by the key
 */
template<typename K, typename V>
unordered_set<std::pair<V, int>, pair_hash> AVLTree<K, V>::searchTree(AVLTree::AVLNode *&curr, const K & k) {
    if(curr == nullptr) { //base condition, has searched the tree and cannot find an equivalent value
        cout << "Word not found" << std::endl;
        unordered_set<std::pair<V, int>, pair_hash> empty;
        return empty;
    }else if(curr->key == k) { //if the key has been found, copy the set and return it
        unordered_set<std::pair<V, int>, pair_hash> set = curr->value;
        return set;
    }
    else if(curr->key < k) { //if the current key is less than key being searched for, recursively run from the next node on the right
        unordered_set<std::pair<V, int>, pair_hash> set = searchTree(curr->right, k);
        return set;
    }
    else { //if the current key is greater than key being searched for, recursively run from the next node on the left
        unordered_set<std::pair<V, int>, pair_hash> set = searchTree(curr->left, k);
        return set;
    }
}

#endif //INC_22SU_SEARCH_ENGINE_AVLTREE_H