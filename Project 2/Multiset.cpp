//
//  Multiset.cpp
//  Project2
//
//  Created by Ashley Chang on 7/5/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#include "Multiset.h"


void Multiset::swapAssist (int& x, int & y) //Swaps integers for member values
{
    int temp = x;
    x = y;
    y = temp;
}

Multiset::Node* Multiset::find(const ItemType& value) const
{
    Node * search = head;
    while (search != nullptr)
    {
        if (search->item == value) //If find a match for value,
        {
            return search; //return a pointer to the node for that value
        }
        search = search->next; //move on to the next node
    }
    return nullptr; //didn't find value
}

Multiset::Multiset()
{
    uniqueCount = 0;
    individual = 0;
    head = nullptr;
    tail = nullptr;
}

Multiset::~Multiset()
{
    Node * deleter = head;
    while (deleter != nullptr)
    {
        Node * point = deleter->next; //Use a pointer to keep track of next node
        delete deleter; //delete current node
        deleter = point;
    }
    head = nullptr;
    tail = nullptr;
}

Multiset::Multiset(const Multiset& other): uniqueCount(other.uniqueCount), individual(other.individual)
{
    Node * getter = other.head; //Points to items in other
    Node * hold = nullptr; //Pointer to assist in setting previous/next values for newly created Nodes
    
    for (int i = 0; i < uniqueCount && getter != nullptr; i++)
    {
        Node * creator = new Node; //New node created, receives copied info from "other"
        creator->item = getter->item;
        creator->itemCount = getter->itemCount;
        if (i == 0) //If this is the first node being copied, set the head to the current node and set previous to null ptr
        {
            head = creator;
            creator->previous = nullptr;

        }
        else //If not the first node, link previous node and set its next node to the current node
        {
            creator->previous = hold;
            hold->next = creator;
        }
        hold = creator;
        creator->next = nullptr;
        getter = getter->next;
    
    }
    tail = hold;
}

Multiset& Multiset::operator=(const Multiset& x)
{
    if (this != &x)
    {
        //Need to first delete memory already allocated to the Multiset
        Node * deleter = head;
        while (deleter != nullptr)
        {
            Node * point = deleter->next;
            delete deleter;
            deleter = point;
        }
        
        //After everything is deleted, make new linked list and copy all the elements
        uniqueCount = x.uniqueCount;
        individual = x.individual;
        
        Node * getter = x.head;
        Node * hold = nullptr;
        
        for (int i = 0; i < uniqueCount && getter != nullptr; i++)
        {
            Node * creator = new Node; //New node created, receives copied info from "other"
            creator->item = getter->item;
            creator->itemCount = getter->itemCount;
            if (i == 0) //If this is the first node being copied, set the head to the current node and set previous to null ptr
            {
                head = creator;
                creator->previous = nullptr;
            }
            else //link previous node and set its next node to the current node
            {
                creator->previous = hold;
                hold->next = creator;
            }
            hold = creator;
            creator->next = nullptr;
            getter = getter->next;
        }
        tail = hold;
    }
    return *this;
}


bool Multiset::insert(const ItemType& value)
{
    //Search through to see if item already exists (use find function)
    
    //If yes, add to count
    if (find(value) != nullptr)
    {
        find(value)->itemCount += 1;
        individual += 1;
        return true;
    }
    //If no, add new node (to front) and set all variables
    else
    {
        Node * p = new Node;
        p->item = value;
        p->itemCount = 1;
        p->next = head;
        p->previous = nullptr; //Adding to front, so no previous item
        if (head == nullptr) //If head doesn't point to anything yet (adding first item now), then new item is both head and tail.
        {
            tail = p;
        }
        else //There are items in the Multiset
        {
            head->previous = p; //Set former head's previous pointer to the new head
        }
        head = p; //Head is the new node (since we're adding to the front)
        uniqueCount += 1;
        individual += 1;
        return true;
    }
}

int Multiset::erase(const ItemType& value)
{
    if (head == nullptr || uniqueCount == 0)
        return 0;
    
    if (find(value) != nullptr) //found value!
    {
        Node * remove;
        if (find(value)->itemCount == 1) //There is only one instance of value, so need to delete entire node
        {
            if (head->item == value || uniqueCount == 1) //If value is at front/there's only on thing in the multiset
            {
                remove = head;
                if (uniqueCount == 1) //Only one thing in the multiset, so multiset will be empty
                {
                    find(value)->previous = nullptr;
                    find(value)->next = nullptr;
                    tail = nullptr;
                }
                head = remove->next;
            }
            else if (tail->item == value) //If value is at end
            {
                remove = tail;
                tail = find(value)->previous;
                find(value)->previous->next = nullptr;
            }
            else //If value is somewhere in the middle
            {
                //Link the nodes before and after value
                remove = find(value);
                remove->previous->next = remove->next;
                remove->next->previous = remove->previous;
            }
            delete remove;
            uniqueCount -= 1;
            individual -=1;
            return 1;
            
        } //*************************************Have deleted an entire node.
        
        find(value)->itemCount -= 1;
        individual -= 1;
        return 1;
    }
    else //did not find value
    {
        return 0;
    }
}

int Multiset::eraseAll(const ItemType& value)
{
    // Remove all instances of value from the multiset if present.
    // Return the number of instances removed.
    if (head == nullptr || uniqueCount == 0)
        return 0;
    if (find(value) != nullptr) //found value!
    {
        Node * remove;
        int deleted;
        if (head->item == value || uniqueCount == 1) //If value is at front/there's only on thing in the multiset
        {
            remove = head;
            if (uniqueCount == 1) //Only one thing in the multiset, so multiset will be empty
            {
                find(value)->previous = nullptr;
                find(value)->next = nullptr;
                tail = nullptr;
            }
            head = remove->next;
            deleted = remove->itemCount;
        }
        else if (tail->item == value) //If value is at end
        {
            remove = tail;
            tail = find(value)->previous;
            find(value)->previous->next = nullptr;
            deleted = remove->itemCount;
        }
        else //If value is somewhere in the middle
        {
            //Link the nodes before and after value
            remove = find(value);
            remove->previous->next = remove->next;
            remove->next->previous = remove->previous;
            deleted = remove->itemCount;
        }
        uniqueCount -= 1; //Adjust totals
        individual -= deleted;
        delete remove;
        return deleted;
    } 
    else //Didn't find value, so don't delete anything.
    {
        return 0;
    }
}

int Multiset::get(int i, ItemType& value) const
 {
    if (head == nullptr || i >= uniqueSize() || i < 0) //Return 0 if list is empty or i exceeds number of unique items/is not valid
         return 0;

    Node * getter = head;
    for (int j = 0; j < i && getter != nullptr; j++) //use j to traverse list until i
    {
        getter = getter->next; //Last incrementation/run of j should leave getter on i
    }
    value = getter->item;
    return getter->itemCount;
     
 }


bool Multiset::getMostFrequentValue(ItemType& value) const
{
    if (uniqueCount == 0 || individual == 0)
        return false;
    int frequency = 0; //Record the highest frequency
    ItemType frequentValue; //Record the item with the highest frequency
    Node * getter = head;
    for (int i = 0; i < uniqueCount && getter != nullptr; i++) //Traverse through list
    {
        if (getter->itemCount > frequency) //If there is an item that has a higher frequency than the higher frequency, set that item to the new "most frequent value"
        {
            frequency = getter->itemCount;
            frequentValue = getter->item;
        }
        getter = getter->next; //Move to the next item in the list
    } //Found highest frequency value (at least one).
    
    //Need to see if there is more than one value that has the highest frequency...
    
    int moreThanOne = 0; //Record whether more than one value has the highest frequency
    getter = head; //Put pointer back at head so we can traverse list again
    for (int j = 0; j < uniqueCount && getter != nullptr; j++) //If there is another item with the highest frequency, increment the moreThanOne counter
    {
        if (getter->itemCount == frequency)
            moreThanOne++;
        getter = getter->next;
    }
    if (moreThanOne > 1)
        return false; //No single value has the highest frequency
    else
        value = frequentValue; //Return the unique value that has the highest frequency
    return true;
}

bool Multiset::getLargestValue(ItemType& value) const
{
    if (uniqueCount == 0 || individual == 0)
        return false;
    Node* getter = head;
    ItemType largest = head->item; //Start from beginning of the list/multiset--first item is default largest
    for (int i = 0; i < uniqueCount && getter != nullptr; i++)
    {
        if (getter->item > largest) //If find some item that is larger than current largest
            largest = getter->item;
        getter = getter->next;
            
    }
    value = largest;
    return true;
}

bool Multiset::getSecondLargestValue(ItemType& value) const
{
    if (individual < 2 || uniqueCount < 2)
        return false;
    ItemType largest;
    getLargestValue(largest); //Find largest value and store it
    ItemType secondLargest = head->item;
    Node* getter = head;
    if (head->item == largest) //Need to ignore actual largest item
    {
        secondLargest = head->next->item;
        getter = getter->next;
    }
    for (int i = 0; i < uniqueCount && getter != nullptr; i++)
    {
        if (getter->item == largest) //If found true largest value, ignore it
        {
            getter = getter->next;
            continue;
        }
        if (getter->item > secondLargest) //If found some item that is larger than current (second) largest
            secondLargest = getter->item; //Set (second) largest to that item
        getter = getter->next;
    }
    value = secondLargest;
    return true;
    
}

bool Multiset::replace(ItemType original, ItemType new_value)
{
    if (uniqueCount == 0 || individual == 0)
        return false;
    if (original == new_value)
        return true;
    if (find(original) == nullptr) //Original does not exist
        return false;
    if (find(new_value) == nullptr) //New value is not already present
    {
        find(original)->item = new_value; //replace all instances of original with new value
    }
    else if (find(original) != find(new_value)) //New value exists already (and is different from original), so add to count and delete duplicate node
    {
        find(new_value)->itemCount += find(original)->itemCount; //Adding original items to new value count
        individual += find(original)->itemCount;
        eraseAll(original);
        
    }
    return true;
}

int Multiset::countIf(char op, ItemType value) const
{
    
    if (op != '<' && op != '>' && op != '=') //If operation sign is invalid, return -1
        return -1;
    int count = 0; //Keep track of items that correspond to op
    Node* getter = head;
    switch (op) //Return corresponding values
    {
        case '>': //Traverse list and record any items that are larger than value
            for (int i = 0; i < uniqueCount && getter != nullptr; i++)
            {
                if (getter->item > value)
                    count += getter->itemCount;
                getter = getter->next;
            }
            return count;
        case '=': //Traverse list and record any items that are equal to value
            for (int i = 0; i < uniqueCount && getter != nullptr; i++)
            {
                if (getter->item == value)
                    count += getter->itemCount;
                getter = getter->next;
            }
            return count;
        case '<': //Traverse list and record any items that are less than value
            for (int i = 0; i < uniqueCount && getter != nullptr; i++)
            {
                if (getter->item < value)
                    count += getter->itemCount;
                getter = getter->next;
            }
            return count;
        default:
            return -1;
    }
}

void Multiset::swap(Multiset& other)
{
    //Swap what the head/tail pointers point to
    Node* temp = head;
    head = other.head;
    other.head = temp;
    
    temp = tail;
    tail = other.tail;
    other.tail = temp;
    
    //Swap all private values
    swapAssist(uniqueCount, other.uniqueCount);
    swapAssist(individual, other.individual);
}

void Multiset::copyIntoOtherMultiset(Multiset& other) const
{
    Node * getter = head; //Use this pointer to traverse through original array
    for (int i = 0; i < uniqueCount && getter != nullptr; i++)
    {
        for (int j = 0; j < getter->itemCount && getter != nullptr; j++) //Copy all instances of each original item into other multiset
        {
            other.insert(getter->item);
        }
        getter = getter->next; //Increment pointer to next item in linked list
    }
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    if (&ms1 != &result && &ms2 != & result)
    {
        if (result.uniqueSize() != 0) //If result is not already empty,
        {
            int clear = result.uniqueSize();
            for (int i = 0; i < clear; i++) //Clear everything
            {
                ItemType x;
                result.get(0, x);
                result.eraseAll(x);
            }
        }
        ms1.copyIntoOtherMultiset(result);
        ms2.copyIntoOtherMultiset(result);
    }
    else if (&ms1 == &result) //Aliasing: add ms2 items to ms1
    {
        ms2.copyIntoOtherMultiset(result);
    }
    else if (&ms2 == &result)
    {
        ms1.copyIntoOtherMultiset(result);
    }
    
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    if (&ms1 != &result)
    {
        if (result.uniqueSize() != 0) //If result is not already empty,
        {
            int clear = result.uniqueSize();
            for (int i = 0; i < clear; i++) //Clear everything
            {
                ItemType n;
                result.get(0, n);
                result.eraseAll(n);
            }
        }
        for (int a = 0; a < ms1.uniqueSize(); a++) //Look at all the members of ms1
        {
            ItemType m;
            ms1.get(a,m); //Store whatever is at a in m
            if (ms2.contains(m)) //If ms2 contains matching items, find difference and put in result
            {
                int instances1 = ms1.count(m);
                int instances2 = ms2.count(m);
                if (instances1 > instances2)
                {
                    for (int b = 0; b < (instances1-instances2); b++)
                        result.insert(m);
                }
            }
            else //If ms2 doesn't have matching item, only add whatever is in ms1 to result
            {
                for (int c = 0; c < ms1.count(m); c++)
                    result.insert(m);
            }
        }
    }
    else if (&ms1 == &result) //Aliasing: delete any matching ms2 items from ms1
    {
        for (int q = 0; q < ms1.uniqueSize(); q++)
        {
            ItemType m;
            ms1.get(q,m);
            if (ms2.contains(m))
            {
                for (int w = 0; w < ms2.count(m); w++)
                    result.erase(m);
            }
        }
    }
    
    
}


