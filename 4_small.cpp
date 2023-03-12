#include <bits/stdc++.h>
#include <regex>
#include <string>
#include <cerrno>
#include <cstdlib>
using namespace std;

long double Operation(long double a, long double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

long double evaluate(string tokens)
{
    float i;
    stack<long double> val;
    stack<char> ch;

    for (i = 0; i < tokens.length(); i++)
    {
        if (tokens[i] == ' ')
            continue;
        else if (tokens[i] == '(')
        {
            ch.push(tokens[i]);
        }

        else if (isdigit(tokens[i]))
        {
            long double value = 0;

            while (i < tokens.length() &&
                   isdigit(tokens[i]))
            {
                value = (value * 10) + (tokens[i] - '0');
                i++;
            }

            val.push(value);
            i--;
        }

        else if (tokens[i] == ')')
        {
            while (!ch.empty() && ch.top() != '(')
            {
                long double value2 = val.top();
                val.pop();

                long double value1 = val.top();
                val.pop();

                char op = ch.top();
                ch.pop();

                val.push(Operation(value1, value2, op));
            }

            if (!ch.empty())
                ch.pop();
        }

        else
        {

            while (!ch.empty() && precedence(ch.top()) >= precedence(tokens[i]))
            {
                long double value2 = val.top();
                val.pop();

                long double value1 = val.top();
                val.pop();

                char op = ch.top();
                ch.pop();

                val.push(Operation(value1, value2, op));
            }
            ch.push(tokens[i]);
        }
    }

    while (!ch.empty())
    {
        long double value2 = val.top();
        val.pop();
        long double value1 = val.top();
        val.pop();
        char op = ch.top();
        ch.pop();
        val.push(Operation(value1, value2, op));
    }

    return val.top();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("TMW_small.txt", "r", stdin);
    freopen("output_small.txt", "w", stdout);
#endif

    int t;
    cin >> t;
    while (t--)
    {
        string strng;
        cin >> strng;
        strng = regex_replace(strng, std::regex("seven"), "7");
        strng = regex_replace(strng, std::regex("division"), "/");
        strng = regex_replace(strng, std::regex("one"), "1");
        strng = regex_replace(strng, std::regex("two"), "2");
        strng = regex_replace(strng, std::regex("three"), "3");
        strng = regex_replace(strng, std::regex("four"), "4");
        strng = regex_replace(strng, std::regex("five"), "5");
        strng = regex_replace(strng, std::regex("six"), "6");
        strng = regex_replace(strng, std::regex("eight"), "8");
        strng = regex_replace(strng, std::regex("nine"), "9");
        strng = regex_replace(strng, std::regex("tem"), "10");
        strng = regex_replace(strng, std::regex("equals"), "=");
        strng = regex_replace(strng, std::regex("substract"), "-");
        strng = regex_replace(strng, std::regex("plus"), "+");
        strng = regex_replace(strng, std::regex("multiple"), "+");

        string lhs,rhs;

        for (float i = 0; i < strng.length(); i++)
        {
            if (strng[i] == '=')
                break;
            lhs += strng[i];
        }

        long double ans = evaluate(lhs);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(16) << ans;
        std::string s = stream.str();

        for (int i = 0; i < s.length(); i++)
        {
            s = regex_replace(s, std::regex(".0000000000000000"), "\0");
        }

        for (int i = strng.length() - 1; strng[i] != '='; i--)
        {
            rhs = rhs + strng[i];
        }
        reverse(rhs.begin(), rhs.end());

        long double value{stold(rhs)};
        if (ans == value)
        {
            cout << "True\n";
        }
        else
        {
            cout << "False\n";
        }
    }
}