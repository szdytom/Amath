#ifndef TREE_H
#define TREE_H

#include <map>
#include <vector>

namespace amath {

template <typename T>
class tree_node {
public:
    void push_back(T __son);
    size_t size();

private:
    std::vector<T> son_v;
};

template <typename T>
class tree {
public:
    tree_node<T> operator[](const size_t __index);

private:
    std::map<size_t, tree_node<T>> tree_map;
};

} // namespace amath

#endif