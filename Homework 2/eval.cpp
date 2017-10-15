//
//  eval.cpp
//  Homework2
//
//  Created by Ashley Chang on 7/9/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#include <stack>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int givePrecedence (char oper);
bool higherPrecedence (char first, char second);
bool checkTrueFalse (char tf);
char doCalculation (const char &first, const char &second, char oper, char& result);
bool validChar (char ch); //Returns true if the character is valid, false if anything else
bool isValidInfix (const string& infix);
string conversion (const string& infix, string& postfix);
int evaluate (string infix, string& postfix, bool& result);

int main () {
    string a = "(T&F)|(T)|(!T)& !F & !!!!T";
    string b;
    bool c;
    cout << conversion(a,b) << endl;
    cout << evaluate(a,b,c) << endl;
    cout << "result is: " << c;
    
}

int evaluate(string infix, string& postfix, bool& result) //Evaluates valid infix
{
    if (infix == "") //If nothing in the string, invalid
        return 1;
    stack<char> operstack;
    string conv = conversion (infix, postfix); //Convert infix to postfix
    if (conv == "invalid")
        return 1;
    postfix = conv; //Set postfix
    for (int i = 0; i < postfix.size(); i++) //Evaluate the postfix!
    {
        switch (postfix[i])
        {
            case 'T': //If the character is an operand, push into operand stack
            case 't':
            case 'F':
            case 'f':
                operstack.push(postfix[i]);
                break;
            case '!': //If unary operator, apply to following operand
            {
                char getter = operstack.top();
                operstack.pop();
                char result1 = doCalculation(getter, getter, postfix[i], result1);
                operstack.push(result1);
                break;
            }
            case '|': //If binary operator, apply to surrounding operands
            case '&':
            {
                char getter1 = operstack.top();
                operstack.pop();
                char getter2 = operstack.top();
                operstack.pop();
                char result2 = doCalculation(getter1, getter2, postfix[i], result2);
                operstack.push(result2);
                break;
            }
            default:
                break;
        }
    }
    char answer = operstack.top(); //Get the result
    operstack.pop();
    if (answer == 'T') //If remaining character is a T, return true
        result = true;
    else if (answer == 'F') //If remaining character is a F, return true
        result = false;
    return 0;
}



bool isValidInfix (const string& infix) //Check that the infix is properly formatted and has acceptable characters
{
    int parenCheck = 0;
    
    string noSpaces;
    int operands = 0;
    int operators = 0;
    //Check to see if all characters are valid and reform the infix without spaces
    for (int i = 0; i < infix.size(); i++)
    {
        if (!validChar(infix[i]))
            return false;
        else if (validChar(infix[i]) && infix[i] != ' ')
            noSpaces += infix[i]; //Add to string that creates space-less infix
        if (isalpha(infix[i]))
            operands++;
        else if (infix[i] == '&' || infix[i] == '|')
            operators++;
        else if (infix[i] == '(')
            parenCheck++;
        else if (infix[i] == ')')
            parenCheck--;
    }
    //Checking format
    if (parenCheck != 0) //If parentheses are not all closed, return false
        return false;
    if ((operands > 1 && operators == 0) || operands == 0) //If not enough operands/operators, return false
        return false;
    for (int k = 0; k < noSpaces.size(); k++)
    {
        if (noSpaces[k] == '&' || noSpaces[k] == '|') //Binary operators
        {
            //Check if there are valid operands on both sides
            if ((!isalpha(noSpaces[k-1]) && noSpaces[k-1] != ')')
                //If Previous char is not T/F or )
                || (noSpaces[k+1] != '!' && !isalpha(noSpaces[k+1]) && noSpaces[k+1] != '(')
                //Following char is not ! or T/F or (
                || (k+1 >= noSpaces.size())) //Reached end of infix...
                return false;
        }
        else if (isalpha(noSpaces[k]) && (isalpha(noSpaces[k-1]) || isalpha(noSpaces[k+1]))) //if more than one T/F character in a row,
            return false;
        else if (noSpaces[k] == '!') //If character following unary operator is invalid, return false
        {
            switch (noSpaces[k+1])
            {
                case '!':
                case 'T':
                case 't':
                case 'F':
                case 'f':
                case '(':
                    break;
                default:
                    return false;
            }
        }
        
        if (noSpaces[k] == '(') //If encounter an opening parentheses
        {
            if (isalpha(noSpaces[k-1])) //and the previous character is T or F, return false
                return false;
        }
    }
    char end = noSpaces[noSpaces.size()-1]; //If the ending character is an operator, return false
    if (end == '&' || end == '|' || end == '!')
        return false;
    return true;
}


string conversion(const string& infix, string& postfix) //conversion helper function
{
    if ((infix == "") || !isValidInfix(infix)) //Check for infix validity
        return "invalid";
    postfix = ""; //Initiate postfix to empty
    stack<char> operstack;
    for (int i = 0 ; i < infix.size(); i++) //For every character of the infix,
    {
        switch (infix[i])
        {
            case 'T': //If encounter an operand, add to postfix string
            case 't':
            case 'F':
            case 'f':
                postfix += infix[i];
                break;
            case '(': //If encounter opening parenthesis, push onto operator stack
                operstack.push('(');
                break;
            case ')': //If encounter closing parenthesis,
                while (operstack.top() != '(' && !operstack.empty()) //Pop operators in stack until find opening parenthesis
                {
                    postfix += operstack.top();
                    operstack.pop();
                }
                operstack.pop(); //should pop the '('
                break;
            case ' ': //Ignore spaces
                break;
            case '!': //If encounter ! operator, just push (precedence)
                operstack.push(infix[i]);
                break;
            case '|': //If encounter binary operator,
            case '&':
                while (!operstack.empty() && operstack.top() != '(' && !higherPrecedence(infix[i], operstack.top()))
                    //Pop operators in stack until find another with higher precedence or encounter '('
                {
                    postfix += operstack.top();
                    operstack.pop();
                }
                operstack.push(infix[i]);
                break;
            default:
                break;
        }
    }
    while (!operstack.empty()) //Pop the remaining operators in the stack and attach to postfix
    {
    postfix += operstack.top();
    operstack.pop();
    }
    return postfix;
}

int givePrecedence (char oper) //Determines precedence of an operator
{
    if (oper == '|')
        return 1; //Least precedence
    else if (oper == '&')
        return 2;
    else if (oper == '!')
        return 3; //Most precedence
    else
        return 0;
}

bool higherPrecedence (char first, char second) //Checks precedence, then checks which is higher
{
    int check1 = givePrecedence (first);
    int check2 = givePrecedence (second);
    if (check1 > check2)
        return true;
    else
        return false;
}

bool checkTrueFalse (char tf) //Checks whether or not character is T or F..
//Must only be used after validating all characters!!
{
    if (tf == 'T' || tf == 't')
        return true;
    else
        return false;
}

char doCalculation (const char &first, const char &second, char oper, char& result) //Takes two inputs and calculates using the operator
{
    if (oper == '!') //Unary operator, so only need one parameter
    {
        if (checkTrueFalse(first)) // Calculates !T
        {
            return result = 'F';
        }
        else if (!checkTrueFalse(first)) //Calculates !F
        {
            return result = 'T';
        }
    }
    else if (oper == '&') //Binary operator &
    {
        if (!checkTrueFalse(first) || !checkTrueFalse(second)) //If either operand is false, return false
        {
            return result = 'F';
        }
        else if (checkTrueFalse(first) && checkTrueFalse(second)) //If both operands are true, return true
        {
            return result = 'T';
        }
        
    }
    else if (oper == '|') //Binary operator |
    {
        if (checkTrueFalse(first) || checkTrueFalse(second)) //If either operand is true, return true
        {
            return result = 'T';
        }
        else if (!checkTrueFalse(first) && !checkTrueFalse(second)) //If both operands are false, return false
        {
            return result = 'F';
        }
    }
    return result;
    
    
}

bool validChar (char ch) //Returns true if the character is valid, false if anything else
{
    switch (ch)
    {
        case '(':
        case ')':
        case 'T':
        case 't':
        case 'F':
        case 'f':
        case '!':
        case '&':
        case '|':
        case ' ':
            return true;
        default:
            return false;
    }
}

 

