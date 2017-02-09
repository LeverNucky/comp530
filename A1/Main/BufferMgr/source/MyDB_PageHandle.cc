
#ifndef PAGE_HANDLE_C
#define PAGE_HANDLE_C

#include <memory>
#include <cstdlib>
#include <iostream>
#include "MyDB_BufferManager.h"
#include "MyDB_PageHandle.h"

void *MyDB_PageHandleBase :: getBytes () {

	return page->getBytes();
}


void MyDB_PageHandleBase :: wroteBytes () {
	page->wroteBytes();
}

//destructor
MyDB_PageHandleBase :: ~MyDB_PageHandleBase () {
	page->decRef();

}

#endif

