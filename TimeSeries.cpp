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
            delete[] years; 
            years = nullptr;
            delete[] data;
            data = nullptr;
            assert(data == nullptr);
            assert(years == nullptr);
        }

        double mean() {

            if( this -> valid_data_count_ == 0) return 0;

            double sum = 0;

            for(std::size_t i = 0; i< this -> data_element_size_; ++i){

                if(data[i] == -1) continue; //skipping invalid elements

                sum += data[i]; //adding all the valid elements together
            }

            return sum / this -> valid_data_count_;  
        }

        bool is_monotonic() {
            if (this->valid_data_count_ == 0) return false;

            bool strictly_increasing_flag = true;
            bool strictly_decreasing_flag = true;
            std::size_t N = this->data_element_size_;
            
            std::size_t i = 0;

            while (i < N - 1) {
                // we keep moving the left pointer until we have found valid data
                while (i < N && data[i] == -1) ++i;

                std::size_t j = i + 1;

                // we keep moving the right pointer until we have found valid data
                while (j < N && data[j] == -1) ++j;
                
                //if we are trying to compare past the array then we break
                if (j >= N) break;
                
                // these are the flags that tell us if we are strictly increasing or decreasing
                if (data[i] > data[j]) strictly_increasing_flag = false;
                if (data[i] < data[j]) strictly_decreasing_flag = false;

                //moving the left pointer to the next valid right pointer's position
                i = j; 
            }

            return strictly_decreasing_flag || strictly_increasing_flag;
        }


        void best_fit(double &m, double &b) {

            assert ( this -> years_element_size_ == this -> data_element_size_ && "years and data are not in pairs");

            std::size_t N = this -> years_element_size_; 
            
            //if we have no valid data then we simply set the m and b to be zer 
            if ( this -> valid_data_count_ == 0) {
                m = 0;
                b = 0;
            }
            int year_sum = 0;

            for (std::size_t i = 0; i < N; ++i){
                //there is no need to check for invalid years since years will always be valid
                year_sum += years[i]; 
            }

            int data_sum = 0;

            for (std::size_t i = 0; i < N; ++i){
                if (data[i] == -1) continue;
                data_sum += data[i];
            }

            int year_year_sum = 0; 

            for (std::size_t i = 0; i < N; ++i){
                year_year_sum += years[i] * years[i];
            }

            int data_year_sum = 0;

            // data_element_size_ should be the same size as the years_element_count since they are pairs
            for ( std::size_t i = 0; i < N; ++i){
                if (data[i] == -1) continue;
                data_year_sum += years[i] * data[i];
            }

            double m_term_1 = N * data_year_sum;
            double m_term_2 = data_sum * year_sum;
            double m_term_3 = N * year_year_sum;
            double m_term_4 = year_year_sum;

            // ensuring that there is no division by zero
            assert((m_term_3 - m_term_4) != 0 && "divide by zero error with slope"); 

            m = (m_term_1 - m_term_2)/(m_term_3 - m_term_4);

            double b_term_1 = data_sum;
            double b_term_2 = m * year_sum;
            double b_term_3 = N;
            
            // asserting that we 
            assert(b_term_3 && "divide by zero for y intercept"); 

            b = (b_term_1 - b_term_2) / b_term_3;

        }    
    private:
        //these values are gonna be the ones that tell me to increase sizing or decreasse sizing
            uint years_element_size_ = 0; 
            uint years_array_capacity_ = 2;
            uint data_element_size_ = 0;
            uint valid_data_count_ = 0;
            uint data_array_capacity_ = 2;
        ///////////////////////////////////////////////////////////////////////////////////////
        
        void IncreaseSize(int*& arr) {

        }

        void DecreaseSize(int*& arr ) {

        }

        void Push(int value, int*& arr){

        }

};
