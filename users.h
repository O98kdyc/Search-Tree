#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <math.h>
using  std::ostream;
using  std::istream;

class user
{
    friend ostream &operator<<(ostream &os,const user &obj);
    friend istream &operator>>(istream &in,user &obj);
    friend bool operator == (const user &obj1,const user &obj2);
    //friend user operator = (const user &obj2);

private:
    char mes1[15];
    char mes2[10];
    int num1;
    int num2;
};

istream& operator>>(istream &in,user &obj)
{
    in>>obj.mes1>>obj.mes2>>obj.num1>>obj.num2;
    return in;
}

ostream& operator<<(ostream &os,const user& obj)
{
    os<<obj.mes1<<" "<<obj.mes2<<" "<<obj.num1<<" "<<obj.num2<<'\n';
    return os;
}

bool operator==(const user &r1, const user &r2)
{
    return r1.mes1==r2.mes1 && r1.mes2==r2.mes2 && r1.num1==r2.num1 && r1.num2==r2.num2;
}

#endif // USER_H_INCLUDED

