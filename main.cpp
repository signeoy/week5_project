// CPP program to convert infix to prefix
#include <bits/stdc++.h>
using namespace std;

bool isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

string infixToPostfix(string infix)
{
    infix = '(' + infix + ')';
    int l = infix.size();
    stack<char> char_stack;
    string output;

    for (int i = 0; i < l; i++) {

        // If the scanned character is an
        // operand, add it to output.
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];

            // If the scanned character is an
            // ‘(‘, push it to the stack.
        else if (infix[i] == '(')
            char_stack.push('(');

            // If the scanned character is an
            // ‘)’, pop and output from the stack
            // until an ‘(‘ is encountered.
        else if (infix[i] == ')') {
            while (char_stack.top() != '(') {
                //adds operands to output
                output += char_stack.top();
                char_stack.pop();
            }

            // Remove '(' from the stack
            char_stack.pop();
        }

            // Operator found
        else
        {
            //output += ' ';
            if (isOperator(char_stack.top()))
            {
                if(infix[i] == '^')
                {
                    while (getPriority(infix[i]) <= getPriority(char_stack.top()))
                    {
                        //adds priority operands to output
                        output += char_stack.top();
                        char_stack.pop();
                    }
                }
                else
                {
                    while (getPriority(infix[i]) < getPriority(char_stack.top()))
                    {
                        output += char_stack.top();
                        char_stack.pop();
                    }

                }

                // Push current Operator on stack
                char_stack.push(infix[i]);
            }
        }
    }
    while(!char_stack.empty()){
        output += char_stack.top();
        char_stack.pop();
    }
    return output;
}

string infixToPrefix(string infix)
{
    /* Reverse String
     * Replace ( with ) and vice versa
     * Get Postfix
     * Reverse Postfix  *  */
    int l = infix.size();

    // Reverse infix
    reverse(infix.begin(), infix.end());

    // Replace ( with ) and vice versa
    for (int i = 0; i < l; i++) {

        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    string prefix = infixToPostfix(infix);

    // Reverse postfix
    reverse(prefix.begin(), prefix.end());

    return prefix;
}
bool isOperand(char c)
{
    // If the character is a digit then it must
    // be an operand
    return isdigit(c);
}
double evaluatePrefix(string exprsn)
{
    stack<double> Stack;

    for (int j = exprsn.size() - 1; j >= 0; j--) {

        // Push operand to Stack
        // To convert exprsn[j] to digit subtract
        // '0' from exprsn[j].
        if (isOperand(exprsn[j]))
            Stack.push(exprsn[j] - '0');

        else {

            // Operator encountered
            // Pop two elements from Stack
            double o1 = Stack.top();
            Stack.pop();
            double o2 = Stack.top();
            Stack.pop();

            // Use switch case to operate on o1
            // and o2 and perform o1 O o2.
            switch (exprsn[j]) {
                case '+':
                    Stack.push(o1 + o2);
                    break;
                case '-':
                    Stack.push(o1 - o2);
                    break;
                case '*':
                    Stack.push(o1 * o2);
                    break;
                case '/':
                    Stack.push(o1 / o2);
                    break;
            }
        }
    }

    return Stack.top();
}

bool isRight(string s){
    for (int i = 0; i < s.length(); ++i) {
        if (reinterpret_cast<const char *>(s[i]) == "+" && reinterpret_cast<const char *>(s[i+1]) == "+" || reinterpret_cast<const char *>(s[i]) == "-" && reinterpret_cast<const char *>(s[i+1]) == "-" || reinterpret_cast<const char *>(s[i]) == "*" && reinterpret_cast<const char *>(s[i+1]) == "*" || reinterpret_cast<const char *>(s[i]) == "/" && reinterpret_cast<const char *>(s[i+1]) == "/" || reinterpret_cast<const char *>(s[i]) == "^" && reinterpret_cast<const char *>(s[i+1]) == "^"){
            return false;
        }
    }
    return true;
}

int main()
{
    string infix, prefix;
    stack<char> stack;
    int index = 1;


    while (index != 0){
        cout << "\nPress 1 to convert infix to prefix\nPress 2 to calculate infix equations\nPress 3 to exit the program" << endl;
        cin >> index;
        if (index == 1){

            cout << "Enter a Infix Expression :" << endl;
            cin >> infix;
            if (isRight(infix)){
                cout << "Invalid expression" << endl;
                return -1;
            }

            cout << "INFIX EXPRESSION: " << infix << endl;
            prefix = infixToPrefix(infix);
            cout << "PREFIX EXPRESSION: " << prefix << endl;

        }
        else if (index == 2){
            cout << "Enter a Infix Expression :" << endl;
            cin >> infix;
            cout << "INFIX EXPRESSION: " << infix << endl;
            prefix = infixToPrefix(infix);
            cout << "PREFIX EXPRESSION: " << prefix << endl;

            cout << evaluatePrefix(prefix) << endl;

        }
        else if (index == 3){
            cout << "EXITING PROGRAM..." << endl;
            break;
        }
        else {
            cout << "INVALID CHOICE. RETURNED TO MENU" << endl;
        }
    }
    return 0;
}