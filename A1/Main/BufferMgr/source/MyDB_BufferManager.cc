
#ifndef BUFFER_MGR_C
#define BUFFER_MGR_C

#include "MyDB_BufferManager.h"
#include "MyDB_Page.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <utility>

using namespace std;

MyDB_PageHandle MyDB_BufferManager :: getPage (MyDB_TablePtr whichTable, long i) {
	//We don't need to update LRU in getPage()
	//https://piazza.com/class/ixrmdcysugc2kl?cid=43
	pair <MyDB_TablePtr, long> whichPage = make_pair(whichTable,i);
	if (pageTable.count(whichPage)==0) {
		if (buffer.size()==0){
			//no available space in buffer, need to kick out one
			//TODO
			evict();
		}
		if (buffer.size()==0){
			//during kickout, we may encounter a dirty, so after kickout, it's still possible there
			//is no available space
			return nullptr;
		}
		//page currently not in pageTable
		MyDB_PagePtr page = make_shared <MyDB_Page> (whichTable,i,false,*this);
		pageTable[whichPage]=page;
		MyDB_PageHandle handle = make_shared<MyDB_PageHandleBase>(page);
        return handle;
	}
	else{
		//page currently in pageTable
		MyDB_PageHandle handle = make_shared<MyDB_PageHandleBase>(pageTable[whichPage]);
		return handle;
	}
	
}

MyDB_PageHandle MyDB_BufferManager :: getPage () {
	if (buffer.size()==0){
			//no available space in buffer, need to kick out one
			//TODO
			evict();
		}
	if (buffer.size()==0){
		//during kickout, we may encounter a dirty, so after kickout, it's still possible there
		//is no available space
		return nullptr;
	}
	pair <MyDB_TablePtr, long> whichPage = make_pair (nullptr, tempIndex);
	MyDB_PagePtr page = make_shared <MyDB_Page> (nullptr, tempIndex,false, *this);
	tempIndex++;
	
	pageTable[whichPage]=page;
	MyDB_PageHandle handle = make_shared<MyDB_PageHandleBase>(page);
    return handle;		
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage (MyDB_TablePtr whichTable, long i) {

	pair<MyDB_TablePtr,long> whichPage= make_pair(whichTable,i);
	
	if (pageTable.count(whichPage)==0) {
		// whichPage is not in pageTable

		if (buffer.size()==0){
			//no available space in buffer, need to kick out one
			//TODO
			evict();
		}
		if (buffer.size()==0){
			//during kickout, we may encounter a dirty, so after kickout, it's still possible there
			//is no available space
			return nullptr;
		}
		MyDB_PagePtr page = make_shared<MyDB_Page>(whichTable,i,true,*this);
		//page->bytes = buffer[buffer.size () - 1];
		//buffer.pop_back();
		pageTable[whichPage]=page;
		
		//open the table storage file
		// int fd = open (whichTable->getStorageLoc().c_str (), O_FSYNC|O_RDWR|O_CREAT, 0666);
		// lseek(fd,i*pageSize,SEEK_CUR);
  //       read(fd,page->bytes,pageSize);
  //       close(fd);

        MyDB_PageHandle handle = make_shared<MyDB_PageHandleBase>(page);
        
        return handle;
	}
	else{
		//whichPage is in pageTable
		MyDB_PageHandle handle = make_shared<MyDB_PageHandleBase>(pageTable[whichPage]);
		return handle;
	}
		
}

MyDB_PageHandle MyDB_BufferManager :: getPinnedPage () {
	if (buffer.size()==0){
			//no available space in buffer, need to kick out one
			//TODO
			evict();
		}
	if (buffer.size()==0){
		//during kickout, we may encounter a dirty, so after kickout, it's still possible there
		//is no available space
		return nullptr;
	}
	pair<MyDB_TablePtr,long> whichPage= make_pair(nullptr,tempIndex);
	MyDB_PagePtr page = make_shared<MyDB_Page>(nullptr,tempIndex,true,*this);
	tempIndex++;

	//page->pinned = true;
	//page->bytes = buffer[buffer.size () - 1];
	//buffer.pop_back();
	pageTable[whichPage]=page;
    MyDB_PageHandle handle = make_shared<MyDB_PageHandleBase>(page);
    return handle;	
}

void MyDB_BufferManager :: unpin (MyDB_PageHandle unpinMe) {
	unpinMe->page->pinned = false;
}
//TODO: Need to Modify
void MyDB_BufferManager :: evict(){
	//TODO
	//cout<<"evict()\n";
	pair<MyDB_TablePtr,long> pageID=recent.back();
	recent.pop_back();
	pos.erase(pos.find(pageID));
	MyDB_PagePtr page=pageTable[pageID];
	while(page!=nullptr){
		
		if (page->pinned){
			recent.push_front(pageID);
			pos[pageID] = recent.begin();
			pageID=recent.back();
			recent.pop_back();
			pos.erase(pos.find(pageID));
			page=pageTable[pageID];
			continue;
		}
		if (page->dirty){
			//open,lseek,write,close
			int fd;
			if (page->whichTable==nullptr){
				fd=open (tempFile.c_str (), O_CREAT | O_RDWR|O_SYNC, 0666);
			}
			else{
				fd=open (page->whichTable->getStorageLoc().c_str (), O_CREAT | O_RDWR|O_SYNC, 0666);
			}
			
			lseek (fd, page->offset * pageSize, SEEK_SET);
			cout<<"write 1\n";
			write (fd, page->bytes, pageSize);
			close(fd);
			page->dirty = false;
			
		}
		buffer.push_back (page->bytes);
		page->bytes = nullptr;
		break;
	}
		

}
void MyDB_BufferManager :: kill(MyDB_Page &page_in){
	//cout<<"kill()\n";
	pair <MyDB_TablePtr, long> key = make_pair (page_in.whichTable, page_in.offset);
	if (pageTable.count (key) ==1) {
		auto page = pageTable[key];

		//unpin
		MyDB_PageHandle handle = make_shared <MyDB_PageHandleBase> (page);
		if (page_in.bytes != nullptr&&pos.find(key) == pos.end())
			unpin(handle);
		if(pos.find(key) != pos.end()){ //this page is in buffer
			recent.erase(pos[key]);
			pos.erase(pos.find(key)); //this page exists, so no need to check whether the page exists in buffer
		}
		pageTable.erase (pageTable.find(key));
	}
	if (page_in.dirty){
			//open,lseek,write,close
		int fd;
		if (page_in.whichTable==nullptr){
			fd=open (tempFile.c_str (), O_CREAT | O_RDWR|O_SYNC, 0666);
		}
		else{
			fd=open (page_in.whichTable->getStorageLoc().c_str (),O_CREAT | O_RDWR|O_SYNC, 0666);
		}
		
		lseek (fd, page_in.offset * pageSize, SEEK_SET);
		cout<<"write 2\n";
		cout<<page_in.bytes;
		write (fd, page_in.bytes, pageSize);
		close(fd);
		page_in.dirty = false;
			
	}
	if (page_in.bytes != nullptr) {
		buffer.push_back (page_in.bytes);
		page_in.bytes = nullptr;
	}
	

}

void MyDB_BufferManager ::process(MyDB_Page &page_in){
	pair<MyDB_TablePtr,size_t> key = make_pair(page_in.whichTable, page_in.offset);
	auto page = pageTable [key];
	if(pos.find(key) != pos.end()){ //this page is in buffer
		recent.erase(pos[key]); //this page exists, so no need to check whether the page exists in buffer
		
	}
	else{ // this page isn't in buffer
		if( buffer.size()==0 ){ //check whether buffer is full
			evict();
		}
		if( buffer.size()==0 ){ //check whether buffer is full
			return;
		}
		page->bytes = buffer[buffer.size () - 1];
		buffer.pop_back();
		int fd;
		if (page->whichTable==nullptr){
			fd=open (tempFile.c_str (), O_CREAT | O_RDWR|O_SYNC, 0666);
		}
		else{
			fd=open (page->whichTable->getStorageLoc().c_str (), O_CREAT | O_RDWR|O_SYNC, 0666);
		}
		//int fd=open (page->whichTable->getStorageLoc().c_str (), O_CREAT | O_RDWR, 0666);
		lseek (fd, page->offset * pageSize, SEEK_SET);
		read(fd, page->bytes, pageSize);
		close(fd);
	}
	recent.push_front(key);
	pos[key] = recent.begin(); //rearrange the order of elements in buffers
}
MyDB_BufferManager :: MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile):pageSize(pageSize),tempFile(tempFile) {
	//this->pageSize = pageSize;
    //this->numPages = numPages;
    //this->tempFile = tempFile;
    tempIndex=0;
    //allocate buffer space
    for (size_t i = 0; i < numPages; i++) {
		buffer.push_back(malloc(pageSize));
	}
}

MyDB_BufferManager :: ~MyDB_BufferManager () {
	for (auto b:buffer){
		free(b);
	}
}
	
#endif


