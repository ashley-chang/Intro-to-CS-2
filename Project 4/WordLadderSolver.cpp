// WordLadderSolver.cpp

// This is an incomplete, and thus incorrect, implementation of WordLadderSolver
// functionality.  Your job is to change WordLadderSolverImpl to a correct,
// hopefully efficient, implementation.  You can change it any way you like,
// subject to restrictions in the spec (e.g., that the only C++ library
// containers you are allowed to use are vector, list, stack, and queue (and
// string); if you want anything fancier, implement it yourself).

#include "WordLadderSolver.h"
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

void removeNonLetters(string& s);

//************************
//TODO: Hash table? Maybe declare as private member.
struct HashItem
{
    HashItem(string s); //Constructor
    //string getWord() {return m_word;}
    string m_word;
    bool m_qd; //queued?
};
HashItem::HashItem(string s): m_word(s), m_qd(false)
{}
//*******************************************************************************************************
class HashTable
{
public:
    HashTable();
    void insertHash (HashItem* insert);
    unsigned int hashFunction(string s); //Function to get index in hash table
    HashItem** find(string s); //Returns a pointer to (a pointer to) a Hash
    ~HashTable();
private:
    int MAX_TABLE_SIZE;
    vector<list<HashItem*>> m_buckets; //Vector of lists. This is a hash table!!
};

HashTable::HashTable(): MAX_TABLE_SIZE(100000) //Constructor
{
    m_buckets.resize(MAX_TABLE_SIZE);
}

void HashTable::insertHash(HashItem* insert)
{
    if (find(insert->m_word) != nullptr) //Make sure the word isn't already in the hash table
        return;
    int index = hashFunction(insert->m_word); //First get the index from the hash Function
    m_buckets[index].push_back(insert); //Insert the Hash (contains the string) into that index's bucket->list
}

unsigned int HashTable::hashFunction (string s)
{
    unsigned int hashIndex = 0;
    for (int i = 0; i < s.length(); i++)
    {
        //Add up all ASCII values of chars in string
        hashIndex = hashIndex * 967 + s[i]; //s[i] is typecast to int
    }
    return hashIndex % MAX_TABLE_SIZE;
}

HashItem** HashTable::find(string s)
{
    int findIndex= hashFunction(s); //Calculates the hash index of the provided string
    list<HashItem*>* ptr = &m_buckets[findIndex]; //Pointer to bucket (of pointers to hash items)
    list<HashItem*>::iterator it = ptr->begin(); //Set iterator to beginning of bucket's list
    while (it != ptr->end()) //Traverse through the items in the bucket
    {
        if ((*it)->m_word == s)
        {
            HashItem** found = &*it; //Dereference the iterator..
            return found;
        }
        it++;
    }
    return nullptr; //didn't find string in this bucket
}

HashTable::~HashTable()
{
    for (int i = 0; i < m_buckets.size(); i++)
    {
        list<HashItem*>* ptr = &m_buckets[i];
        list<HashItem*>::iterator it = ptr->begin();
        while (it != ptr->end())
        {
            delete *it;
            it++;
        }
        m_buckets[i].clear();
    }
    m_buckets.clear();
}
//*******************************************************************************************************

  // This class does the real work of the implementation.

class WordLadderSolverImpl
{
  public:
	WordLadderSolverImpl() {}
	~WordLadderSolverImpl() {}
	void createWordList(const vector<string>& words);
	int buildLadder(string start, string end, vector<string>& ladder);
  private:
	  // You probably want something more sophisticated/efficient than this:
	//vector<string> m_words;
    //TODO: probably declare HashTable variable here.
    HashTable m_wordBank;
};

void WordLadderSolverImpl::createWordList(const vector<string>& words)
{
	  // You probably want something more sophisticated/efficient than this;
	  // for one thing, it's horribly slow on a 60,000 word file.

	for (string word : words)
	{
        //TODO: push stuff into the hash table.
        removeNonLetters(word);
        if (!word.empty() && m_wordBank.find(word) == nullptr) //If word is nonempty and is not already in the word bank, insert it into the hash table!
        {
            HashItem* addMe = new HashItem(word);
            m_wordBank.insertHash(addMe);
        }
    }
}
//*******************************************************************************************************
//Word editing functions
string replaceChar(string word, char replace, int index)
{
    if (index > word.size() || index < 0)
        return "";
    word[index] = replace;
    return word;
}
string insertChar(string word, char insert, int index)
{
    if (index > word.size() || index < 0)
        return "";
    word.insert(word.begin()+index, insert);
    return word;
}
string deleteChar(string word, int index)
{
    if (index > word.size() || index < 0)
        return "";
    word.erase(word.begin()+index);
    return word;
}
string swapChar(string word, int index1, int index2)
{
    if (index1 > word.size() || index2 > word.size() || index1 < 0 || index2 < 0)
        return "";
    char temp = word[index1];
    word[index1] = word[index2];
    word[index2] = temp;
    return word;
}
//*******************************************************************************************************

int WordLadderSolverImpl::buildLadder(string start, string end, vector<string>& ladder)
{
	ladder.clear();
    if (m_wordBank.find(start) == nullptr)
        return 1;
    if (m_wordBank.find(end) == nullptr)
        return 2;
    if (start == end)
        return 3;
    
    //If the start word is not in the word list, the function returns 1 and ladder must be empty when the function returns.
    //If the start word is in the word list but the end word isn't, the function returns 2 and ladder must be empty when the function returns.
    //If both words are in the word list and are the same word, the function returns 3 and ladder must be empty when the function returns.
    
    //At this point, both words are in word list and are different. Check for word ladder:
    queue<vector<string>> check;
    //Make the ladder (vector)
    vector<string> init;
    vector<HashItem*> restartMe; //Vector to keep track of things that have been qd
    init.push_back(start);
    
    check.push(init); //Contains first ladder (only one word right now)
    
    
    while (!check.empty())
    {
        vector<string> next = check.front(); //get the next ladder
        check.pop(); //pop the ladder from the queue
        string examine = next.back();
        if (examine == end) //If this ladder has reached the end word, done!
        {
            for (int q = 0; q < restartMe.size(); q++)
            {
                restartMe[q]->m_qd = false; //Set all the things that have been queued back to false, so they can be searched again.
            }
            ladder = next;
            return 0;
        }

        for (int i = 0; i < examine.size(); i++)
        {
            //Letter replacement
            for (char c = 'a'; c <= 'z'; c++) //Replace every letter in the starting word with another from the alphabet
            {
                string temp = replaceChar(examine, c, i);
                if (m_wordBank.find(temp) != nullptr && temp != examine && (*m_wordBank.find(temp))->m_qd == false)
                    //If newly formed word is in dictionary, not the original, and has not been queued yet,
                {
                    vector<string> step = next; //Make a copy of the ladder being examined and add new word
                    step.push_back(temp);
                    (*m_wordBank.find(temp))->m_qd = true; //Don't use same word again
                    restartMe.push_back(*m_wordBank.find(temp));
                    check.push(step); //Push the ladder into the queue to be examined later
                }
            }
            //Letter swapping
            for (int j = 1; j < examine.size(); j++) //Swap characters in every possible combination
            {
                string temp2 = swapChar(examine, i, j);
                if (m_wordBank.find(temp2) != nullptr && temp2!= examine && (*m_wordBank.find(temp2))->m_qd == false)
                {
                    vector<string> step = next;
                    step.push_back(temp2);
                    (*m_wordBank.find(temp2))->m_qd = true;
                    restartMe.push_back(*m_wordBank.find(temp2));
                    check.push(step);
                }
            }
        }
        //Letter addition/ deletion
        for (int i = 0; i <= examine.size(); i++)
        {
            for (char c = 'a'; c <= 'z'; c++) //For every position where a char can be added, try inserting a letter from the alphabet
            {
                string temp = insertChar(examine, c, i);
                if (m_wordBank.find(temp) != nullptr && temp != examine && (*m_wordBank.find(temp))->m_qd == false)
                {
                    vector<string> step = next;
                    step.push_back(temp);
                    (*m_wordBank.find(temp))->m_qd = true;
                    restartMe.push_back(*m_wordBank.find(temp));
                    check.push(step);
                }
            }
            string temp2 = deleteChar(examine, i); //Attempt to delete each of the characters in the word to see if still valid
            if (m_wordBank.find(temp2) != nullptr && temp2 != examine && (*m_wordBank.find(temp2))->m_qd == false)
            {
                vector<string> step = next;
                step.push_back(temp2);
                (*m_wordBank.find(temp2))->m_qd = true;
                restartMe.push_back(*m_wordBank.find(temp2));
                check.push(step);
            }
            
        }
    }
    for (int q = 0; q < restartMe.size(); q++)
    {
        restartMe[q]->m_qd = false; //Set all the things that have been queued back to false, so they can be searched again.
    }
	return -1;
}

void removeNonLetters(string& s)
{
	string::iterator to = s.begin();
	for (char ch : s)
	{
		if (isalpha(ch))
		{
			*to = tolower(ch);
			to++;
		}
	}
	s.erase(to, s.end());  // chop off everything from "to" to end.
} 

//******************** WordLadderSolver functions **********************************

// These functions simply delegate to WordLadderSolverImpl's functions.
// You probably don't want to change any of this code.

WordLadderSolver::WordLadderSolver()
{
	m_impl = new WordLadderSolverImpl;
}

WordLadderSolver::~WordLadderSolver()
{
	delete m_impl;
}

void WordLadderSolver::createWordList(const vector<string>& words)
{
	m_impl->createWordList(words);
}

int WordLadderSolver::buildLadder(string start, string end, vector<string>& ladder)
{
	return m_impl->buildLadder(start, end, ladder);
}
