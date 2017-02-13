

#ifndef TABLE_REC_ITER_C
#define TABLE_REC_ITER_C

#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableRecIterator.h"

void MyDB_TableRecIterator :: getNext () {
	curPageIter->getNext ();
}

bool MyDB_TableRecIterator :: hasNext () {
	if (curPageIter->hasNext ())
		return true;

	while (curPageIter->hasNext()==false){
		index++;
		if (index>myTable->lastPage()){
			return false;
		}
		curPageIter = myParent[index].getIterator(myRec);
	}
	return true;
	
}

MyDB_TableRecIterator :: MyDB_TableRecIterator (MyDB_TableReaderWriter &myParent,MyDB_TablePtr forMe, MyDB_RecordPtr myRec):myParent(myParent){
	this->myTable = myTable;
	this->myRec = myRec;
	curPageIter = myParent[0].getIterator (myRec);
	index = 0;	
}


#endif