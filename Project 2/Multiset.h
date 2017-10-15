//
//  Multiset.h
//  Project2
//
//  Created by Ashley Chang on 7/5/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#ifndef __Project2__Multiset__
#define __Project2__Multiset__

#include <iostream>
#include <string>

typedef std::string ItemType;
class Multiset
{
public:
    Multiset();
    ~Multiset(); //destructor
    Multiset(const Multiset& other); //copy constructor
    Multiset& operator=(const Multiset& x); //assignment operator
    
    bool empty() const;
    int size() const;
    int uniqueSize() const;
    bool insert(const ItemType& value);
    int erase(const ItemType& value);
    int eraseAll(const ItemType& value);
    bool contains(const ItemType& value) const;
    int count(const ItemType& value) const;
    int get(int i, ItemType& value) const;
    bool getMostFrequentValue(ItemType& value) const;
    bool getLargestValue(ItemType& value) const;
    bool getSecondLargestValue(ItemType& value) const;
    bool replace(ItemType original, ItemType new_value);
    int countIf(char op, ItemType value) const;
    void swap(Multiset& other);
    void copyIntoOtherMultiset(Multiset& other) const;
private:
    int uniqueCount;
    int individual;
    struct Node {
        ItemType item;
        int itemCount;
        Node* next;
        Node* previous;
    };
    Node * head;
    Node * tail;
    Node* find(const ItemType& value) const;
    void swapAssist (int& x, int & y);
};

inline bool Multiset::empty() const
{
    if (head == nullptr)
        return true;
    else
        return false;
}

inline int Multiset::size() const
{
    return individual;
}


inline int Multiset::uniqueSize() const
{
    return uniqueCount;
}

inline bool Multiset::contains(const ItemType& value) const
{
    // Return true if the value is in the multiset, otherwise false.
    if (find(value) != nullptr) //Found value!
    {
        return true;
    }
    else //Didn't find value
        return false;
}

inline int Multiset::count(const ItemType& value) const
{
    // Return the number of instances of value in the multiset.
    if (find(value) != nullptr) //Found value!
    {
        return find(value)->itemCount; //follow pointer to see how many of that item there are
    }
    else //Didn't find value
        return 0;
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);



#endif /* defined(__Project2__Multiset__) */
