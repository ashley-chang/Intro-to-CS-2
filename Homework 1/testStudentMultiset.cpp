//
//  testStudentMultiset.cpp
//  Homework1
//
//  Created by Ashley Chang on 7/1/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//



#include "StudentMultiset.h"
#include <cassert>

//add
//size
//print

int main () {
    StudentMultiset person;
    person.add(123456);
    person.add(123456);
    person.print();
    assert(person.add(500005));
    person.add(246802);
    assert(person.size() == 4);
    person.add(135791);
    assert(person.size() == 5);
    person.print();
    
    std::cout << std::endl;
    
    StudentMultiset another;
    another.add(987654);
    another.add(192837);
    another.add(222222);
    assert(another.size() == 3);
    another.add(505050);
    another.add(999999);
    another.add(222222);
    assert(another.size() == 6);
    assert(another.add(222222));
    assert(another.add(505050));
    another.print();
    std::cout<< "Passed all tests!";
    
} 
