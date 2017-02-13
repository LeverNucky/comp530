
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"
#include "MyDB_PageRecIterator.h"
#include <stdlib.h>

#define HEADER_SIZE (sizeof (MyDB_PageType) + sizeof (size_t))
#define GET_TYPE(ptr) (*((MyDB_PageType *) ptr))
#define GET_OFFSET_UNTIL_END(ptr)  (*((size_t *) (((char *) ptr) + sizeof (MyDB_PageType))))

MyDB_PageReaderWriter :: MyDB_PageReaderWriter (MyDB_TableReaderWriter &parent, MyDB_TablePtr myTable, MyDB_BufferManagerPtr myBuffer, int whichPage) {
	myPage = myBuffer->getPage (myTable, whichPage);
	pageSize = myBuffer->getPageSize ();
}
void MyDB_PageReaderWriter :: clear () {
	GET_OFFSET_UNTIL_END (myPage->getBytes()) = HEADER_SIZE;
	myPage->wroteBytes();
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return GET_TYPE(myPage->getBytes());
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared<MyDB_PageRecIterator> (iterateIntoMe,myPageHandle);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType pT) {
	GET_TYPE (myPage->getBytes()) = pT;
	myPage->wroteBytes();
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr) {
	
	return true;
}

#endif
