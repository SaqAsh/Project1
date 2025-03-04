#include <iostream>
#include <string>
#include "BST_Node.h"
class BST{
    public:
        BST_Node* root;
        BST();
        ~BST();
        bool deleteFn(std::string country_name);
        void find(std::string mean, std::string operation);
        void Limits(std::string condition);
        void Range(std::string series_code);
    private:
        void printNode();
        void destructorHelper(BST_Node* node);

};