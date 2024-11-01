#include "four.h"
#include <stdexcept>
#include <algorithm>

void Four::allocate(size_t size) {
    data = new unsigned char[size];
    length = size;
}

void Four::deallocate() {
    delete[] data;
    data = nullptr;
    length = 0;
}

bool Four::isValidFour(const unsigned char* str, size_t len) const {
    for (size_t i = 0; i < len; ++i) {
        if (str[i] < '0' || str[i] > '3') {
            return false;
        }
    }
    return true;
}

Four::Four() : data(nullptr), length(0) {
    allocate(1);
    data[0] = '0';
}

Four::Four(const size_t& n, unsigned char t) {
    if (t < '0' || t > '3') {
        throw std::invalid_argument("Цифра должна быть от 0 до 3");
    }
    allocate(n);
    for (size_t i = 0; i < length; ++i) {
        data[i] = t;
    }
}

Four::Four(const std::initializer_list<unsigned char>& t) {
    if (!isValidFour(t.begin(), t.size())) {
        throw std::invalid_argument("Недопустимые четверичные цифры");
    }
    allocate(t.size());
    std::copy(t.begin(), t.end(), data);
}

Four::Four(const std::string& t) {
    if (!isValidFour(reinterpret_cast<const unsigned char*>(t.c_str()), t.length())) {
        throw std::invalid_argument("Недопустимые четверичные цифры");
    }
    allocate(t.length());
    for (size_t i = 0; i < length; ++i) {
        data[i] = t[i];
    }
}

Four::Four(const Four& other) {
    allocate(other.length);
    std::copy(other.data, other.data + length, data);
}

Four::Four(Four&& other) noexcept : data(other.data), length(other.length) {
    other.data = nullptr;
    other.length = 0;
}

Four::~Four() noexcept {
    deallocate();
}

Four& Four::operator=(const Four& other) {
    if (this != &other) {
        deallocate();
        allocate(other.length);
        std::copy(other.data, other.data + length, data);
    }
    return *this;
}

Four& Four::operator=(Four&& other) noexcept {
    if (this != &other) {
        deallocate();
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}

Four Four::operator+(const Four& other) const {
    size_t max_len = std::max(length, other.length);
    Four result(max_len + 1, '0');
    
    int carry = 0;
    for (size_t i = 0; i < max_len || carry; ++i) {
        int sum = carry;
        if (i < length) sum += data[length - 1 - i] - '0';
        if (i < other.length) sum += other.data[other.length - 1 - i] - '0';
        
        result.data[result.length - 1 - i] = (sum % 4) + '0';
        carry = sum / 4;
    }
    
    size_t start = 0;
    while (start < result.length - 1 && result.data[start] == '0') start++;
    
    if (start > 0) {
        Four trimmed(result.length - start);
        std::copy(result.data + start, result.data + result.length, trimmed.data);
        return trimmed;
    }
    
    return result;
}

Four Four::operator-(const Four& other) const {
    if (*this < other) {
        throw std::runtime_error("Невозможно вычесть большее число из меньшего");
    }

    Four result(length, '0');
    int borrow = 0;
    
    for (size_t i = 0; i < length; ++i) {
        int digit1 = data[length - 1 - i] - '0';
        int digit2 = (i < other.length) ? (other.data[other.length - 1 - i] - '0') : 0;
        
        digit1 -= borrow;
        if (digit1 < digit2) {
            digit1 += 4;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.data[length - 1 - i] = (digit1 - digit2) + '0';
    }
    
    size_t start = 0;
    while (start < result.length - 1 && result.data[start] == '0') start++;
    
    if (start > 0) {
        Four trimmed(result.length - start);
        std::copy(result.data + start, result.data + result.length, trimmed.data);
        return trimmed;
    }
    
    return result;
}

Four& Four::operator+=(const Four& other) {
    *this = *this + other;
    return *this;
}

Four& Four::operator-=(const Four& other) {
    *this = *this - other;
    return *this;
}

bool Four::operator>(const Four& other) const {
    if (length != other.length) {
        return length > other.length;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return data[i] > other.data[i];
        }
    }
    return false;
}

bool Four::operator<(const Four& other) const {
    if (length != other.length) {
        return length < other.length;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return data[i] < other.data[i];
        }
    }
    return false;
}

bool Four::operator==(const Four& other) const {
    if (length != other.length) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

size_t Four::size() const {
    return length;
}

unsigned char Four::get(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Индекс выходит за пределы");
    }
    return data[index];
}

void Four::set(size_t index, unsigned char value) {
    if (index >= length) {
        throw std::out_of_range("Индекс выходит за пределы");
    }
    if (value < '0' || value > '3') {
        throw std::invalid_argument("Значение должно быть от 0 до 3");
    }
    data[index] = value;
}