#pragma once
#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <cstring>
#include <iostream>
#include <cassert>
#include <initializer_list>
#include <exception>
#include <concepts>
#include <cmath>
#include <fstream>
#include <cstdlib>

#include <string>
#include <vector>
#include <queue>
#include <map>

namespace str
{
    class MyString;

    /* Integer conversions */
    struct int_converter
    {
        char *buffer;
        template <typename T, class>
        operator T() const;
    };

    /* Floating point type conversion */
    struct floating_converter
    {
        char *buffer;
        template <typename T, class>
        operator T() const;
    };

    /* An one-use trie for the Aho-Corasick algorithm. Need to reset count to zero for all nodes to reuse */
    struct TrieNode
    {
        std::map<char, TrieNode *> children;
        bool is_end_of_word;
        int depth;
        TrieNode *suffix_link;
        TrieNode *output_link;

        TrieNode(int depth = 0)
        {
            this->depth = depth;
            this->is_end_of_word = false;
            this->suffix_link = nullptr;
            this->output_link = nullptr;
        }
    };

    /* Aho-Corasick class for main init functions. */
    class AhoCorasick
    {
    private:
        TrieNode *root;
        std::vector<std::string> patterns;

    public:
        std::vector<size_t> find(MyString &current_string);
        void build_trie();
        void build_suffix_links();
        void build_output_links();
        AhoCorasick(std::vector<std::string> &patterns);
        ~AhoCorasick();
    };

    bool operator==(const MyString &first_object, const MyString &second_object);
    bool operator!=(const MyString &first_object, const MyString &second_object);
    bool operator<(const MyString &first_object, const MyString &second_object);
    bool operator>(const MyString &first_object, const MyString &second_object);
    bool operator>=(const MyString &first_object, const MyString &second_object);
    bool operator<=(const MyString &first_object, const MyString &second_object);
    std::istream &operator>>(std::istream &in, MyString &src);
    std::ostream &operator<<(std::ostream &out, const MyString &src);
    std::ifstream &operator>>(std::ifstream &in, MyString &src);
    std::ofstream &operator<<(std::ofstream &out, const MyString &src);

    /* MyString class declaration.*/
    class MyString
    {
    private:
        size_t len_;                                                   /* Count of symbols (length of string) in string */
        size_t cur_capacity_;                                          /* Current capacity of string.
                                                                        * The variable may not be equal to the length of the string if,
                                                                        * for example, there is an increase in string length
                                                                        */
        char *str_;                                                    /* Pointer to string in memory*/
        void _swap_(MyString &, MyString &);                           /* Additional copy-memory function */
        void _copy_(const MyString &);                                 /* Private copy function to copy all values from some object*/
        size_t _update_capacity_(size_t predict_size);                 /* Additional function to update capacity value thanks by math stuff */
        bool _check_buf_size_(size_t add_size);                        /* Capacity value check */
        void _append_(const char *str, size_t index, bool with_index); /* Main append function with all parameters. This is base function for mostly append functions. */
        void _reverse_();                                              /* Reverse object's string */
        template <class T>
        void _itoa_(T num, int base); /* Private itoa implement */

    public:
        /*
         * Constructor overloading with different string's declaration.
         */
        MyString(void);
        MyString(const char *str, size_t new_len = 0);
        MyString(std::initializer_list<char> list);
        MyString(std::string &str);
        MyString(const char *str, int elems_count);
        MyString(int rep_times, const char sym);
        MyString(const MyString &other_obj);
        MyString(MyString &&other_object);
        template <typename T, class = typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
        MyString(T possible_int);
        ~MyString(void);

        /* Assignment operator overloading with different data types */
        MyString &operator=(const MyString &other_obj);
        MyString &operator=(std::string &str);
        MyString &operator=(const char *str);
        MyString &operator=(const char sym);
        MyString &operator=(MyString &&other_obj);

        /* Concatenate operator overloading with different data types */
        MyString operator+(const MyString &other_obj) const;
        MyString operator+(const char *str) const;
        MyString operator+(std::string &str) const;

        /* Assignment with concatenate operator overloading with different data types */
        MyString &operator+=(MyString other_obj);
        MyString &operator+=(const char *str);
        MyString &operator+=(std::string &str);

        /* Index operator overloading */
        char &operator[](long long int index) const;

        /*
         * Lexicographically comparing operators overloading.
         * Defined as a friend of the function, because otherwise an error
         * of a large number of parameters passed to the operator occurs
         */
        friend bool str::operator==(const MyString &first_object, const MyString &second_object);
        friend bool str::operator!=(const MyString &first_object, const MyString &second_object);
        friend bool str::operator<(const MyString &first_object, const MyString &second_object);
        friend bool str::operator>(const MyString &first_object, const MyString &second_object);
        friend bool str::operator>=(const MyString &first_object, const MyString &second_object);
        friend bool str::operator<=(const MyString &first_object, const MyString &second_object);

        /* Methods of returning class properties */
        const char *c_str() const;
        const char *data() const;
        size_t lenght() const;
        size_t size() const;
        bool empty() const;
        size_t capacity() const;
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
        void append(const char *str);
        void append(size_t count, const char sym);
        void append(const char *str, size_t index, size_t count);
        void append(std::string &str);
        void append(std::string &str, size_t index, size_t count);

        /* Replace method overloading */
        void replace(size_t index, size_t count, const char *str);
        void replace(size_t index, size_t count, std::string &str);

        /* "At" method likewise .operator[] */
        char &at(size_t index);

        /* Integral type conversion */
        int_converter to_int();
        floating_converter to_float();

        /* Substr method overloading */
        MyString substr(size_t index);
        MyString substr(size_t index, size_t count);

        /* Find method overloading */
        size_t find(const char *str);
        size_t find(const char *str, size_t index);
        size_t find(std::string &str);
        size_t find(std::string &str, size_t index);
        void find(std::vector<std::string> &strs, std::vector<size_t> &result);

        /* Input and Output stream overloading as friend function */
        friend std::istream &str::operator>>(std::istream &in, MyString &src);
        friend std::ostream &str::operator<<(std::ostream &out, const MyString &src);
        /*friend std::ifstream &str::operator>>(std::ifstream &in, MyString &src);
        friend std::ofstream &str::operator<<(std::ofstream &out, const MyString &src);*/
    };
#include "MyString.ipp"

} // namespace str

#endif