#include <iostream>
#include "IndexFomular.h"
#include "DBHelper.h"
<<<<<<< HEAD

=======
#include <math.h>
>>>>>>> 97e7080690dad5c9fe707f9d2645f519e6815571
/*
    IndexFomular.cpp
    * A set of fomulars
    * author: Finvest
*/
using namespace std;
//IndexFomular index_fomular;
//DBHelper db_helper;
 
int rsi;
 int ratio;
 int pivot;
    int t_close;
    int prev_close;

//RSI = {(14일간이 상승폭 합계) / (14일간의 상승폭 합계 + 14일간의 하락폭 합계) } * 100

/*void IndexFomular::RSI(){
    data1 = sql_manager.GetData();
    ...
    data 14 = sql_manager.GetData();

}*/

int IndexFomular::ratio(){
<<<<<<< HEAD
=======
// 변화율 = {(오늘종가 - 12일전 종가) / 12일전 종가 } * 100

>>>>>>> 12ec62312b39a7fd7d44dbc4173dd6e383b3ce56
    int ratio = 0;
    int t_close;
    int prev_close;

<<<<<<< HEAD
    //db_helper.SetStock("LG전자");
    //t_close = db_helper.GetClose();
    //prev_close = db_helper.GetPrevClose(12);

    //ratio = ((t_close - prev_close)/prev_close) * 100;
=======
    t_close = db_helper.GetClose();
    //prev_close = db_helper.GetPrevClose(12);
    std::cout << "test: " << t_close << std::endl;
    std::cout << "test: " << db_helper.GetPrevClose(12) << std::endl;
    //ratio = ((t_close - prev_close)/prev_close) * 100;

    return ratio; // hyojin kim
}

int IndexFomular::pivot(){
//pivot point = (전일의 고가 + 전일의 저가 + 전일의 종가) / 3
    int ppoint;
    int y_high;
    int y_low;
    int y_close;
    int res1;
    int sup1;
    int res2;
    int sup2;

   y_high = db_helper.GetPrevHigh(1);
   y_low = db_helper.GetPrevLow(1);
   y_close = db_helper.GetPrevClose(1);

   std::cout << "test: " << y_high << std::endl;
   std::cout << "test: " << y_low << std::endl;
   std::cout << "test: " << y_close << std::endl;

    ppoint = (y_high + y_low + y_close) / 3;
    res1 = (2 * ppoint) - y_low;
    sup1 = (2 * ppoint) - y_high;
    res2 = (ppoint - sup1) + res1;
    sup2 = ppoint - (res1 - sup1);

   // return ppoint, res1, sup1, res2, sup2;
    //hyojin kim
   //ppoint
>>>>>>> 12ec62312b39a7fd7d44dbc4173dd6e383b3ce56

}


<<<<<<< HEAD
=======
#include "IndexFomular.h"

DBHelper dbhelper;


void IndexFomular::getSC_KValue(){ //n기간동안 하는거 포인터 해결 어떻게 하는지 ㅠㅠㅠ

	
	int sc_k = ((dbhelper.GetClose() - dbhelper.GetPeriodLow())/(dbhelper.GetPeriodHigh()- dbhelper.GetPeriodLow()))*100;
	

	
}

void IndexFomular::getSC_DValue(){

	int sc_d = 0;

	for(int i=0; i<3; i++){

		sc_d = ((dbhelper.GetClose() - dbhelper.GetPeriodLow())/(dbhelper.GetPeriodHigh() - dbhelper.GetPeriodLow()))*100 + sc_d;
		
	}
	sc_d = sc_d/3;
}






void IndexFomular::getCCIValue(){
	
	int M = (dbhelper.GetHigh() + dbhelper.GetLow() + dbhelper.GetClose()) / 3;
	int m;

	for(int i=0; i<20; i++)
	{
		m = ((dbhelper.GetHigh() + dbhelper.GetLow() + dbhelper.GetClose()) / 3)+m;
	}
	m = m/20;

	int d;
	for(int i=0; i<20; i++)
	{
		d= abs(M-m) + d;
	}
	d = d/20;

	int cci = (M-m)/(d*0.015);

} 

void IndexFomular::getSONARValue()  //day는 10일을 추천

{
	int sonar = (dbhelper.GetClose() - dbhelper.GetPrevClose(10))/dbhelper.GetPrevClose(10);

}

void IndexFomular::getSONARAve() //기간은 5일을 추천
{
	int sonarave = 0;

	for(int i=0; i<5; i++){

		sonarave = ((dbhelper.GetClose() -dbhelper.GetPrevClose(10))/dbhelper.GetPrevClose(10))+sonarave;
	}

	sonarave = sonarave/5;

}
>>>>>>> 97e7080690dad5c9fe707f9d2645f519e6815571
