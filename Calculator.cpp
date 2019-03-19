//main function here
#include "Binary.h"
using namespace std;

int main()
{
    int a_val   = 0;
    int b_val   = 0;
    int a_len   = 0;
    int b_len   = 0;
    cout<<"Enter the length and value of a and b respectively.\nLength of a: ";
    cin>>a_len;
    cout<<"Value of a: ";
    cin>>a_val;
    cout<<"Length of b: ";
    cin>>b_len;
    cout<<"Value of b: ";
    cin>>b_val;

    Binary a = Binary(a_val,a_len>0?a_len:8);
    Binary b = Binary(b_val,b_len>0?b_len:8);

    cout<<a<<endl<<b<<endl;
    cout<<"Enter the operation: a_?_b ";
    char oper;
    cin>>oper;
    if(oper=='+')
    {
        cout<<"a+b=\n\t"<<a+b<<endl;
    }
    else if(oper=='-')
    {
        b.negative();
        cout<<"a-b=\n\t"<<a+b<<endl;
        b.negative();
    }
    else if(oper=='*')
    {
        cout<<"a*b=\n\t"<<a*b<<endl;
    }
    else if(oper=='/')
    {
        cout<<"a/b=\n\t"<<a/b<<endl;
    }
    else
    {
        cout<<"Wrong Operator"<<endl;
    }
    return 0;
}
