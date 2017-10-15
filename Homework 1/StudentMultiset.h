//
//  studentMultiset.h
//  Homework1
//
//  Created by Ashley Chang on 7/1/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//
//Can't use for, while, [, *

#ifndef __Homework1__studentMultiset__
#define __Homework1__studentMultiset__

#include "Multiset.h"

class StudentMultiset
{
public:
    StudentMultiset();       // Create an empty student multiset.
    
    bool add(unsigned long id);
    
    int size() const;
    
    void print() const;
    
private:
    Multiset client;
    // Some of your code goes here.
};

#endif /* defined(__Homework1__studentMultiset__) */
