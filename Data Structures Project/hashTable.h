#ifndef hashTable_h
#define hashTable_h
#include <cstring>
#include <iostream>
using namespace std;

class Pair
{
  public:
    int value;//the number of times a word has appeared, acts as the data
    char* key;//the word that will be given, acts as the key
    Pair(int d, char* k)//The pair of key and data that will be used
    {
      value=d;
      key=new char[strlen(k)+1];
	    strcpy(key,k);
    }
	~Pair(){
		if(key!=nullptr)
			delete []key;
	}
};


class hashTable
{
  private:
    unsigned long arrSize; //the size of the hash table
    unsigned long usedBuckets; //the number of the non-empty buckets in the hash table
    Pair **arr;//the hash table
    Pair *& search(char *); //will be used to search the given word and to find the correct buckets
    unsigned long hash(char *);//hash function
    unsigned long hash2(unsigned int);//hash2 function

    unsigned long length;//length of the given word

    unsigned long indx; //index of the value of the pair class
  public:
    hashTable();//initializes variables and the hash table
    ~hashTable();
    void reset();
    bool insert(char *); //inserts the words in the hash table
    bool search(char* ,ostream &); //looks for the given word by calling the private search function
};

#endif