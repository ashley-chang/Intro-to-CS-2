//
//  studentMultiset.cpp
//  Homework1
//
//  Created by Ashley Chang on 7/1/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#include "StudentMultiset.h"
#include "Multiset.h"

StudentMultiset::StudentMultiset() {};
// Create an empty student multiset.
    
bool StudentMultiset::add(unsigned long id)
{
    if (client.uniqueSize()> DEFAULT_MAX_ITEMS)
        return false;
    client.insert(id);
    return true;
    
}
    // Add a student id to the StudentMultiset.  Return true if and only
    // if the id was actually added.
    
int StudentMultiset::size() const
{
    return client.size();
}
    // Return the number of items in the StudentMultiset.  If an id was
    // added n times, it contributes n to the size.
    
void StudentMultiset::print() const
{
    for (int i = 0; i < client.uniqueSize(); i++) //For every student id in the multiset
    {
        ItemType printThis;
        for (int j = 0; j < client.get(i, printThis); j++) //Print however many times it appears
            std::cout << printThis << std::endl;
    }
}
    // Print to cout every student id in the StudentMultiset one per line;
    // print as many lines for each id as it occurs in the StudentMultiset.

    
