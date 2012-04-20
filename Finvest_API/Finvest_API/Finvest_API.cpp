/*
    Finvest_API.cpp
    * API test program
    * author: Finvest
    * jag9123@gmail.com
*/


#include <iostream>
#include "DBHelper.h"
#include "IndexFomular.h"

#define LINE "--------------------------------------------------"

using namespace std;

void SelectMenu(int menunum);
void SetMainStock();
DBHelper db_helper;
IndexFomular index_fomular;


int main()
{
    index_fomular.db_helper.SetStock("LG");
    int menu_num = 0;

    cout << LINE << endl;
    cout << "Database API Test Program" << endl;
    cout << LINE << endl;
    SetMainStock();

    while(menu_num != -1) 
    {
        cout << LINE << endl;

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
        case -1:
            cout << "Good Bye" << endl;
            db_helper.~DBHelper();
        break;

        case 10:
            cout << "15. Ratio of Change" << endl;
            cout << "executing...";
            data = index_fomular.ratio();
             if(data != 1)
            {
                cout << "\r" << "Ratio:\t" << data << endl;
                //data가 0이하에서 0이상이 되면 매수
                //data가 0이상에서 0이하가 되면 매도
            }
            else
            {
                cout << "\rThere are no result." << endl;
            }
        break;

        case 11:
            cout << "17. Pivot Point" << endl;
            cout << "executing...";
            data = index_fomular.pivot();
             if(data != 1)
            {
                cout << "\r" << "Pivot Point:\t" << data << endl;
                
            }
            else
            {
                cout << "\rThere are no result." << endl;
            }
        break;

		case 12:
			cout <<"10. sonar"<<endl;
			cout << IndexFomular.getSONARValue() << endl;
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