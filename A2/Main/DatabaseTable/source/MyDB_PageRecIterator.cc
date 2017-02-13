#ifndef PAGE_REC_ITER_C
#define PAGE_REC_ITER_C

#include <iostream>
#include "MyDB_PageRecIterator.h"
//#include "MyDB_TableReaderWriter.h"

using namespace std;
// constructor
MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr myRec, MyDB_PageHandle myPage){
    this->myPage = myPage;
    this->myRec = myRec;
    readBytesLength = 0;
}

void MyDB_PageRecIterator::getNext(){
    // MyDB_PageHandle myHandle = myBuffer->getPage(myTable,pageID);
    curr_pos = &(((char*)myHandle->getBytes()) [readBytesLength]);
    curr_pos = myRec->fromBinary(curr_pos);
    readBytesLength += myRec->getBinarySize(); // get bytesLength of this rec.
}

bool MyDB_PageRecIterator::hasNext(){
    cout<<"This is a page."<<endl;
    current_pos = &(((char*)myHandle->getBytes()) [readBytesLength]);
    pageSize = myBuffer->getPageSize();
    if(readBytesLength >= pageSize){
        cout<<"reach the end"<<pageSize<<" "<<readBytesLength<<endl;// Testing
        return false;
    }
    return true;
}
#endif