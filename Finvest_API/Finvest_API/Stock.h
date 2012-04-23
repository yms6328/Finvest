#ifndef STOCK_H
#define STOCK_H
#include <string>

class Stock

        Stock();
	~Stock();
        std::string GetCode();
	std::string GetDate();
	int GetClose();
	int GetOpen();
	int GetHigh();
	int GetLow();
	int GetDiff();
	float GetVolume();
	double GetScale();

	int GetMA5();
	int GetMA10();
	int GetMA20();
	int GetMA60();
	int GetMA120();
};
#endif
