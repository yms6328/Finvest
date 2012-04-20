#ifndef STOCKINDEX_H
#define STOCKINDEX_H

class StockIndex
{
    public:
        IndexFomula index_formula;

        bool SetStock(const std::string& stock_name);

        bool CCI();
        bool Sonar();
        bool SC();
};
#endif;
