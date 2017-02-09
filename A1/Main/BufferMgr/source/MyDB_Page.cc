#ifndef PAGE_C
#define PAGE_C

#include "MyDB_BufferManager.h"
#include "MyDB_Page.h"
#include "MyDB_Table.h"

void *MyDB_Page :: getBytes () {
	bufferManager.process(*this);	
	return bytes;
}

void MyDB_Page :: wroteBytes () {
	dirty = true;
}



MyDB_Page :: MyDB_Page (MyDB_TablePtr t, size_t i, bool p,MyDB_BufferManager &bm):whichTable(t),offset(i),pinned(p),bufferManager(bm){ 
	//bufferManager=bm;
	//whichTable=t;
	//offset=i;
	bytes=nullptr;
	dirty=false;	
	//pinned=p;
	count=0;
	
}

void MyDB_Page :: decRef() {
	count--;
	if (count == 0) {
		bufferManager.kill(*this);
	}
}

void MyDB_Page :: incRef() {
	count++;
}

MyDB_Page :: ~MyDB_Page () {}

#endif