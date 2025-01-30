#ifndef TIMESERIES_H
#define TIMESERIES_H
#include <string>

class TimeSeries {
public:
    TimeSeries();
    ~TimeSeries();

    double mean();
    bool is_monotonic();
    void best_fit(double &m, double &b);
    void LOAD(std::string file_name);
    void ADD(double Y, double D);
    void UPDATE(double Y, double D);
    void PRINT();
    bool emptyDataSet();
    std::string series_name;
    std::string series_code;
private:
    double* years;
    double* data;
    double m;
    double b;
    int years_array_size_;
    int years_array_capacity_;
    int data_array_size_;
    int valid_data_count_;
    int data_array_capacity_;
    void IncreaseSize(double*& arr, int size, int &capacity);
    void DecreaseSize(double*& arr, int size, int &capacity); 
    void Push(double value, double*& arr, int &size, int &capacity); 
    int SearchInsertPosition(double* arr, double value, int size);
    void InsertIntoPosition(double*& arr, double value, int position, int& size, int& capacity);
    void MakeSpaceAtPosition(double*& arr, int position, int size, int capacity);
};

#endif
