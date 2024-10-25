#include<iostream>
#include<string>

using namespace std;

//方法2


//方法1
string intToRoman(int num) {
    string ans;
    while(num >= 900)
    {
        if(num >= 1000)
        {
            num -= 1000;
            ans += "M";
        }
        else
        {
            num -= 900;
            ans += "CM";
        }
    }
    while(num >= 400)
    {
        if(num >= 500)
        {
            num -= 500;
            ans += "D";
        }
        else
        {
            num -= 400;
            ans += "CD";
        }
    }
    while(num >= 90)
    {
        if(num >= 100)
        {
            num -= 100;
            ans += "C";
        }
        else
        {
            num -= 90;
            ans += "XC";
        }
    }
    while(num >= 40)
    {
        if(num >= 50)
        {
            num -= 50;
            ans += "L";
        }
        else
        {
            num -= 40;
            ans += "XL";
        }
    }
    while(num >= 9)
    {
        if(num >= 10)
        {
            num -= 10;
            ans += "X";
        }
        else
        {
            num -= 9;
            ans += "IX";
        }
    }
    while(num >= 4)
    {
        if(num >= 5)
        {
            num -= 5;
            ans += "V";
        }
        else
        {
            num -= 4;
            ans += "IV";
        }
    }
    while(num >= 1)
    {

        num -= 1;
        ans += "I";
    }
    return ans;
}

int main()
{
    int num = 58;
    cout << intToRoman(num) << endl;
    return 0;
}