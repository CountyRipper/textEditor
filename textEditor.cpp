#include "textEditor.h"

void editor::ChangeLine(){
    //用户输入指定文本串，在当前行或者所有行中用输入的新文本串替换指定文本串
    char answer;//用户回答字符
    bool initialResponse;//初始回答
    //循环直到用户输入合理字符
    do{
        if(initialResponse){
            //初始回答
            cout<<"替换当前行(c) 或者 替换所有行(a):";
        }
        else{
            //非初始回答
            cout<<"请输入 c or a:";
        }

        cin>>answer;
        while(cin.get()!='\n');//忽略用户输入的其他字符
        if(answer>='A'&&answer<='Z'){
            answer+=32;
        }//大写转换
        initialResponse=false;
    }while(answer!='c'&&answer!='a');
    cout<<"请输入要被替换的字符串:";
    string strOld;
    getline(cin,strOld);//输入要替换的字符串
    cout<<"请输入新字符串:";
    string strNew;
    getline(cin,strNew);

    for(int row=1;row<textBuffer.Length();row++){
        if(answer=='c'&&row!=curLineNo){
            //只替换当前行
            continue;//开始下一次循环
        }
        string strRow;//
        strRow=textBuffer.GetPostionElem(row);//取出当前行
        if(strRow.find(strOld)!=strRow.npos){
            //匹配成功
            string Newline;
            //Newline获得匹配串之前的全部字符
            Newline=strRow.substr(0,strRow.find(strOld)-1);
            Newline.append(strNew);
            //Newline活得替换之后的所有字符
            Newline.append(strRow.substr(strRow.find(strOld)+strOld.length()-1));
            textBuffer.SetElem(row,Newline);
        }
    }
}

void editor::FindString(){
    //从当前行或者第一行开始查找
    char answer;
    bool initialresponse=true;
    do{
        if(initialresponse){
            //初始回答
            cout<<"从第一行开始(first) or 从当前行开始(current):";
        }
        else{
            //非初始回答
            cout<<"请输入 f or c :";
        }
        cin>>answer;
        while(cin.get()!='\n');//忽略后面多余的字符
        if(answer>='A'&&answer<='Z'){
            answer+=32;
        }//大写转换
        initialresponse=false;
    }while(answer!='f'&&answer!='c');
    if(answer=='f') curLineNo=1;//输入f时从第一行开始
    bool flag=false;//用于标记是否查找到指定串
    cout<<"请输入需要查找的字符串:";
    string strSearch;
    getline(cin,strSearch);//获取搜索的字符串
    string strRow=textBuffer.GetPostionElem(curLineNo);
    while(curLineNo<=textBuffer.Length()){
        if(strRow.find(strSearch)!=strRow.npos){
            flag=true;
            break;
        }
        else{
            curLineNo++;
            strRow=textBuffer.GetPostionElem(curLineNo);//再取出下一行
        }
    }
    if(flag){
        //查找成功
        cout<<strRow<<endl;
        for(int i=0;i<strRow.find(strSearch);i++){
            cout<<" ";
        }
        for(int j=0;j<strSearch.length();j++){
            cout<<"^";
        }
    }
    else{
        //查找失败
        cout<<"查询失败!";
    }
    cout<<endl;
} 

void editor::Run(){
    char command;//用户命令
    do{
        string strTmp;//临时串
        string curLine;//当前行
        if(curLineNo!=0){
            //存在当前行
            curLine=textBuffer.GetPostionElem(curLineNo);//去取出当前行
            cout<<curLineNo<<":"<<curLine<<endl<<"?";//显示当前行及?
        }
        else{
            //不存在当前行
            cout<<"文件缓存空!"<<endl<<"?";
        }
        cin>>command;
        if(command>='A'&&command<='Z'){
            command+=32;
        }//大写转换
        while(cin.get()!='\n');//忽略其他字符
        if(command!='u'&&command!='h'&&command!='?'&&command!='v'){
            //存储撤销信息
            textUndoBuffer=textBuffer;//撤销的缓存(整体)
            curUndoLineNo=curLineNo;//撤销的行号
        }
        //运行操作命令
        switch(command){
            case 'b'://转到第一行b(begin)
                if(textBuffer.Isempty()){
                    //文本缓存空
                    cout<<"警告：文本缓存空！"<<endl;
                }
                else{
                    //非空转到第一行
                    curLine=1;
                }
                break;

            case 'c'://替换当前行或者所有行
                if(textBuffer.Isempty()){
                    cout<<"警告：文本缓存空！"<<endl;
                }
                else{
                    //替换
                    ChangeLine();
                }
                break;
            
            case 'd'://删除当前行(delete)
                if(textBuffer.DeleteElem(curLineNo,strTmp)==0){
                    cout<<"删除失败！"<<endl;
                }
                break;
            
            case 'e'://转到最后一行e(end)
                if(textBuffer.Isempty()){
                    cout<<"警告：文本缓存空！"<<endl;
                }
                else{
                    
                }
        }
    }

}