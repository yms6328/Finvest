/*
    StockIndex.cpp
    * Implements index
    * Return up/down flag
    * author: Finvest
*/

#include "StockIndex.h"
#include "IndexFomular.h"



void StockIndex.CCIFlag()
	{
		if(IndexFomular.getCCIValue() > 100)
		{
			return 매수flag;
		}
		else if(IndexFomular.getCCIValue() < -100)
		{
			return 매도flag;
		}
	}



void SONARFlag(){

	if(IndexFomular.getSONARValue() >0)
	{
		return 매수flag;
	}
	else if(IndexFomular.getSONARValue() <0)
	{
		return 매도flag;
	}
}
/*	
void StockIndex::SCFlag(){

	if(getSCValue() < 20)
	{
		return 매수flag;
	}
	else if(getSCValue() > 80)
	{
		return 매도flag;
	}


}*/
