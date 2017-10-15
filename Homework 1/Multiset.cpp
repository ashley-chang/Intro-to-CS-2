//
//  Multiset.cpp
//  Homework1
//
//  Created by Ashley Chang on 6/29/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#include "Multiset.h"

Multiset::Multiset() //DONE
{
    numDiffItems = 0;
    individual = 0;
}// Create an empty multiset.


bool Multiset::insert(const ItemType& value) //DONE
{
    int i;
    for (i = 0; i < numDiffItems; i++) //Search if there is already a value existing, then add 1
    {
        if (set[i].item == value)
        {
            set[i].count++;
            individual++;
            return true;
        }
    }
    if (numDiffItems >= DEFAULT_MAX_ITEMS)
        return false;
    set[i].item = value; //First instance of the value
    set[i].count = 1;
    numDiffItems++;
    individual++;
    return true;
}
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full).

int Multiset::erase(const ItemType& value) //DONE
{
    bool erased = false;
    for (int i = 0; i < numDiffItems && erased == false; i++) //Search for value in the multiset
    {
        if (set[i].item == value) //If found a match,
        {
            erased = true;
            set[i].count--; //Subtract one from it's count.
            individual--;
            if (set[i].count == 0) //If there are 0 left of this value, remove it
            {
                numDiffItems--; //One less unique item now
                set[i].item = set[numDiffItems].item; //Put last item in the empty space
                set[i].count = set[numDiffItems].count;
            }
        }
    }
    if (erased)
        return 1;
    else //Didn't find a match
        return 0;
}
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.

int Multiset::eraseAll(const ItemType& value) //DONE
{
    int removed = 0;
    for (int i = 0; i < numDiffItems; i++)
    {
        if (set[i].item == value)
        {
            numDiffItems--; //One less unique value
            removed = set[i].count; //Return this--how many instances of value were removed
            individual -= removed;
            set[i] = set[numDiffItems]; //Replace the item with the last item's contents
            return removed;
        }
    }
    return removed;
}
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.

bool Multiset::contains(const ItemType& value) const
{
    if (individual == 0 || numDiffItems == 0)
        return false;
    for (int i = 0; i < numDiffItems; i++) //Search the multiset
    {
        if (set[i].item == value) //If find something that matches value, return true
            return true;
    }
    return false;
}
 // Return true if the value is in the multiset, otherwise false.

int Multiset::count(const ItemType& value) const
{
    for (int i = 0; i < numDiffItems; i++)
    {
        if (set[i].item == value)
            return set[i].count; //Set value to count
    }
    return 0;
}
 // Return the number of instances of value in the multiset.
 //************************************************************************************************

 int Multiset::get(int i, ItemType& value) const //i is the index we want
{
    if (i >= 0 && i < uniqueSize())
    {
        value = set[i].item;
        return set[i].count;
    }
    else
        return 0;
}
 // If 0 <= i < uniqueSize(), copy into value an item in the
 // multiset and return the number of instances of that item in
 // the multiset.  Otherwise, leave value unchanged and return 0.
 // (See below for details about this function.)
    //i is the index.

 //*****************************************************************
bool Multiset::getMostFrequentValue(ItemType &value) const
{
    if (numDiffItems == 0 || individual == 0)
        return false;
    int frequency = 0;
    ItemType frequentValue;
    for (int i = 0; i < numDiffItems; i++)
    {
        if (set[i].count > frequency) //If count is larger than current frequentValue
        {
            frequency = set[i].count;
            frequentValue = set[i].item;
        }
    }
    //Found largest number of instances (stored in frequent)
    int moreThanOne = 0;
    for (int i = 0; i < numDiffItems; i++) //Check whether more than one item have the largest number of instances
    {
        if (set[i].count == frequency)
            moreThanOne++;
    }
    if (moreThanOne > 1)
        return false;
    else //There exists a single item that has the largest number of instances
        value = frequentValue; //copy the item into value
        return true;
}
 // If there exists a single item that has the largest number of instances in the multiset,
 // then copy into value that item in the multiset and return true.
 // However, if there exist more than 1 item that have the largest number of instances in the multiset,
 // then do not copy into value any item in the multiset and return false. In other words, value should remain unchanged.
 // If there's no item in the multiset, return false.
 
bool Multiset::getLargestValue(ItemType &value) const
{
    if (numDiffItems == 0 || individual == 0)
        return false;
    ItemType largest = set[0].item; //Start from the beginning of the multiset--first item is default largest
    for (int i = 0; i < numDiffItems; i++)
    {
        if (set[i].item > largest) //If find some item that is larger than current largest
            largest = set[i].item; //Set largest to that item
    }
    value = largest;
    return true;
}
 // If there exists a value that is the largest value among all the values in the multiset,
 // then copy into value that item in the multiset and return true
 // Otherwise, return false.
 // For both unsigned long and string data type, the higher value can be found by using greater than operator (>).
 // For example, 100 is greater than 20, so 100 > 20 is true.
 // "ZOO" is greater than "ABC", so "ZOO" > "ABC" is true.
 //******************************************************************************

bool Multiset::getSecondLargestValue(ItemType &value) const
{
    if (individual < 2 || numDiffItems < 2)
        return false;
    ItemType largest;
    getLargestValue(largest); //Find largest value and store it
    ItemType secondLargest = set[0].item; //Start from beginning of the multiset--first item is default largest
    for (int i = 0 ; i < numDiffItems; i++)
    {
        if (set[i].item == largest) //Found the true largest value; ignore it
            continue;
        if (set[i].item > secondLargest) //If find some item that is larger than current (second) largest
            secondLargest = set[i].item; //Set (second) largest to that item
    }
    value = secondLargest;
    return true;
}

 // Similar to getLargestValue(), but this time you need to find the second largest value.
 // If there exists a value that is the 2nd largest value among all the values in the multiset,
 // then copy into value that item in the multiset and return true.
 // Otherwise, return false.
 // Please note that you cannot use any sorting algorithm to sort the multiset.
 
bool Multiset::replace(ItemType original, ItemType new_value)
{
   if (individual == 0 || numDiffItems == 0)
       return false;
    bool replaced = false;
    for (int i = 0; i < numDiffItems; i++) //Go through multiset
    {
        if (set[i].item == new_value) //See if the item already exists so we can add to existing count
        {
            set[i].count += count(original);
            individual += count(original);
            eraseAll (original); //Remove the original after replacement
            return true;
        }
    }
    //The item does not already exist
    for (int j = 0; j < numDiffItems; j++)
    {
        if (set[j].item == original) //Search for match for original--this will be replaced
        {
            set[j].item = new_value;
            replaced = true;
            break;
        }
    }
    if (replaced)
        return true;
    else //If no match for original was found, return false
        return false;
}
 // Replace the item that has the value equal to original by the new value new_value.
 // For example, replace("ABC","XYZ") will search the multiset for the item "ABC" and replace all occurrences of "ABC" as "XYZ".
 // If the replacement is successful, then return true.
 // If there is no item to be replaced, then return false.
 
int Multiset::countIf(char op, ItemType value) const //DONE
{
    int greater = 0;
    int equal = 0;
    int less = 0;
    for (int i = 0; i < numDiffItems; i++)
    {
        if (set[i].item > value)
            greater += set[i].count;
        else if (set[i].item == value)
            equal += set[i].count;
        else if (set[i].item < value)
            less += set[i].count;
    }
    switch (op)
    {
        case '>':
            return greater;
        case '=':
            return equal;
        case '<':
            return less;
        default:
            return -1;
    }
}
 // Count the number of items that the item is greater than, less than, or equal to value.
 // For example:
 // countIf('>',100) returns the number of items in multiset in which the item is greater than 100.
 // countIf('=',"ABC") returns the number of items in multiset in which the item is equal to "ABC".
 // countIf('<',50) returns the number of items in multiset in which the item is less than 50.
 // If op is a character other than '>','=', and '<', then return -1.
 
void Multiset::swap(Multiset& other)
{
    Multimember temp;
    int howManyOriginal;
    int indivCount;
    if (numDiffItems == other.numDiffItems) //If there are the same number of unique elements in both multisets
    {
        indivCount = individual;
        for (int k = 0; k < numDiffItems; k++)
        {
            temp = set[k]; //Send contents to temp
            set[k] = other.set[k]; //Replace with other
            other.set[k] = temp; //Put original in other
        }
        individual = other.individual;
        other.individual = indivCount;
        return;
    }
    else if (numDiffItems < other.numDiffItems) //If this multiset is smaller than the other
    {
        int i;
        indivCount = individual;
        for (i = 0; i < numDiffItems; i++) //For every member in the original multiset
        {
            temp = set[i] ;      //Send the contents to temp
            //Replace that (original) item with one from the other multiset
            set[i] = other.set[i];
            //Done transferring from other multiset--put original values in other
            other.set[i] = temp;
        }
        //Transfer the remaining items
        for (int j = i; j < other.numDiffItems; j++)
        {
            set[j] = other.set[j];
        }
        howManyOriginal = numDiffItems; //Adjust active array size
        numDiffItems = other.numDiffItems;
        other.numDiffItems = howManyOriginal;
        individual = other.individual;
        other.individual = indivCount;
        return;
    }
    else if (numDiffItems > other.numDiffItems) //If this multiset is larger than the other
    {
        int p;
        indivCount = individual;
        for (p = 0; p < other.numDiffItems; p++) //Until the other multiset runs out
        {
            temp = set[p]; //Send the contents to temp
            set[p] = other.set[p]; //Replace original item with one from other multiset
            other.set[p] = temp; //Put original in other
        }
        //Transfer the remaining items
        for (int q = p; q < numDiffItems; q++)
        {
            other.set[q] = set[q];
        }
        howManyOriginal = numDiffItems;
        numDiffItems = other.numDiffItems;
        other.numDiffItems = howManyOriginal;
        individual = other.individual;
        other.individual = indivCount;
        return;
    }
}
 // Exchange the contents of this multiset with the other one.
 
void Multiset::copyIntoOtherMultiset(Multiset &other)
{
    int startCopy = other.numDiffItems; //Start copying here if there are new unique items to add
    for (int i = 0; i < numDiffItems; i++) //For every member of this multiset,
    {
        bool exists = false;
        for (int j = 0; j < other.numDiffItems && exists == false; j++) //check if something already exists in the other multiset
        {
            if (set[i].item == other.set[j].item) //Something exists!
            {
                exists = true; //Mark true to break out of this loop (move on to next item in the multiset)
                other.set[j].count += set[i].count; //Add count to the other multiset's existing item
                other.individual += set[i].count;
            }
        }
        if (exists == false) //Didn't find a matching existing item, so add on to end of other multiset
        {
            other.set[startCopy] = set[i];
            startCopy++;
            other.numDiffItems++;
            other.individual += set[i].count;
        }
    }
        
}
    //
 // Insert all the items into the multiset in other.


