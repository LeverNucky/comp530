#ifndef PAGE_REC_ITER_C
#define PAGE_REC_ITER_C

#include <iostream>
#include "MyDB_PageRecIterator.h"

using namespace std;

#define HEADER_SIZE (sizeof (MyDB_PageType) + sizeof (size_t))//12
#define GET_OFFSET_UNTIL_END(ptr)  (*((size_t *) (((char *) ptr) + sizeof (MyDB_PageType))))

MyDB_PageRecIterator::MyDB_PageRecIterator (MyDB_PageReaderWriter &myParent,MyDB_RecordPtr iterateIntoMe, MyDB_PageHandle myPageHandle):myParent(myParent){
    this->myRec=iterateIntoMe;
    this->myPage=myPageHandle;
    curPos=HEADER_SIZE;
}
void MyDB_PageRecIterator::getNext(){
    void *ptr=myPage->getBytes();
    void *oldRecPos=(char*)ptr+curPos;
 	myRec->fromBinary(oldRecPos);
	curPos+=myRec->getBinarySize();
}

bool MyDB_PageRecIterator::hasNext(){
	cout<<"In MyDB_PageRecIterator :: hasNext ()\n";
	//cout<<sizeof (MyDB_PageType)<<endl;
	//4
	//cout<<sizeof (size_t)<<endl;
	//8
	cout<<"TMP test\n";
	cout<<curPos;
	//cout<<GET_OFFSET_UNTIL_END(myPage->getBytes());
	
	cout<<"Out MyDB_TableRecIterator :: hasNext ()\n";
	return GET_OFFSET_UNTIL_END(myPage->getBytes())!=curPos;
	
    
}
#endif