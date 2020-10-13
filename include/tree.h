#ifndef TREE_H
#define TREE_H

#include <map>
#include <vector>

namespace algo {

template <typename T>
class tree {
public:
    T& operator[](const size_t __index);
    void new_son(const size_t __father_index, const size_t __son_index);

    size_t lca(size_t __node_a, size_t __node_b, const size_t __root);

private:
    void lca_dfs(size_t u);

    const size_t SUPER_ROOT = SIZE_MAX;
    std::map<size_t, std::vector<size_t>> son;
    std::map<size_t, size_t> father;
    std::map<size_t, T> value;

    std::map<std::pair<size_t, unsigned int>, size_t> lca_father;
    std::map<size_t, size_t> lca_depth;
};

} // namespace algo

#endif