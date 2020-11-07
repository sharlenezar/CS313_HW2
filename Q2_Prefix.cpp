#include <bits/stdc++.h>
using namespace std;

// expression that checks if each character is a digit and returns a boolean
bool
isOperand (char c)
{
  // if the character is a digit then it must be an operand 
  return isdigit (c);
}

// function that is used to evalute the prefix and returns a double
double
calculate (string expression)
{
  //establishes a stack containing double values
  stack < double >Stack;

  // for loop that iterates through the entire expression
  for (int i = expression.size () - 1; i >= 0; i--)
    {

      // pushes operand to Stack 
      // checks if we are working with a digit
      if (isOperand (expression[i]))
	// converts expression[i] to a digit by subtracting '0' from it
	Stack.push (expression[i] - '0');

      // the else indicates that we are working with an operator
      else
	{

	  // pops two elements from Stack 
	  double opOne = Stack.top ();
	  Stack.pop ();
	  double opTwo = Stack.top ();
	  Stack.pop ();

	  // uses switch case to operate on opOne and opTwo 
	  // performs opOne O opTwo. 
	  switch (expression[i])
	    {
	    case '+':
	      Stack.push (opOne + opTwo);
	      break;
	    case '-':
	      Stack.push (opOne - opTwo);
	      break;
	    case '*':
	      Stack.push (opOne * opTwo);
	      break;
	    case '/':
	      Stack.push (opOne / opTwo);
	      break;
	    }
	}
    }

  return Stack.top ();
}

// tests our work in main 
int
main ()
{
  string expression = "+9*26";
  cout << calculate (expression) << endl;
  return 0;
}
