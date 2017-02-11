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
};

// a simple LIFO stack
template <class Data> 
class Stack {

	Node <Data> *head;

public:

	// destroys the stack
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
