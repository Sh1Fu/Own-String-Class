#include "MyString.hpp"

/* Default constructor. Init new string as nullptr with len = 0 */
MyString::MyString(void)
{
    cur_capacity_ = 0;
    len_ = 0;
    str_ = nullptr;
}

/* Base constructor. Copy const char content to new ``MyString`` object */
MyString::MyString(const char *s, size_t new_len)
{
    len_ = ((new_len == 0) ? (strlen(s)) : (new_len));
    cur_capacity_ = len_ + 1;
    str_ = new char[cur_capacity_];
    memcpy(str_, s, len_);
    str_[len_] = '\0';
}

/*
 * list-based constructor. Calls ``Mystring::Mystring(const char *s)``
 * Redesigned because of new standards and new compilers. Now ``std::initializer_list`` class is used
 */
MyString::MyString(std::initializer_list<char> list)
{
    len_ = list.size();
    cur_capacity_ = len_ + 1;
    str_ = new char[cur_capacity_];
    size_t loop_index = 0;
    for (auto &element : list)
    {
        str_[loop_index] = element;
        ++loop_index;
    }
    str_[loop_index] = '\0';
}

/*
 * Constructor to copy std::string content to new MyString object.
 * Calls ``Mystring::Mystring(const char *s)``
 */
MyString::MyString(std::string &s) : MyString(s.c_str(), s.size()) {}

/* Constructor to copy ``count`` bytes from initial string */
MyString::MyString(const char *s, int count) : MyString(s, static_cast<size_t>(count)) {}

/* Constructor to copy <sym> to string ``count`` times */
MyString::MyString(int count, const char sym)
{
    len_ = count;
    cur_capacity_ = len_ + 1;
    str_ = new char[cur_capacity_];
    for (size_t index = 0; index < cur_capacity_; ++index)
    {
        str_[index] = sym;
    }
    str_[len_] = '\0';
}

/* Base copy constructor */
MyString::MyString(const MyString &own_str)
{
    size_t own_str_len = own_str.len_;
    len_ = own_str_len;
    cur_capacity_ = len_ + 1;
    str_ = new char[cur_capacity_];
    for (size_t index = 0; index < len_; ++index)
    {
        str_[index] = own_str.str_[index];
    }
    str_[len_] = '\0';
}

/* Base destructor */
MyString::~MyString(void)
{
    if (str_ != nullptr)
    {
        delete[] str_;
    }
}

/* Additional swap function. Needs to copy constructor and assignment operator overloading. */
void MyString::swap(MyString &first, MyString &second)
{
    using std::swap;
    swap(first.len_, second.len_);
    swap(first.str_, second.str_);
    swap(first.cur_capacity_, second.cur_capacity_);
}

/* Updating capacity, using alignment of the allocated block in memory */
void MyString::_update_capacity_(size_t predict_size)
{
    this->cur_capacity_ = sizeof(size_t) * (static_cast<size_t>(predict_size / sizeof(size_t)) + 1); // Implemented only to show the functionality of capacity and shrink_to_fit
}

/* Assignment operator overloading. Copy all data fields from other object to current*/
MyString &MyString::operator=(MyString other_obj)
{
    swap(*this, other_obj);
    return *this;
}

/* Assignment operator overloading with std::string object. Based on ``.operator(MyString)`` */
MyString &MyString::operator=(std::string &s)
{
    return (*this).operator=(MyString(s));
}

/* Assignment operator overloading with null-terminated string. Based on ``.operator(MyString)`` */
MyString &MyString::operator=(const char *s)
{
    return (*this).operator=(MyString(s));
}

/* Assignment operator overloading with char value. Based on ``.operator(MyString)`` */
MyString &MyString::operator=(const char sym)
{
    return (*this).operator=(MyString(1, sym));
}

/*
 * Summary operator overloading with char array.
 * Basic sum overloading. Very useful in another operators.
 */
MyString MyString::operator+(const char *str) const
{
    size_t str_len = strlen(str), op_len = len_ + str_len;
    char *new_str = new char[op_len];
    strncpy(new_str, str_, len_);
    strncat(new_str, str, str_len);
    return MyString(new_str, op_len);
}

/*
 * Summary operator overloading with ``MyString`` object.
 * Basic sum overloading. Based on ``.operator+(const char *)``.
 */
MyString MyString::operator+(const MyString &other_obj) const
{

    return (*this).operator+(other_obj.str_);
}

/*
 * Summary operator overloading with ``std::string`` object.
 * Basic sum overloading. Based on ``.operator+(const char *)``.
 */
MyString MyString::operator+(std::string &s) const
{
    return (*this).operator+(s.c_str());
}

/*
 * Assignment with concatenate operator overloading with another MyString object. Uses _update_capacity_ function.
 * Build new null-terminated string with cstring functions and update current (*this) object.
 */
MyString &MyString::operator+=(MyString other_obj)
{
    // MyString res;
    // res = (*this).operator+(other_obj);
    // swap(*this, res);
    // return *this;
    if (cur_capacity_ < other_obj.len_ + len_)
    {
        size_t predict_size = cur_capacity_ + other_obj.len_;
        _update_capacity_(predict_size);
    }
    char *new_str = new char[cur_capacity_];
    strncpy(new_str, str_, len_);
    strncat(new_str, other_obj.str_, other_obj.len_);
    len_ += other_obj.len_;
    new_str[len_] = '\0';
    delete[] str_;
    str_ = new_str;
    return *this;
}

/* Assignment with concatenate operator overloading with ``null-terminated string``. Based on ``.operator+=(MyString)``. */
MyString &MyString::operator+=(const char *str)
{
    return (*this).operator+=(MyString(str));
}

/* Assignment with concatenate operator overloading with ``std::string`` object. Based on ``.operator+=(MyString)``. */
MyString &MyString::operator+=(std::string &str)
{
    return (*this).operator+=(MyString(str));
}

/* Index operator overloading. Calculate index inside operator. Negative index are supported. */
char &MyString::operator[](int index)
{
    size_t mod_index = (this->len_ + static_cast<ptrdiff_t>(index)) % this->len_;
    return this->str_[mod_index];
}

/* Null-terminated string pointer return function */
const char *MyString::c_str()
{
    return str_;
}

/* Return current lenght of string without null-terminating symbol */
size_t MyString::lenght()
{
    return len_;
}

/* Returns current size of string without null-terminating symbol */
size_t MyString::size()
{
    return len_;
}

/* Returns true if current string size eq to zero (string is empty). */
bool MyString::empty()
{
    return (len_ == 0 ? true : false);
}

/* Returns string capacity value. */
size_t MyString::capacity()
{
    return cur_capacity_;
}

/* Reduce string memory allocation size. Create new MyString obj, swap it with (*this) object. */
void MyString::shrink_to_fit()
{
    if (cur_capacity_ > len_)
    {
        assert(strlen(str_) == len_);
        MyString tmp((*this).str_);
        swap(*this, tmp);
    }
}

/* Delete all symbols in string (sets to 0). */
void MyString::clear()
{
    memset(str_, 0, len_);
    len_ = 0;
}

/*
 * Main insert by index function.
 * Inserts the received string at the specified index into the object string.
 * 1. First, a chunk up to the used index is copied to the new line.
 * 2. Then the string from the argument is added.
 * 3. At the end, the characters that were after the index are added.
 * 4. The properties of the class object are updated
 */
void MyString::insert(size_t index, const char *str)
{
    size_t str_len = strlen(str), new_size = (cur_capacity_ <= index ? cur_capacity_ + str_len + 1 : cur_capacity_ + str_len);
    char *new_str = new char[new_size];
    memset(new_str, 0, new_size);

    strncpy(new_str, str_, index);
    strncat(new_str, str, str_len);

    str_ += index;
    strncat(new_str, str_, len_ - index);
    str_ -= index;
    delete[] str_;

    str_ = new_str;
    len_ = strlen(new_str);
    _update_capacity_(new_size);
}

/* Insert by index function. Based on ``MyString::insert(size_t index, const char *str)`` */
void MyString::insert(size_t index, size_t rep_times, const char sym)
{
    char *form_str = new char[rep_times + 1];
    memset(form_str, sym, rep_times);
    form_str[rep_times] = '\0';
    this->insert(index, form_str);
    delete[] form_str;
}

/*
 * Insert by index function with ``null-terminated string``, which size is elems_count.
 * Based on ``MyString::insert(size_t index, const char *str)``
 */
void MyString::insert(size_t index, const char *str, size_t elems_count)
{
    char *form_str = new char[elems_count + 1];
    strncpy(form_str, str, elems_count);
    form_str[elems_count] = '\0';
    this->insert(index, form_str);
}

/*
 * Insert by index function with ``std::string``.
 * Based on ``MyString::insert(size_t index, const char *str)``
 */
void MyString::insert(size_t index, std::string &str)
{
    this->insert(index, str.c_str());
}

/*
 * Insert by index function with ``std::string``, which size is elems_count.
 * Based on ``MyString::insert(size_t index, const char *str)``
 */
void MyString::insert(size_t index, std::string &str, size_t elems_count)
{
    this->insert(index, std::string(str.begin(), str.begin() + elems_count).c_str());
}

/*
 * Erase substr function.
 * Checks the count parameter to see if it is possible to remove that many characters. If not, clear() is called.
 * Otherwise, a set of actions is performed to copy data from the old string without the piece to be deleted
 * Updates the object properties (capacity does not change)
 */
void MyString::erase(size_t index, size_t count)
{
    size_t new_len = ((count > (len_ - index + 1)) ? (index) : (len_ - count));
    if (new_len <= 0)
    {
        this->clear();
        return;
    }
    char *new_str = new char[new_len + 1];
    memset(new_str, 0, new_len + 1);

    strncpy(new_str, str_, index);
    size_t hole_size = (index + count);
    str_ += hole_size;
    strncat(new_str, str_, len_ - hole_size);
    str_ -= hole_size;
    delete[] str_;

    str_ = new_str;
    len_ = new_len;
    cur_capacity_ = len_ + 1;
}

/* Main append function. Based on insert by index function */
void MyString::_append_(const char *str, size_t index, bool with_index)
{
    size_t act_index = (with_index ? index : len_);
    this->insert(act_index, str, strlen(str));
}

/* Classical append function with null-terminated string. */
void MyString::append(const char *str)
{
    this->_append_(str, 0, false);
}

/* append function. Based on insert by index function */
void MyString::append(size_t count, const char sym)
{
    this->insert(len_, count, sym);
}

/* append function with null-terminated string, which size is ``count``. Based on main append function */
void MyString::append(const char *str, size_t index, size_t count)
{
    char *form_str = new char[count + 1];
    strncpy(form_str, str, count);
    form_str[count] = '\0';
    this->_append_(form_str, index, true);
}

/* append function with ``std::string`` object. Based on main append function */
void MyString::append(std::string &str) noexcept
{
    this->_append_(str.c_str(), 0, false);
}

/* append function with ``std::string`` object, which size is ``count``. Based on main append function */
void MyString::append(std::string &str, size_t index, size_t count) noexcept
{
    this->_append_(std::string(str.begin(), str.begin() + count).c_str(), index, true);
}

/* Comparison operator overload */
bool operator==(const MyString &first_str, const MyString &second_str)
{
    return (strcmp(first_str.str_, second_str.str_) == 0);
}

bool operator<(const MyString &first_str, const MyString &second_str)
{
    return (strcmp(first_str.str_, second_str.str_) < 0);
}

bool operator!=(const MyString &first_str, const MyString &second_str)
{
    return !(first_str == second_str);
}

bool operator>(const MyString &first_str, const MyString &second_str)
{
    return !(first_str == second_str) && !(first_str < second_str);
}

bool operator<=(const MyString &first_str, const MyString &second_str)
{
    return first_str < second_str || first_str == second_str;
}

bool operator>=(const MyString &first_str, const MyString &second_str)
{
    return !(first_str < second_str);
}

/*
 * Input data stream operator overload.
 * Uses reading the entire stream over a buffer of size 4096
 * bytes, adding each new chunk to the string
 */
std::istream &operator>>(std::istream &in, MyString &src)
{
    char buffer[4096];
    memset(buffer, 0, 4096);
    size_t part_len = 0;
    while (in.get(buffer, sizeof(buffer), '\n'))
    {
        char *pos_newline = strchr(buffer, '\n');
        bool has_newline = (pos_newline != nullptr);
        (has_newline ? (buffer[buffer - pos_newline] = '\0') : NULL);
        part_len = strlen(buffer);
        if ((src.cur_capacity_ - part_len) > 0 && src.str_ != nullptr)
        {
            strncat(src.str_, buffer, part_len);
            src.len_ += part_len;
        }
        else if (src.len_ == 0)
        {
            char *new_str = new char[part_len + 1];
            strncpy(new_str, buffer, part_len);
            new_str[part_len] = '\0';
            delete[] src.str_;
            src.str_ = new_str;
            src.len_ = part_len;
            src.cur_capacity_ = src.len_ + 1;
        }
        else
        {
            char *new_str = new char[src.cur_capacity_ + (part_len * 2)];
            strncpy(new_str, src.str_, src.len_);
            strncat(new_str, buffer, part_len);
            new_str[src.len_ + part_len] = '\0';
            delete[] src.str_;
            src.str_ = new_str;
            src.len_ = strlen(src.str_);
            src.cur_capacity_ = src.len_ + 1;
        }
        memset(buffer, 0, part_len);
        if (has_newline)
            break;
    }
    return in;
}

/* Standard output operator overloading */
std::ostream &operator<<(std::ostream &out, const MyString &src)
{
    out << src.str_;
    return out;
}
