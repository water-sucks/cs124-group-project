#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

enum class StoreSection
{
  None,
  Meat,
  Produce,
  Freezer,
  Shelves
};

#include <string>

class BinaryTree
{
public:
  BinaryTree();
  BinaryTree(StoreSection section);
  BinaryTree(const std::string& question, const BinaryTree& left,
             const BinaryTree& right);

  // Traverse tree by asking the specified questions and
  // find an appropriate store section based on the answers.
  StoreSection find_store_section() const;

  // TODO: define
  ~BinaryTree();

private:
  struct Node
  {
    explicit Node(const std::string& question);
    explicit Node(StoreSection section);

    std::string question;
    StoreSection section = StoreSection::None;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  Node* root;
};

#endif
