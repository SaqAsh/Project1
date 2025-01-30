#ifndef COUNTRY_H
#define COUNTRY_H

#include "TimeSeries.h"
#include "LinkedList.h"
class Country {
    public:
        std::string country_name;
        std::string country_code;
        LinkedList* time_series_linked_list;
        Country();
        ~Country();
        void LOAD(std::string file_name);
        void ADD(double Y, double D, std::string series_code);
        void UPDATE(double Y, double D, std::string series_code);
        void PRINT(std::string series_code);
        void LIST();
        void DELETE(std::string series_code);   
        void BIGGEST();

    private:
        LinkedList* time_series_linked_list_;

};

#endif