//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
  
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"
 
using namespace std; 
// function used to evaluate the expression that does not return anything
void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
// function used to evaluate the operands that does not return anything 
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
// function used to discard the expression that does not return anything
void discardExp(ifstream& in, ofstream& out, char& ch);
// function used to print the result that does not return anything
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    // establishes variables
    bool expressionOk;
    char ch;
    stackType<double> stack(100);
    ifstream infile;
    ofstream outfile;
 
    // uploads textfile to be read 
    infile.open("RpnData.txt");

    // if we are not looking at the file
    if (!infile)
    {
        // prints that the file couldn't be opened
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        // terminates program
        return 1;
    }
     
    // allows us to write in this text file
    outfile.open("RpnOutput.txt");
    // sets the floating point value to gather two decimal places
    outfile << fixed << showpoint;
    outfile << setprecision(2); 
    // begins the first expression
    infile >> ch;
    while (infile)
    {
        // initializes the stack
        stack.initializeStack();
        // initialize expressionOk (no error)
        expressionOk = true;
        // begins the first expression
        outfile << ch;
        // calls evaluateExpression 
        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk);
        // calls printResult
        printResult(outfile, stack, expressionOk);
        // begin processing the next expression
        infile >> ch;
    } // end while 

    // closes the files
    infile.close();
    outfile.close();

    return 0;

} // end main


void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;

    // while the character is not the equals symbol
    while (ch != '=')
    {
        // switch the character
        switch (ch)
        {
        // we grab the number
        case '#': 
            inpF >> num;
            outF << num << " ";
            // checks if the stack is full
            if (!stack.isFullStack())
                // if it is not full, we push the number onto the stack
                stack.push(num);
            // if it is full
            else
            {
                // we print a message stating that the stack is full
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                // terminate the program
                exit(0);
            }

            break;
        default: 
            evaluateOpr(outF, stack, ch, isExpOk);
        }// end switch

        // if there is no error
        if (isExpOk)
        {
            // we grab the next character
            inpF >> ch;
            outF << ch;

            // if it is not a nummber
            if (ch != '#')
                // we shift to the left
                outF << " ";
        }
        // if it is a number
        else
            // we call discardExp
            discardExp(inpF, outF, ch);
    } // ends while (!= '=')
} // ends evaluateExp


void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;

    // if the stack is empty
    if (stack.isEmptyStack())
    {
        // we indicate that we do not have enough operands
        out << " (Not enough operands)";
        // indicate that there is an error
        isExpOk = false;
    }
    // if the stack is not empty
    else
    {
        // we put operand two to the top of the stack
        op2 = stack.top();
        // and popping it off
        stack.pop();

        // if the stack is empty
        if (stack.isEmptyStack())
        {
            // we indicate that there are not enough operands
            out << " (Not enough operands)";
            // indicate that there is an error
            isExpOk = false;
        }
        // if the stack is not empty
        else
        {
            // we put operand one on the top of the stack
            op1 = stack.top();
            // pop off the top of the stack
            stack.pop();

            switch (ch)
            {
            // when we see +, we add operand one and two
            case '+': 
                stack.push(op1 + op2);
                break;
            // when we see -, we subtract operand two from one
            case '-': 
                stack.push(op1 - op2);
                break;
            // when we see *, we multiply operand one and two
            case '*': 
                stack.push(op1 * op2);
                break;
            // when we see /, we divide operand one by two (as long as operand two is not zero)
            case '/': 
                if (op2 != 0)
                    stack.push(op1 / op2);
                else
                {
                    out << " (Division by 0)";
                    isExpOk = false;
                }
                break;
            default:  
                out << " (Illegal operator)";
                isExpOk = false;
            }// end switch
        } // end else
    } // end else
} // end evaluateOpr


void discardExp(ifstream& in, ofstream& out, char& ch)
{
    // while the character is the equals symbol
    while (ch != '=')
    {
        // we get the character
        in.get(ch);
        // and shift it to the left
        out << ch;
    }
} // end discardExp

void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    // if there is no error, print the result
    if (isExpOk)
    {
        // if the stack is not empty
        if (!stack.isEmptyStack())
        {
            // the result is located at the top of the stack
            result = stack.top();
            // pop off the top of the stack
            stack.pop();

            // if the stack is empty
            if (stack.isEmptyStack())
            // print out error message
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;
        } // end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} // end printResult
