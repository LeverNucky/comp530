
#ifndef PAGE_RW_H
#define PAGE_RW_H

#include "MyDB_PageType.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_Table.h"
#include "MyDB_Record.h"
#include "MyDB_RecordIterator"

class MyDB_PageReaderWriter {

public:

	// ANY OTHER METHODS YOU WANT HERE
	//constructor
	MyDB_PageReaderWriter::MyDB_PageReaderWriter(MyDB_Table myTable);

	// empties out the contents of this page, so that it has no records in it
	// the type of the page is set to MyDB_PageType :: RegularPage
	void clear ();	

	// return an itrator over this page... each time returnVal->next () is
	// called, the resulting record will be placed into the record pointed to
	// by iterateIntoMe
	MyDB_RecordIteratorPtr getIterator (MyDB_RecordPtr iterateIntoMe);

	// appends a record to this page... return false is the append fails because
	// there is not enough space on the page; otherwise, return true
	bool append (MyDB_RecordPtr appendMe);

	// gets the type of this page... this is just a value from an ennumeration
	// that is stored within the page
	MyDB_PageType getType ();

	// sets the type of the page
	void setType (MyDB_PageType toMe);
	
private:

	// ANYTHING ELSE YOU WANT HERE
	size_t readBytesLength;
	size_t pageID;
	MyDB_pageHandle myPage;
	MyDB_bufferManagerPtr myBuffer;
	MyDB_TablePtr myTable;
	MyDB_PageType myPageType;

};

#endif
