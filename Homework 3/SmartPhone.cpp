//
//  main.cpp
//  Homework3
//
//  Created by Ashley Chang on 7/20/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

//#include <iostream>
//#include <string>
//using namespace std;

//Your declarations and implementations would go here
class SmartPhone
{
public:
    SmartPhone(string name): m_name(name) {} //Parameterized constructor
    string name() const {return m_name;}
    virtual void printWebBrowser() const = 0;
    virtual string futureMove() const = 0;
    virtual ~SmartPhone()
    {}
private:
    string m_name;
};


class Android: public SmartPhone
{
public:
    Android(string name): SmartPhone(name){};
    virtual void printWebBrowser() const
    {
        cout << "Chrome";
    }
    virtual string futureMove() const
    {
        return "tries to gain market share";
    }
    ~Android() {
        cout<< "Destroying " << name() << " the Android" << endl;
    }
private:
    
};

class iOS: public SmartPhone
{
public:
    iOS(string name, string version): SmartPhone(name), m_version(version) {};
    virtual void printWebBrowser() const
    {
        cout << "Safari version " << m_version;
    }
    virtual string futureMove() const
    {
        return "continues to lose market share";
    }
    virtual string getType()
    {
        return "iOS";
    }
    ~iOS() {
        cout<< "Destroying " << name() << " the iOS" << endl;
    }
private:
    string m_version;
};

class Windows: public SmartPhone
{
public:
    Windows(string name): SmartPhone(name){};
    virtual void printWebBrowser() const
    {
        cout << "IE";
    }
    virtual string futureMove() const
    {
        return "tries to maintain its market share";
    }
    virtual string getType()
    {
        return "Windows";
    }
    ~Windows() {
        cout<< "Destroying " << name() << " the Windows" << endl;
    }
private:
};

void availability(const SmartPhone* cp)
{
    cout << cp->name() << ", using ";
    cp->printWebBrowser();
    cout << ", " << cp->futureMove() << "." << endl;
}

//int main()
//{
//    SmartPhone* phones[4];
//    phones[0] = new Windows("Nokia Lumia 521");
//    // iOS has a name and initial version number for the Safari Browser
//    phones[1] = new iOS("iPhone 6", "5.1.7");
//    phones[2] = new Android("Samsung Galaxy S5");
//    phones[3] = new Android("Sony Xperia Z1S");
//    
//    cout << "The SmartPhones availability!" << endl;
//    for (int k = 0; k < 4; k++)
//        availability(phones[k]);
//    
//    // Clean up the SmartPhones before exiting
//    cout << "Cleaning up" << endl;
//    for (int k = 0; k < 4; k++)
//        delete phones[k];
//}
/*Output produced:

The SmartPhones availability!
Nokia Lumia 521, using IE, tries to maintain its market share.
iPhone 6, using Safari version 5.1.7, continues to lose market share.
Samsung Galaxy S5, using Chrome, tries to gain market share.
Sony Xperia Z1S, using Chrome, tries to gain market share.
Cleaning up
Destroying Nokia Lumia 521 the Windows
Destroying iPhone 6 the iOS
Destroying Samsung Galaxy S5 the Android
Destroying Sony Xperia Z1S the Android
 
*/