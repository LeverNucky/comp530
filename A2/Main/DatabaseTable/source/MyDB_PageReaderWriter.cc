
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"

MyDB_PageReaderWriter::MyDB_PageReaderWriter(MyDB_Table myTable, MyDB_BufferManagerPtr myBuffer){
  this->myBuffer = myBuffer;
  this->myTable = myTable;
  myPage = myBuffer->getBytes();
  readBytesLength = 0;
}
void MyDB_PageReaderWriter :: clear () {
  //TODO
  
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return myPageType;
}

MyDB_RecordIterator MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr myRec) {
	MyDB_PageRecIterator myPageIt = make_shared <MyDB_PageRecIterator> (myRec, myPage);
  return myPageIt;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
  myPageType = toMe;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr appendMe) {
  MyDB_RecordPtr myRec = make_shared <MyDB_Record> (myTable->getSchema());
  void* curr_pos = myPage->getBytes();
  size_t pageSize = myBuffer->getPageSize();
  readBytesLength = 0;
  while(readBytesLength < pageSize){
    curr_pos = myRec->fromBinary(curr_pos);
    readBytesLength += myRec->getBinarySize();
  }
  if(readBytesLength + appendMe->getBinarySize()+4 > pageSize){
    return false;
  } //+4
  *(unsigned int*)curr_pos = appendMe->toBinary(curr_pos);
  myPage->wroteBytes();
	return true;
}

#endif
