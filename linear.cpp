#include "linear.h"

template<class Type>
int lineEditor<Type>::Clean(){
    while(head->next!=nullptr){
        DeletElem();
    }
    delete head;
}

template<class Type>
bool lineEditor<Type>::IsEmpty(){
    if(head->next==nullptr)
        return true;
    else return false;
}

template<class Type>
int lineEditor<Type>::Length(){
    int count=0;
    Node<Type>* cur=head;
    while(cur->next!=nullptr){
        cur=cur->next;
        count++;
    }
    return count;
}

template<class Type>
void lineEditor<Type>::Traverse(void(*visit)(const Type &)){
    if(!IsEmpty()){
        Node<Type>* cur=head->next;
        while(cur!=nullptr){
            visit(cur->data);
            cur=cur->next
        }
    }
}

template<class Type>
Type lineEditor<Type>::GetPositionPtr(int position=0){
    if(position<0||position>Length()) return nullptr;
    Node<Type>* Ptr=head;
    for(int i=0;i<position;i++){
        Ptr=Ptr->next;
    }
    return Ptr;
}

template<class Type>
Type lineEditor<Type>::GetPositionElem(int position=1){
    if(IsEmpty()) return nullptr;
    if(position<=0||position>Length()) return nullptr;
    if(position>0&&position<=Length()){
        Node<Type>*Ptr=GetPositionPtr(position);
        return Ptr->data;
    }
    else return nullptr;
}