/*
    Finvest_API.cpp
    * API test program
    * author: Finvest
    * jag9123@gmail.com
*/


#include <iostream>
#include "DBHelper.h"

#define LINE "--------------------------------------------------"

using namespace std;

void SelectMenu(int menunum);
void SetMainStock();
DBHelper db_helper;

int main()
{
    int menu_num = 0;

    cout << LINE << endl;
    cout << "Database API Test Program" << endl;
    cout << LINE << endl;
    SetMainStock();

    while(menu_num != 6) 
    {
        cout << LINE << endl;
        cout << "Select Menu \n";
        cout << "1. Change Stock" << endl;
        cout << "2. Get Today Close" << endl;
        cout << "3. Get Previous Close" << endl;
        cout << "6. Exit" << endl;
        cin >> menu_num;
        cout << LINE << endl;
        SelectMenu(menu_num);
    }
    return 0;
}

void SelectMenu(int menunum)
{
    string name;
    string code;
    int close;
    int number;

    switch(menunum)
    {
        case 1:
            cout << "1. Change Stock" << endl;
            SetMainStock();
        break;

        case 2:
            cout << "2. Get Today Close" << endl;
            cout << "executing...";
            close = db_helper.GetClose();
            if(close != 1)
            {
                cout << "\r" << "Close:\t" << close << endl;
            }
            else
            {
                cout << "\rThere are no result." << endl;
            }
        break;

        case 3:
            cout << "3. Get Before Cloase" << endl;
            cout << "enter the number: ";
            cin >> number;
            cout << db_helper.GetPrevClose(number) << endl;
        break;

        case 6:
            cout << "Good Bye" << endl;
            db_helper.~DBHelper();
        break;
    }
}

void SetMainStock()
{
    string name;

    cout << "enter the stock name: ";
    cin >> name;
    db_helper.SetStock(name);
    cout << "You choose the " << name << "(" << db_helper.GetStockCode() << ")" << endl;
}