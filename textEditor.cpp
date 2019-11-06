#include "textEditor.h"

void editor::ChangeLine(){
    //用户输入指定文本串，在当前行或者所有行中用输入的新文本串替换指定文本串
    char answer;//用户回答字符
    bool initialResponse;//初始回答
    //循环直到用户输入合理字符
    do{
        if(initialResponse){
            //初始回答
            cout<<"change current line (c) or repalce all lines (a):";
        }
        else{
            //非初始回答
            cout<<"please input c or a:";
        }

        cin>>answer;
        while(cin.get()!='\n');//忽略用户输入的其他字符
        if(answer>='A'&&answer<='Z'){
            answer+=32;
        }//大写转换
        initialResponse=false;
    }while(answer!='c'&&answer!='a');
    cout<<"please input the replacede string:";
}