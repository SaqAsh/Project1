#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <sys/types.h>
#include <bits/c++config.h>
#include <string>

class TimeSeries {
public:
    TimeSeries();
    ~TimeSeries();

    double mean();
    bool is_monotonic();
    void best_fit(double &m, double &b);
    void LOAD(std::string file_name);
    void ADD(uint Y, int D);
    void UPDATE(uint Y, int D);
    void PRINT();

private:
    uint* years;
    int* data;
    double m;
    double b;
    uint years_array_size_;
    uint years_array_capacity_;
    uint data_array_size_;
    uint valid_data_count_;
    uint data_array_capacity_;
    void IncreaseSize(int*& arr, uint size, uint &capacity);
    void DecreaseSize(int*& arr, uint size, uint &capacity); 
    void Push(int value, int*& arr, uint size, uint &capacity);
    void Push(int value, uint* &arr, uint size, uint &capacity);
};

#endif
