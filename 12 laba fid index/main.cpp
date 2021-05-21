#include <iostream>
#include<cstdio>
#include <cstring>
#include <QString>

using namespace std;

int main()
{
    while(true)
    {
        char symbol[1];
        char str[10000];
        int index[10000];
        int n=0;
        int k=0;

        try
        {
            cout << "\nEnter text:  ";
            gets(str);
            if (strlen(str) == 0)
                throw invalid_argument("");

            if (strlen(str) > 10000) 
                throw invalid_argument("");

            cout << "Enter the symbol you are looking for: ";
            gets(symbol);
            if (strlen(symbol) == 0 || strlen(symbol) > 1)
                throw invalid_argument("");
            for (int i = 0; i < 9999; i++)
            {
                if (symbol[0] == str[i])
                {
                    index[n] = i;
                    n++;
                }
            }
        }
        catch (const exception)
        {
            cout << "\nIncorrect data entered\n";

            continue;
        }
        if (n > 0)
        {
            cout << "\n|Search results|";
            cout << "\nSymbol: " << symbol[0] << " has positions: | ";

            for (int i = 0; i<n; i++)
            {
                cout << index[k]+1 << " | ";
                k++;
            }
            cout << "\n";
        }
        else
        {
            cout << "\n|Search results|";
            cout << "\nSymbol: " << symbol[0] << " not found";
            cout << "\n";
        }

        cout << "\nPress enter to continue . . .";
        return 0;
    }
}

