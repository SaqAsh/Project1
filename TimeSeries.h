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
    void ADD(int Y, int D);
    void UPDATE(int Y, int D);
    void PRINT();
    bool emptyDataSet();

private:
    int* years;
    int* data;
    double m;
    double b;
    std::string series_name;
    std::string series_code;
    int years_array_size_;
    int years_array_capacity_;
    int data_array_size_;
    int valid_data_count_;
    int data_array_capacity_;
    void IncreaseSize(int*& arr, int size, int &capacity);
    void DecreaseSize(int*& arr, int size, int &capacity); 
    void Push(int value, int*& arr, int &size, int &capacity); 
};

#endif
