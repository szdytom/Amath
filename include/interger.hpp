#ifndef AMATH_INTERGER_HPP
#define AMATH_INTERGER_HPP

#include <bitset>
#include <string>
#include <vector>

template < std::size_t Size >
class interger {
public:
    interger();

    interger(interger&& src);
    interger(const interger&& src);
    interger(const interger& src);
    interger(const std::bitset< Size >& src);
    interger(const std::string& src);
    interger(const char* src);
    interger(const int src);
    interger(const unsigned int src);
    interger(const long long int src);
    interger(const unsigned long long int src);

    template < typename T >
    interger operator=(const T src);

    template < typename T >
    interger operator=(T&& src);

    interger operator=(interger&& src);

    interger< Size > operator<<(const std::size_t position) const;
    void operator<<=(const std::size_t position);

    bool operator==(const interger< Size >& value) const;
    bool operator!=(const interger< Size >& value) const;

    bool operator<(const interger< Size >& value) const;
    bool operator>(const interger< Size >& value) const;

    bool operator<=(const interger< Size >& value) const;
    bool operator>=(const interger< Size >& value) const;

    interger< Size > operator+(const interger< Size >& value) const;
    void operator+=(const interger< Size >& value);
    interger< Size > operator+(const unsigned int num) const;
    void operator+=(const unsigned int& num);
    interger< Size > operator+(const unsigned long long int num) const;
    void operator+=(const unsigned long long int num);

    interger< Size > operator-(const interger< Size >& value) const;
    void operator-=(const interger< Size >& value);

    interger< Size > operator*(interger< Size > value) const;
    void operator*=(const interger< Size >& value);

    interger< Size > operator/(const interger< Size >& value) const;
    void operator/=(const interger< Size >& value);

    std::string to_string() const;
    unsigned int to_uint() const;
    unsigned long long int to_ullong() const;
    std::string to_bin_string() const;
    std::bitset< Size > to_bitset() const;

private:
    std::bitset< Size > _base;
};

template < std::size_t Size >
template < typename T >
interger< Size > interger< Size >::operator=(T src) {
    this->_base = std::move(interger(src)._base);
    return *this;
}

template < std::size_t Size >
template < typename T >
interger< Size > interger< Size >::operator=(T&& src) {
    this->_base = std::move(interger(std::forward(src))._base);
    return *this;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator=(interger&& src) {
    this->_base = std::move(src._base);
    return *this;
}

template < std::size_t Size >
interger< Size >::interger() {
    this->_base = std::bitset< Size >(0);
}

template < std::size_t Size >
interger< Size >::interger(interger&& src) {
    this->_base = std::move(src._base);
}

template < std::size_t Size >
interger< Size >::interger(const interger&& src) {
    this->_base = std::forward(src._base);
}

template < std::size_t Size >
interger< Size >::interger(const interger& src) {
    this->_base = src._base;
}

template < std::size_t Size >
interger< Size >::interger(const std::bitset< Size >& src) {
    this->_base = src;
}

template < std::size_t Size >
interger< Size >::interger(const std::string& src) {
    interger res;
    for (auto ch : src)
        res = interger(res._base << 3) + interger(res._base << 1) + interger(ch - '0');

    this->_base = res._base;
}

template < std::size_t Size >
interger< Size >::interger(const char* src)
    : interger< Size >::interger< Size >(std::string(src)) {}

template < std::size_t Size >
interger< Size >::interger(const int src) {
    this->_base = src;
}

template < std::size_t Size >
interger< Size >::interger(const unsigned int src) {
    this->_base = src;
}

template < std::size_t Size >
interger< Size >::interger(const long long int src) {
    this->_base = src;
}

template < std::size_t Size >
interger< Size >::interger(const unsigned long long int src) {
    this->_base = src;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator<<(const std::size_t position) const {
    return this->_base << position;
}

template < std::size_t Size >
void interger< Size >::operator<<=(const std::size_t position) {
    this->_base <<= position;
}

template < std::size_t Size >
bool interger< Size >::operator==(const interger< Size >& value) const {
    for (auto i = this->_base.size() - 1; i >= 0; i--)
        if (this->_base[i] != value._base[i]) return false;

    return true;
}

template < std::size_t Size >
bool interger< Size >::operator!=(const interger< Size >& value) const {
    if (this == value) return false;

    return true;
}

template < std::size_t Size >
bool interger< Size >::operator<(const interger< Size >& value) const {
    for (auto i = this->_base.size() - 1; i >= 0; i--)
        if (this->_base[i] != value._base[i]) return this->_base[i] < value._base[i];

    return false;
}

template < std::size_t Size >
bool interger< Size >::operator>(const interger< Size >& value) const {
    if (this < value or this == value) return false;

    return true;
}

template < std::size_t Size >
bool interger< Size >::operator<=(const interger< Size >& value) const {
    if (this < value or this == value) return true;

    return false;
}

template < std::size_t Size >
bool interger< Size >::operator>=(const interger< Size >& value) const {
    if (this > value or this == value) return true;

    return false;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator+(const interger< Size >& value) const {
    interger a(this->_base ^ value._base);
    interger b((this->_base & value._base) << 1);

    return value._base.any() ? a + b : a;
}

template < std::size_t Size >
void interger< Size >::operator+=(const interger< Size >& value) {
    interger< Size > res = (*this + value);
    this->_base = res._base;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator+(const unsigned int value) const {
    return *this + interger(value);
}

template < std::size_t Size >
void interger< Size >::operator+=(const unsigned int& value) {
    interger< Size > res = (*this + value);
    this->_base = res._base;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator+(const unsigned long long int value) const {
    return *this + interger(value);
}

template < std::size_t Size >
void interger< Size >::operator+=(const unsigned long long int value) {
    interger< Size > res = (*this + value);
    this->_base = res._base;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator-(const interger< Size >& value) const {
    return *this + (interger(std::bitset< Size >(1)) + interger(~value._base));
}

template < std::size_t Size >
void interger< Size >::operator-=(const interger< Size >& value) {
    interger< Size > res = *this - value;
    this->_base = res._base;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator*(interger< Size > value) const {
    interger tmp_this;
    tmp_this._base = this->_base;

    interger res(std::bitset< Size >(0));
    while (value._base.any()) {
        if (value._base[0]) res += tmp_this;
        value._base >>= 1;
        tmp_this += tmp_this;
    }

    return res;
}

template < std::size_t Size >
interger< Size > interger< Size >::operator/(const interger< Size >& value) const {
    interger< Size > tmp = *this;
    interger< Size > res;

    while (tmp > value) {
        int k = 0;
        for (interger c = tmp; tmp >= c; c <<= 1, k++)
            if (tmp < value + c) res += 1 << k;
    }

    return res;
}

template < std::size_t Size >
std::string interger< Size >::to_string() const {
    std::string res;
    std::vector< unsigned char > res_v;
    res_v.push_back(0);

    for (auto i = this->_base.size() - 1; i <= this->_base.size() - 1; i--) {
        int front = this->_base.test(i);

        for (auto& col : res_v) {
            if ((col & 0xf0) >= 0x50) { col += 0x30; }
            if ((col & 0x0f) >= 5) { col += 3; }

            int back = col > 127 ? 1 : 0;
            col <<= 1;
            col |= front;

            front = back;
        }

        if (front ^ 0) { res_v.push_back(1); }
    }

    if (res_v[res_v.size() - 1] & 0xf0) { res += std::to_string(res_v[res_v.size() - 1] >> 4); }

    res += std::to_string(res_v[res_v.size() - 1] & 0x0f);

    if (res_v.size() >= 2) {
        for (auto i = res_v.size() - 2; i <= res_v.size() - 2; i--) {
            res += std::to_string((res_v[i] & 0xf0) >> 4) + std::to_string(res_v[i] & 0x0f);
        }
    }

    return res;
}

template < std::size_t Size >
unsigned int interger< Size >::to_uint() const {
    static_assert(Size <= 32, "to unsigned int overflow.");
    return this->_base.to_ulong();
}

template < std::size_t Size >
unsigned long long int interger< Size >::to_ullong() const {
    static_assert(Size <= 64, "to unsigned long long overflow.");
    return this->_base.to_ullong();
}

template < std::size_t Size >
std::string interger< Size >::to_bin_string() const {
    return this->_base.to_string();
}

template < std::size_t Size >
std::bitset< Size > interger< Size >::to_bitset() const {
    return this->_base;
}

#endif
