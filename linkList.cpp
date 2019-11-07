#include "linkList.h"

template<class Type>
linklist<Type>::linklist(){
    init();
}

template<class Type>
bool linklist<Type>::Isempty(){
    if(count==0)
        return true;
    else return false;
}

template<class Type>
int linklist<Type>::Length(){
    return count;
}

template<class Type>
void linklist<Type>::Clear(){
    while(head->next!=head){
        Type a1;
        DeleteElem(count,a1);//如果头结点next指针不为head，就继续删除
    }
}

template<class Type>
void linklist<Type>::Traverse(void(*visit)(const Type&)){
    Node<Type>* cur=head->next;
    while(cur!=NULL&&cur!=head){
        (*visit)(cur->data);//对每个元素调用*visit
        cur=cur->next;
    }
}

template<class Type>
Type linklist<Type>::GetPostionElem(int position){
    Node<Type>* get;
    get=GetPositionPtr(position);
    return get->data;
}

//插入到当前序号的下一个，如果是0就在头节点后面直接插入
template<class Type>
int linklist<Type>::InsertElem(const Type &Elem,int position){
    if(position<1||position>Length()+1){
        return 0;
    }
    else{
        Node<Type>*tmpPtr,*nextPtr,*newPtr;
        tmpPtr=GetPositionPtr(position-1);
        nextPtr=tmpPtr->next;
        newPtr=new Node<Type>(Elem,tmpPtr,nextPtr);//生成新节点
        tmpPtr->next=newPtr;
        nextPtr->back=newPtr;
        curposition=position;
        curPtr=newPtr;
        count++;
        return 1;
    }
}

template<class Type>
int linklist<Type>::DeleteElem(int position,Type &Elem){
    if(!Isempty()){
        if(position>0&&position<=Length()){
            Node<Type>* tmpPtr=GetPositionPtr(position-1);//去取出指向position的指针
            tmpPtr->back->next=tmpPtr->next;//前一个指针的后继修改
            tmpPtr->next->back=tmpPtr->back;//后一个指针的前驱修改
            Elem=tmpPtr->data;//用Elem来返回删除的元素
            if(position==Length()){
                //删除尾节点,当前节点变为头节点
                curposition=0;
                curPtr=head;
            }
            else{
                curposition=position;//设置当前位序号
                curPtr=tmpPtr->next;//设置当前位置指向的指针
            }
            count--;
            delete tmpPtr;
        }
        return 1;
    }
    else return 0;
}
/*
template<class Type>
int linklist<Type>::DeleteElem(){
    if(!Isempty()){
        Node<Type>* cur=head;
        for(int i=0;i<Length();i++){
            cur=cur->next;
        }
        delete cur;
        return 1;
    }
    return 0;
}
*/

template<class Type>
int linklist<Type>::SetElem(int position, const Type &Elem){
    if(Isempty()) return 0;
    Node<Type>* cur=GetPositionPtr(position);
    cur->data=Elem;
    return 1;
}

template<class Type>
linklist<Type>::~linklist(){
    Clear();
    delete head;
}

template<class Type>
linklist<Type>::linklist(linklist<Type>&copy){
    linklist<Type> tmplist;
    tmplist.count=copy.count;
    for(int i=1;i<=count;i++){
        tmplist.InsertElem(copy.GetPostionElem(i),i);
    }
    tmplist.curposition=copy.curposition;
}
/*
template<class Type>
linklist<Type> operator=(const linklist<Type>&copy){
}*/

