//#include <iostream>
//using namespace std;

int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0) //Found all n2 elements
        return 1; //Found one way that the sequence appears in the array
    if (n1 <= 0) //Got to end of a1 but didn't find all n2
        return 0;
    if (a1[0] == a2[0]) //Found an a2 element
    {
        if (countIncludes(a1+1, n1-1, a2+1, n2-1) != 0)
            return countIncludes(a1+1, n1-1, a2, n2) + countIncludes(a1+1, n1-1, a2+1, n2-1);
        else
            return countIncludes(a1+1, n1-1, a2+1, n2-1);
    }
    else //Keep searching for a2 element
        return countIncludes(a1+1, n1-1, a2, n2);
    
}

void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

void separate(double a[], int n, double separator,
              int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

void order(double a[], int n)
{
    if (n <= 1) //Do nothing
        return;
    int firstNotGreater;
    int firstLess;
    separate(a, n, a[n/2], firstNotGreater, firstLess); //Split bigger/smaller
    order (a, firstNotGreater); //Order first half
    order (a+firstLess, n-firstLess); //Order second half
        
}

