#include <iostream>
#include<cstdio>
#include <cstring>
#include <QString>
#include <math.h>
#include <cmath>

using namespace std;

int main()
{
    while(true)
    {
        double op1, op2, res;
        char input1[10000], input2[10000];
        QString conver1, conver2, converCalc;
        bool flag1, flag2;
        char calc[100];
        int errorCode=9;


        try
        {
            cout << "\nEnter the first operand:";
            gets(input1);

            conver1.append(input1);
            op1 = conver1.toDouble(&flag1);
            if(flag1 == 0)
            {
                errorCode = 1;
                throw invalid_argument("");
            }

            cout << "\nEnter the second operand: ";
            gets(input2);
            conver2.append(input2);
            op2 = conver2.toDouble(&flag2);
            if(flag2 == 0)
            {
                errorCode = 2;
                throw invalid_argument("");
            }

            cout << "Existing operations: | + | - | * | / |\nChoose one of them to calculate: ";
            gets(calc);

            QString(converCalc) = calc;
            if (strlen(calc) != 1)
            {
                errorCode = 3;
                throw invalid_argument("");
            }
            else
            {
                if (converCalc != "+")
                {
                    if (converCalc != "-")
                    {
                        if (converCalc != "*")
                        {
                            if (converCalc != "/")
                            {
                                errorCode = 3;
                                throw invalid_argument("");
                            }
                            else if (op2 != 0)
                                if (op1 == 0)
                                    res = 0;
                                else
                                    res = op1 / op2;
                            else
                            {
                                errorCode = 4;
                                throw invalid_argument("");
                            }
                        }
                        else
                            res = op1 * op2;
                    }
                    else
                        res = op1 - op2;
                }
                else
                    res = op1 + op2;
            }
            if (isinf(res))
            {
                errorCode = 5;
                throw invalid_argument("");
            }


        }
        catch (const exception)
        {
            if (errorCode == 1)
            {
                cout << "\n|incorrect input of the first operand|";
            }
            if (errorCode == 2)
            {
                cout << "\n|incorrect input of the second operand|";
            }
            if (errorCode == 3)
            {
                cout << "\n|incorrect choice of operation|";
            }
            if (errorCode == 4)
            {
                cout << "\n|division by zero is prohibited|";
            }
            if (errorCode == 5)
            {
                cout << "\n|The result is out of range|";
            }

            continue;
        }

        cout << "\n|Result|";
        cout << "\n " << op1 << " " << calc << " " << op2 << " = " << round(res*100000)/100000 << "\n";
        cout << "\nPress to continue ENTER . . .";
        return 0;
    }
}

