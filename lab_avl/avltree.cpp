/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

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
    Node* node_=t->right;
    t->right=node_->left;
    node_->left=t;
    t=node_;
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
    Node* node_=t->left;
    t->left=node_->right;
    node_->right=t;
    t=node_;
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
    // your code here
    if(subtree==NULL)
    {
        return;
    }
    subtree->height=std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(balance==-2)
    {
        if(heightOrNeg1(subtree->left->right)-heightOrNeg1(subtree->left->left)==-1)
        {
            rotateRight(subtree);

        }
        else
        {
            rotateLeftRight(subtree);

        }
        
        rebalance(subtree->right);
        rebalance(subtree);
    }
    else if(balance==2)
    {
        if(heightOrNeg1(subtree->right->right)-heightOrNeg1(subtree->right->left)==1)
        {
            rotateLeft(subtree);

        }
        else
        {
            rotateRightLeft(subtree);

        }
        rebalance(subtree->left);
        rebalance(subtree);
    }
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
    if(subtree==NULL)
    {
        subtree=new Node(key,value);
        return;
    }
    if(key<subtree->key)
    {
        insert(subtree->left, key, value);
    }
    else if(key>subtree->key)
    {
        insert(subtree->right,key,value);
    }
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
        remove(subtree->left,  key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,  key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree=NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            getInorderTraversal(subtree->left,inorder);
            K key_=inorder.back();
            while(!inorder.empty())
            {
                if(key_<inorder.back())
                {
                    key_=inorder.back();
                }
                inorder.pop_back();
            }
            subtree->value=find(subtree->left,key_);
            subtree->key=key_;
            remove(subtree->left,key_);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->right!=NULL)
            {
                swap(subtree,subtree->right);
                delete subtree->right;
                subtree->right=NULL;
            }
            else
            {
                swap(subtree,subtree->left);
                delete subtree->left;
                subtree->left=NULL;
            }
        }
        // your code here

    }
    rebalance(subtree);
}
