#include "../include/tree.h"

template <typename T>
void amath::tree_node<T>::push_back(T __son) {
    son_v.push_back(__son);
}

template <typename T>
size_t amath::tree_node<T>::size() {
    return son_v.size();
}

template <typename T>
amath::tree_node<T> amath::tree<T>::operator[](const size_t __index) {
    return tree_map[__index];
}