#include "Binary.h"
#include <iostream>
#include <string>

enum mani_algorithm
{
    BOOTH_ALGORITHM=1,NORMAL_ALGORITHM=2
};

const short MANIPULATION_OPERATION = BOOTH_ALGORITHM;

Binary::Binary(int value, int length)
{
    this->length = length;
    this->bits = new short [length];
    unsigned char sign = value>=0?0:1;
    value = sign?-1*value:value;
    for(int i=0;i<length-1;i++)
    {
        //This iteration convers the value into the binary pattern
        #ifdef DEBUG
            std::cout<<value % 2<<"\t";
            #endif
        bits[i] = value % 2;
        value /= 2;
        #ifdef DEBUG
            std::cout<<"Bits["<<i<<"]: "<<bits[2]<<std::endl;
            #endif
    }
    //Then deal with the sign issue. 
    bits[length-1]=sign;
    if(sign)
    {
        #ifdef DEBUG
            std::cout<<"Before converting: ";
            for(int i=length-1;i>=0;i--)
            {
                std::cout<<bits[i];
            }
            #endif
        for(int i=0;i<length-1;i++)
        {
            bits[i] = bits[i]?0:1;
        }
        #ifdef DEBUG
            std::cout<<"\nAfter converting: ";
            for(int i=length-1;i>=0;i--)
            {
                std::cout<<bits[i];
            }
            #endif
        bits [0] = bits[0]+1;
        short carry = bits[0]/2;
        bits[0] %= 2;
        for(int i=1;i<length-1;i++)
        {
            #ifdef DEBUG
                std::cout<<"\n bits["<<i<<"]: "<<bits[i]<<" Carry out: "<<carry;
                #endif
            bits[i] = bits[i]+carry;
            carry = bits[i]/2;
            bits[i] %= 2;
        }
        #ifdef DEBUG
            std::cout<<std::endl;
            #endif
    }
}

Binary::Binary(const Binary & copy)
{
    this->length = copy.get_length();
    this->bits = new short[length];
    for(int i=0;i<this->length;i++)
    {
        this->bits[i] = copy.bits[i];
    }
}

int Binary::get_length() const
{
    return this->length;
}
short Binary::get_sign() const
{
    return this->bits[this->length-1];
}

void Binary::output_sign() const
{
    if(this->get_sign())    std::cout<<"-";
    else                    std::cout<<"+";
}

void Binary::output_demical() const
{
    long power = 1;
    int value = 0;
    for(int i=0;i<length-1;i++)
    {
        value += bits[i]*power;
        power *= 2;
    }
    if(this->get_sign())
    {
        value -= power;
    }
    std::cout<<value;
}
void Binary::output_binary() const
{
    for(int i=length-1;i>=0;i--)
    {
        std::cout<<this->bits[i];
    }
}


bool check_valid(const Binary & toCheck)
{
    for(int i=0;i<toCheck.length;i++)
    {
        if(toCheck.bits[i]!=0 && toCheck.bits[i]!=1)    return false;
    }
    return true;
}
std::ostream & operator <<(std::ostream & cout, const Binary & binary_value)
{
    /*
    std::string str = "";
    for(int i=binary_value.length-1;i>=0;i--)
    {
        str += binary_value.bits[i]?"1":"0";
    }
    cout<<str;
    return cout;
    */
   binary_value.output_binary();
   std::cout<<"\t";
   binary_value.output_demical();
}
std::istream & operator >>(std::istream & cin, Binary & binary_value)
{
    int value = 0;
    cin>>value;
    //need to convert the integer to binary pattern
    unsigned char sign = value>=0?0:1;
    value = sign?-1*value:value;
    for(int i=0;i<binary_value.length-1;i++)
    {
        //This iteration convers the value into the binary pattern
        binary_value.bits[i] = value % 2;
        value /= 2;
    }
    //Then deal with the sign issue. 
    binary_value.bits[binary_value.length-1]=sign;
    if(sign)
    {
        for(int i=0;i<binary_value.length-1;i++)
        {
            binary_value.bits[i] = binary_value.bits[i]?0:1;
        }
        binary_value.bits [0] = binary_value.bits[0]+1;
        short carry = binary_value.bits[0]/2;
        binary_value.bits[0] %= 2;
        for(int i=1;i<binary_value.length-1;i++)
        {
            binary_value.bits[i] = binary_value.bits[i]+carry;
            carry = binary_value.bits[i]/2;
            binary_value.bits[i] %= 2;
        }
    }
    return cin;
}

void Binary::sign_extension(int to_len)
{
    if(to_len<=this->length)    return;
    short * origin = this->bits;
    this->bits = new short [to_len];
    for(int i=0;i<this->length;i++)
    {
        this->bits[i]=origin[i];
    }
    for(int i=this->length;i<to_len;i++)
    {
        this->bits[i]=this->bits[length-1];
    }
    delete origin;
    this->length = to_len;
}
void Binary::sign_shrink(int to_len)
{
    if(to_len>=this->length)    return;
    short * origin = this->bits;
    this->bits = new short[to_len];
    this->bits[to_len-1] = origin[this->length-1];
    for(int i=0;i<to_len-1;i++)
    {
        this->bits[i]=origin[i];
    }
    delete origin;
    this->length = to_len;
}
void Binary::shift_left(int dist)
{
    if(dist<1)  dist = 1;
    for(int i=length-2;i>=dist;i--)
    {
        bits[i] = bits[i-dist];
    }
    for(int i=0;i<dist;i++)
    {
        bits[i]=0;
    }
}
void Binary::shift_right(int dist)
{
    if(dist<1)  dist=1;
    for(int i=0;i<length-dist-1;i++)
    {
        bits[i]=bits[i+dist];
    }
    for(int i=length-dist-1;i<length;i++)
    {
        bits[i]=bits[length-1];
    }
}
    
void Binary::negative()
{
    for(int i=0;i<length;i++)
    {
        bits[i] = bits[i]?0:1;
    }
    bits[0] = bits[0]+1;
    short carry = bits[0]/2;
    bits[0] %= 2;
    for(int i=1;i<length-1;i++)
    {
        bits[i] = bits[i]+carry;
        carry = bits[i]/2;
        bits[i] %= 2;
    }
}

Binary operator +(Binary a, Binary b)
{
    int result_length = a.length>b.length?a.length:b.length;
    a.sign_extension(result_length);
    b.sign_extension(result_length);
    Binary result = Binary(0,result_length);
    short carry = 0;
    for(int i=0;i<result_length;i++)
    {
        result.bits[i] = carry + a.bits[i] + b.bits[i];
        carry = result.bits[i]/2;
        result.bits[i] = result.bits[i]%2;
    }
    return result;
}
Binary operator *(const Binary & a, const Binary & b)
{
    if(MANIPULATION_OPERATION==NORMAL_ALGORITHM)
    {
        //using the normal shifting and adding algorithm to calculate
        Binary copy_a = Binary(a);
        copy_a.sign_extension(a.length+b.length);
        Binary ret_val = Binary(0,a.length+b.length);
        for(int i=0;i<b.length-1;i++)
        {
            #ifdef DEBUG
                std::cout<<copy_a<<std::endl;
                #endif
            if(b.bits[i])
            {
                #ifdef DEBUG
                    std::cout<<"b.bits["<<i<<"] is 1 and the result should = "<<ret_val+copy_a;
                    #endif
                ret_val = ret_val + copy_a;
                #ifdef DEBUG
                    std::cout<<"\tthe current result = "<<ret_val<<std::endl;
                    #endif
            }
            copy_a.shift_left();
        }
        if(b.bits[b.length-1])
        {
            copy_a.shift_right(b.length-2);
            copy_a.negative();
            #ifdef DEBUG
                std::cout<<"Sign: Before shifting"<<copy_a<<std::endl;
                #endif
            copy_a.shift_left(b.length-2);
            #ifdef DEBUG
                std::cout<<"Sign: After shifting"<<copy_a<<std::endl;
                #endif
            ret_val = ret_val+copy_a;
        }
        ret_val.sign_shrink(a.length>b.length?a.length:b.length);
        return ret_val;
    }
    else if(MANIPULATION_OPERATION==BOOTH_ALGORITHM)
    {
        if(a.length>b.length)   return b*a;

        //a length <= b length
        Binary first_half = Binary(0,b.length);
        short * last_half = new short [b.length+1];

        for(int i=0;i<b.length;i++)     last_half[i]=b.bits[i];
        last_half[b.length] = 0;

        for(int i=0;i<b.length;i++)
        {
            if(last_half[0]==last_half[1]) //0-0 or 1-1: shift
            {
                for(int j=0;j<b.length-1;j++)   last_half[i]=last_half[i+1];
                last_half[b.length-1]=first_half.bits[0];
                first_half.shift_right();
            }
            else if(last_half[1]==1 && last_half[0]==0) //1-0: first_half-a, shift
            {
                Binary c = Binary(a);
                c.negative();
                first_half = first_half + c;

                for(int j=0;j<b.length-1;j++)   last_half[i]=last_half[i+1];
                last_half[b.length-1]=first_half.bits[0];
                first_half.shift_right();                
            }
            else //0-1: last_half+a, shift
            {
                first_half = first_half + a;

                for(int j=0;j<b.length-1;j++)   last_half[i]=last_half[i+1];
                last_half[b.length-1]=first_half.bits[0];
                first_half.shift_right();
            }
            std::cout<<"a: "<<first_half<<" q: ";
            for(int f=b.length-1;f>0;f--)  std::cout<<last_half[f];
            std::cout<<" q0: "<<last_half[0]<<std::endl;
        }
        first_half.sign_extension(2*b.length);
        first_half.shift_left(b.length);
        for(int k=0;k<b.length;k++)     first_half.bits[k]=last_half[k];
        delete last_half;
        return first_half;
    }
}
Binary operator /(const Binary & a, const Binary & b)
{
    std::cout<<"Integer division is not supported yet"<<std::endl;
}
void Binary::operator=(const Binary & a)
{
    this->bits[this->length-1] = a.bits[a.length-1];
    for(int i=0;i<this->length-1;i++)
    {
        this->bits[i] = a.bits[i];
    }
}