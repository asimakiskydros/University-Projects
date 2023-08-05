#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>
using namespace std;

template <typename mytype> class PriorityQueue{
	private:
		mytype *data;
		int size,maxsize;
	public:
		PriorityQueue(){
			data=new mytype[10];
			size=0;
			maxsize=10;
		}
		~PriorityQueue(){
			delete [] data;
		}
		void enQueue(mytype obj){
			if(this->size==this->maxsize){
				cout<<"Not enough space. Requesting more..."<<endl;
				try{
					mytype *temp=new mytype[maxsize+5];
					cout<<"Space found. Moving data..."<<endl;
					for(int i=0;i<size;i++)
						temp[i]=this->data[i];
					delete [] this->data;
					this->data=temp;
					this->maxsize+=5;
				} catch(std::bad_alloc&){
					cout<<"Space not found. Stopping."<<endl;
					return;
				}
			}
			bool flag=false;
			for(int i=0;i<this->size+1 && !flag;i++)
				if(obj>this->data[i]){
					flag=true;
					for(int j=this->size-1;j>=i;j--)
						this->data[j+1]=this->data[j];
					this->data[i]=obj;
				}
			this->size++;
		}
		void deQueue(mytype obj){
			if(this->size==0){
				cout<<"Array empty...."<<endl;
				return;
			}
			for(int i=0;i<this->size;i++)
				this->data[i]=this->data[i+1];
			this->size--;
			if(this->maxsize-this->size>=5){
				cout<<"Too much available space. Deleting extra memory..."<<endl;
				try{
					mytype *temp=new mytype[this->maxsize-5];
					for(int i=0;i<this->size;i++)
						temp[i]=this->data[i];
					delete [] this->data;
					this->data=temp;
					this->maxsize-=5;
					cout<<"Extra space deleted."<<endl;
				}catch(std::bad_alloc&){
					cout<<"Could not delete extra space."<<endl;
					return;
				}
			}
		}
		void show(){
			cout<<"--------------"<<endl<<"Size = "<<this->size<<endl<<"maxSize = "<<this->maxsize<<endl;
			for (int i=0;i<this->size;i++)
				cout<<this->data[i]<<endl;
			cout<<"--------------"<<endl;
		}
};

#endif //PRIORITYQUEUE_H