#include "TimeSeries.h"
#include <sys/types.h>
#include <bits/c++config.h>
class TimeSeries {

    public:

        //pointer to the years array, since years cannot be negative, that is why it is an uint
        uint* years; 

        //pointer to the data array, since data can be negative, that is why it is an int
        int* data; 

        //slope of the best fit line of data
        double m;

        //y int of the best fit ilne of data
        double b;
        

        TimeSeries(){

        }

        ~TimeSeries() {

        }

        double mean() {

            if( this -> valid_data_count_ == 0) return 0;

            double sum = 0;

            for(std::size_t i = 0; i< this -> data_array_size; ++i){

                if(data[i] == -1) continue; //skipping invalid elements

                sum+=data[i]; //adding all the valid elements together
            }

            return sum / this -> valid_data_count_;  
        }

        bool is_monotonic() {
            return true;
        }

        void best_fit(double &m, double &b) {
        }    
    private:
        //these values are gonna be the ones that tell me to increase sizing or decreasse sizing
            uint years_element_count_ = 0; 
            uint years_array_size_ = 2;
            uint data_element_count_ = 0;
            uint valid_data_count_ = 0;
            uint data_array_size = 2;
        ///////////////////////////////////////////////////////////////////////////////////////
        
        void IncreaseSize(int*& arr) {

        }

        void DecreaseSize(int*& arr ) {

        }

        void Push(int value, int*& arr){

        }

};
