#include "IndexFomular.h"
#include "DBHelper.h"

/*
    IndexFomular.cpp
    * A set of fomulars
    * author: Finvest
*/

//IndexFomular index_fomular;
//DBHelper db_helper;
 
int rsi;
 int ratio;
    int t_close;
    int prev_close;

//RSI = {(14일간이 상승폭 합계) / (14일간의 상승폭 합계 + 14일간의 하락폭 합계) } * 100

/*void IndexFomular::RSI(){
    data1 = sql_manager.GetData();
    ...
    data 14 = sql_manager.GetData();

}*/

int IndexFomular::ratio(){
    int ratio;
    int t_close;
    int prev_close;

    t_close = db_helper.GetClose();
    prev_close = db_helper.GetPrevClose(12);

    ratio = ((t_close - prev_close)/prev_close) * 100;

    return ratio;
}
