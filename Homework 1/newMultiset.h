//
//  Header.h
//  Homework1New
//
//  Created by Ashley Chang on 7/1/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#ifndef Homework1New_Header_h
#define Homework1New_Header_h


#include <iostream>
#include <string>
typedef unsigned long ItemType;
//typedef std::string ItemType;
const int DEFAULT_MAX_ITEMS = 200;


class Multiset
{
public:
    Multiset();
    
    Multiset(int maximum);
    
    //copy constructor
    Multiset(const Multiset &m);
    
    //assignment operator
    Multiset &operator=(const Multiset &source);
    
    ~Multiset();
    
    bool empty() const;
    
    int size() const;
    
    int uniqueSize() const;
    
    bool insert(const ItemType& value);
    
    int erase(const ItemType& value);
    
    int eraseAll(const ItemType& value);
    
    bool contains(const ItemType& value) const;
    
    int count(const ItemType& value) const;
    
    int get(int i, ItemType& value) const;
    
    bool getMostFrequentValue(ItemType &value) const;
    
    bool getLargestValue(ItemType &value) const;
    
    bool getSecondLargestValue(ItemType &value) const;
    
    bool replace(ItemType original, ItemType new_value);
    
    int countIf(char op, ItemType value) const;
		  
    void swap(Multiset& other);
		  
    void copyIntoOtherMultiset(Multiset &other);
private:
    struct Multimember
    {
        ItemType item;
        int count = 0;
    };
    //Multiset contains a array data member.
    Multimember* set;
    int max;
    int numDiffItems;
    int individual;
    
};

inline bool Multiset::empty() const //DONE
{
    if (numDiffItems == 0 || individual == 0)
        return true;
    else
        return false;
}// Return true if the multiset is empty, otherwise false.

inline int Multiset::size() const //DONE
{
    return individual;
}
// Return the number of items in the multiset.  For example, the size
// of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.

inline int Multiset::uniqueSize() const //DONE
{
    if (numDiffItems==0 || individual == 0)
        return 0;
    return numDiffItems;
}

#endif
