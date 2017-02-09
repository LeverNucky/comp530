<<<<<<< HEAD
#ifndef STACK_H
#define STACK_H
// this is the node class used to build up the LIFO stack

template <class Data>
class Node {

private:
	Data data;
    Node* next;
public:
	Data getData(){return data;}
	Node* getNext(){return next;}
	void setData(Data d){data=d;}
	void setNext(Node* n){next=n;}
=======
#include <cstddef>
#ifndef STACK_H
#define STACK_H
// this is the node class used to build up the LIFO stack
template <class Data> 
class Node {

private:

	Data holdMe;
	Node *next;
	
public:
	// Data holdMe;
	// Node *next;

	//friend class Stack;
	Data getData() {
		return holdMe;
	}
	Node* getNext() {
		return next;
	}
	void setData(Data d){
		holdMe = d;
	}
	void setNext(Node *n){
		next = n;
	}

	void push(Data);	//store new top element
	Data pop();		//remove and return top element
	bool isEmpty();			//check whether the stack is empty


	//friend void push(Data);	//store new top element
	//friend Data pop();		//remove and return top element
	//friend bool isEmpty();			//check whether the stack is empty

	/*****************************************/
	/** WHATEVER CODE YOU NEED TO ADD HERE!! */
	/*****************************************/

>>>>>>> 8a71ca1cbce1b6c4c670f61952462502400c4579
};

// a simple LIFO stack
template <class Data> 
class Stack {

	Node <Data> *head;

public:

	// destroys the stack
<<<<<<< HEAD
	~Stack () {
		Node<Data>* current = head;

	    while ( current!= NULL)
	    {
	        Node<Data>* next = current->getNext();
	        delete current;
	        current = next;
	    }

	    head = NULL;
			
	}

	// creates an empty stack
	Stack ():head(NULL){}

	// adds pushMe to the top of the stack
	void push (Data data) {
		Node<Data> *newHead = new Node<Data>;
		newHead->setData(data);
        newHead->setNext(head);
        head = newHead;

		
	}

	// return true if there are not any items in the stack
	bool isEmpty () { return head==NULL; }

	// pops the item on the top of the stack off, returning it...
	// if the stack is empty, the behavior is undefined
	Data pop () {
		if (!isEmpty()) 
		{
	        Node<Data> *oldHead = head;
	        Data data = oldHead->getData();
	        head = head->getNext();
	        
	        delete oldHead;
	        return data;
    	}
    	return Data();
    	
	}
};

#endif
=======
	~Stack () { /* your code here */ 
		while(head != NULL){
			Node <Data> *ptr = head;
			head = head->getNext();
			delete ptr;
		}
	}

	// creates an empty stack
	Stack () { /* your code here */ 
		head = NULL;
	}

	// adds pushMe to the top of the stack
	// void push (Data d) { /* your code here */ 
	// 	Node <Data> *newHead = new Node <Data>;
	// 	if(head == NULL){
	// 		newHead->holdMe = d;
	// 		newHead->next = NULL;
	// 		head = newHead;
	// 	}
	// 	else{
	// 		newHead->holdMe = d;
	// 		newHead->next = head;
	// 		head = newHead;
	// 	}
	// }

	void push (Data d) { /* your code here */ 
		Node<Data>* newHead = new Node <Data>;
		if(head == NULL){
			newHead->setData(d);
			newHead->setNext(NULL);
			head = newHead;
		}
		else{
			newHead->setData(d);
			newHead->setNext(head);
			head = newHead;
		}
	}

	// return true if there are not any items in the stack
	bool isEmpty () { /* replace with your code */ 
		if(head != NULL){
			return false;
		}
		return true;
	}


	// pops the item on the top of the stack off, returning it...
	// if the stack is empty, the behavior is undefined
	// Data pop () { /* replace with your code */ 
	// 	if(head == NULL){
	// 		//cout<<"Nothing to pop.";
	// 		return -1;
	// 	}
	// 	Data d = head->holdMe;
	// 	Node <Data> *former = head;
	// 	head = head->next;
	// 	delete(former);
	// 	return d;
	// }

	Data pop () { /* replace with your code */ 
		if(head == NULL){
			//cout<<"Nothing to pop.";
			return -1;
		}
		Data d = head->getData();
		Node <Data> *former = head;
		head = head->getNext();
		delete(former);
		return d;
	}



};

#endif
>>>>>>> 8a71ca1cbce1b6c4c670f61952462502400c4579
