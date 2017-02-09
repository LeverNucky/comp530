COMP 530 Assignment 1: LRU Buffer Manager

Author:

Qiang Wan (qw13)
Yifan Li (Yifan.Li)

LRU Implementation Note:

1) We use two maps and a list to represent LRU. The list contains all the keys in buffer. The first member of the list the
most recently used one and the last one indicates the least recently used key. 
2) When evicting, we first find the first page that is not pinned. Then we would evict that page
anyway. We would further write back to disk if the page is dirty
3) When all the pageHandles referenced to a page are out of scope(In our implementation,we use a private member of 
Page to count the number of valid pageHandles that are currently point to the page), we would call a function called 
kill(MyDB_Page) to deallocate this page.


