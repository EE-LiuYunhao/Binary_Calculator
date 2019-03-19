//binary class here
#include <iostream>
//#define DEBUG

class Binary
{
private:
    int length;
    short * bits;
public:
    Binary(int value=0, int length=16);
    Binary(const Binary & copy);
    ~Binary()
    {
        delete this->bits;
    }
    int get_length() const;
    short get_sign() const;

    void output_sign() const;
    void output_demical() const;
    void output_binary() const;

    friend bool check_valid(const Binary & toCheck);
    friend std::ostream & operator <<(std::ostream & cout, const Binary & binary_value);
    friend std::istream & operator >>(std::istream & cin,  Binary & binary_value);

    void sign_extension(int to_len);
    void shift_left(int dist=1);
    void shift_right(int dist=1);
    
    void negative();

    friend Binary operator +(Binary a, Binary b);
    friend Binary operator *(const Binary & a, const Binary & b);
    friend Binary operator /(const Binary & a, const Binary & b);
};

bool check_valid(Binary * toCheck);
Binary operator +(Binary a, Binary b);
Binary operator *(const Binary & a, const Binary & b);
Binary operator /(const Binary & a, const Binary & b);
std::ostream & operator <<(std::ostream & cout, const Binary & binary_value);
std::istream & operator >>(std::istream & cin,  Binary & binary_value);