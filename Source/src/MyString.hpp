#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <cstring>
#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <cassert>
class MyString
{
protected:
    size_t len_;                                 /* Count of symbols (length of string) in string */
    size_t cur_capacity_;                        /* Current capacity of string.
                                                  * The variable may not be equal to the length of the string if,
                                                  * for example, there is an increase in string length
                                                  */
    char *str_;                                  /* Pointer to string in memory*/
    void swap(MyString &, MyString &);           /* Additional copy-memory function */
    void _update_capacity_(size_t predict_size); /* Additional function to update capacity value thanks by math stuff */

public:
    /*
     * Constructor overloading with different string's declaration.
     */
    MyString(void);
    MyString(const char *str, size_t new_len = 0);
    MyString(const char (&str_as_array)[]);
    MyString(std::string &str);
    MyString(const char *str, int elems_count);
    MyString(int rep_times, const char sym);
    MyString(const MyString &other_obj);
    ~MyString(void);

    /* Assignment operator overloading with different data types */
    MyString &operator=(MyString other_obj);
    MyString &operator=(std::string &str);
    MyString &operator=(const char *str);
    MyString &operator=(const char sym);

    /* Concatenate operator overloading with different data types */
    MyString operator+(const MyString &other_obj) const;
    MyString operator+(const char *str) const;
    MyString operator+(std::string &str) const;

    /* Assignment with concatenate operator overloading with different data types */
    MyString &operator+=(MyString other_obj);
    MyString &operator+=(const char *str);
    MyString &operator+=(std::string &str);

    /* Index operator overloading */
    char &operator[](int index);

    /*
     * Lexicographically comparing operators overloading.
     * Defined as a friend of the function, because otherwise an error
     * of a large number of parameters passed to the operator occurs
     */
    friend bool operator==(const MyString &first_object, const MyString &second_object);
    friend bool operator!=(const MyString &first_object, const MyString &second_object);
    friend bool operator<(const MyString &first_object, const MyString &second_object);
    friend bool operator>(const MyString &first_object, const MyString &second_object);
    friend bool operator>=(const MyString &first_object, const MyString &second_object);
    friend bool operator<=(const MyString &first_object, const MyString &second_object);

    /* Methods of returning class properties */
    const char *c_str();
    size_t lenght();
    size_t size();
    bool empty();
    size_t capacity();
    void shrink_to_fit();
    void clear();

    /* Insert method with different data types. Method overloading */
    void insert(size_t index, const char *str);
    void insert(size_t index, size_t rep_times, const char sym);
    void insert(size_t index, const char *str, size_t count);
    void insert(size_t index, std::string &str);
    void insert(size_t index, std::string &str, size_t count);

    /* Erase method */
    void erase(size_t index, size_t count);

    /* Modified append method with different data types*/
    void append(const char *str, size_t index = 0, size_t unsued = 0, bool with_index = false);
    void append(size_t count, const char sym);
    void append(const char *str, size_t index, size_t count);
    void append(std::string &str, size_t index = 0) noexcept;
    void append(std::string &str, size_t index, size_t count) noexcept;

    /* Replace method overloading */
    void replace(size_t index, size_t count, const char *str);
    void replace(size_t index, size_t count, std::string &str);

    /* Substr method overloading */
    char *substr(size_t index);
    char *substr(size_t index, size_t count);

    /* Find method overloading */
    size_t find(const char *str);
    size_t find(const char *str, size_t index);
    size_t find(std::string &str);
    size_t find(std::string &str, size_t index);

    /* Input and Output stream overloading as friend function */
    friend std::istream &operator>>(std::istream &in, MyString &src);
    friend std::ostream &operator<<(std::ostream &out, const MyString &src);
};
#endif