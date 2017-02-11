
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"
#include "MyDB_PageRecIterator.h"

void MyDB_PageReaderWriter :: clear () {
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return myPageType;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared<MyDB_PageRecIterator> (iterateIntoMe,myPage);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType pT) {
	myPageType=pT;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr) {
	return true;
}

#endif
