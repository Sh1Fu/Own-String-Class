#include "MyString.hpp"

/* Additional swap function. Needs to copy constructor and assignment operator overloading. */
void MyString::_swap_(MyString &first, MyString &second)
{
    using std::swap;
    swap(first.len_, second.len_);
    swap(first.str_, second.str_);
    swap(first.cur_capacity_, second.cur_capacity_);
}

void MyString::_copy_(const MyString &second)
{
    assert(second.str_ != nullptr);
    if (this->str_ != nullptr)
        delete[] this->str_;
    this->len_ = second.len_;
    this->cur_capacity_ = second.cur_capacity_;
    this->str_ = new char[this->cur_capacity_];
    memset(this->str_, 0, this->cur_capacity_);
    for (size_t index = 0; index < this->len_; ++index)
    {
        this->str_[index] = second.str_[index];
    }
    this->str_[len_] = '\0';
}

/* Private function. Own impement of strrev function from string.h */
void MyString::_reverse_()
{
    size_t start = 0, end = this->len_ - 1;
    while (start < end)
    {
        char temp = this->str_[start];
        this->str_[start] = this->str_[end];
        this->str_[end] = temp;
        end--;
        start++;
    }
}

/* Updating capacity, using alignment of the allocated block in memory */
void MyString::_update_capacity_(size_t predict_size)
{
    this->cur_capacity_ = sizeof(size_t) * (static_cast<size_t>(predict_size / sizeof(size_t)) + 1); // Implemented only to show the functionality of capacity and shrink_to_fit
}

/* Default constructor. Init new string as nullptr with len = 0 */
MyString::MyString(void)
{
    cur_capacity_ = 0;
    len_ = 0;
    str_ = nullptr;
}

/* Base constructor. Copy const char content to new ``MyString`` object */
MyString::MyString(const char *s, size_t new_len) : MyString()
{
    len_ = ((new_len == 0 && s != nullptr) ? (strlen(s)) : (new_len));
    cur_capacity_ = len_ + 1;
    str_ = new char[cur_capacity_];
    memset(str_, 0, cur_capacity_);
    memcpy(str_, s, len_);
    str_[len_] = '\0';
}

/*
 * list-based constructor. Calls ``Mystring::Mystring(const char *s)``
 * Redesigned because of new standards and new compilers. Now ``std::initializer_list`` class is used
 */
MyString::MyString(std::initializer_list<char> list) : MyString()
{
    len_ = list.size();
    cur_capacity_ = len_ + 1;
    str_ = new char[cur_capacity_];
    memset(str_, 0, cur_capacity_);
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
MyString::MyString(int count, const char sym) : MyString()
{
    len_ = count;
    cur_capacity_ = len_ + 1;
    str_ = new char[cur_capacity_];
    memset(str_, sym, count);
    str_[count] = '\0';
}

/* Move constructor. Based on copy constructor*/
MyString::MyString(MyString &&other_object) : MyString()
{
    *this = std::move(other_object);
}

/* Base copy constructor */
MyString::MyString(const MyString &own_str) : MyString()
{
    _copy_(own_str);
}

/* Base destructor */
MyString::~MyString(void)
{
    if (str_ != nullptr)
    {
        delete[] str_;
    }
}

/* Assignment operator overloading. Copy all data fields from other object to current*/
MyString &MyString::operator=(const MyString &other_obj)
{
    _copy_(other_obj);
    return *this;
}

/* Assignment operator overloading with std::string object. Based on ``.operator(MyString)`` */
MyString &MyString::operator=(std::string &s)
{
    return this->operator=(MyString(s));
}

/* Assignment operator overloading with null-terminated string. Based on ``.operator(MyString)`` */
MyString &MyString::operator=(const char *s)
{
    return this->operator=(MyString(s));
}

/* Assignment operator overloading with char value. Based on ``.operator(MyString)`` */
MyString &MyString::operator=(const char sym)
{
    return this->operator=(MyString(1, sym));
}

/// @brief Move assgnment operator. Uses private swap function likewise move constructor
/// @param other_obj
/// @return pointer to current object. ``*this``
MyString &MyString::operator=(MyString &&other_obj)
{
    if (this != &other_obj)
    {
        delete[] this->str_;

        this->str_ = other_obj.str_;
        this->len_ = other_obj.len_;
        this->cur_capacity_ = other_obj.cur_capacity_;

        other_obj.str_ = nullptr;
        other_obj.len_ = 0;
        other_obj.cur_capacity_ = 0;
    }
    return *this;
}

/*
 * Summary operator overloading with char array.
 * Basic sum overloading. Very useful in another operators.
 */
MyString MyString::operator+(const char *str) const
{
    size_t str_len = strlen(str), op_len = len_ + str_len;
    char *new_str = new char[op_len];
    memset(new_str, 0, op_len + 1);
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
    return this->operator+(other_obj.str_);
}

/*
 * Summary operator overloading with ``std::string`` object.
 * Basic sum overloading. Based on ``.operator+(const char *)``.
 */
MyString MyString::operator+(std::string &s) const
{
    return this->operator+(s.c_str());
}

/*
 * Assignment with concatenate operator overloading with another MyString object. Uses _update_capacity_ function.
 * Build new null-terminated string with cstring functions and update current (*this) object.
 */
MyString &MyString::operator+=(MyString other_obj)
{
    // MyString res;
    // res = this->operator+(other_obj);
    // _swap_(*this, res);
    // return *this;
    if (cur_capacity_ < other_obj.len_ + len_)
    {
        size_t predict_size = cur_capacity_ + other_obj.len_;
        _update_capacity_(predict_size);
    }
    char *new_str = new char[cur_capacity_];
    memset(new_str, 0, cur_capacity_);
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
    return this->operator+=(MyString(str));
}

/* Assignment with concatenate operator overloading with ``std::string`` object. Based on ``.operator+=(MyString)``. */
MyString &MyString::operator+=(std::string &str)
{
    return this->operator+=(MyString(str));
}

/* Index operator overloading. Calculate index inside operator. Negative index are supported. */
char &MyString::operator[](long long int index)
{
    size_t mod_index = (this->len_ + static_cast<ptrdiff_t>(index)) % this->len_;
    return this->str_[mod_index];
}

/* Null-terminated string pointer return function */
const char *MyString::c_str()
{
    return str_;
}

const char *MyString::data()
{
    return this->c_str();
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
        MyString tmp(this->str_);
        _swap_(*this, tmp);
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
    assert(str != nullptr);
    if (index > this->len_ + 1)
        throw std::out_of_range("Current index more than string's len");
    size_t act_index = ((index > this->len_ + 1) ? this->len_ : index);
    size_t str_len = strlen(str), new_size = (cur_capacity_ <= act_index ? cur_capacity_ + str_len + 1 : cur_capacity_ + str_len);
    char *new_str = new char[new_size];
    memset(new_str, 0, new_size);

    strncpy(new_str, str_, act_index);
    strncat(new_str, str, str_len);
    try
    {
        str_ += act_index;
        strncat(new_str, str_, len_ - act_index);
        str_ -= act_index;
    }
    catch (const std::exception &e)
    {
        throw e.what();
    }

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
    memset(form_str, 0, elems_count + 1);
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
    size_t hole_size = (index + count);
    if (hole_size > this->len_)
        throw std::out_of_range("Current delete size more than a string's part");
    size_t new_len = ((count > (len_ - index + 1)) ? (index) : (len_ - count));
    if (new_len <= 0)
    {
        this->clear();
        return;
    }
    char *new_str = new char[new_len + 1];
    memset(new_str, 0, new_len + 1);

    strncpy(new_str, str_, index);
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
    memset(form_str, 0, count + 1);
    str += index;
    strncpy(form_str, str, count);
    str -= index;
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
    this->_append_(std::string(str.begin() + index, str.begin() + index + count).c_str(), index, true);
}

/*
 * Main replace function.
 * Take null-terminated string and try to paste it into object's string
 * Update all object value (but not capacity).
 */
void MyString::replace(size_t index, size_t count, const char *str)
{
    if (index >= this->len_)
        throw std::out_of_range("Current index is more than string's len");
    assert(str != nullptr);
    size_t substr_len = strlen(str), offset = index + count;
    size_t new_len = len_ - count + substr_len;
    char *new_str;
    try
    {
        new_str = new char[new_len + 1];
        memset(new_str, 0, new_len + 1);
        memcpy(new_str, str_, index);
        strncat(new_str, str, substr_len);
        if (offset <= len_)
        {
            str_ += offset;
            strncat(new_str, str_, (len_ - offset));
            str_ -= offset;
        }
        delete[] str_;
    }
    catch (const std::exception &e)
    {
        throw e.what();
    }
    str_ = new_str;
    len_ = new_len;
    _update_capacity_(new_len);
}

/* Replace function with ``std::string`` object. Based on ``MyString::replace(size_t index, size_t count, const char *str)`` */
void MyString::replace(size_t index, size_t count, std::string &str)
{
    this->replace(index, count, str.c_str());
}

/* Base substr function. Concatenate pointer with ``index`` and returns it. */
char *MyString::substr(size_t index)
{
    if (index > this->len_)
        throw std::out_of_range("Current index more than string's len");
    try
    {
        return str_ + index;
    }
    catch (const std::exception &e)
    {
        throw e.what();
    }
}

/* Substr function. Based on ``MyString::substr(size_t index)`` and cut off function's result string  */
char *MyString::substr(size_t index, size_t count)
{
    static char *substr_p = new char[count + 1];
    memset(substr_p, 0, count + 1);
    substr_p = this->substr(index);
    substr_p[count] = '\0';
    return substr_p;
}

/* Find substr in object's string. Returns index of substr start. Uses ``strstr`` */
size_t MyString::find(const char *str)
{
    return strstr(str_, str) - str_;
}

/*
 * Find substr in object's string. Returns index of substr start. Uses ``strstr``
 * Moves ``str_`` to ``index`` bytes and calls ``strstr``
 */
size_t MyString::find(const char *str, size_t index)
{
    return strstr(str_ + index, str) - str_;
}

/* Find function with ``std::string`` object. Based on ``MyString::find(const char *str)`` */
size_t MyString::find(std::string &str)
{
    return this->find(str.c_str());
}

/* Find function with ``std::string`` object. Based on ``MyString::find(const char *str, size_t index)`` */
size_t MyString::find(std::string &str, size_t index)
{
    return this->find(str.c_str(), index);
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
    bool empty_by_default = (src.len_ == 0 ? true : false);
    while (in.get(buffer, sizeof(buffer), '\n'))
    {
        char *pos_newline = strchr(buffer, '\n');
        ((pos_newline != nullptr) ? (buffer[buffer - pos_newline] = '\0') : NULL);
        part_len = strlen(buffer);
        size_t new_size = (empty_by_default ? part_len + 1 : src.cur_capacity_ + (part_len * 2));
        char *new_str = new char[new_size];
        memset(new_str, 0, new_size);
        if ((src.cur_capacity_ - part_len) > 0 && src.str_ != nullptr)
        {
            strncat(src.str_, buffer, part_len);
            src.len_ += part_len;
        }
        else if (empty_by_default)
        {
            strncpy(new_str, buffer, part_len);
            new_str[part_len] = '\0';
        }
        else
        {
            strncpy(new_str, src.str_, src.len_);
            strncat(new_str, buffer, part_len);
            new_str[src.len_ + part_len] = '\0';
        }
        delete[] src.str_;
        src.str_ = new_str;
        src.len_ = strlen(src.str_);
        src.cur_capacity_ = src.len_ + 1;

        memset(buffer, 0, part_len);
        if (pos_newline != nullptr)
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
