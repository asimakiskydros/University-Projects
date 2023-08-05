#include <iostream>
using namespace std;
template<typename T>
void quicksort(T *arr, int low, int high){
	if(low<high){
		T pivot=arr[high];
		int i=low;
		
		for(int j=low;j<=high;j++)
			if(arr[j]>pivot){
				//swap contents of i,j
				T temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;

				i++;
			}
		//swap contents of high,i
		T temp=arr[high];
		arr[high]=arr[i];
		arr[i]=temp;

		quicksort(arr,low,i-1);
		quicksort(arr,i+1,high);
	}
}
template <typename T>
void mySort(T *arr,int length){
	quicksort(arr,0,length-1);
}
template <typename T>
bool median(T *arr, int length, T &ret){
	if(!length)
		return false;
	short counter;
	//scan each slot to check if it's bigger than (length-1)/2, and only that many, other slots
	for(int i=0;i<length;i++){
		ret=arr[i];
		counter=0;
		for(int j=0;j<length;j++)
			if(arr[j]<ret)
				counter++;
		if(counter==(length-1)/2)
			break;
	}
	return true;
}
template<typename A, typename B>
B compare(A A1,A A2,B B1,B B2,B B3){
	if(A1>A2)
		return B1;
	if(A1<A2)
		return B2;
	else
		return B3;
}
template<typename T>
T *read(int length, T &m){
	T *arr=new T[length];
	int i=0;
	while(i<length)
		cin>>arr[i++];
	return arr;
}