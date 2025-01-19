#include "TimeSeries.h"
#include <iostream>
#include <sstream>
#include <fstream>

//This is the constructor for the TimeSeries class
// It initializes the years and data arrays with a capacity of 2 and with the size of 0, which is the initial state of the application 
// It also initializes the valid_data_count_ to 0, which is the number of valid data points in the array which is strategy that I used
// instead of filtering out all the invalid data points, instead I just kept track of which of the data points were valid and which were not
TimeSeries::TimeSeries() {
    years = new int[2];  
    years_array_capacity_ = 2;
    years_array_size_ = 0;
    data = new int[2];   
    data_array_capacity_ = 2;
    data_array_size_ = 0;
    valid_data_count_ = 0;
}


// This is the destructor for the TimeSeries class
// It deletes the years and data arrays and sets them to nullptr to make sure that we don't have any memory leaks
TimeSeries::~TimeSeries() {
    delete[] years;
    years = nullptr;
    delete[] data;
    data = nullptr;
}

//This is the mean function for the TimeSeries class, it goes through and finds the mean of the valid data points 
double TimeSeries::mean() {
    // Had to make sure that we don't have zero valid data since that would cause a division by zero error
    if (valid_data_count_ == 0) return 0;

    double sum = 0;
    // Going through the data array and adding all the valid elements together
    for (int i = 0; i < data_array_size_; ++i) {
        if (data[i] == -1) continue; //skipping invalid elements
        sum += data[i]; //adding all the valid elements together
    }

    // Returning the mean of the valid data points via dividing the sum by the number of valid data points
    return sum / valid_data_count_;
}

//This is the is_monotonic function for the TimeSeries class, it goes through and checks if the data is strictly increasing or decreasing
bool TimeSeries::is_monotonic() {
    // making sure that we don't have no valid data, this is the edge case that we need to handle per the project instructions
    if (valid_data_count_ == 0) return false;

    //these are the flags that tell us if we are increasing or decreasing, we first assume that we are increasing and then we figure out if we are not via two pointers in the while loop
    bool increasing_flag = true;
    bool decreasing_flag = true;
    int N = data_array_size_;

    int i = 0;

    // we are going through the data array and checking if we are strictly increasing or decreasing, this is done via two pointers method, 
    // we are comparing the two valid pointers that are adjacent to each other and checking if they are increasing or decreasing
    while (i < N - 1) {
        // we keep moving the left pointer until we have found valid data
        while (i < N && data[i] == -1) ++i;

        int j = i + 1;

        // we keep moving the right pointer until we have found valid data
        while (j < N && data[j] == -1) ++j;

        //if we are trying to compare past the array then we break
        if (j >= N) break;

        // these are the flags that tell us if we are strictly increasing or decreasing
        if (data[i] > data[j]) increasing_flag = false;
        if (data[i] < data[j]) decreasing_flag = false;

        //moving the left pointer to the next valid right pointer's position
        i = j;
    }

    return decreasing_flag || increasing_flag;
}

//This is the best_fit function for the TimeSeries class, it goes through and finds the best fit line for the data points
void TimeSeries::best_fit(double &m, double &b) {

    int N = valid_data_count_;

    // If no valid data, set m and b to zero
    if (valid_data_count_ == 0) {
        m = 0;
        b = 0;
        return;
    }

    double data_sum = 0;
    double year_sum = 0;
    double data_year_sum = 0;
    double year_year_sum = 0;

    // Going through the data array and adding all the valid data and associated years together 
    // we are also constructing the individual terms for all the variables that we need to calculate the slope and intercept
    for (int i = 0; i < data_array_size_; ++i) {
        if (data[i] == -1) continue;
        year_sum += years[i];
        data_sum += data[i];
        year_year_sum += years[i] * years[i];
        data_year_sum += years[i] * data[i];
    }

    //constructing the terms for the calculation of slope and intercept
    double m_term_1 = N * data_year_sum; 
    double m_term_2 = data_sum * year_sum;
    double m_term_3 = N * year_year_sum;
    double m_term_4 = year_sum * year_sum; 

    //calculating the m value
    m = (m_term_1 - m_term_2) / (m_term_3 - m_term_4);

    //constructing the terms for the calculation of the intercept
    double b_term_1 = data_sum;
    double b_term_2 = m * year_sum;
    double b_term_3 = N;


    // Ensure no division by zero in intercept calculation
    b = (b_term_1 - b_term_2) / b_term_3;
}

//This is the function that decides if it needs to increase the size of the array based off of the array size and capacity, adhering to project specs
void TimeSeries::IncreaseSize(int*& arr, int size, int &capacity) {
    if (size != capacity) return;

    // then delete the old array and take the pointer arr, and attach that to the new array
    // and set the new array's pointer to nullptr
    int* new_arr = new int[capacity * 2];
    for (int i = 0; i < capacity; ++i) {
        new_arr[i] = arr[i]; // putting in all the existing elements into new array
    }
    capacity *= 2;
    delete[] arr;

    arr = new_arr;
}

// this is the function that decides if it needs to decrease the size of the array based off of the array size and capacity, adhering to project specs
void TimeSeries::DecreaseSize(int*& arr, int size, int &capacity) {
    //preliminary checks to see if further computation is required or not, don't want to overcompute if not needed to. 
    double ratio = capacity / 4;
    if (size != ratio) return;
    if (capacity / 2 < 2) return;

    capacity /= 2;

    //declaring the new array that we will be putting the previous elements into
    int *new_arr = new int[capacity];

    //copying all the values of the array into this new array
    for(int i = 0; i < size; ++i) {
        new_arr[i] = arr[i];
    }

    //ensuring that there is no memory leaks and setting the old pointer to point to the new array
    delete[] arr;
    arr = new_arr;
}

//adds to the array and increases the size if needed
void TimeSeries::Push(int value, int*& arr, int &size, int &capacity) {
    //Will Increase size if needed

    TimeSeries::IncreaseSize(arr, size, capacity);
    // Add the value to the end of the array and increment the count
    arr[size++] = value;
}

//this is load function for the file, it takes the file name as argument and reads the file with the correct information
void TimeSeries::LOAD(std::string file_name) {
    std::ifstream file(file_name); 
    std::string line;

    //followed the instructions for project zero, checking if the file is open or not
    while (std::getline(file, line)) {
        //this is the stringstream that we are using to parse the line
        std::stringstream s_stream(line);
        std::string component;
        int year = 1960;
        //skipping the first two values
        std::getline(s_stream, component, ','); 

        std::getline(s_stream, component, ',');

        //storing the time series name and code
        std::getline(s_stream, series_name, ',');

        std::getline(s_stream, series_code, ',');

        //going through the rest of the line and parsing the data and years, pushing all the data into the arrays, using the helper methods I made 
        // so we don't have to deal with all the resizing logic and memory management
        while (std::getline(s_stream, component, ',')) {
            int data_sample = std::stoi(component);

            //this is super important piece of data that we have, it is used to make sure that we know what the valid data is
            if(data_sample != -1) ++valid_data_count_;

            Push(data_sample, data, data_array_size_, data_array_capacity_); // here we are casting a string into an int to actually get the numbers into a number format

            Push(year++, years, years_array_size_, years_array_capacity_); // no need to cast to a number, we are simply just pushing in the years
        }
    }

    file.close();
}

//this is the ADD function for the TimeSeries class, it adds a new data point to the data array
void TimeSeries::ADD(int Y, int D){
    // goes through each value in the data array and checks if the year is already in the array, if it is then we don't add it
    //if its invalid data at that point then we change it up
    for(int i = 0; i < data_array_size_; ++i){
        //invalid data in the position
        if (years[i] == Y && data[i] == -1){
            data[i] = D;
            ++ valid_data_count_;
            std::cout<<"success"<<std::endl;
            return;
        }
        if (years[i] == Y && data[i] != -1){
            std::cout<<"failure"<<std::endl;
            return;
        }
    }
    //adding to the end of the list
    TimeSeries::Push(D, data, data_array_size_, data_array_capacity_);
    TimeSeries::Push(Y, years, years_array_size_, years_array_capacity_);
    ++valid_data_count_;
    std::cout<<"success"<<std::endl;

}
//this function is the update function for the TimeSeries class, it updates the data point in the data array if it is valid
void TimeSeries::UPDATE(int Y, int D){
    //goes through all the elements in the data array and checks if the year in the array is there and if there is valid at that point 
    // if there is valid data at that point then we update the data point
    for(int i = 0; i < data_array_size_; ++i){
        if(years[i] == Y && data[i] != -1){
            data[i] = D;
            std::cout<<"success"<<std::endl;
            return;
        }
    }

    std::cout<<"failure"<<std::endl;
}
//this is the print function for the TimeSeries class, it prints out the data points in the data array
void TimeSeries::PRINT() {

    //this is the flag that tells us if we have printed out any valid data points to avoid the extra spacing before the first valid data point
    bool valid_printed = false;
    // if we have no valid data then we print failure
    if ( valid_data_count_ == 0) {
        std::cout<<"failure"<<std::endl;
        return;
    }   

    //goes through all the valid data points and prints them pairwise with the year
    for (int i = 0; i <  data_array_size_; ++i){
        if(data[i] == -1) continue;
        if(valid_printed) std::cout<<" ";  
        std::cout<<"("<<years[i]<<","<<data[i]<<")";
        valid_printed = true;
    }

    std::cout<<std::endl;
}

//this is essentially a getter type function that checks if that is any valid data in the data array
bool TimeSeries::emptyDataSet() {
    return valid_data_count_ == 0;
}  