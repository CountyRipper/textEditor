#ifndef _LINKLIST_H_

#define _LINKLIST_H_
#include <stddef.h>


template<class Type>
struct Node
{
    Type data; //数据域
    Node<Type> *back;//前驱指针域
    Node<Type> *next; //后继指针域

    Node(){
        next=NULL;
    } //构造函数模板
    Node(Type item,Node<Type>*linkback = NULL,Node<Type>*linknext=NULL){
        next=linknext;
        back=linkback;
        data=item;
    } //已知一个数据，或者指针也知道，新建一个结点
};

template<class Type>
class linklist{
    protected:
        Node<Type>* head;
        mutable int curposition;//当前位置
        mutable Node<Type>* curPtr;//指向当前位置指针
        int count;//元素个数
        void init(){
            head = new Node<Type>;//构造头指针
            head->next=head;//头节点初始化为循环链表
            curPtr=head; curposition=0;//初始化当前指针指向头节点
            count=0;//初始化元素个数
        }
        //辅助函数，返回指向第position个结点的指针
        Node<Type>* GetPositionPtr(int position){
            if(curposition<position){
                //当前位置在查找位置之前，向后查找
                for(;curposition<position;curposition++){
                    curPtr=curPtr->next;
                }
            }
            else if(curposition>position){
                //当前位置在查找位置之后
                while(curposition>position){
                    curPtr=curPtr->back;
                    curposition--;
                }
            }
            //curposition=position;
            //position=curposition
            return curPtr;
        }
    public:
        linklist();//无参构造函数
        virtual ~linklist();//析构函数
        bool Isempty();//判断是否为空
        int Length();//返回线性表长度
        void Clear();//清空线性表
        void Traverse(void(*visit)(const Type &));//遍历线性表
        Type GetPostionElem(int position);//获得指定位置的元素值
        int InsertElem(const Type &Elem,int position);//插入指定元素到指定为位置
        int DeleteElem(int position,Type &Elem);//删除指定位置元素
        int DeleteElem();//直接删除队尾元素
        int SetElem(int position,const Type &Elem);//设置指定位置元素
        linklist(linklist<Type>&copy);//复制构造函数模板
        linklist<Type>& operator =(linklist<Type>&copy){
            
            for(int i=1;i<=copy.count;i++){
                this->InsertElem(copy.GetPostionElem(i),i);
            }
            
        }            
         //重载=
};

#endif