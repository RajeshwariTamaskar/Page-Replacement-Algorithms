/*
 * main.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: rajeshwari
 */

#include<iostream>
#include<cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>
#include <climits>
#include <map>
#include"unorderedLinkedList.h"
using namespace std;

class page
{
public:
	int freq;//NUmber of times page has been called
	int timeStp;//Timestamp of page call
};

//First In First Out Algorithm

void fifo(int logMem, int phyMem, int* pageRef, int total){
	vector<int>pageFrame;//Physical page frame
	int fifoIndex = 0;
	int pageFrameIndex = 0;
	int faultCounter = 0;
	cout<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<"          FIFO ALGORITHM			"<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<endl;
	for(int i = 0 ; i<total; i++){
		if((int)(pageFrame.size()) != phyMem){//If page frame is not full
			if(find(pageFrame.begin(),pageFrame.end(),pageRef[i]) == pageFrame.end()){//If the page is not in the page frame
				pageFrame.push_back(pageRef[i]);//Add page to frame
				cout<<pageRef[i]<<" : "<<"Page-Fault - ";
				faultCounter++;
				cout<<"Added to physical page frame."<<endl;
				pageFrameIndex++;
			}
			else{//If page is in the page frame
				cout<<pageRef[i]<<" : No page fault "<<endl;
			}
		}
		else{//If page frame is full
			if(find(pageFrame.begin(),pageFrame.end(),pageRef[i]) == pageFrame.end()){//If not in the page frame
				pageFrame[fifoIndex] = pageRef[i];//Use FIFO index
				cout<<pageFrame[fifoIndex]<<" : "<<"Page-Fault - ";
				faultCounter++;
				cout<<"Added to physical page frame."<<endl;
				if(fifoIndex+1 > phyMem-1)
					fifoIndex = 0;
				else
					fifoIndex++;
			}
			else{//If page is already in the physical frame
				cout<<pageRef[i]<<" : No page fault "<<endl;
			}
		}
	}
	cout<<endl;
	cout<<"Output: Total number of pages: "<<total<<"\nTotal number of page hits: "<<total-faultCounter<<endl;
}

//Least recently used Algorithm

void lru(int phyMem, int* pageRef, int total){
	unorderedLinkedList<int> pageList(phyMem);
	int faultCounter = 0;
	cout<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<"          LRU ALGORITHM			"<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<endl;
		for(int j = 0; j<total ; j++){
				if(!pageList.search(pageRef[j])){
					pageList.insertFirst(pageRef[j]);
					cout<<pageRef[j]<<" : Page-Fault - Added to physical frame"<<endl;
					faultCounter++;
				}
				else{
					pageList.deleteNode(pageRef[j]);
					pageList.insertFirst(pageRef[j]);
					cout<<pageRef[j]<<" : No page fault "<<endl;
				}
		}
		cout<<endl;
		cout<<"Output: Total number of pages: "<<total<<"\nTotal number of page hits: "<<total-faultCounter<<endl;

}

//Next appearance function

int nextAppearance(int num, int *arr, int total, int q){
	for(int h = q+1; h<total; h++){
			if(arr[h] == num)//find next appearance
				return h;
	}
	return total;
}

//Optimal Algorithm

void optimal(int phyMem, int* pageRef, int total){
	vector<int>pageFrame;//Physical page frame
	int faultCounter = 0;
	cout<<endl;
		cout<<"------------------------------------"<<endl;
		cout<<"        OPTIMAL ALGORITHM			"<<endl;
		cout<<"------------------------------------"<<endl;
		cout<<endl;
	for(int i = 0 ; i<total; i++){
				if((int)(pageFrame.size()) != phyMem){//If page frame is not full
					if(find(pageFrame.begin(),pageFrame.end(),pageRef[i]) == pageFrame.end()){//Not found in pageFrame and pageTable
						pageFrame.push_back(pageRef[i]);//Add to the page frame
						cout<<pageRef[i]<<" : Page-Fault - Added to physical frame"<<endl;
						faultCounter++;
					}
					else{//Exists in the page frame
						cout<<pageRef[i]<<" : No page fault "<<endl;
					}
				}
				else{ //If page frame is full
					if(find(pageFrame.begin(),pageFrame.end(),pageRef[i]) == pageFrame.end()){//Not found in page frame
							int maxIndex = INT_MIN;
							int swapPage;
							for (int k = 0; k<phyMem; k++){//Swap with the farthest next element
								int nextIndex = nextAppearance(pageFrame[k],pageRef,total,i)-i;
								if(maxIndex< nextIndex){
									maxIndex = nextIndex;
									swapPage = k;
								}
							}
							pageFrame[swapPage] = pageRef[i];
							cout<<pageRef[i]<<" : Page-Fault - Added to physical frame"<<endl;
							faultCounter++;
					}
					else{//I already exists in the page frame
						cout<<pageRef[i]<<" : No page fault "<<endl;
					}
				}

    }
	cout<<endl;
	cout<<"Output: Total number of pages: "<<total<<"\nTotal number of page hits: "<<total-faultCounter<<endl;
}

//Not Frequently Used Algorithm

void nfu(int phyMem, int* pageRef, int total){
	map<int, page> pageTable;//To store all the records of pages
	vector<int>pageFrame;//Physical page frame
	int timeStamp = 0;
	int faultCounter = 0;
	cout<<endl;
		cout<<"------------------------------------"<<endl;
		cout<<"           NFU ALGORITHM			"<<endl;
		cout<<"------------------------------------"<<endl;
		cout<<endl;
	for(int i = 0 ; i<total; i++){
			if((int)(pageFrame.size()) != phyMem){//If page frame is not full
				if(find(pageFrame.begin(),pageFrame.end(),pageRef[i]) == pageFrame.end()){//Not found in pageFrame and pageTable
					pageFrame.push_back(pageRef[i]);//Add to page frame
					pageTable[pageRef[i]].freq = 1;//Add to page table
					pageTable[pageRef[i]].timeStp = timeStamp++;
					cout<<pageRef[i]<<" : Page-Fault - Added to physical frame"<<endl;
					faultCounter++;
				}
				else{//if it exists in pageframe
					pageTable[pageRef[i]].freq++;
					cout<<pageRef[i]<<" : No page fault "<<endl;
				}
			}
			else{//if the page frame is full
				if(find(pageFrame.begin(),pageFrame.end(),pageRef[i]) == pageFrame.end()){//Not found in page frame
					int minFreq = pageTable[pageFrame[0]].freq;
					int minIndex = 0;
					int fifoTimeStmp = pageTable[pageFrame[0]].timeStp;
					for(int j = 0; j<phyMem; j++){//Check min freq in pageFrame
							if(minFreq > pageTable[pageFrame[j]].freq){
								minFreq = pageTable[pageFrame[j]].freq;
								fifoTimeStmp = pageTable[pageFrame[j]].timeStp;
							}
					}

					for(int k = 0 ; k<phyMem; k++){//Check the min Time stamp
						 if(pageTable[pageFrame[k]].freq == minFreq){
							 if(pageTable[pageFrame[k]].timeStp <= fifoTimeStmp){
								 fifoTimeStmp = pageTable[pageFrame[k]].timeStp;
								 minIndex = k;
							 }
					    }
					}
					//Replace minimum frequency page
					pageTable[pageFrame[minIndex]].timeStp = INT_MAX;//Set timestmp to infinity
					pageFrame[minIndex] = pageRef[i];
					pageTable[pageRef[i]].freq++;
					pageTable[pageRef[i]].timeStp = timeStamp++;
					cout<<pageRef[i]<<" : Page-Fault - Added to physical frame"<<endl;
					faultCounter++;
				}
				else{//found in page frame
					pageTable[pageRef[i]].freq++;
					cout<<pageRef[i]<<" : No page fault "<<endl;
				}

			}

	}
	cout<<endl;
	cout<<"Output: Total number of pages: "<<total<<"\nTotal number of page hits: "<<total-faultCounter<<endl;
	cout<<endl;
}

int main(){
	enum repAlgo{FIFO = 1, LRU = 2, Optimal = 3, NFU = 4, ALL = 5};
	repAlgo algo;
	int n;
	cout<<"Choose the replacement algorithm that you want to simulate:\n 1.FIFO\n 2.LRU\n 3.Optimal\n 4.NFU\n 5.All Algorithms\n";
	cin>>n;
    int logMem;
    cout<<"Enter number of pages in logical memory:\n";
    cin>>logMem;
    int phyMem;
    cout<<"Enter number of frames in physical memory:\n";
    cin>>phyMem;
    int* pageRef;
    pageRef = new int[1000];
    cout<<"Enter the page-reference string:\n";
    int i = 0;
    cin>>pageRef[0];
    while(pageRef[i] != -1){
    	if(pageRef[i]<0 || pageRef[i] >= logMem){
    	    cerr<<"Error: Enter valid page number"<<endl;
    	    exit(1);
    	}
    	i++;
    	cin>>pageRef[i];

    }
    int total = i;
    switch(n){
       		case 1:
       			algo  = repAlgo(n);
       			fifo(logMem,phyMem, pageRef, total);
       			break;
       		case 2:
       			algo  = repAlgo(n);
       			lru(phyMem, pageRef, total);
       			break;
       		case 3:
       			algo = repAlgo(n);
       			optimal(phyMem, pageRef, total);
       			break;
       		case 4:
       			algo = repAlgo(n);
       			nfu(phyMem, pageRef, total);
       			break;
       		case 5:
       			algo = repAlgo(n);
       			fifo(logMem,phyMem, pageRef, total);
       			lru(phyMem, pageRef, total);
       			optimal(phyMem, pageRef, total);
       			nfu(phyMem, pageRef, total);
       			break;
       		default:
       			cout<<"Error: Please enter appropriate algorithm number!\n";
       			exit(0);
    }
    delete []pageRef;
	return 0;
}



