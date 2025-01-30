#ifndef COUNTRY_H
#define COUNTRY_H

#include "TimeSeries.h"
#include "LinkedList.h"
class Country {
    public:
        bool isEmpty;
        std::string country_name;
        std::string country_code;
        LinkedList* linked_list;
        Country();
        ~Country();
        void LOAD(std::string file_name);
        void ADD(double Y, double D, std::string series_code);
        void UPDATE(double Y, double D, std::string series_code);
        void PRINT(std::string series_code);
        void LIST();
        void DELETE(std::string series_code);   
        void BIGGEST();
};

#endif