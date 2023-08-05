#include "Stack.h"

Stack::Stack(){
    size=10;
    pos=0;
    data=new int[size];
}
Stack::Stack(int num){
    size=num;
    pos=0;
    data=new int[size];
}
Stack::Stack(const Stack &other){
    size=other.size;
    pos=other.pos;
    data=new int[size];
    for(int i=0;i<size;i++)
        data[i]=other.data[i];
}
Stack::~Stack(){delete[] data;}
bool Stack::isEmpty(){return (pos==0);}
bool Stack::push(int num){
    if(pos==size)
        if(!more_memory(size+5))
            return false;
    data[pos++]=num;
    return true;
}
bool Stack::pop(int &num){
    if(pos==0)
        return false;
    pos--;
    num=data[pos];
    return true;
}
bool Stack::more_memory(int new_size){
    int *temp=new int[new_size];
    if(temp==nullptr)
        return false;
    for(int i=0;i<size;i++)
        temp[i]=data[i];
    delete[] data;
    data=temp;
    size=new_size;
    return true;
}