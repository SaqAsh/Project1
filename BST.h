#include <iostream>
#include <string>
class BST{
    public:
        BST();
        ~BST();
        bool deleteFn(std::string country_name);
        void find(std::string mean, std::string operation);
        void Limits(std::string condition);
        void Range(std::string series_code);
    private:
        void printNode();

};