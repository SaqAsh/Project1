#include "TimeSeries.h"
#include <sys/types.h>
#include <bits/c++config.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>

uint* years;
int* data;
double m;
double b;
std::string series_name;
std::string series_code;

TimeSeries::TimeSeries() {
    years = new int[2];
    this->years_array_capacity_ = 2;
    this->years_array_size_ = 0;
    data = new int[2];
    this->data_array_capacity_ = 2;
    this->data_array_size_ = 0;
    this->valid_data_count_ = 0;
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
    if (this->valid_data_count_ == 0) return 0;

    double sum = 0;

    for (std::size_t i = 0; i < this->data_array_size_; ++i) {
        if (data[i] == -1) continue; //skipping invalid elements
        sum += data[i]; //adding all the valid elements together
    }

    return sum / this->valid_data_count_;
}

bool TimeSeries::is_monotonic() {
    if (this->valid_data_count_ == 0) return false;

    bool strictly_increasing_flag = true;
    bool strictly_decreasing_flag = true;
    std::size_t N = this->data_array_size_;

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
    assert(this->years_array_size_ == this->data_array_size_ && "years and data are not in pairs");

    std::size_t N = this->years_array_size_;

    //if we have no valid data then we simply set the m and b to be zer
    if (this->valid_data_count_ == 0) {
        m = 0;
        b = 0;
    }
    int year_sum = 0;

    for (std::size_t i = 0; i < N; ++i) {
        //there is no need to check for invalid years since years will always be valid
        year_sum += years[i];
    }

    int data_sum = 0;

    for (std::size_t i = 0; i < N; ++i) {
        if (data[i] == -1) continue;
        data_sum += data[i];
    }

    int year_year_sum = 0;

    for (std::size_t i = 0; i < N; ++i) {
        year_year_sum += years[i] * years[i];
    }

    int data_year_sum = 0;

    // data_array_size_ should be the same size as the years_element_count since they are pairs
    for (std::size_t i = 0; i < N; ++i) {
        if (data[i] == -1) continue;
        data_year_sum += years[i] * data[i];
    }

    double m_term_1 = N * data_year_sum;
    double m_term_2 = data_sum * year_sum;
    double m_term_3 = N * year_year_sum;
    double m_term_4 = year_year_sum;

    // ensuring that there is no division by zero
    assert((m_term_3 - m_term_4) != 0 && "divide by zero error with slope");

    m = (m_term_1 - m_term_2) / (m_term_3 - m_term_4);

    double b_term_1 = data_sum;
    double b_term_2 = m * year_sum;
    double b_term_3 = N;

    // asserting that we
    assert(b_term_3 && "divide by zero for y intercept");

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
    // Add the value to the end of the array
    arr[size++] = value;
}

void TimeSeries::LOAD(std::string file_name){
    std::ifstream file(file_name); //opens the file
    std::string line; // declare the string that when using get line will read the string into this string
    while (std::getline(file, line)) { 
        std::stringstream s_stream(line); // using the string, we use the std::stringstream to create a string stream
        std::string component; //we declare another string that will be passed into the get line to get the component

        while (std::getline(s_stream, component, ',')) {
            std::cout << component << "\n";  // we print the component with a new line at the end
        }
    }
    file.close(); 
}
void TimeSeries::ADD(uint Y, int D){
    for(std::size_t i = 0; i < data_array_size_; ++i){
        //invalid data in the position
        if (years[i] == Y && data[i] == -1){
            data[i] = D;
            ++ this ->valid_data_count_;
            std::cout<<"success"<<"\n";
            return;
        }
        if (years[i] == Y && data[i] != -1){
            std::cout << "failure" << "\n";
            return;
        }
    }
    //adding to the end of the list
    TimeSeries::Push(D, data, data_array_size_, data_array_capacity_);
    TimeSeries::Push(Y, years, years_array_size_, years_array_capacity_);

}
void TimeSeries::UPDATE(uint Y, int D){
    for(std::size_t i = 0; i < data_array_size_; ++i){
        if(years[i] == Y && data[i] != -1){
            data[i] = D;
            std::cout<<"success"<<"\n";
            return;
        }
    }
    std::cout<<"failure"<<"\n";
}
void TimeSeries::PRINT() {
    if( this -> valid_data_count_ == 0) std::cout<<"failure";
    for (std::size_t i = 0; i < this -> data_array_size_; ++i){
        std::cout<<"("<<years[i]<<","<<data[i]<<")";
    }
}