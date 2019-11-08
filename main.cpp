#include "textEditor.h"
#include "textEditor.cpp"
#include <iostream>
#include <string.h>


int main(int, char**) {
    cout<<"**********************************"<<endl;
    cout<<"          欢迎使用文本编辑器          "<<endl;
    cout<<"功能表:"<<endl;
    cout<<"R:读取文本文件到缓冲区，缓冲区内容将丢失"<<endl;
    cout<<"W:将缓冲区内容写入文本，当前缓冲区不变"<<endl;
    cout<<"D:删除当前行"<<endl;
    cout<<"F:查找，可以从第一行或者指定行开始查找"<<endl;
    cout<<"C:替换文本，将用户请求的字符串修改为指定值"<<endl;
    cout<<"Q:退出编辑器"<<endl;
    cout<<"H:显示所有命令行消息，?也接受"<<endl;
    cout<<"N:当前行移动到下一行"<<endl;
    cout<<"P:当前行移动到上一行"<<endl;
    cout<<"B:当前行移动到开始位置"<<endl;
    cout<<"E:当前行移动到结束位置，缓冲区最后一行"<<endl;
    cout<<"G:当前行移动到缓冲区中用户指定的行"<<endl;
    cout<<"V:查看缓冲区所有内容"<<endl;
    cout<<"输入文件名(默认:file_in.txt):"<<endl;
    char infilename[128];
    char c1;
    int n1=0;
    while((c1=getchar())!='\n'){
        infilename[n1++]=c1;
    }
    if(n1==0){
        strcpy(infilename,string("file_in.txt").c_str());
    }
    cout<<"输出文件名(默认:file_out.txt):"<<endl;
    char outfilename[128];   
    char c2;
    int n2=0;
    while((c2=getchar())!='\n'){
        outfilename[n2++]=c2;
    }
    if(n2==0){
        strcpy(outfilename,string("file_out.txt").c_str());
    }
    editor E1(infilename,outfilename);
    E1.Run();
    return 0;
}
