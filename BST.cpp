#include "BST.h"
#include <iostream>
#include <string>

BST::BST(){

}

BST::~BST(){
    destructorHelper(root);
}
void BST::destructorHelper(BST_Node* node){
    if(!node)return;
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}
bool BST::deleteFn(std::string country_name){
    return true;
}   
void BST::find(std::string mean, std::string operation){
    std::cout<<"not implemented"<<std::endl;
}
void BST::Limits(std::string condition){
    std::cout<<"not implemented"<<std::endl;
}
void BST::Range(std::string series_code){
    std::cout<<"not implemented"<<std::endl;
}
void BST::printNode(){
    std::cout<<"not implemented"<<std::endl;
}