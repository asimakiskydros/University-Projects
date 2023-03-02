#include "sortedArray.h"
#include <cstring>
#include <iostream>
using namespace std;

sortedArray::sortedArray()
{
  //initializing integers to 0 and pointers to nullptr
  last_word=0;
  arr=nullptr;
}



sortedArray::~sortedArray()
{
  reset();
  delete arr;
}



void sortedArray::reset()
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


void sortedArray::insert(char* string)
{
  if(arr==nullptr)//Basically this block of code runs only on the FIRST word given and allocates memory for the array.
  {
    arr_size=10;
    arr=new slots*[arr_size];
	for(int i=0;i<10;i++)
		arr[i]=nullptr;
  }
  if(!wordExists(string,0,last_word))//If the word does not exist in the array, we store it in the array.
  {
    
    if(last_word==arr_size)//If the array is full its size should get doubled
    {
      arr_size*=2;

      //Creating temporary pointer that point to the new, bigger array.  
      slots **tempArr=new slots*[arr_size];
      
      //Copying the old array's contents to the new arrays.
      for(unsigned int i=0; i<last_word; i++)
      {
        tempArr[i]=new slots(arr[i]->word,arr[i]->sum);

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
	//We take advantage of the fact that the array is sorted:
	//linealry traverse the array until you find the correct spot for the string
	unsigned int i;
	for(i=0;i<last_word;i++)
		if(strcmp(string,arr[i]->word)<0)//this slot is bigger than the string, found
			break;
	//move every slot >=i one slot forward
	for(unsigned int j=last_word;j>i;j--){
		if(arr[j]!=nullptr)
			delete arr[j];
		arr[j]=new slots(arr[j-1]->word,arr[j-1]->sum);
	}
	//place the string in the now vacant [i] slot
	delete arr[i];
	arr[i]=new slots(string,1);
	last_word++;
  }
  else//This means that the words exists, so the number that the word has appeared increases by 1. indx is the index of the found word after performing binary searching.
  {
    arr[indx]->sum++;
  }
}


//PRIVATE, I NEED THIS IN ORDER TO KNOW IF THE ARRAYS SHOULD BE UPDATED OR NOT
//Recursive binary search
bool sortedArray::wordExists(char* string, int low, int high)
{
  if(low<=high)
  {
    unsigned int mid=(low+high)/2;
    if(arr[mid]==nullptr)
		return false;
	else if(strcmp(string,arr[mid]->word)==0)
    {
      indx=mid;
      return true;
    }  
    else if(strcmp(string, arr[mid]->word)>0)
      return wordExists(string,mid+1,high);
    else if (strcmp(string, arr[mid]->word)<0)
      return wordExists(string,low,mid-1);
  }
  return false;
}




bool sortedArray::search(char* string, ostream &o)
{
  //Looks for the word
  unsigned int low = 0;
  unsigned int high = last_word;
  if(wordExists(string, low, high))
  {
    o<<">>\""<<arr[indx]->word<<"\" found "<<arr[indx]->sum<<" times"<<endl;
    return true; //word found
  }
  else
  {
    return false; // word not found
  }  
}



bool sortedArray::delete_word(char * string)
{
  if(!wordExists(string,0,last_word))
  {
    return false; //The given word does not exist in the array
  }
  else if(arr[indx]->sum>1)
  {
    arr[indx]->sum--;
  }
  else
  {
	//we care about the order of the slots, and we can use that to our advantage:
	//linearly move all slots after the deleted one back one slot  
	for(unsigned int i=indx;i<last_word-1;i++){
		if(arr[i]!=nullptr)
			delete arr[i];
		arr[i]=new slots(arr[i+1]->word,arr[i+1]->sum);
	}
	//exiting the loop, the last and second to last slots have the same contents
	//delete the last word
	delete arr[last_word-1];
	arr[last_word-1]=nullptr;
	last_word--;
  }
  	return true;
}

void sortedArray::printToStdOut(){
	for(unsigned int i=0;i<last_word;i++)
		cout<<arr[i]->word<<" "<<arr[i]->sum<<endl;
}