#include "slist.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// Constructors
Node::Node(){
	this->data = new Airport();
	this->next = NULL;}

Node::Node(Airport* a){
	this->data = a;
	this->next = NULL;}

Node::Node(Airport* a, Node* b){
	this->data = a;
	this->next = b;}

// Constructors
LinkedList::LinkedList(){

    this->length = 0;
    this->head = new Node();
}
LinkedList::LinkedList(Node* h){
    this->length = 1;
    this->head = h;
}
// Destructor
LinkedList::~LinkedList(){
   Node* current = this->head;
    while(current){
        this->head = current->next;
        this->length -= 1;
		delete current;
		current = this->head;
    }
    cout << "LIST DELETED: " << this->length << endl;
}

void LinkedList::add(Airport* value){// Adds a new value to the end of this list.
	Node* n = this->head;
	for (int i = 0;i<this->length;i++){
		n = n->next;
	}
	Node* n1 = new Node(value);
	this->length++;
	n->next = n1;
}				

void LinkedList::clear(){// Removes all elements from this list.
	Node* n = this->head;
	Node* n1 = this->head;
	for(int i = 0;i<this->length;i++){
		n = n1;
		n1 = n1->next;
		free(n);	
	}
	this->length = 0;
}					
bool LinkedList::equals(LinkedList* list){// Returns true if the two lists contain the same elements in the same order.
	Node* me = this->head;
	Node* you = list->head;
	for (int i = 0;i<this->length;i++){
		if (me->data != you->data){
			return false;
		}
		me = me->next;
		you = you->next;
	}
	return true;
}

Airport* LinkedList::get(int index){// Returns the element at the specified index in this list.
	Node* n = this->head;
	for (int i = 0;i<index;i++){
		n = n->next;
	}
	return n->data;
}				

void LinkedList::insert(int index, Airport* value){ // Inserts the element into this list before the specified index.
	Node* n = this->head;
	Node* n1 = this->head;
	for (int i = 0;i<this->length;i++){
		n1 = n1->next;
		if (i != index){
			n = n->next;
		}
		else{
			n1 = n1->next;
			break;
		}
	}
	Node* mynode = new Node(value, n1);
	this->length++;
	n->next = mynode;
}	

void LinkedList::exchg(int index1, int index2){// Switches the payload data of specified indexex.
	Node* n = this->head;
	Node* n2 = this->head;
	for (int i = 0;i<this->length;i++){
		n = n->next;
		if (i == index1){
			for (int k = 0;k<this->length;k++){
				n2 = n2->next;
				if (k == index2){
					Node* temp = new Node();
					temp->data = n->data;
					n->data = n2->data;
					n2->data = temp->data;
				}
			}
		}
	}
}

void LinkedList::swap(int index1, int index2){   // Swaps node located at index1 with node at index2    
	Node* n = this->head;
	Node* n1 = this->head;
	Node* temp2 = this->head;
	Node* temp3 = this->head;
	for (int i = 0;i < index2+1;i++){
		n = n->next;
		if (i == index1){
			for (int k = 0;k<index2+1;k++){
				n1 = n1->next;
				if (k!= index2){
					temp3 = temp3->next;
				}
				else if (k == index2){
					break; 
				}
			}
			break;
		}
		else{
			temp2 = temp2->next;
		}
	}
	cout << "1: " << n->data->code << " | 2: " << n1->data->code << endl;
	/*temp2->next = n1;
	temp3->next = n;
	Node* temp = n->next;
	n->next = n1->next;
	n1->next = temp;*/
	
	Airport* tmp = n->data;
	n->data = n1->data;
	n1->data = tmp;
	cout << "1: " << n->data->code <<  " | 2: " << n1->data->code << endl;
}
bool LinkedList::isEmpty(){// Returns true if this list contains no elements.
	if (this->length == 0){
		return true;
	}
	return false;
}	

void LinkedList::remove(int index){// Removes the element at the specified index from this list.
	Node* n = this->head;
	Node* p = this->head;
	if (index != 0){
		int i = 0;
		for( i = 0;i<index;i++){
			n = n->next;
			if (i != 0){
				p = p->next;
			}
		}
		if (i == index-1){
			this->length--;
			p->next = NULL;
			free(n);
		}
		else{
			this->length--;
			p->next = n->next;
			n->next = NULL;
			free(n);
		}
	}
	else{
		Node* newfirst = n->next;
		this->head = newfirst;
		n->next = NULL;
		free(n);
	}
}	

void LinkedList::set(int index, Airport* value){// Replaces the element at the specified index in this list with a new value.
	Node* n = this->head;
	for (int i = 0;i<this->length;i++){
		if (i == index){
			n->data = value;
		}
		n = n->next;
	}
}	

int LinkedList::size(){// Returns the number of elements in this list.
	return this->length;
}					

LinkedList LinkedList::subList(int start, int len) {// Returns a new list containing elements from a sub-range of this list.
	Node* first = this->head;
	LinkedList lost = LinkedList();
	for (int i = 0;i<len;i++){
		first = first->next;
		if (i == start){
			lost.head = first;
		}
		else if (i > start){
			lost.add(first->data);
		}
	}
	return lost;
}

string  LinkedList::toString(){ // Converts the list to a printable string representation.
	string total;
	for (int i = 0;i<this->length;i++){
		total+=this->get(i)->code;
		total+=',';
		total+=this->get(i)->latitude;
		total+=',';
		total+=this->get(i)->longitude;
		total+=',';}
	return total;}