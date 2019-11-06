#ifndef _TEXTEDITOR_H_
#define _TEXTEDITOR_H_
#include "linkList.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class editor{
private:
    linklist<string> textBuffer;//文本缓存
    int curLineNo;//当前行号
    linklist<string> textUndoBuffer;//用于恢复文本的缓存
    int curUndoLineNo;//用于恢复的当前行号
    ifstream inFile;//输入文件
    ofstream outFile;//输出文件
    //辅助函数
    int NextLine();//切换到下一行
    int PreviousLine();//转到前一行
    int GotoLine(int linenum);//转到指定行
    int InsertLine(string tmpline);//插入一行
    void ChangeLine();//替换当前行或者所有指定行的指定文本串
    void ReadFile();//读入文本文件
    void WriteFile();//写入文本文件
    void FindString();//查找串
    
public:
    editor(char inFName[],char outfName[]);//构造函数
    void Run();//运行文本编辑器
};

#endif