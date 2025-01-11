#ifdef TIMESERIES_H
#define TIMESERIES_H
#include <iostream>

class TimeSeries {
    public:
        //constructor for the class 
        TimeSeries(); 

        // destructor for the class
        ~TimeSeries(); 
        
        //Computes the standard mean of all the valid(not missing) data
        double mean(); 

        //Returns true if the series is monotonic and false otherwise
        bool is_monotonic();
        
        //computes the slope and y intercept of the line of best fit for the data
        void best_fit(double &m, double &b);

    private:
    
};
#endif