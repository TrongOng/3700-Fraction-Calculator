#include <iostream>
#include "stack.h"
#include "dictionary.h"
#include <string>

using namespace std;

struct value {
    string
        name;
    Fraction
        num;
};

Stack<value> numStack;
Stack<char> opStack;
Dictionary holder;

bool isOperator(char);
bool hasPrecedence(char, char);
void evaluate(string);
Fraction doOperation(value, value);

int main() {
    string s;
    cout << "Enter Equation" << endl;
    getline(cin, s);
    while (s != "#") {
        evaluate(s);
        getline(cin, s);
    }
    return 0;
}
bool isOperator(char s) {
    if (s == '*' || s == '+' || s == '-' || s =='/' || s=='=') {
        return true;
    }
    else {
        return false;
    }
}
bool hasPrecedence(char a, char b) {
    if (a == '*' || a == '/') {
        return true;
    }
    if (a == '(' || a == '=' || a == '$') {
        return false;
    }
    return b == '+' || b == '-' || b == '=';
}

void evaluate(string s) {

    //clear numStack
    numStack.clear();
    //clear opStack
    opStack.clear();
    //push $ to opStack
    opStack.push('$');
    //first <-- 0
    int first = 0;
    value values;
    value right;
    value left;
    
    //while first < s.length do
    while (first < s.length()) {
        //if s[first] is a digit then
        if (isdigit(s[first])) {
            //convert digit sequence into fraction
            values.name = "";
            values.num = 0;
            while (isdigit(s[first])) {
                values.num = values.num*10+(s[first] - '0');
                //advance first to first character past digit sequence
                first++;
            }
            //store fraction object into struct and push numStack
            numStack.push(values);
        }
        else if (isalpha(s[first])) {
            values.name = "";
            values.num = 0;
            //extract name into string
            while (isalpha(s[first])) {
                //store name in structure
                values.name = values.name + s[first];
                //advance first to first character past name
                first++;
            }
            //push onto numStack
            numStack.push(values);
            
        }
        //else if s[first] is a letter then
        else if (s[first] == '(') {
            //push ( onto opStack
            opStack.push('(');
            //increment first
            first++;
        }
        //else if s[first] is ) then
        else if (s[first] == ')') {
            //while top of opStack is not ( do
            while (opStack.peek() != '(') {
                //perform top operation
                right = numStack.pop();
                left = numStack.pop();
                values.num = doOperation(left, right);
                numStack.push(values);
                //end while loop
            }
            //pop ( from top of numStack? opStack?
            if (opStack.peek() == '(') {
                opStack.pop();
            }
            first++;
        }
        //else if s[first] is an operator then
        else if (isOperator(s[first])) { 
            //while top of opStack has precedence over s[first] do
            while (hasPrecedence(opStack.peek(), s[first])) {
                right = numStack.pop();
                left = numStack.pop();
                //perform top operation
                values.num = doOperation(left, right);
                numStack.push(values);
                //end while loop
            }
            //push s[first] onto opStack
            opStack.push(s[first]);
            first++;
        }
        else {
            //first++;
        }
    }
    //cout << numStack.peek().num << "top of numStack" << endl;
    while (opStack.peek() != '$') {
        //perform top operation
        right = numStack.pop();
        left = numStack.pop();
        values.num = doOperation(left, right);
        numStack.push(values);

    }
    //output top of numStack
    cout << numStack.peek().num << endl;
    //cout << opStack.peek() << endl;

}
Fraction doOperation(value l, value r) {
    value answer;
    answer.name = "";
    answer.num = 0;
    if (opStack.peek() == '*') {
        if (l.num != 0 && r.num != 0) {
            opStack.pop();
            answer.num = l.num*r.num;
        }
        else if (l.name !="" || r.name !="") {
            opStack.pop();
            if (holder.search(l.name) != 0 && r.num != 0) {
                l.num = holder.search(l.name);
                answer.num = l.num*r.num;
            }
            else if (holder.search(r.name) != 0 && l.num != 0) {
                r.num = holder.search(r.name);
                answer.num = l.num*r.num;
            }
        }
        else if (l.num == 0 || r.num == 0) {
            opStack.pop();
            answer.num = 0;
        }
    }
    else if (opStack.peek() == '/') {
        if (l.num != 0 && r.num != 0) {
            opStack.pop();
            answer.num = l.num/r.num;
        }
        else if (l.name !="" || r.name !="") {
            opStack.pop();
            if (holder.search(l.name) != 0 && r.num != 0) {
                l.num = holder.search(l.name);
                answer.num = l.num/r.num;
            }
            else if (holder.search(r.name) != 0 && l.num != 0) {
                r.num = holder.search(r.name);
                answer.num = l.num/r.num;
            }
        }
        else if (l.num == 0 || r.num == 0) {
            opStack.pop();
            answer.num = 0;
        }
    }
    else if (opStack.peek() == '+') {
        if (l.num != 0 && r.num != 0) {
            opStack.pop();
            answer.num = l.num+r.num;
        }
        else if (l.name !="" || r.name !="") {
            opStack.pop();
            if (holder.search(l.name) != 0 && r.num != 0) {
                l.num = holder.search(l.name);
                answer.num = l.num+r.num;
            }
            else if (holder.search(r.name) != 0 && l.num != 0) {
                r.num = holder.search(r.name);
                answer.num = l.num+r.num;
            }
        }
        else if (l.num == 0 || r.num == 0) {
            opStack.pop();
            answer.num = l.num+r.num;
        }
    }
    else if (opStack.peek() == '-') {
        if (l.num != 0 && r.num != 0) {
            opStack.pop();
            answer.num = l.num-r.num;
        }
        else if (l.name !="" || r.name !="") {
            opStack.pop();
            if (holder.search(l.name) != 0 && r.num != 0) {
                l.num = holder.search(l.name);
                answer.num = l.num-r.num;
            }
            else if (holder.search(r.name) != 0 && l.num != 0) {
                r.num = holder.search(r.name);
                answer.num = l.num-r.num;
            }
        }
        else if (l.num == 0 || r.num == 0) {
            opStack.pop();
            answer.num = l.num-r.num;
        }
    }
    //if the operator is =, left must be a variable name. use as key and right operant is a value; store in dictionary (bug)
    else if (opStack.peek() == '=') {
        opStack.pop();
        answer.num = r.num;
        if (l.name != "") {
            //cout << l.name << " variable" << endl;
            holder.add(l.name, answer.num);
        }
    }
   //Fraction variable = holder.search(l.name);
    //cout << variable << "dictionary" << endl;

    return answer.num;
}