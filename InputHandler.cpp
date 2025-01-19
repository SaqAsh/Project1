#include <iostream>

#include <string>
#include "TimeSeries.h"

//This is the function that handles the load command, it takes the TimeSeries object and loads the file using the LOAD function 
void HandleLoad(TimeSeries *&t_series) {
    std::string file_name;
    if (std::cin >> file_name) {
        delete t_series;
        t_series = new TimeSeries();  
    }

    t_series->LOAD(file_name);
    std::cout << "success" << std::endl;
}

//takes in the time series object and adds a new data point using the add function
void HandleAdd(TimeSeries *t_series){
    unsigned int Y;
    int D;
    if (std::cin >> Y >> D) {
        t_series->ADD(Y, D);
    }
}

//takes in the time series object and updates a new data point using the update function
void HandleUpdate(TimeSeries *t_series){
    unsigned int Y;
    int D;
    if (std::cin >> Y >> D) {
        t_series->UPDATE(Y, D);
    }
}

//takes in the time series object and finds the mean using the mean function or if the data set is empty then just prints the failure
void HandleMean(TimeSeries *t_series){
    double m = t_series->mean();
    if(t_series->emptyDataSet()){
        std::cout<<"failure" << std::endl;
        return;
    }   
    std::cout << "mean is " << m <<std::endl;
}


//takes in the time series object and finds if the series is monotonic or not 
void HandleMonotonic(TimeSeries *t_series){
    if(t_series -> emptyDataSet()){
        std::cout<<"failure" << std::endl;
        return;
    }
    t_series->is_monotonic() ? std::cout << "series is monotonic"<<std::endl : std::cout << "series is not monotonic"<<std::endl; 
}

//takes in the time series object and finds the best fit line using the function implemented in time series
void HandleFit(TimeSeries *t_series){
    double slope, intercept;

    if (t_series->emptyDataSet()){
        std::cout<<"failure" << std::endl;
        return;
    } else{
        t_series->best_fit(slope, intercept);
        std::cout << "slope is " << slope<< " intercept is " << intercept << std::endl;
    } 
}


//this is the entry point of our application 
int main() {

    TimeSeries *time_series = new TimeSeries();          

    std::string command;

    //this is the loop of our application that handles the input
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
