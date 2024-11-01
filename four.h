#ifndef FOUR_H
#define FOUR_H

#include <cstddef>
#include <string>
#include <initializer_list>

class Four {
public:
    Four(); 
    Four(const size_t& n, unsigned char t = '0');  
    Four(const std::initializer_list<unsigned char>& t);  
    Four(const std::string& t);  
    Four(const Four& other);  
    Four(Four&& other) noexcept;  
    virtual ~Four() noexcept;  

    Four& operator=(const Four& other);  
    Four& operator=(Four&& other) noexcept;  

    Four operator+(const Four& other) const;  
    Four operator-(const Four& other) const; 
    Four& operator+=(const Four& other);  
    Four& operator-=(const Four& other);  

    bool operator>(const Four& other) const;  
    bool operator<(const Four& other) const; 
    bool operator==(const Four& other) const; 

    size_t size() const;  
    unsigned char get(size_t index) const; 
    void set(size_t index, unsigned char value);  

private:
    unsigned char* data; 
    size_t length;  

    void allocate(size_t size);  
    void deallocate(); 
    bool isValidFour(const unsigned char* str, size_t len) const;  
};

#endif