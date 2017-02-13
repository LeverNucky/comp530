
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_TableRecIterator.h"

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr forMe, MyDB_BufferManagerPtr myBuffer) {
	this->myTable=forMe;
	this->myBuffer=myBuffer;
	init();
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t index) {
	shared_ptr <MyDB_PageReaderWriter> last;
	while (index > myTable->lastPage ()) {
		myTable->setLastPage (myTable->lastPage () + 1);
		last = make_shared <MyDB_PageReaderWriter> (*this,myTable,myBuffer,myTable->lastPage ());
		last->clear ();	
	}

	last = make_shared <MyDB_PageReaderWriter> (*this, myTable,myBuffer,index);
	return *last;
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	
	return make_shared <MyDB_Record> (myTable->getSchema());
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
    return (*this)[myTable->lastPage()];
}

void MyDB_TableReaderWriter :: append (MyDB_RecordPtr appendMe) {
	shared_ptr <MyDB_PageReaderWriter> last = make_shared <MyDB_PageReaderWriter> (*this,myTable,myBuffer, myTable->lastPage ());
	if (!last->append (appendMe)) {
		myTable->setLastPage (myTable->lastPage () + 1);
		last = make_shared <MyDB_PageReaderWriter> (*this, myTable,myBuffer,myTable->lastPage ());
		last->clear();
		last->append(appendMe);
	}
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fileName) {
	init();
	ifstream fin;
	fin.open(fileName);
	string line;
	MyDB_RecordPtr emptyRec = getEmptyRecord ();
	while (getline (fin,line)) {
		emptyRec->fromString (line);		
		append (emptyRec);
	}
	fin.close ();

}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared <MyDB_TableRecIterator> (*this,myTable,iterateIntoMe);
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string fileName) {
	ofstream fout;
	fout.open (fileName);

	MyDB_RecordPtr emptyRec = getEmptyRecord ();	

	MyDB_RecordIteratorPtr recIter= getIterator (emptyRec);
	while (recIter->hasNext()) {
		recIter->getNext ();
	}
	fout.close ();
}
void MyDB_TableReaderWriter ::init(){
	myTable->setLastPage (0);
	shared_ptr <MyDB_PageReaderWriter> last = make_shared <MyDB_PageReaderWriter> (*this,myTable,myBuffer,0);
	last->clear ();
}

#endif

