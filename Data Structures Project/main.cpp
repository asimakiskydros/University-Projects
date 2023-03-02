#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include "unsortedArray.h"
#include "sortedArray.h"
#include "BinarySearchTree.h"
#include "BinarySearchTreeAVL.h"
#include "hashTable.h"
#include "mystring.h"
#define CEILING 1000

using namespace std;
using namespace std::chrono;

int main(){
	ifstream ifs;
	ofstream ofs;
	mystring string;
	mystring Q[CEILING];

	//Get 1000 sample-words from document
	ifs.open("input.txt");
	if(ifs.is_open()){
		int count=0;
		while(ifs>>string && count<CEILING){
			string.fix();
			Q[count++]=string;
		}
		ifs.close();
	}
	else{
		cerr<<"(!) Failed to get a word sample. Shutting down..."<<endl;
		exit(1);
	}

	//Unsorted Array
	unsortedArray UARR;
	ifs.open("input.txt");
	if(ifs.is_open()){
		//Insert
		auto t0=high_resolution_clock::now();
		while(ifs>>string){
			string.fix();
			UARR.insert(string.getData());
		}
		auto t1=high_resolution_clock::now();
		duration<double,milli> DTinsert=t1-t0;
		
		ofs.open("output.txt", ios::out | ios::app);
		if(ofs.is_open()){
			ofs<<"UNSORTED ARRAY RESULTS:"<<endl;
			ofs<<"Elapsed insertion time: "<<DTinsert.count()<<" msec"<<endl;
		
			//Search
			auto t2=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!UARR.search(Q[indx].getData(),ofs))
					ofs<<"\""<<Q[indx].getData()<<"\" not found"<<endl;
			auto t3=high_resolution_clock::now();
			duration<double,milli> DTsearch = t3-t2;
			ofs<<"Elapsed search time: "<<DTsearch.count()<<" msec"<<endl;
			
			//Delete
			auto t4=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)//The first BOUNDS words out of CEILING saved
				if(!UARR.delete_word(Q[indx].getData()))
					ofs<<"Could not delete \""<<Q[indx].getData()<<"\""<<endl;
			auto t5=high_resolution_clock::now();
			duration<double,milli> DTdelete = t5-t4;
			ofs<<"Elapsed deletion time: "<<DTdelete.count()<<" msec"<<endl<<endl;

			ofs.close();
		}
		else
			cerr<<"(!) Exiting file error in unsorted array."<<endl;
		ifs.close();
	}
	else
		cerr<<"(!) Reading file error trying to initialize unsorted array."<<endl;
	UARR.reset();

	//Sorted Array
	sortedArray SARR;
	ifs.open("input.txt");
	if(ifs.is_open()){
		//Insert
		auto t0=high_resolution_clock::now();
		while(ifs>>string){
			string.fix();
			SARR.insert(string.getData());
		}
		auto t1=high_resolution_clock::now();
		duration<double,milli> DTinsert=t1-t0;
		
		ofs.open("output.txt", ios::out | ios::app);
		if(ofs.is_open()){
			ofs<<"SORTED ARRAY RESULTS:"<<endl;
			ofs<<"Elapsed insertion time: "<<DTinsert.count()<<" msec"<<endl;
		
			//Search
			auto t2=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!SARR.search(Q[indx].getData(),ofs))
					ofs<<"\""<<Q[indx].getData()<<"\" not found"<<endl;
			auto t3=high_resolution_clock::now();
			duration<double,milli> DTsearch = t3-t2;
			ofs<<"Elapsed search time: "<<DTsearch.count()<<" msec"<<endl;
			
			//Delete
			auto t4=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!SARR.delete_word(Q[indx].getData()))
					ofs<<"Could not delete \""<<Q[indx].getData()<<"\""<<endl;
			auto t5=high_resolution_clock::now();
			duration<double,milli> DTdelete = t5-t4;
			ofs<<"Elapsed deletion time: "<<DTdelete.count()<<" msec"<<endl<<endl;

			ofs.close();
		}
		else
			cerr<<"(!) Exiting file error in sorted array."<<endl;
		ifs.close();
	}
	else
		cerr<<"(!) Reading file error trying to initialize sorted array."<<endl;
	SARR.reset();
	
	//Simple binary search tree
	BinarySearchTree BST;
	ifs.open("input.txt");
	if(ifs.is_open()){
		//Insert
		auto t0=high_resolution_clock::now();
		while(ifs>>string){
			string.fix();
			BST.insert(string.getData());
		}
		auto t1=high_resolution_clock::now();
		duration<double,milli> DTinsert=t1-t0;
		
		ofs.open("output.txt", ios::out | ios::app);
		if(ofs.is_open()){
			ofs<<"SIMPLE BINARY SEARCH TREE RESULTS:"<<endl;
			ofs<<"Elapsed insertion time: "<<DTinsert.count()<<" msec"<<endl;
		
			//Search
			auto t2=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!BST.search(Q[indx].getData(),ofs))
					ofs<<"\""<<Q[indx].getData()<<"\" not found"<<endl;
			auto t3=high_resolution_clock::now();
			duration<double,milli> DTsearch = t3-t2;
			ofs<<"Elapsed search time: "<<DTsearch.count()<<" msec"<<endl;

			/*//Traversals
			BST.preorder(ofs<<"Pre-order: "<<endl);
			BST.inorder(ofs<<"In-order: "<<endl);
			BST.postorder(ofs<<"Post-order: "<<endl);*/
			
			//Delete
			auto t4=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!BST.remove(Q[indx].getData()))
					ofs<<"Could not delete \""<<Q[indx].getData()<<"\""<<endl;
			auto t5=high_resolution_clock::now();
			duration<double,milli> DTdelete = t5-t4;
			ofs<<"Elapsed deletion time: "<<DTdelete.count()<<" msec"<<endl<<endl;

			ofs.close();
		}
		else
			cerr<<"(!) Exiting file error in simple binary search tree."<<endl;
		ifs.close();
	}
	else
		cerr<<"(!) Reading file error trying to initialize simple binary search tree."<<endl;
	BST.reset();

	//Binary search tree AVL
	BinarySearchTreeAVL BSTAVL;
	ifs.open("input.txt");
	if(ifs.is_open()){
		//Insert
		auto t0=high_resolution_clock::now();
		while(ifs>>string){
			string.fix();
			BSTAVL.insert(string.getData());
		}
		auto t1=high_resolution_clock::now();
		duration<double,milli> DTinsert=t1-t0;
		
		ofs.open("output.txt", ios::out | ios::app);
		if(ofs.is_open()){
			ofs<<"BINARY SEARCH TREE AVL RESULTS:"<<endl;
			ofs<<"Elapsed insertion time: "<<DTinsert.count()<<" msec"<<endl;
		
			//Search
			auto t2=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!BSTAVL.search(Q[indx].getData(),ofs))
					ofs<<"\""<<Q[indx].getData()<<"\" not found"<<endl;
			auto t3=high_resolution_clock::now();
			duration<double,milli> DTsearch = t3-t2;
			ofs<<"Elapsed search time: "<<DTsearch.count()<<" msec"<<endl;

			/*//Traversals
			BSTAVL.preorder(ofs<<"Pre-order: "<<endl);
			BSTAVL.inorder(ofs<<"In-order: "<<endl);
			BSTAVL.postorder(ofs<<"Post-order: "<<endl);*/
			
			//Delete
			auto t4=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!BSTAVL.remove(Q[indx].getData()))
					ofs<<"Could not delete \""<<Q[indx].getData()<<"\""<<endl;
			auto t5=high_resolution_clock::now();
			duration<double,milli> DTdelete = t5-t4;
			ofs<<"Elapsed deletion time: "<<DTdelete.count()<<" msec"<<endl<<endl;

			ofs.close();
		}
		else
			cerr<<"(!) Exiting file error in binary search tree AVL."<<endl;
		ifs.close();
	}
	else
		cerr<<"(!) Reading file error trying to initialize binary search tree AVL."<<endl;
	BSTAVL.reset();

	//Hash Table
	hashTable HSTBL;
	ifs.open("input.txt");
	if(ifs.is_open()){
		//Insert
		auto t0=high_resolution_clock::now();
		while(ifs>>string){
			string.fix();
			HSTBL.insert(string.getData());
		}
		auto t1=high_resolution_clock::now();
		duration<double,milli> DTinsert=t1-t0;

		ofs.open("output.txt", ios::out | ios::app);
		if(ofs.is_open()){
			ofs<<"HASH TABLE RESULTS:"<<endl;
			ofs<<"Elapsed insertion time: "<<DTinsert.count()<<" msec"<<endl;

			//Search
			auto t2=high_resolution_clock::now();
			for(int indx=0;indx<CEILING;indx++)
				if(!HSTBL.search(Q[indx].getData(),ofs))
					ofs<<"\""<<Q[indx].getData()<<"\" not found"<<endl;
			auto t3=high_resolution_clock::now();
			duration<double,milli> DTsearch=t3-t2;
			ofs<<"Elapsed search time: "<<DTsearch.count()<<" msec"<<endl;

			ofs.close();
		}
		else
			cerr<<"(!) Exiting file error in hash table."<<endl;
		ifs.close();
	}
	else
		cerr<<"(!) Reading file error trying to initialize hash table."<<endl;
	HSTBL.reset();

	return 0;
}