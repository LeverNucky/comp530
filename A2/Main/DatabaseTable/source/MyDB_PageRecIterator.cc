#ifndef PAGE_REC_ITER_C
#define PAGE_REC_ITER_C

#include <iostream>
#include "MyDB_PageRecIterator.h"

using namespace std;

MyDB_PageRecIterator::MyDB_PageRecIterator (MyDB_RecordPtr iterateIntoMe, MyDB_PageHandle myPageHandle){
    this->iterateIntoMe=iterateIntoMe;
    this->myPageHandle=myPageHandle;

}
void MyDB_PageRecIterator::getNext(){
    
}

bool MyDB_PageRecIterator::hasNext(){
    
}
#endif