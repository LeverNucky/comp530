
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
	GET_OFFSET_UNTIL_END (myPage->getBytes()) = HEADER_SIZE;
	GET_TYPE(myPage->getBytes())=MyDB_PageType :: RegularPage;
	myPage->wroteBytes();
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return myPageType;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared<MyDB_PageRecIterator> (*this,iterateIntoMe,myPage);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
  myPageType = toMe;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr appendMe) {
<<<<<<< HEAD
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
=======
	size_t recSize = appendMe->getBinarySize ();
	void* ptr=myPage->getBytes();
	if (recSize > pageSize-GET_OFFSET_UNTIL_END(ptr))
		return false;
	else{
		appendMe->toBinary (((char *)ptr) + GET_OFFSET_UNTIL_END (ptr));
		GET_OFFSET_UNTIL_END (ptr)+=recSize;
		myPage->wroteBytes ();
		return true;
	}
	
>>>>>>> d7e32409dbbe8800778e26b12bf3757df30c8756
}

#endif
