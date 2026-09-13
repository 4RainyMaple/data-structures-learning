#include"stack.h"
#include<iostream>
#include<string>

bool StringIsBalance( const std::string & str )
{
    Stack <char> stk;
    for ( size_t i = 0; i < str.size(); ++i )
    {
        if ( str[i] == '(' || str[i] == '[' || str[i] == '{')
            stk.push(str[i]);

        else 
        {
            if ( stk.empty() )
                return false;
            else if (   ( stk.top() == '(' && str[i] == ')' ) ||
                        ( stk.top() == '[' && str[i] == ']' ) ||
                        ( stk.top() == '{' && str[i] == '}' )   )
                stk.pop();
            else 
                return false;
        }
    }
    return stk.empty();     //再查空防止全是开放符号的情况
}

int main()
{
    std::string str;
    std::cin >> str;
    if ( StringIsBalance(str) )
        std::cout << "str is balance "<<std::endl;
    else 
        std::cout << "str is not balance "<<std::endl;
}