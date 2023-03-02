#include "hashTable.h"
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

hashTable::hashTable()
{
	arr=nullptr;
}


hashTable::~hashTable()
{
	reset();
	delete arr;
}


unsigned long hashTable::hash(char * key)
{
  //The next lines of code convert the char value of the key to an integer value
  //for example, the word "hey" will be converted to integer value like:
  // 10^2 * "h" + 10 * "e" + "y"
  unsigned long long sum=0;
  length = strlen(key);
  for(unsigned long i=0; i<length; i++)
  {
    sum+=pow(10,length-(i+1))*key[i];
  }

  return sum%arrSize;
}



unsigned long hashTable::hash2(unsigned int key)
{
  return (key+1)%arrSize;
}


bool hashTable::insert (char * key)
{
  //initializing the hash table
	if(arr==nullptr){
		arrSize=10;
		usedBuckets=0;
		arr= new Pair *[arrSize];
		for(unsigned long i=0; i<arrSize; i++)
			arr[i]=nullptr;
	}

  //if the hash table's full buckets use 50% of its size or more , we double the table's size
  if(usedBuckets==arrSize/2)
  {
    Pair **temp;
    arrSize*=2;
    temp = new Pair*[arrSize];
    //creating a temporary array
    for(unsigned long i=0;i<arrSize;i++)
      temp[i]=nullptr;

    for (unsigned long i=0;i<arrSize/2;i++)
    {
      //the bucket i is not empty
      if (arr[i]!=nullptr)
      {
        unsigned long p = hash(arr[i]->key);
        while (temp[p]!=nullptr)
          p = hash2(p);

        //putting i bucket's contents to the temporary array  
        temp[p]=arr[i];

        arr[i]=nullptr;
      }        
    }
    delete[]arr;

    //the hash table's pointer arr is pointing to the new, bigger array we just created
    arr=temp;
  }
  //searching for the word in the hash table
	if(search(key)!=nullptr)
    arr[indx]->value++;//the word exists, so the value (instances) increases
	else{
		arr[indx]=new  Pair(1,key);//the word doesn't exist, the value is initialized to 1.
		usedBuckets++;
	}
  return true;
}



Pair *&hashTable::search(char * key)
{
  indx = hash(key);
  while ((arr[indx]!=nullptr && strcmp(arr[indx]->key,key)))//empty bucket not found and the found bucket's key is not equal the given word's key.
    indx = hash2(indx);
  return arr[indx];//found the correct bucket
}




bool hashTable::search(char* key, ostream &o)
{
	if(arr==nullptr)
		return false;//arr not pointing to anything

	Pair *p = search(key);
	if (p==nullptr)
    	return false;//word not found

	o<<">>\""<<p->key<<"\" found "<<p->value<<" times"<<endl;
 	return true;
}


void hashTable::reset(){
	if(arr!=nullptr){
		for(unsigned long i=0;i<arrSize;i++)
			delete arr[i];
		delete [] arr;
		arr=nullptr;
	}
}