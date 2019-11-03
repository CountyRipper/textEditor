#ifndef _LINEAR_H_
#define _LINEAR_H_

template<class Type>
struct Node
{
    Type data;
    Node<Type>* prev;//指向前一个结点的指针
    Node<Type>* next;//指向下一个结点的指针
    Node(){}
    Node(Type Elem,Node<Type>* p1=nullptr,Node<Type>*n1=nullptr):data(Elem),prev(p1),next(n1){}
};

template<class Type>
class lineEditor
{
private:
    Node<Type>* head;
    void init(){
        head->data=nullptr;
        head->prev=nullptr;
        head->next=nullptr;
    }
public:
    lineEditor();
    int Clean();
    bool IsEmpty();
    int Length();
    void Traverse(void(*visit)(const Type &));
    Type GetPositionPtr(int position=0);
    Type GetPositionElem(int position=1);
    int InsertElem(const Type &Elem,int position);
    int DeletElem(int position=1);
    virtual ~lineEditor();
};

template<class Type>
lineEditor<Type>::lineEditor(){
    init();
}
template<class Type>
lineEditor<Type>::~lineEditor(){
    Clean();
}

#endif