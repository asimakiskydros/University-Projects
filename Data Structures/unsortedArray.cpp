#include "unsortedArray.h"
#include <iostream>
#include <cstring>
using namespace std;

unsortedArray::unsortedArray()
{
  //initializing integers to 0 and pointers to nullptr
  last_word=0;
  arr=nullptr;
}


void unsortedArray::reset()
{
	if(arr!=nullptr){
		for(int i=0;i<arr_size;i++)
			delete arr[i];
		delete [] arr;
		arr=nullptr;
		last_word=0;
		arr_size=0;
		indx=0;
	}
}

unsortedArray::~unsortedArray()
{
  reset();
  delete arr;
}


void unsortedArray::insert(char* string)
{
  if(arr==nullptr)//Basically this block of code runs only on the FIRST word given and allocates memory for the array.
  {
    arr_size=10;
    arr=new slot*[arr_size];
	for(int i=0;i<10;i++)
		arr[i]=nullptr;
  }
  if(!wordExists(string))//If the word does not exist in the array, we store it in the array.
  {
    
    if(last_word==arr_size)//If the array is full its size should get doubled
    {
      arr_size*=2;

      //Creating temporary pointer that point to the new, bigger array.  
      slot **tempArr=new slot*[arr_size];
      
      //Copying the old array's contents to the new arrays.
      for(unsigned int i=0; i<last_word; i++)
      {
        tempArr[i]=new slot(arr[i]->word,arr[i]->sum);

      }
	  //The rest of the slots must be initialized
	  for(unsigned int i=last_word;i<arr_size;i++){
	  	tempArr[i]=nullptr;
	  }
      
      //Pointing the old pointers to the new arrays and deleting the temporary pointers.
	  for(unsigned int i=0;i<last_word;i++){
	  	delete arr[i];
	  }
      delete[] arr;
	  arr=tempArr;
    }
    arr[last_word]=new slot(string,1);
	last_word++;
  }
  else//This means that the words exists, so the number that the word has appeared increases by 1. indx is the index of the found word after performing linear searching.
  {
    arr[indx]->sum++;
  }
}

//PRIVATE, I NEED THIS IN ORDER TO KNOW IF I SHOULD UPDATE THE ARRAYS OR NOT.
bool unsortedArray::wordExists(char* string)
{
  indx=0;
  bool flag=false;//If the word is found, flag will become true.
  while(indx<last_word && flag==false)
  {
    if(strcmp(string,arr[indx]->word)==0)//checks if the given word is the same word as words[indx]
    {
      flag=true;//The word is found!
    }
    else
    {
      indx++; //Checking the next word.
    }
  }
  return flag;
}



bool unsortedArray::search(char* string, ostream &o)
{
  //The following lines of code searches if the word exists in the array, just like the linear searching we did above
  if(wordExists(string))
  {
	  o<<">>\""<<arr[indx]->word<<"\" found "<<arr[indx]->sum<<" times"<<endl;
    //Word found
    return true;
  }
  else
  {
    //The word is not found
    return false ;
  }
}


bool unsortedArray::delete_word(char * string)
{
  if(!wordExists(string))
  {
    return false; //The given word does not exist in the array
  }
  if(arr[indx]->sum>1){
	arr[indx]->sum--;
	return true;
  }
  else
  {
	//we dont care about the order of the array, so simply paste the last word over
	//the one to-be-deleted
	delete arr[indx];
	arr[indx]=new slot(arr[last_word-1]->word,arr[last_word-1]->sum);
	//then delete the last word;
	delete arr[last_word-1];
	arr[last_word-1]=nullptr;
	last_word--;
    
	return true;
  }
}