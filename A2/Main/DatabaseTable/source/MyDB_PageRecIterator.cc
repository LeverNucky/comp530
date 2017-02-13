#ifndef PAGE_REC_ITER_C
#define PAGE_REC_ITER_C

#include <iostream>
#include "MyDB_PageRecIterator.h"

using namespace std;

#define HEADER_SIZE (sizeof (MyDB_PageType) + sizeof (size_t))
#define GET_OFFSET_UNTIL_END(ptr)  (*((size_t *) (((char *) ptr) + sizeof (MyDB_PageType))))

MyDB_PageRecIterator::MyDB_PageRecIterator (MyDB_PageReaderWriter &myParent,MyDB_RecordPtr iterateIntoMe, MyDB_PageHandle myPageHandle):myParent(myParent){
    this->myRec=iterateIntoMe;
    this->myPage=myPageHandle;
    curPos=HEADER_SIZE;

}
void MyDB_PageRecIterator::getNext(){
    void *ptr=myPage->getBytes ();
    void *oldRecPos=(char*)ptr+curPos;
 	void *newRecPos=myRec->fromBinary(oldRecPos);
	curPos+=((char *)newRecPos)-((char *)oldRecPos);
}

bool MyDB_PageRecIterator::hasNext(){

	return GET_OFFSET_UNTIL_END(myPage->getBytes())!=curPos;
    
}
#endif