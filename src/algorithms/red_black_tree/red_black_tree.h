#pragma once
#include <algorithm>

template <typename T>
class RedBlackTree
{
public:
  bool search(const T &key) const;

  void insert(const T &key);

  int height() const;

private:
  enum Color
  {
    red,
    black
  };

  struct Node
  {
    Node *parent;

    Node *left;

    Node *right;

    Color color = black;

    T key;
  };

  const Node *searchNode(Node *node, const T &key) const;

  void insertNode(Node *z);

  void rotateLeft(Node *x);

  void rotateRight(Node *y);

  void fixInsert(Node *z);

  int treeHeight(Node *z) const;

private:
  static Node NULL_NODE;

  Node *m_Null = &NULL_NODE;

  Node *m_Root = m_Null;
};

template <typename T>
typename RedBlackTree<T>::Node RedBlackTree<T>::NULL_NODE;

template <typename T>
bool RedBlackTree<T>::search(const T &key) const
{
  if (searchNode(m_Root, key) != m_Null)
  {
    return true;
  }

  return false;
}

template <typename T>
const typename RedBlackTree<T>::Node *RedBlackTree<T>::searchNode(Node *z, const T &key) const
{
  while (z != m_Null && key != z->key)
  {
    if (key < z->key)
    {
      z = z->left;
    }
    else
    {
      z = z->right;
    }
  }
  return z;
}

template <typename T>
void RedBlackTree<T>::insert(const T &key)
{
  Node *z = new Node();
  z->key = key;

  insertNode(z);
}

template <typename T>
void RedBlackTree<T>::rotateLeft(Node *x)
{
  Node *y = x->right;
  x->right = y->left;

  if (y->left != m_Null)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;

  if (x->parent == m_Null)
  {
    m_Root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rotateRight(Node *y)
{
  Node *x = y->left;
  y->left = x->right;

  if (x->right != m_Null)
  {
    x->right->parent = y;
  }
  x->parent = y->parent;

  if (y->parent == m_Null)
  {
    m_Root = x;
  }
  else if (y == y->parent->left)
  {
    y->parent->left = x;
  }
  else
  {
    y->parent->right = x;
  }

  x->right = y;
  y->parent = x;
}

template <typename T>
void RedBlackTree<T>::insertNode(Node *z)
{
  Node *x = m_Root;
  Node *y = m_Null;

  while (x != m_Null)
  {
    y = x;
    if (z->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  z->parent = y;

  if (y == m_Null)
  {
    m_Root = z;
  }
  else if (z->key < y->key)
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }

  z->left = m_Null;
  z->right = m_Null;
  z->color = red;

  fixInsert(z);
}

template <typename T>
void RedBlackTree<T>::fixInsert(Node *z)
{
  while (z->parent->color == red)
  {
    if (z->parent == z->parent->parent->left)
    {
      Node *y = z->parent->parent->right;

      if (y->color == red)
      {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->right)
        {
          z = z->parent;
          rotateLeft(z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        rotateRight(z->parent->parent);
      }
    }
    else
    {
      Node *y = z->parent->parent->left;

      if (y->color == red)
      {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->left)
        {
          z = z->parent;
          rotateRight(z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        rotateLeft(z->parent->parent);
      }
    }
  }
  m_Root->color = black;
}

template <typename T>
int RedBlackTree<T>::height() const
{
  return treeHeight(m_Root);
}

template <typename T>
int RedBlackTree<T>::treeHeight(Node *z) const
{
  if (z == m_Null)
  {
    return -1;
  }

  int leftHeight = treeHeight(z->left);
  int rightHeight = treeHeight(z->right);

  return 1 + std::max(leftHeight, rightHeight);
}
