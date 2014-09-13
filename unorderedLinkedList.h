/***********************************************************
 * linkedListType.h
 *
 *  Created on: Mar 22, 2013
 *      Author: rajeshwari
 */
//***********************************************************
//***********************************************************
//	Portion of this code is from:
//	Author: D.S. Malik
// This class specifies the members to implement the basic
// properties of an unordered linked list. This class is
// derived from the class linkedListType.
//***********************************************************
#ifndef H_UnorderedLinkedList
#define H_UnorderedLinkedList
#include <iostream>
#include <limits>
using namespace std;

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};

template <class Type>
class unorderedLinkedList
{
public:
	bool search(const Type& searchItem) const;
	  //Function to determine whether searchItem is in the list.
	  //Postcondition: Returns true if searchItem is in the list,
	  //    otherwise the value false is returned.

	bool searchRec(const Type& searchItem, nodeType<Type>*current) const;
	      //Function to determine whether searchItem is in the list using recursion.
	      //Postcondition: Returns true if searchItem is in the list,
	      //    otherwise the value false is returned.

	void insertFirst(const Type& newItem);
      //Function to insert newItem at the beginning of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the beginning of the list, last points to
      //    the last node, and count is incremented by 1.
	void insertLast(const Type& newItem);
	  //Function to insert newItem at the end of the list.
	  //Postcondition: first points to the new list, newItem is
	  //    inserted at the end of the list, last points to the
	  //    last node, and count is incremented by 1.

    void deleteLastNode();
      //Function to delete last node from the list.
      //Postcondition: first points to the first and most used node of the list
      // last points to the last and least recently used node
      // delete the last node and point last pointer to second last node
    void deleteNode(const Type& deleteItem);
      //Function to delete deleteItem from the list.
      //Postcondition: If found, the node containing deleteItem
      //    is deleted from the list. first points to the first
      //    node, last points to the last node of the updated
      //    list, and count is decremented by 1.
    bool isFullList();
      //Function to check if the linked list is full
     //Check if all physical memory frames are full
    unorderedLinkedList(int totalNum);
      //default constructor
      //Initializes the list to an empty state.
      //Postcondition: first = NULL, last = NULL, count = 0;
    ~unorderedLinkedList();
      //destructor
      //Deletes all the nodes from the list.
      //Postcondition: The list object is destroyed.
protected:
    int count; //variable to store the number of list elements
    int total; //variable to store the capacity of list
    nodeType<Type> *first; //pointer to the first node of the list
    nodeType<Type> *last;  //pointer to the last node of the list
};

template <class Type>
bool unorderedLinkedList<Type>::
                   search(const Type& searchItem) const
{
	    if(searchRec(searchItem, first)){//Recursively search through the linked list
	    	return true;
	    }
	    else{
	    	return false;
	    }
}

template <class Type>
bool unorderedLinkedList<Type>::searchRec(const Type& searchItem, nodeType<Type>  *current) const
{	//Sequential search function for unordered linked list implemented using recursion
	if(current == NULL){//if the linked list is empty or item not found
		return false;
	}
	else if(current->info == searchItem){//if the item is found
		return true;
	}
	else{
		current = current->link;
		this->searchRec(searchItem, current);//Recursively call the function
	}
}//end search

template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& newItem)
{
    nodeType<Type> *newNode; //pointer to create the new node

    newNode = new nodeType<Type>; //create the new node
    newNode->info = newItem;    //store the new item in the node
    if(this->isFullList()){
    	this->deleteLastNode();
    }
 	 newNode->link = this->first;      //insert newNode before first
     this->first = newNode;            //make first point to the actual first node
     this->count++;                    //increment count

     if (this->last == NULL)   //if the list was empty, newNode is also
                         //the last node in the list
         this->last = newNode;
}//end insertFirst

template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type& newItem)
{
    nodeType<Type> *newNode; //pointer to create the new node

    newNode = new nodeType<Type>; //create the new node

    newNode->info = newItem;  //store the new item in the node
    newNode->link = NULL;     //set the link field of newNode to NULL


    if (this->first == NULL)  //if the list is empty, newNode is
                        //both the first and last node
    {
        this->first = newNode;
        this->last = newNode;
        this->count++;        //increment count
     }
    else    //the list is not empty, insert newNode after last
    {
        last->link = newNode; //insert newNode after last
        this->last = newNode; //make last point to the actual
                        //last node in the list
        this->count++;        //increment count
    }
}//end insertLast

template <class Type>
void unorderedLinkedList<Type>::deleteLastNode()
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    current = first;
    trailCurrent = current;
    while(current->link!=NULL){//Till pointer reaches end
    	trailCurrent = current;
    	current = current->link;
    }
    last = trailCurrent;
    last->link = NULL;//Delete last node
    count--;
    delete current;
}//end deleteNode

template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    bool found;

    if (this->first == NULL)    //Case 1; the list is empty.
        cout << "Cannot delete from an empty list."
             << endl;
    else
    {
        if (this->first->info == deleteItem) //Case 2
        {
            current = this->first;
            this->first = first->link;
            this->count--;
            if (this->first == NULL)    //the list has only one node
                this->last = NULL;
            delete current;
        }
        else //search the list for the node with the given info
        {
            found = false;
            trailCurrent = this->first;  //set trailCurrent to point
                                   //to the first node
            current = this->first->link; //set current to point to
                                   //the second node

            while (current != NULL && !found)
            {
                if (current->info != deleteItem)
                {
                    trailCurrent = current;
                    current = current-> link;
                }
                else
                    found = true;
            }//end while

            if (found) //Case 3; if found, delete the node
            {
                trailCurrent->link = current->link;
                this->count--;

                if (this->last == current)   //node to be deleted
                                       //was the last node
                    this->last = trailCurrent; //update the value
                                         //of last
                delete current;  //delete the node from the list
            }
            else
                cout << "The item to be deleted is not in "
                     << "the list." << endl;
        }//end else
    }//end else
}//end deleteNode

template<class Type>
bool unorderedLinkedList<Type>::isFullList(){
	return(total == count);//Check if the total number of frames are full
}

template<class Type>
unorderedLinkedList<Type>::unorderedLinkedList(int totalNum)
{
	first = NULL;
	last = NULL;
	count = 0;//Initialize count to 0
	total = totalNum;//Total number of physical memory frames
}

template <class Type>
unorderedLinkedList<Type>::~unorderedLinkedList() //destructor
{
	nodeType<Type> *temp;   //pointer to deallocate the memory
	                            //occupied by the node
	    while (first != NULL)   //while there are nodes in the list
	    {
	        temp = first;        //set temp to the current node
	        first = first->link; //advance first to the next node
	        delete temp;   //deallocate the memory occupied by temp
	    }

	    last = NULL; //initialize last to NULL; first has already
	                 //been set to NULL by the while loop
	    count = 0;
	    total = 0;
}//end destructor


#endif
