#include <iostream>
#include "BST.h"    
#include "Country.h"

class Countries{
    public:
    // BST * CountryTree;
    Countries ();
    ~Countries();
    void LOAD(std::string filename);
    void LIST(std::string country_name);
    void RANGE(std::string series_code);
    void BUILD(std::string country_name);
    void FIND(std::string mean, std::string operation); 
    void DELETE(std::string country_name);
    void LIMITS(std::string condition);
    private:
        Country **country_array;
        int total_countries; 
};