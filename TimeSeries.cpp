#include "TimeSeries.h"
#include <sys/types.h>
#include <bits/c++config.h>
#include <cassert>
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

            for(std::size_t i = 0; i< this -> data_element_count_; ++i){

                if(data[i] == -1) continue; //skipping invalid elements

                sum += data[i]; //adding all the valid elements together
            }

            return sum / this -> valid_data_count_;  
        }

        bool is_monotonic() {
            return true;
        }

        void best_fit(double &m, double &b) {

            assert ( this -> years_element_count_ == this -> data_element_count_ );
            //if we have no valid data then we simply set the m and b to be zer 
            if ( this -> valid_data_count_ == 0) {
                m = 0;
                b = 0;
            }
            int year_sum = 0;

            for (std::size_t i = 0; i < this -> years_element_count_; ++i){
                year_sum += years[i]; //there is no need to check for invalid years since years will always be valid
            }

            int data_sum = 0;

            for (std::size_t i = 0; i < this -> data_element_count_; ++i){
                if (data[i] == -1) continue;
                data_sum += data[i];
            }

            int data_data_sum = 0; 

            for (std::size_t i = 0; i < this -> data_element_count_; ++i){
                if (data[i] == -1) continue;
                data_data_sum += data[i] * data[i];
            }

            int data_year_sum = 0;

            // data_element_count_ should be the same size as the years_element_count since they are pairs
            for ( std::size_t i = 0; i < this -> data_element_count_; ++i){
                if (data[i] == -1) continue;
                data_year_sum += years[i] * data[i];
            }
            double m_term_1;
            double m_term_2;
            double m_term_3;
            double m_term_4;

            assert((m_term_3 - m_term_4) != 0);

            m = (m_term_1 - m_term_2)/(m_term_3 - m_term_4);

            double b_term_1;
            double b_term_2;
            double b_term_3;

            assert(b_term_3); // asserting that we 

            b = (b_term_1 - b_term_2) / b_term_3;

            //not else we gotta do a lot of operations to figure out what the best fit line values are, thus we use a helper function 
            // called sum elements

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
