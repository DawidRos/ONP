#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>

bool isSign(const char& s)
{
    if(s=='+'||s=='-'||s=='*'||s=='%'||s=='/'||s=='^')
        return true;
    return false;
}

int priority(const char  ch)
{
    switch (ch)
    {
        case '^' : return 3;
        case '*' :
        case '/' :
        case '%' : return 2;
        case '+' :
        case '-' :
        case ')' : return 1;
        default: return 0;
    }
}

std::stringstream  translate(std::stringstream& input )
{
    std::stringstream output;
    std::string tempStr,ppp;
    char tempChar,tempNext;
    double tempDouble;
    std::stack<char> stackSign;
    std::cout <<input.str()<<std::endl;
    while(input.peek()!=-1)
    {
        tempNext=input.peek();
        if (tempNext== '(')
        {
            stackSign.push('(');
            input>>tempChar;
        }
        else if (tempNext==')')
        {
            while(stackSign.top()!='(')
            {
                output << stackSign.top()<<' ';
                stackSign.pop();
            }
            stackSign.pop();
            input>>tempChar;
        }
        else if(isSign(tempNext))
        {
            if(stackSign.empty()||priority(tempNext)>priority(stackSign.top()))
            {
                input>>tempChar;
                stackSign.push(tempChar);
            }
            else
            {
                while (priority(stackSign.top())>=priority(tempNext))
                {
                    output << stackSign.top()<<' ';
                    stackSign.pop();
                }
                input>>tempChar;
                stackSign.push(tempChar);
            }
        }
        else
        {
            input>>tempDouble;
            output<<tempDouble<<' ';
        }
    }
    while(!stackSign.empty())
    {
        output << stackSign.top()<<' ';
        stackSign.pop();
    }
    return output;
}

void operation(std::stack<double>& sd, char& sign)
{
    double temp_d;
    switch(sign)
    {
        case '+' :
            temp_d=sd.top();
            sd.pop();
            sd.top()+=temp_d;
            break;
        case '-' :
            temp_d=sd.top();
            sd.pop();
            sd.top()-=temp_d;
            break;
        case '*' :
            temp_d=sd.top();
            sd.pop();
            sd.top()*=temp_d;
            break;
        case '/' :
            temp_d=sd.top();
            sd.pop();
            if(static_cast<int>(temp_d)==0)
            {
                std::cout << "Can not divine by 0\nEXIT FAILURE.";
                exit(EXIT_FAILURE);
            }
            sd.top() =sd.top()/ static_cast<int>(temp_d);
            break;
        case '%' :
            temp_d=sd.top();
            sd.pop();
            if(static_cast<int>(temp_d)==0)
            {
                std::cout << "Can not divine by 0\nEXIT FAILURE.";
                exit(EXIT_FAILURE);
            }
            sd.top() =static_cast<int>(sd.top()) % static_cast<int>(temp_d);
            break;
        case '^' :
            temp_d=sd.top();
            sd.pop();
            sd.top()=pow(sd.top(),temp_d);
            break;
    }
}

double calculate (std::stringstream& inPut)
{
    double temp_d;
    char nextInput;
    std::stack<double> stack_double;
    while(inPut.peek()!=-1)
    {
        nextInput=inPut.peek();
        if(isSign(nextInput))
        {
            inPut>>nextInput;
            operation(stack_double,nextInput);
        }
        else if (nextInput==' ')
            inPut.get();
        else
        {
            inPut>>temp_d;
            stack_double.push(temp_d);
        }
    }
    return stack_double.top();
}

int main() {
    std::cout <<"Put equation in standard notation ( allowed sign: ( ) + - / % * ^ ):\n";
    std::string tempStr;
    getline(std::cin,tempStr);
    std::stringstream inSS,outSS;
    inSS<<tempStr;
    outSS=translate(inSS);
    std::cout << "In reverse polish notation:\n"<<outSS.str()<<std::endl;
    std::cout <<"Result: "<<calculate(outSS)<<std::endl;
    return 0;
}