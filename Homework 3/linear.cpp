//
//  linear.cpp
//  Homework3
//
//  Created by Ashley Chang on 7/20/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

//#include <cctype>
//#include <iostream>

// Return true if any of the chars in the array is lowercase, false
// otherwise.
bool anyLowercase(const char a[], int n)
{
    if (n <= 0)
        return false;
    if (islower(a[0]))
        return true;
    return anyLowercase(a+1, n-1);

}

// Return the number of lowercase chars in the array.
int countLowercase(const char a[], int n)
{
    if (n <= 0)
        return 0;
    if (islower(a[0]))
        return countLowercase(a+1, n-1) + 1;
    else
        return countLowercase(a+1, n-1);
        
}

// Return the subscript of the first lowercase char in the array.
// If no element is lowercase, return -1.
int firstLowercase(const char a[], int n)
{
    if (n <= 0)
        return -1;
    if (islower(a[0])) //Lowercase, so start going back
        return 0;
    int lc = firstLowercase(a+1, n-1);
    if (lc == -1) //No lowercase found, so return (-1) before it gets to "else"
        return -1;
    else //Not lowercase, so keep going / add one to account for index on the way back
        return lc + 1;
}



// Return the subscript of the least char in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].)  If the array has no elements to examine, return -1.
int indexOfLeast(const char a[], int n)
{
    if (n <= 0)
        return -1;
    //if (n == 1)
      //  return 0;
    int least = indexOfLeast(a+1, n-1) + 1;
    if (a[least] < a[0])
        return least;
    else
        return 0;
  
}

//int main()
//{
//    char a[4];
//    a[0] = 'A';
//    a[1] = 'd';
//    a[2] = 'f';
//    a[3] = 'b';
//    std::cout << indexOfLeast(a, 4);
//}

