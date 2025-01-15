#include <iostream>

#include <string>
#include "TimeSeries.h"  
void HandleLoad (bool first_load, TimeSeries *&t_series){
    std::string file_name;
    if(std::cin>> file_name){
        if (first_load) {
            first_load = false;
        } else {
            delete t_series;
            t_series = new TimeSeries();  
        }
    }

    t_series->LOAD(file_name);
    std::cout << "success" << "\n";
}

void HandleAdd(TimeSeries *t_series){
    unsigned int Y;
    int D;
    if (std::cin >> Y >> D) {
        t_series->ADD(Y, D);
    }
}

void HandleUpdate(TimeSeries *t_series){
    unsigned int Y;
    int D;
    if (std::cin >> Y >> D) {
        t_series->UPDATE(Y, D);
    }
}

void HandleMean(TimeSeries *t_series){
    double m = t_series->mean();
    !m ? std::cout<<"failure" << "\n" : std::cout << "mean is " << m <<"\n";
}

void HandleMonotonic(TimeSeries *t_series){
    t_series->is_monotonic() ? std::cout << "series is monotonic"<<"\n" : std::cout << "series is not monotonic"<<"\n"; 
}

void HandleFit(TimeSeries *t_series){
    double slope, intercept;

    t_series->best_fit(slope, intercept);

    if (slope == 0 && intercept == 0){
        std::cout<<"failure" << "\n";
    } else{
        std::cout << "slope is " << slope<< " intercept is " << intercept << "\n";
    } 
}

int main() {

    bool first_load = true;  
    TimeSeries *time_series = new TimeSeries();          

    std::string command;

    while (1) {

        std::cin >> command;

        if (command == "EXIT") {
            delete time_series;
            return 0;
        }
        else if (command == "LOAD") {
            HandleLoad(first_load, time_series);
        }
        else if (command == "PRINT") {
            time_series->PRINT();
        }
        else if (command == "ADD") {
            HandleAdd(time_series);
        }
        else if (command == "UPDATE") {
            HandleUpdate(time_series);
        }
        else if (command == "MEAN") {
            HandleMean(time_series);
        }
        else if (command == "MONOTONIC") {
            HandleMonotonic(time_series);
        }
        else if (command == "FIT") {
            HandleFit(time_series); 
        }
    }
    delete time_series;
    return 0;
}
