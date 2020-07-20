#include <iostream>

template <typename T>
class minimum {
    public:
    T operator()(T x, T y) {
        return std::min(x, y);
    }
};

template <typename T>
class maximum {
    public:
    T operator()(T x, T y) {
        return std::max(x, y);
    }
};

template <typename T>
class sum {
    public:
    T operator()(T x, T y) {
        return x + y;
    }
};

template <typename T, typename _function = sum<T>, T _empty = 0>
class TreeArray {
    protected:
    _function __function;
    T *c;
    int size;

    inline int lowbit(int x) {
        return x & (-x);
    }

    public:
    TreeArray() {
        c = new T;
        *c = _empty;
        size = 1;
    }

    TreeArray(size_t size, bool set_zero_required = 0) {
        c = new T[size];
        this->size = size;

        if (set_zero_required) {
            for (int i = 0; i < size; ++i)
                c[i] = _empty;
        }
    }

    void resize(size_t size) {
        delete c;
        c = new T[size];
        this->size = size;
    }

    void change(int x, T w) {
        for (; x <= size; x += lowbit(x))
            c[x] = __function(c[x], w);
    }

    T calc(int x) {
        T ans = _empty;
        for (; x; x -= lowbit(x))
            ans = __function(ans, c[x]);
        return ans;
    }
};