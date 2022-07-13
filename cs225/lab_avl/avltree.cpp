/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <algorithm>
#include <iostream>

using namespace std;
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *t_ = t;
    Node *x = t_ -> right;
    t_ -> right = x -> left;
    x -> left = t_;
    // gauge height
    t_ -> height = std::max(getHeight(t_ -> left), getHeight(t_ -> right)) + 1;
    t = x;
    t -> height = std::max(getHeight(t -> left), getHeight(t -> right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *t_ = t;
    Node *x = t_ -> left;
    t_ -> left = x -> right;
    x -> right = t_;
    // gauge height & assign the correct height
    t_ -> height = std::max(getHeight(t_ -> left), getHeight(t_ -> right)) + 1;
    t = x;
    t -> height = std::max(getHeight(t -> left), getHeight(t -> right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (subtree == NULL) {
        return;
    }
    // your code here
    int croot_b = getHeight(subtree -> right) - getHeight(subtree -> left); 
    if (croot_b == 2) {
        int right_b = getHeight(subtree -> right -> right) - getHeight(subtree -> right -> left); 
        if (right_b == 1) {
            rotateLeft(subtree);
        }
        if (right_b == -1) {
            rotateRightLeft(subtree);
        }
    } else if (croot_b == -2) {
        int left_b = getHeight(subtree -> left -> right) - getHeight(subtree -> left -> left);
        if (left_b == 1) {
            rotateLeftRight(subtree);
        }
        if (left_b == -1) {
            rotateRight(subtree);
        }
    }
    subtree->height = std::max(getHeight(subtree->right), getHeight(subtree->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        Node *ins = new Node(key, value);
        subtree = ins;
    }
    if (subtree -> key > key) {
        insert(subtree -> left, key, value);
    }
    if (subtree -> key < key) {
        insert(subtree -> right, key, value);
    }
    // this is very important step since 
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node *& left_ = getIOP(subtree->left);
            swap(left_, subtree);
            remove(left_, key);
        } else {
            /* one-child remove */
            // your code here
            Node* replacement = subtree;
            if (subtree->left != NULL) {
                replacement = subtree->left;
            } else {
                replacement = subtree->right;
            }
            delete subtree;
            subtree = replacement;
        }
        // your code here
        rebalance(subtree);
    }
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* subRoot) {
    if (subRoot == NULL) {
        return -1;
    }
    return subRoot->height;

}


template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::getIOP(Node*& subRoot) {
    return subRoot -> right == NULL ? subRoot : getIOP(subRoot -> right);
}

