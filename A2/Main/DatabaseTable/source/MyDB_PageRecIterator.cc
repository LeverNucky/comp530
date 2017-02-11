#ifndef PAGE_REC_ITER_C
#define PAGE_REC_ITER_C

#include <iostream>
#include "MyDB_PageRecIterator.h"
//#include "MyDB_TableReaderWriter.h"

using namespace std;

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr myRec, MyDB_BufferManagerPtr myBuffer, MyDB_TablePtr myTable){
    pageSize = myBuffer->getPageSize();
    this->myBuffer = myBuffer;
    this->myTable = myTable;
    this->myRec = myRec;
}

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_RecordPtr myRec, MyDB_BufferManagerPtr myBuffer, MyDB_TablePtr myTable, size_t pageID){
    pageSize = myBuffer->getPageSize();
    this->myRec = myRec;
    this->myBuffer = myBuffer;
    this->myTable = myTable;
    this->pageID=pageID;
    MyDB_PageHandle myHandle = myBuffer->getPage(myTable,pageID);
    current_pos = myHandle->getBytes();
    covered_bytes = 0;
}

void MyDB_PageRecIterator::setPageHandle(size_t pageID){
    this->pageID=pageID;
    MyDB_PageHandle myHandle = myBuffer->getPage(myTable,pageID);
    current_pos = myHandle->getBytes();
    covered_bytes = 0;
}

void MyDB_PageRecIterator::getNext(){
    MyDB_PageHandle myHandle = myBuffer->getPage(myTable,pageID);
    current_pos = &(((char*)myHandle->getBytes()) [covered_bytes]);
    current_pos = myRec->fromBinary(current_pos);
    covered_bytes+=myRec->getBinarySize();
}

bool MyDB_PageRecIterator::hasNext(){
    //cout<<"I'm a page."<<endl;
    MyDB_PageHandle myHandle = myBuffer->getPage(myTable,pageID);
    current_pos = &(((char*)myHandle->getBytes()) [covered_bytes]);
    if( *((unsigned int *)current_pos) == ENDING_SIGN){
        //cout<<"==================encounter a $==================="<<endl;
        return false;
    }
    if(covered_bytes >= pageSize){
        //cout<<"==================reach to the end==================="<<pageSize<<" "<<covered_bytes<<endl;
        return false;
    }
    return true;
}
#endif