 //
//  testNewMultiset.cpp
//  Homework1New
//
//  Created by Ashley Chang on 7/1/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//
/*

 #include "Multiset.h"
 #include <iostream>
 #include <cassert>
 using namespace std;
 
 int main()
 {
 Multiset ms;
 assert(ms.empty());
 string x = "dill";
 assert(ms.get(0, x) == 0  &&  x == "dill");  // x unchanged by get failure
 assert( ! ms.contains("tamarind"));
 ms.insert("tamarind");
 ms.insert("tamarind");
 assert(ms.size() == 2  &&  ms.uniqueSize() == 1);
 assert(ms.get(1, x) == 0  &&  x == "dill");  // x unchanged by get failure
 assert(ms.get(0, x) == 2  &&  x == "tamarind");
 cout << "Passed all tests" << endl;
 }
 
 
 */
 #include "newMultiset.h"
 #include <iostream>
 #include <cassert>
 
 int main()
 {
 Multiset ms;
 assert(ms.empty());
 unsigned long x = 999;
 assert(ms.get(0, x) == 0  &&  x == 999);  // x unchanged by get failure
 assert( ! ms.contains(42));
 
 ms.insert(42);
 ms.insert(42);
 
 assert( ! ms.getSecondLargestValue(x)  &&  x == 999 );
 assert(ms.size() == 2  &&  ms.uniqueSize() == 1);
 assert(ms.get(1, x) == 0  &&  x == 999);  // x unchanged by get failure
 assert(ms.get(0, x) == 2  &&  x == 42);
 
 assert(ms.getLargestValue(x) && x == 42 );
 assert(ms.countIf('=',42) == 2);
 assert(ms.countIf('>',42) == 0);
 assert(ms.countIf('<',42) == 0);
 
 //***************
     
     Multiset a(1000);   // a can hold at most 1000 distinct items
     Multiset b(5);      // b can hold at most 5 distinct items
     Multiset c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
     ItemType v[6] = {1,2,3,4,5,6};
     // No failures inserting 5 distinct items twice each into b
     for (int k = 0; k < 5; k++)
     {
         assert(b.insert(v[k]));
         assert(b.insert(v[k]));
     }
     assert(b.size() == 10  &&  b.uniqueSize() == 5  &&  b.count(v[0]) == 2);
     // Failure if we try to insert a sixth distinct item into b
     assert(!b.insert(v[5]));
     
     // When two Multisets' contents are swapped, their capacities are swapped
     // as well:
     a.swap(b);
     assert(!a.insert(v[5])  &&  b.insert(v[5]));

     
     
     
 Multiset test;
 unsigned long woo = 999;
 unsigned long yeah = 999;
 assert(test.size() == 0);
 assert(test.empty());
 
 test.insert(1000);
 test.insert(1000);
 test.insert(1000);
 
 assert (test.uniqueSize() == 1 && test.size() == 3);
 
 test.insert(20000);
 test.insert(300000);
 
 assert (test.uniqueSize() == 3 && test.size() == 5 && test.getMostFrequentValue(woo));
 assert (test.getLargestValue(woo) && test.getSecondLargestValue(yeah));
 assert (test.get(1, woo) == 1 && woo == 20000);
 assert (test.get(2, yeah) == 1 && yeah == 300000);
 assert (test.get(3, woo) == 0 && woo == 20000);
 
 test.insert(300000);
 test.insert(4000000);
 test.insert(50000000);
 
 assert(test.contains(50000000));
 assert (test.uniqueSize() == 5 && test.size() == 8);
 assert (test.count(3428) == 0);
 assert (test.count(300000) == 2);
 
 test.eraseAll(20000);
 
 assert(!test.contains(20000) && test.contains(1000) && test.contains(300000));
 assert(test.contains(50000000));
 assert(test.countIf('>', 50000000) == 0 && test.countIf('=', 1000) == 3 && test.countIf('>', 5000) == 4 && test.countIf('<', 4000000) == 5);
 
 test.insert(12345);
 test.insert(23456);
 test.insert(34567);
 test.insert(1);
 test.insert(98);
 test.insert(893);
 test.erase(12345);
 
 assert(test.uniqueSize() == 9 && test.contains(1) && !test.contains(12345));
 assert(test.countIf('=',1934) == 0 && test.countIf('<', 1000) == 3);
 
 test.erase(1000);
 
 assert(test.count(1000) == 2);
 assert(test.size() == 11 && test.uniqueSize() == 9);
 assert(test.getSecondLargestValue(woo) && woo == 4000000);
 
 assert(test.eraseAll(50000000) == 1);
 assert(test.eraseAll(39283) == 0);
 assert(test.eraseAll(4000000) == 1);
 
 assert(test.getLargestValue(yeah) && yeah == 300000);
 assert(test.getSecondLargestValue(yeah) && yeah == 34567);
 assert(test.uniqueSize() == 7);
 assert(test.get(0,yeah) == 2 && yeah == 1000);
 assert(test.countIf('>', 1) == 8);
 assert(test.countIf('<', 4589) == 5);
 assert(test.countIf('u', 2093) == -1);
     
 test.insert(-123);
 assert(test.contains(-123));
    
//*******************************************************

 Multiset extra(3);
 extra.insert(1324);
 extra.insert(5);
 extra.insert(10000);
 extra.insert(10000);
 extra.insert(5);
 assert(extra.contains(1324) && extra.contains(5) && extra.contains(10000));
 assert(extra.uniqueSize() == 3 && extra.size() == 5);
 assert(!extra.insert(33));
 extra.erase(5);
 assert(extra.count(5) == 1 && extra.size() == 4);
 
 unsigned long wow;
 unsigned long yay;
 assert(extra.getLargestValue(wow) && wow == 10000 && extra.getSecondLargestValue(yay) && yay == 1324);
 assert(extra.countIf('=',1324) == 1 && extra.countIf('>',5) == 3);
 assert(extra.get(0, wow) == 1);
 assert(extra.eraseAll(10000) == 2 && extra.uniqueSize() == 2 && extra.size() == 2);
 
 
     
     
     
     std::cout << "Passed all tests" << std::endl;
 }
 

