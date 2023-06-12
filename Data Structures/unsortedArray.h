#ifndef unsortedArray_h
#define unsortedArray_h
#include <cstring>
#include <iostream>
using namespace std;

class slot{
	public:
		char *word;
		int sum;
		slot(){
			word=nullptr;
			sum=0;
		}
		slot(char* string,int s){
			word=new char[strlen(string)+1];
			strcpy(word,string);
			sum=s;
		}
		~slot(){
			if(word!=nullptr)
				delete[] word;
		}
		int length(){
			return strlen(word)+1;
		}
};

class unsortedArray
{
  protected:
	slot** arr;
  
  unsigned int indx;//index of the found word after performing linear searching.
  
  unsigned int arr_size; //holds the size of the array which gets doubled whenever it gets full
  unsigned int last_word;//holds the index of the last word in the array

  virtual bool wordExists(char *);//Looks for the word with linear search, returns true or false depending on if the word is found or not.

  bool firstWord;//I need this to control the value of last_word, basically if I dont use this, last_word's value might increase without getting a new word.
 

  public:
  unsortedArray();//initializes the pointers to null and some helpful variables to 0
  ~unsortedArray();//destroys the array
  void insert(char *);//Inserts the unique words in the array, if the given word already exists, nothing is inserted and only the sum array is updated
  bool search(char *, ostream &);//Looks for the word with linear search, shows the times the word has appeared(if it exists) plus the searching time
  bool delete_word(char *);//Deletes a specific word in the array and returns true, if the word isn't found returns false
  void reset();//Resets the array to an empty one (deletes everything and sets integers to 0 and pointers to NULL)

  
};

#endif