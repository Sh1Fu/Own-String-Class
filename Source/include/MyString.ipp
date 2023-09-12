
/* Template implementation of itoa function. Uses to convert integral types to object's string. */
template <class T>
void MyString::_itoa_(T num, int base)
{
    this->len_ = static_cast<size_t>(log10(num) + 1);
    this->cur_capacity_ = this->len_ + 1;
    this->str_ = new char[int(log10(num) + 1) + 1];
    if (base < 0)
        throw "Integer base is a negative value";
    size_t i = 0;
    bool is_negative = false;
    if (num == 0)
    {
        this->str_[i++] = '0';
        this->str_[i] = '\0';
        return;
    }
    if (num < 0 && base == 10)
    {
        is_negative = true;
        num = -num;
    }
    while (num != 0)
    {
        int rem = num % base;
        this->str_[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    if (is_negative)
        this->str_[i++] = '-';

    this->str_[i] = '\0';
    this->_reverse_();
}

/* Basic integral types constructor */
template <typename T, class>
MyString::MyString(T possible_int) : MyString()
{
    if (std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, long double>::value)
    {
        this->str_ = new char[21];
        this->cur_capacity_ = 21;
        snprintf(this->str_, 20, "%f", possible_int);
        this->len_ = strlen(this->str_);
        size_t i = this->len_;
        while (this->str_[--i] == '0');
        ++i;
        this->str_ += i;
        memset(this->str_, 0, this->len_ - i);
        this->str_ -= i;
        this->len_ = i;
        this->shrink_to_fit();
    }
    else
    {
        size_t new_int = static_cast<size_t>(possible_int);
        this->_itoa_(new_int, 10);
    }
}