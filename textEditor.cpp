#include "textEditor.h"

template<class Type>
void show(const Type &elem){
    cout<<elem;
}

//�л�����һ��
int editor::NextLine(){
    if(textBuffer.Isempty()){
        cout<<"���棺�ı������"<<endl;
        return 0;
    }
    if(curLineNo<textBuffer.Length()){
        curLineNo++;
        cout<<"��ǰ�ڵ�"<<curLineNo<<"��"<<endl;
        return 1;
    }
    else return 0;
}
//ת��ǰһ��
int editor::PreviousLine(){
    if(textBuffer.Isempty()){
        cout<<"���棺�ı������"<<endl;
        return 0;
    }
    if(curLineNo>1){
        curLineNo--;
        cout<<"��ǰ�ڵ�"<<curLineNo<<"��"<<endl;
        return 1;
    }
    else return 0;
}
//ת��ָ����
int editor::GotoLine(){
    int gotonum;
    if(textBuffer.Isempty()) return 0;
    cout<<"��������Ҫ��ת������"<<endl;
    cin>>gotonum;
    if(gotonum>0&&gotonum<=textBuffer.Length()){
        curLineNo=gotonum;
        cout<<"��ǰ�ڵ�"<<curLineNo<<"��"<<endl;
        return 1;
    }
    else return 0;
    
}
//����һ��
int editor::InsertLine(){
    cout<<"��ǰ����"<<textBuffer.Length()<<"��"<<endl;
    cout<<"��������뵽�ڼ��к���:"<<endl;
    int row;
    cin>>row;
    if(row>=0&&row<=textBuffer.Length()){
        cout<<"����������е��ַ���:"<<endl;
        string instr;
        getline(cin,instr);
        textBuffer.InsertElem(instr,row+1);
        curLineNo=row+1;
        cout<<"����ɹ�"<<"��ǰ�ڵ�"<<curLineNo<<"��"<<endl;
        return 1;
    }
    else return 0;

}
//�滻��ǰ�л�������ָ���е�ָ���ı���
void editor::ChangeLine(){
    //�û�����ָ���ı������ڵ�ǰ�л���������������������ı����滻ָ���ı���
    char answer;//�û��ش��ַ�
    bool initialResponse;//��ʼ�ش�
    //ѭ��ֱ���û���������ַ�
    do{
        if(initialResponse){
            //��ʼ�ش�
            cout<<"�滻��ǰ��(c) ���� �滻������(a):";
        }
        else{
            //�ǳ�ʼ�ش�
            cout<<"������ c or a:";
        }

        cin>>answer;
        while(cin.get()!='\n');//�����û�����������ַ�
        if(answer>='A'&&answer<='Z'){
            answer+=32;
        }//��дת��
        initialResponse=false;
    }while(answer!='c'&&answer!='a');
    cout<<"������Ҫ���滻���ַ���:";
    string strOld;
    getline(cin,strOld);//����Ҫ�滻���ַ���
    cout<<"���������ַ���:";
    string strNew;
    getline(cin,strNew);

    for(int row=1;row<textBuffer.Length();row++){
        if(answer=='c'&&row!=curLineNo){
            //ֻ�滻��ǰ��
            continue;//��ʼ��һ��ѭ��
        }
        string strRow;//
        strRow=textBuffer.GetPostionElem(row);//ȡ����ǰ��
        if(strRow.find(strOld)!=strRow.npos){
            //ƥ��ɹ�
            string Newline;
            //Newline���ƥ�䴮֮ǰ��ȫ���ַ�
            Newline=strRow.substr(0,strRow.find(strOld)-1);
            Newline.append(strNew);
            //Newline����滻֮��������ַ�
            Newline.append(strRow.substr(strRow.find(strOld)+strOld.length()-1));
            textBuffer.SetElem(row,Newline);
        }
    }
}
//�����ı��ļ�
void editor::ReadFile(){
    cout<<"����������ı�����:"<<endl;
    char *in_file=new char[128];
    cin>>in_file;
    ifstream intofile;
    intofile.open(in_file,ios::in);
    if(!intofile){
        //�����ʧ��
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
//д���ı��ļ�
void editor::WriteFile(){
    cout<<"������Ҫд����ļ���:"<<endl;
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
//���Ҵ�
void editor::FindString(){
    //�ӵ�ǰ�л��ߵ�һ�п�ʼ����
    char answer;
    bool initialresponse=true;
    do{
        if(initialresponse){
            //��ʼ�ش�
            cout<<"�ӵ�һ�п�ʼ(first) or �ӵ�ǰ�п�ʼ(current):";
        }
        else{
            //�ǳ�ʼ�ش�
            cout<<"������ f or c :";
        }
        cin>>answer;
        while(cin.get()!='\n');//���Ժ��������ַ�
        if(answer>='A'&&answer<='Z'){
            answer+=32;
        }//��дת��
        initialresponse=false;
    }while(answer!='f'&&answer!='c');
    if(answer=='f') curLineNo=1;//����fʱ�ӵ�һ�п�ʼ
    bool flag=false;//���ڱ���Ƿ���ҵ�ָ����
    cout<<"��������Ҫ���ҵ��ַ���:";
    string strSearch;
    getline(cin,strSearch);//��ȡ�������ַ���
    string strRow=textBuffer.GetPostionElem(curLineNo);
    while(curLineNo<=textBuffer.Length()){
        if(strRow.find(strSearch)!=strRow.npos){
            flag=true;
            break;
        }
        else{
            curLineNo++;
            strRow=textBuffer.GetPostionElem(curLineNo);//��ȡ����һ��
        }
    }
    if(flag){
        //���ҳɹ�
        cout<<strRow<<endl;
        for(int i=0;i<strRow.find(strSearch);i++){
            cout<<" ";
        }
        for(int j=0;j<strSearch.length();j++){
            cout<<"^";
        }
    }
    else{
        //����ʧ��
        cout<<"��ѯʧ��!";
    }
    cout<<endl;
} 

void editor::Run(){
    char command;//�û�����
    do{
        string strTmp;//��ʱ��
        string curLine;//��ǰ��
        if(curLineNo!=0){
            //���ڵ�ǰ��
            curLine=textBuffer.GetPostionElem(curLineNo);//ȥȡ����ǰ��
            cout<<curLineNo<<":"<<curLine<<endl<<"?";//��ʾ��ǰ�м�?
        }
        else{
            //�����ڵ�ǰ��
            cout<<"�ļ������!"<<endl<<"?";
        }
        cin>>command;
        if(command>='A'&&command<='Z'){
            command+=32;
        }//��дת��
        while(cin.get()!='\n');//���������ַ�
        if(command!='u'&&command!='h'&&command!='?'&&command!='v'){
            //�洢������Ϣ
            textUndoBuffer=textBuffer;//�����Ļ���(����)
            curUndoLineNo=curLineNo;//�������к�
        }
        //���в�������
        switch(command){
            case 'b'://ת����һ��b(begin)
                if(textBuffer.Isempty()){
                    //�ı������
                    cout<<"���棺�ı�����գ�"<<endl;
                }
                else{
                    //�ǿ�ת����һ��
                    curLine=1;
                }
                break;

            case 'c'://�滻��ǰ�л���������
                if(textBuffer.Isempty()){
                    cout<<"���棺�ı�����գ�"<<endl;
                }
                else{
                    //�滻
                    ChangeLine();
                }
                break;
            
            case 'd'://ɾ����ǰ��(delete)
                if(textBuffer.DeleteElem(curLineNo,strTmp)==0){
                    cout<<"ɾ��ʧ�ܣ�"<<endl;
                }
                break;
            
            case 'e'://ת�����һ��e(end)
                if(textBuffer.Isempty()){
                    cout<<"���棺�ı�����գ�"<<endl;
                }
                else{
                    curLineNo=textBuffer.Length();
                }
                break;
            
            case 'f'://�ӵ�ǰ�л��ߵ�һ�в���ָ���ı�
                if(textBuffer.Isempty()){
                    cout<<"���棺�ı�����գ�"<<endl;
                }
                else{
                    //�ӵ�ǰ�л��߿�ʼ����
                    FindString();
                }
                break;

            case 'g'://ת��ָ����g(o)
                if(GotoLine()==0){
                    //��תʧ��
                    cout<<"��תʧ�ܣ�û��ָ����"<<endl;
                }
                break;

            case '?':
            case 'h':
                cout<<"��Ч���b(begin) c(change) d(del) e(end) "<<endl;
                cout<<"f(find) g(go) h(help) i(insert) n(next) p(prior) "<<endl;
                cout<<"q(quit) r(read) u(undo) v(view) w(write) "<<endl;
                break;
            
            case 'i':
                if(InsertLine()==0){
                    //����ʧ��
                    cout<<"���󣺲�����ʧ��"<<endl;
                }
                break;
            
            case 'n'://ת����һ��
                if(NextLine()==0){
                    cout<<"���棺��ǰ�������һ��"<<endl;
                }
                break;

            case 'p'://ת��ǰһ��p(previous)
                if(PreviousLine()==0){
                    //��תʧ��
                    cout<<"���棺��ǰ���ǵ�һ��"<<endl;
                }
                break;

            case 'q':break;

            case 'r'://���ı��ļ�
                ReadFile();
                break;
            
            case 'u'://�����ϴβ���
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
            
            case 'v'://��ʾ�ı�
                textBuffer.Traverse(show);
                break;
            
            case 'w'://д�뵽�ļ�
                if(textBuffer.Isempty()){
                    cout<<"���棺�ı������"<<endl;
                }
                else{
                    //д�������ı�������ļ�
                    WriteFile();
                }
                break;
            
            default: 
                cout<<"����h����?����ȡ����\n";
        }
    }while(command!='q');

}