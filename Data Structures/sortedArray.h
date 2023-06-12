#ifndef sortedarr_h
#define sortedarr_h
#include <iostream>
#include <cstring>
using namespace std;

class slots{
	public:
		char *word;
		int sum;
		slots(){
			word=nullptr;
			sum=0;
		}
		slots(char* string,int s){
			word=new char[strlen(string)+1];
			strcpy(word,string);
			sum=s;
		}
		~slots(){
			if(word!=nullptr)
				delete[] word;
		}
		int length(){
			return strlen(word)+1;
		}
};

class sortedArray
{
  private:
	slots** arr;

  unsigned int arr_size; //holds the size of the array which gets doubled whenever it gets full
  unsigned int last_word;//holds the index of the last word in the array

  bool wordExists(char *, int, int);//Looks for the word with binary search, returns true or false depending on if the word is found or not.
  unsigned int indx;//index of the found word after performing binary searching.

  public:
  sortedArray();//initializes the pointers to null and variables to 0
  ~sortedArray();//destroys the array
  void reset();//Resets the array to an empty one (deletes everything and sets integers to 0 and pointers to nullptr)

  void insert(char *);//Inserts the unique words in the array while the array is getting sorted. If the given word already exists, nothing is inserted and only the sum array is updated
  bool search(char *,ostream &);//Looks for the word with binary search, shows the times the word has appeared(if it exists) plus the searching time
  bool delete_word(char *);//Deletes a specific word in the array, sorts the array and returns true. If the total number of that word is bigger than 1, we update the sum array by doing: sum[index of the word]--. If the word isn't found returns false
  void printToStdOut();//Pretty self explanatory, order-testing is its only value

};

#endif