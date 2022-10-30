#include "slist.h"
#include <string>
using namespace std;
/*
Class Library File
*/

// add(value)				//Adds a new value to the end of this list.
void LinkedList::add(Airport value) {
  Node* newNode = new Node(value);
  if (length==0) {
    head = newNode;
  }
  else {
    //casting head
    Node* temp = head;
    while (temp->next != NULL) {
      //iterates from each non-null node to the next
      temp = temp->next;
    }
    temp->next = newNode;
  }
  length++;
}
// clear()					//Removes all elements from this list.
void LinkedList::clear() {
  head = NULL;
  length = 0;
}
// equals(list)				//Returns true if the two lists contain the same elements in the same order.
bool LinkedList::equals(LinkedList l) {
  if(length!=l.length) {
    return false;
  }
  else {
    //cast lists to node
    Node* lAsNode = l.head;
    Node* currentAsNode = head;
    while((lAsNode!=NULL)&&(currentAsNode!=NULL)) {
      if(!(lAsNode->data.equals(currentAsNode->data))) {
        return false;
        }
        lAsNode = lAsNode->next;
        currentAsNode = currentAsNode->next;
      }
    return true;
    }
  }
//get(index)				//Returns the element at the specified index in this list.
Airport LinkedList::get(int i) {
  Node* temp = head;
  Airport def = Airport(); //create default Airport in header class?
  if(i>length) {
    return def;
  }
  else {
  for(int n=0; n<i; n++) {
    temp = temp->next;
  }
  return temp->data;
  }
}

//insert(index, value)		//Inserts the element into this list before the specified index.
void LinkedList::insert(int in, Airport value) {
  Node* current = head;
  if(in>length-1) {
    cout << "Error: out of bounds" << "\n";
  }
  else {
  for(int i=0; i<in; i++) {
    if(current==NULL) {
      cout << "NULL location, no insertion made\n";
      }
    else {
      current = current->next;
    }
  }
    //now, as for substituting and shifting around the nodes after execution of this for loop
    Node* after = current->next;
    Node* inserted; //will be after "current", before "after"
    inserted->data = value;
    inserted->next = after; //substituted before "after"
    current->next = inserted; //"current" is before "inserted"
    length++;
  }
}

//exchg(index1, index2)		//Switches the payload data of specified indexex.
void LinkedList::exchange(int in1, int in2) {
  Node* node1 = head;
  Node* node2 = head;
  if((in1 > length)||(in2 > length)) {
    cout << "Index not in bounds";
  }
  else {
    //swaps ints
    if(in1>in2) {
      int temp = in1;
      in1 = in2;
      in2 = temp;
    }
    for(int i=0; i<in1; i++) {
      node1 = node1->next;
    }
    for(int l=0; l<in2; l++) {
      node2 = node2->next;
    }
    Airport castMe = node1->data;
    node1->data = node2->data;
    node2->data = castMe;
  }
  
}

//swap(index1,index2)		//Swaps node located at index1 with node at index2
void LinkedList::swap(int in1, int in2) {
  //we basically swap the +1 index of the in1 and in2, as this index represents the "next" value of the previous node, so this means that by swapping these "next" values, it actually swaps the in2 and in2 nodes
  //declare all 6 nodes
  Node* prev1 = head;
  Node* curr1 = head;
  Node* next1 = head;
  Node* prev2 = head;
  Node* curr2 = head;
  Node* next2 = head;
  //initialize all 6
  for(int i=0; i<in1; i++) {
    prev1=prev1->next;
  }
  for(int i=0; i<in1+1; i++) {
    curr1=curr1->next;
  }
  for(int i=0; i<in1+2; i++) {
    next1=next1->next;
  }
  for(int i=0; i<in2; i++) {
    prev2=prev2->next;
  }
  for(int i=0; i<in2+1; i++) {
    curr2=curr2->next;
  }
  for(int i=0; i<in2+2; i++) {
    next2=next2->next;
  }
  //now for swapping; We're able to do the below without accidently manipulating values in the casting process, as "prev->next" points to the current node
  prev1->next = curr2;
  prev2->next = curr1;
  curr1->next = next2;
  curr2->next = next1;
}

// isEmpty()				//Returns true if this list contains no elements.
bool LinkedList::isEmpty() {
  if(length==0) {
    return true;
  }
  else {
    return false;
  }
}

// remove(index)			//Removes the element at the specified index from this list.
void LinkedList::remove(int in) {
  //removing alters the "next" values of the node, so we'll declare the nodes before and after a removal
  Node* before;
  Node * after;
  for(int i=0; i<length; i++) {
    before = before->next;
    after = after->next;
    if(i==(in-1)) {
      after = after->next;
      after = after->next;
      before->next = after;
      length--;
      return; //I initally made a while loop to iterate i until i=length, but that didn't work as planned, so hopfully this return statement works
    }
  }
}

// set(index, value)		//Replaces the element at the specified index in this list with a new value.
void LinkedList::set(int in, Airport value) {
  Node* current = head;
  for(int i=0; i<length; i++) {
    current = current->next;
    if(i==in+1) {
      current->data = value;
      return;
    }
  }
}

// size()					//Returns the number of elements in this list.
int LinkedList::size() {
  return length;
}

// DO NOT IMPLEMENT >>> subList(start, length)	//Returns a new list containing elements from a sub-range of this list.

// DO NOT IMPLEMENT >>> toString()				//Converts the list to a printable string representation.
std::string LinkedList::toString() {
  string out = "";
  Node* current = head;
  string castCode;
  int indexOnList = 1;
  for(int i=0; i<length; i++) {
    castCode = current->data.code;
    //the std method to_string converts ints to string form
    out+=std::to_string(indexOnList) + ": " + castCode + ", Lat: " + std::to_string(current->data.latitude) + ", Long: " + std::to_string(current->data.longitude) + ", Dist: " + std::to_string(current->data.distToAB) + "\n";
    current = current->next;
    indexOnList++;
  }
  return out;
}