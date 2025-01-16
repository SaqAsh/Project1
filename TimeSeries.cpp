#include "TimeSeries.h"
#include <sys/types.h>
#include <bits/c++config.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>

TimeSeries::TimeSeries() {
    years = new int[2];  
    years_array_capacity_ = 2;
    years_array_size_ = 0;
    data = new int[2];   
    data_array_capacity_ = 2;
    data_array_size_ = 0;
    valid_data_count_ = 0;
}

TimeSeries::~TimeSeries() {
    delete[] years;
    years = nullptr;
    delete[] data;
    data = nullptr;
    assert(data == nullptr);
    assert(years == nullptr);
}

double TimeSeries::mean() {
    if (valid_data_count_ == 0) return 0;

    double sum = 0;

    for (std::size_t i = 0; i < data_array_size_; ++i) {
        if (data[i] == -1) continue; //skipping invalid elements
        sum += data[i]; //adding all the valid elements together
    }

    return sum / valid_data_count_;
}

bool TimeSeries::is_monotonic() {
    if (valid_data_count_ == 0) return false;

    bool strictly_increasing_flag = true;
    bool strictly_decreasing_flag = true;
    std::size_t N = data_array_size_;

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

void TimeSeries::best_fit(double &m, double &b) {
    assert(years_array_size_ == data_array_size_);

    std::size_t N = valid_data_count_;

    // If no valid data, set m and b to zero
    if (valid_data_count_ == 0) {
        m = 0;
        b = 0;
        return;
    }

    int data_sum = 0;
    int year_sum = 0;
    int data_year_sum = 0;
    int year_year_sum = 0;

    for (std::size_t i = 0; i < data_array_size_; ++i) {
        if (data[i] == -1) continue;
        year_sum += years[i];
        data_sum += data[i];
        year_year_sum += years[i] * years[i];
        data_year_sum += years[i] * data[i];
    }

    double m_term_1 = N * data_year_sum;
    double m_term_2 = data_sum * year_sum;
    double m_term_3 = N * year_year_sum;
    double m_term_4 = year_sum * year_sum; 

    // Ensure no division by zero in slope calculation
    assert((m_term_3 - m_term_4) != 0);
    m = (m_term_1 - m_term_2) / (m_term_3 - m_term_4);

    double b_term_1 = data_sum;
    double b_term_2 = m * year_sum;
    double b_term_3 = N;

    // Ensure no division by zero in intercept calculation
    assert(b_term_3 != 0);
    b = (b_term_1 - b_term_2) / b_term_3;
}


void TimeSeries::IncreaseSize(int*& arr, uint size, uint &capacity) {
    // don't needa do anything if the capacity is not equal to the size
    if (size != capacity) return;

    //we needa basically take all the elements of the arr and then copy it into a new array
    // then delete the old array and take the pointer arr, and attach that to the new array
    // and set the new array's pointer to nullptr
    int* new_arr = new int[capacity * 2];
    for (std::size_t i = 0; i < capacity; ++i) {
        new_arr[i] = arr[i]; // putting in all the existing elements into new array
    }
    capacity *= 2;
    delete[] arr;

    arr = new_arr;
    assert(arr == new_arr);
}

void TimeSeries::DecreaseSize(int*& arr, uint size, uint &capacity) {
    double ratio = capacity / 4;
    if (size != ratio) return;
    if (capacity / 2 < 2) return;

    capacity /= 2;

    assert(capacity > size);

    int *new_arr = new int[capacity];

    for(std::size_t i = 0; i < size; ++i) {
        new_arr[i] = arr[i];
    }

    delete[] arr;
    arr = new_arr;
    assert(arr == new_arr);
}

void TimeSeries::Push(int value, int*& arr, uint &size, uint &capacity) {
    //Will Increase size if needed

    TimeSeries::IncreaseSize(arr, size, capacity);
    // Add the value to the end of the array and increment the count
    arr[size++] = value;
}

void TimeSeries::LOAD(std::string file_name) {
    std::ifstream file(file_name); 
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream s_stream(line);
        std::string component;
        int year = 1960;
        std::getline(s_stream, component, ',');

        std::getline(s_stream, component, ',');

        std::getline(s_stream, series_name, ',');

        std::getline(s_stream, series_code, ',');

        while (std::getline(s_stream, component, ',')) {
            int data_sample = std::stoi(component);

            if(data_sample != -1) ++valid_data_count_;

            Push(data_sample, data, data_array_size_, data_array_capacity_); // here we are casting a string into an int to actually get the numbers into a number format

            Push(year++, years, years_array_size_, years_array_capacity_); // no need to cast to a number, we are simply just pushing in the years
        }
    }

    file.close();
}


void TimeSeries::ADD(uint Y, int D){
    for(std::size_t i = 0; i < data_array_size_; ++i){
        //invalid data in the position
        if (years[i] == Y && data[i] == -1){
            data[i] = D;
            ++ valid_data_count_;
            std::cout<<"success"<<std::endl;
            return;
        }
        if (years[i] == Y && data[i] != -1){
            std::cout << "failure"<<std::endl;
            return;
        }
    }
    //adding to the end of the list
    TimeSeries::Push(D, data, data_array_size_, data_array_capacity_);
    TimeSeries::Push(Y, years, years_array_size_, years_array_capacity_);
    ++valid_data_count_;
    std::cout<<"success"<<std::endl;

}
void TimeSeries::UPDATE(uint Y, int D){

    for(std::size_t i = 0; i < data_array_size_; ++i){
        if(years[i] == Y && data[i] != -1){
            data[i] = D;
            std::cout<<"success"<<std::endl;
            return;
        }
    }

    std::cout<<"failure"<<std::endl;
}
void TimeSeries::PRINT() {
    bool valid_printed = false;
    if ( valid_data_count_ == 0) {
        std::cout<<"failure"<<std::endl;
        return;
    }   

    for (std::size_t i = 0; i <  data_array_size_; ++i){
        if(data[i] == -1) continue;
        if(valid_printed) std::cout<<" ";  
        std::cout<<"("<<years[i]<<","<<data[i]<<")";
        valid_printed = true;
    }

    std::cout<<std::endl;
}

bool TimeSeries::emptyDataSet() {
    return valid_data_count_ == 0;
}  