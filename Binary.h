//binary class here
#include <iostream>

class Binary
{
private:
    int length;
    short * bits;
public:
    Binary(int value=0, int length=16);
    ~Binary()
    {
        delete this->bits;
    }
    int get_length();
    short get_sign();

    void output_sign();
    void output_demical();
    void output_binary();

    friend bool check_valid(Binary & toCheck);
    friend std::ostream & operator <<(std::ostream & cout, const Binary & binary_value);
    friend std::istream & operator >>(std::istream & cin,  const Binary & binary_value);

    void sign_extension(int to_len);
    void shift_left(int & dist);
    void shift_right(int & dist);
    
    void negative();

    friend Binary operator +(const Binary & a, const Binary & b);
    friend Binary operator *(const Binary & a, const Binary & b);
    friend Binary operator /(const Binary & a, const Binary & b);
};

bool check_valid(Binary * toCheck);
Binary operator +(const Binary & a, const Binary & b);
Binary operator *(const Binary & a, const Binary & b);
Binary operator /(const Binary & a, const Binary & b);
std::ostream & operator <<(std::ostream & cout, const Binary & binary_value);
std::istream & operator >>(std::istream & cin,  const Binary & binary_value);