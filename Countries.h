#include <iostream>
#include "BST.h"    
#include "Country.h"

class Countries{
    public:
        Country **country_array;
        BST * CountryTree;
        Countries ();
        ~Countries();
        void LOAD(std::string filename);
        void LIST(std::string country_name);
        void RANGE(std::string series_code);
        void BUILD(std::string country_name);
        void FIND(double mean, std::string operation); 
        void DELETE(std::string country_name);
        void LIMITS(std::string condition);
        void LOOKUP(std::string country_code);
        void REMOVE(std::string country_code);
        void INSERT(std::string country_code, std::string file_name);
    private:
        int total_countries; 
        int primary_hash(std::string country_code);
        int secondary_hash(std::string country_code);
        int overall_hash_insert(std::string country_code, int& i);
        bool countryExists(std::string country_code) ;
        int overall_hash_delete(std::string country_code, int& i);
};