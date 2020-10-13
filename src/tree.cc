#include "../include/tree.h"
#include <utility>
#include <vector>
#include <cmath>
#include <cstddef>

template <typename T>
T& algo::tree<T>::operator[](const size_t __index) {
    return this->value[__index];
}

template <typename T>
void algo::tree<T>::new_son(const size_t __father_index, const size_t __son_index) {
    this->son[__father_index].push_back(__son_index);
    this->father[__son_index] = __father_index;
}

template <typename T>
size_t algo::tree<T>::lca(size_t __node_a, size_t __node_b, const size_t __root) {
    this->lca_depth.clear();
    this->lca_father.clear();
    this->father.clear();
    this->father[__root] = SUPER_ROOT;

    lca_dfs(__root);

    if (this->lca_depth[__node_a] < this->lca_depth[__node_b])
        std::swap(__node_a, __node_b);

    while (this->lca_depth[__node_a] > this->lca_depth[__node_b])
        __node_a = this->lca_father[std::make_pair(
            __node_a, std::log2(this->lca_depth[__node_a] - this->lca_depth[__node_b] - 1))];

    if (__node_a == __node_b)
        return __node_a;

    for (int i = lca_depth[this->lca_depth[__node_a]] - 1; i >= 0; i--) {
        auto fa_a = this->lca_father[std::make_pair(__node_a, i)];
        auto fa_b = this->lca_father[std::make_pair(__node_b, i)];
        if (fa_a != fa_b) {
            __node_a = fa_a;
            __node_b = fa_b;
        }
    }

    return __node_a;
}

template <typename T>
void algo::tree<T>::lca_dfs(size_t u) {
    auto fa = this->father[u];

    this->lca_father[std::make_pair(u, 0)] = fa;
    this->lca_depth[u] = this->lca_depth[fa] + 1;

    for (int i = 1; i <= std::log2(this->lca_depth[u]); i++) {
        this->lca_father[std::make_pair(u, i)] =
            this->lca_father[std::make_pair(this->lca_father[std::make_pair(u, i - 1)], i - 1)];
    }

    for (auto v : this->son[u]) {
        if (v != fa)
            this->lca_dfs(v);
    }
}
