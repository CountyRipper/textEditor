#include "textEditor.h"

template<class Type>
void show(const Type &elem){
    cout<<elem;
}

//切换到下一行
int editor::NextLine(){
    if(textBuffer.Isempty()){
        cout<<"警告：文本缓存空"<<endl;
        return 0;
    }
    if(curLineNo<textBuffer.Length()){
        curLineNo++;
        cout<<"当前在第"<<curLineNo<<"行"<<endl;
        return 1;
    }
    else return 0;
}
//转到前一行
int editor::PreviousLine(){
    if(textBuffer.Isempty()){
        cout<<"警告：文本缓存空"<<endl;
        return 0;
    }
    if(curLineNo>1){
        curLineNo--;
        cout<<"当前在第"<<curLineNo<<"行"<<endl;
        return 1;
    }
    else return 0;
}
//转到指定行
int editor::GotoLine(){
    int gotonum;
    if(textBuffer.Isempty()) return 0;
    cout<<"请输入需要跳转的行数"<<endl;
    cin>>gotonum;
    if(gotonum>0&&gotonum<=textBuffer.Length()){
        curLineNo=gotonum;
        cout<<"当前在第"<<curLineNo<<"行"<<endl;
        return 1;
    }
    else return 0;
    
}
//插入一行
int editor::InsertLine(){
    cout<<"当前共有"<<textBuffer.Length()<<"行"<<endl;
    cout<<"请输入插入到第几行后面:"<<endl;
    int row;
    cin>>row;
    if(row>=0&&row<=textBuffer.Length()){
        cout<<"请输入插入行的字符串:"<<endl;
        string instr;
        getline(cin,instr);
        textBuffer.InsertElem(instr,row+1);
        curLineNo=row+1;
        cout<<"插入成功"<<"当前在第"<<curLineNo<<"行"<<endl;
        return 1;
    }
    else return 0;

}
//替换当前行或者所有指定行的指定文本串
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
//读入文本文件
void editor::ReadFile(){
    cout<<"请输入读入文本名称:"<<endl;
    char *in_file=new char[128];
    cin>>in_file;
    ifstream intofile;
    intofile.open(in_file,ios::in);
    if(!intofile){
        //如果打开失败
        return;
    }
    string str1;
    textBuffer.Clear();
    curLineNo=0;
    while(getline(intofile,str1)){
        textBuffer.InsertElem(str1,curLineNo++);
        cout<<curLineNo<<":"<<str1<<endl;
    }
}
//写入文本文件
void editor::WriteFile(){
    cout<<"请输入要写入的文件名:"<<endl;
    char *out_file=new char[128];
    cin>>out_file;
    ofstream outtofile;
    outtofile.open(out_file,ios::out);
    int num=1;
    string str1;
    while(num<=textBuffer.Length()){
        str1=textBuffer.GetPostionElem(num++);
        outtofile<<str1<<endl;
    }
}
//查找串
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
                    curLineNo=textBuffer.Length();
                }
                break;
            
            case 'f'://从当前行或者第一行查找指定文本
                if(textBuffer.Isempty()){
                    cout<<"警告：文本缓存空！"<<endl;
                }
                else{
                    //从当前行或者开始查找
                    FindString();
                }
                break;

            case 'g'://转到指定行g(o)
                if(GotoLine()==0){
                    //跳转失败
                    cout<<"跳转失败，没有指定行"<<endl;
                }
                break;

            case '?':
            case 'h':
                cout<<"有效命令：b(begin) c(change) d(del) e(end) "<<endl;
                cout<<"f(find) g(go) h(help) i(insert) n(next) p(prior) "<<endl;
                cout<<"q(quit) r(read) u(undo) v(view) w(write) "<<endl;
                break;
            
            case 'i':
                if(InsertLine()==0){
                    //插入失败
                    cout<<"错误：插入行失败"<<endl;
                }
                break;
            
            case 'n'://转到下一行
                if(NextLine()==0){
                    cout<<"警告：当前已是最后一行"<<endl;
                }
                break;

            case 'p'://转到前一行p(previous)
                if(PreviousLine()==0){
                    //跳转失败
                    cout<<"警告：当前已是第一行"<<endl;
                }
                break;

            case 'q':break;

            case 'r'://读文本文件
                ReadFile();
                break;
            
            case 'u'://撤销上次操作
                {
                linklist<string> tmpBuffer;
                tmpBuffer=textBuffer;
                int tmpcurLineNo=curLineNo;
                textBuffer=textUndoBuffer;
                curLineNo=curUndoLineNo;
                textUndoBuffer=tmpBuffer;
                curUndoLineNo=tmpcurLineNo;
                break;
                }
            
            case 'v'://显示文本
                textBuffer.Traverse(show);
                break;
            
            case 'w'://写入到文件
                if(textBuffer.Isempty()){
                    cout<<"警告：文本缓存空"<<endl;
                }
                else{
                    //写缓存区文本到输出文件
                    WriteFile();
                }
                break;
            
            default: 
                cout<<"输入h或者?来获取帮助\n";
        }
    }while(command!='q');

}