#include <iostream>
#include<cstdio>
#include <cstring>
#include <QString>
using namespace std;

int main()
{
    while(true)
    {
        unsigned int index;
        char input[10000];
        char str[10000];
        QString convert;
        bool flag;
        try
        {
            cout << "\nEnter text:  ";
            gets(str);
            if (strlen(str) == 0)
                throw invalid_argument("");
	    
            if (strlen(str) > 10000) 
                throw invalid_argument("");


            cout << "\nSelect the position of the desired character in the range from 1 to " << strlen(str) << ": ";
            gets(input);
            if (strlen(input) == 0)
                throw invalid_argument("");

            convert.append(input);
            index = convert.toUInt(&flag);
            if(index > strlen(str) || index == 0 || flag == 0)
                throw invalid_argument("");
        }
        catch (const exception)
        {
            cout << "\n|Search results|";

            continue;
        }

            cout << "\nPosition: " << input << " Has a symbol: " << str[index-1] << "           \n";
            cout << "\nPress enter to continue . . .";
            return 0;
    }
}

