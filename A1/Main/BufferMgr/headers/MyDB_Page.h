#ifndef PAGE_H
#define PAGE_H

#include "MyDB_Table.h"

using namespace std;
class MyDB_Page;
typedef shared_ptr<MyDB_Page> MyDB_PagePtr;

class MyDB_BufferManager;

class MyDB_Page{
    
public:
    MyDB_Page(MyDB_TablePtr whichTable, size_t offset, bool pinned,MyDB_BufferManager &bufferManager);
    void decRef(); 
    void incRef();
    void* getBytes();
    void wroteBytes();
    ~MyDB_Page();
private:
    friend class MyDB_BufferManager;
    MyDB_TablePtr whichTable;
    void* bytes;
    int count;//count the reference
    size_t offset;
    bool pinned;
    bool dirty;
    MyDB_BufferManager& bufferManager;
    long timeStamp;
};

#endif