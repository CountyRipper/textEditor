#include <iostream>
#include <stdio.h>
#include <cstring>

class String{
    private:
        mutable char *strVal;
        int length;//串长
    public:
        String();
        virtual~String();//析构函数
        String(const String &copy);//复制构造函数
        String(const char* copy);//从c风格串转换的构造函数
        /*String(LinkList<char>&copy);//从线性表转换的构造函数*/
        int Length();//求长度
        bool IsEmpty();//是否为空串
        String &operator=(const String &copy);//重载=
        const char* CStr() const;//转化为C风格串
        char &String::operator[](int pos)const;//重载下标

};
