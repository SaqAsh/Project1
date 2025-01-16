#include <iostream>

#include <string>
#include "TimeSeries.h"  
void HandleLoad(TimeSeries *&t_series) {
    std::string file_name;
    if (std::cin >> file_name) {
        delete t_series;
        t_series = new TimeSeries();  
    }

    t_series->LOAD(file_name);
    std::cout << "success" << std::endl;
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
    if(t_series->emptyDataSet()){
        std::cout<<"failure" << std::endl;
        return;
    }   
    std::cout << "mean is " << m <<std::endl;
}

void HandleMonotonic(TimeSeries *t_series){
    if(t_series -> emptyDataSet()){
        std::cout<<"failure" << std::endl;
        return;
    }
    t_series->is_monotonic() ? std::cout << "series is monotonic"<<std::endl : std::cout << "series is not monotonic"<<std::endl; 
}

void HandleFit(TimeSeries *t_series){
    double slope, intercept;

    t_series->best_fit(slope, intercept);

    if (t_series->emptyDataSet()){
        std::cout<<"failure" << std::endl;
    } else{
        std::cout << "slope is " << slope<< " intercept is " << intercept << std::endl;
    } 
}

int main() {

    TimeSeries *time_series = new TimeSeries();          

    std::string command;

    while (1) {

        std::cin >> command;

        if (command == "EXIT") {
            delete time_series;
            return 0;
        }
        else if (command == "LOAD") {
            HandleLoad(time_series);
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
