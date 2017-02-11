
#ifndef TABLE_REC_ITER_H
#define TABLE_REC_ITER_H

#include <memory>
#include "MyDB_RecordIterator.h"
using namespace std;


class MyDB_TableRecIterator;
typedef shared_ptr <MyDB_TableRecIterator> MyDB_TableRecIteratorPtr;



class MyDB_TableRecIterator: public MyDB_RecordIterator {

public:

	// put the contents of the next record in the file/page into the iterator record
	// this should be called BEFORE the iterator record is first examined
	void getNext();

	// return true iff there is another record in the file/page
	bool hasNext();

	// destructor and contructor
	MyDB_TableRecIterator () {};
	~MyDB_TableRecIterator () {};

};

#endif
