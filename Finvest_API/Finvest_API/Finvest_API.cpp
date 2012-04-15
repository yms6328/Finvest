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

    while(menu_num != -1) 
    {
        cout << LINE << endl;
        cout << "Select Menu \n";
        cout << "1. Change Stock" << endl;
        cout << "2. Get Today Close" << endl;
        cout << "3. Get Previous Close" << endl;
        cout << "4. Get Today Open" << endl;
        cout << "5. Get Previous Open" << endl;
        cout << "6. Get Today High" << endl;
        cout << "7. Get Previous High" << endl;
        cout << "8. Get Today Low" << endl;
        cout << "9. Get Previous Low" << endl;
        cout << "-1. Exit" << endl;
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
    int data;
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
            data = db_helper.GetClose();
            if(data != 1)
            {
                cout << "\r" << "Close:\t" << data << endl;
            }
            else
            {
                cout << "\rThere are no result." << endl;
            }
        break;

        case 3:
            cout << "3. Get Before Close" << endl;
            cout << "enter the number: ";
            cin >> number;
            cout << db_helper.GetPrevClose(number) << endl;
        break;

        case 4:
            cout << "4. Get Today Open" << endl;
            cout << "executing...";
            data = db_helper.GetOpen();
            if(data != 1)
            {
                cout << "\r" << "Open:\t" << data << endl;
            }
            else
            {
                cout << "\rThere are no result." << endl;
            }
        break;

        case 5:
            cout << "5. Get Before Open" << endl;
            cout << "enter the number: ";
            cin >> number;
            cout << db_helper.GetPrevOpen(number) << endl;
        break;

        case 6:
            cout << "6. Get Today High" << endl;
            cout << "executing...";
            data = db_helper.GetOpen();
            if(data != 1)
            {
                cout << "\r" << "High:\t" << data << endl;
            }
            else
            {
                cout << "\rThere are no result." << endl;
            }
        break;

        case 7:
            cout << "7. Get Before High" << endl;
            cout << "enter the number: ";
            cin >> number;
            cout << db_helper.GetPrevHigh(number) << endl;
        break;

        case 8:
            cout << "8. Get Today Low" << endl;
            cout << "executing...";
            data = db_helper.GetOpen();
            if(data != 1)
            {
                cout << "\r" << "Low:\t" << data << endl;
            }
            else
            {
                cout << "\rThere are no result." << endl;
            }
        break;

        case 9:
            cout << "9. Get Before Low" << endl;
            cout << "enter the number: ";
            cin >> number;
            cout << db_helper.GetPrevLow(number) << endl;
        break;

        case -1:
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