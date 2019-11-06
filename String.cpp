#include "String.h"

//串操作
String Read(std::istream &input);//从输入流中读入串
String Read(std::istream &input,char &terminalChar);//用terminalChar返回结束串字符
void Write(String &s);
void Concat(String &addTo,const String &addOn);//将串addOn接到addTo后面
void Copy(String &copy,const String &original);
void Copy(String &copy,const String &original,int num);//复制num个字符到copy里面
int Index(const String &target,const String &pattern,int pos=0);//查找模式串第一次出现在target串中的位置

String::String(const char*inString){
    
}


String::String(const String &copy){
    length=strlen(copy.CStr());
}
