#include "structures/tree.hpp"

#include "ui.hpp"

BinaryTree::BinaryTree() { root = nullptr; }

BinaryTree::BinaryTree(StoreSection section) : root(new Node(section)) {}

BinaryTree::BinaryTree(const std::string& question, const BinaryTree& left,
                       const BinaryTree& right)
    : root(new Node(question))
{
  root->left = left.root;
  root->right = right.root;
}

StoreSection BinaryTree::find_store_section() const
{
  Node* trav = root;
  while (trav != nullptr)
  {
    if (trav->section != StoreSection::None)
    {
      return trav->section;
    }
    bool answer = confirm(trav->question);
    trav = answer ? trav->left : trav->right;
  }

  return StoreSection::None;
}

BinaryTree::Node::Node(const std::string& question) : question(question) {}

BinaryTree::Node::Node(StoreSection section) : question(""), section(section) {}

BinaryTree::~BinaryTree() {}
