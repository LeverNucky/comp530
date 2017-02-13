
#ifndef TABLE_REC_ITER_H
#define TABLE_REC_ITER_H

#include <memory>
#include "MyDB_RecordIterator.h"
#include "MyDB_Record.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_Table.h"
using namespace std;


class MyDB_TableRecIterator;
typedef shared_ptr <MyDB_TableRecIterator> MyDB_TableRecIteratorPtr;

class MyDB_TableRecIterator: public MyDB_RecordIterator {
public:

	// put the contents of the next record in the file/page into the iterator record
	// this should be called BEFORE the iterator record is first examined
	void getNext() override;

	// return true iff there is another record in the file/page
	bool hasNext() override;

	// destructor and contructor
	MyDB_TableRecIterator (MyDB_TableReaderWriter &myParent,MyDB_TablePtr forMe, MyDB_RecordPtr myRec);
	~MyDB_TableRecIterator () {};
private:
	MyDB_TableReaderWriter &myParent;
	MyDB_TablePtr myTable;
    MyDB_RecordPtr myRec;
    MyDB_RecordIteratorPtr curPageIter;
	int index;
	
};

#endif