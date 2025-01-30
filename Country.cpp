#include "Country.h"
#include <iostream>
#include <sstream>
#include <fstream>

Country::Country(){
    isEmpty = true;
    linked_list = new LinkedList();
}

Country::~Country() {
    delete linked_list;
}

void Country::LOAD(std::string country_name) {
    std::ifstream file("lab2_multidata.csv");
    std::string line;
    bool found = false;
    
    while(std::getline(file, line)) {
        std::stringstream s_stream(line);
        std::string country;
        std::getline(s_stream, country, ',');
        
        if (country == country_name && !found) {
            found = true;
            this->country_name = country;
            std::getline(s_stream, country_code, ',');
            isEmpty = false;
            TimeSeries* series = new TimeSeries();
            series->LOAD(line);
            linked_list->handle_insert(series);
        }
        else if (found && country == country_name) {
            isEmpty = false;
            TimeSeries* series = new TimeSeries();
            std::getline(s_stream, country_code, ',');
            series->LOAD(line);
            linked_list->handle_insert(series);
        }
        else if (found && country != country_name) {
            break;
        }
    }
    
    file.close();
}

void Country::ADD(double Y, double D, std::string series_code){
    Node *temp = linked_list->head;
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }

    while(temp!=NULL && temp->data->series_code != series_code){
        temp = temp->next;
    }
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data->ADD(Y,D);
}   

void Country::UPDATE(double Y, double D, std::string series_code){
    Node *temp = linked_list->head;
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }   
    while(temp!=NULL && temp->data->series_code != series_code){
        temp = temp->next;
    }
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data->UPDATE(Y,D);
}

void Country::PRINT(std::string series_code){
    Node * temp = linked_list->head;

    while(temp !=NULL && temp->data->series_code !=series_code){
        temp = temp->next;
    }
    // now that we are at the point where we may have found the series, we can print that series
    if(temp == NULL){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data->PRINT();
}

void Country::LIST(){
    std::cout<<country_name<<" " << country_code << " ";
    Node * temp = linked_list->head;
    while(temp){
        std::cout<<temp->data->series_name<<" ";
        temp = temp->next;
    }
    std::cout<<"\n";
}

void Country::DELETE(std::string series_code){

    if(!linked_list->head){
        std::cout<<"failure"<<"\n";
        return;
    }

    Node *head = linked_list->head;
    if (head && head->data->series_code == series_code) {
        Node* temp =head; 
        head = head->next;
        delete temp->data; //making sure the time series is deleted before deleting the node
        delete temp; //deleting the node itself
        std::cout << "success" << "\n";
        return;
    }

    Node* temp = linked_list->head;
    while(temp && temp->next && temp->next->data->series_code != series_code){
        temp = temp->next;
    }
    
    //checking if the node is there or if we even have a linked list
    if(!temp || !temp->next){
        std::cout << "failure" << "\n";
        return;
    }
    Node* node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    delete node_to_delete->data; //making sure the time series is deleted before deleting the node
    delete node_to_delete; //deleting the node itself
    std::cout << "success" << "\n";
}
void Country::BIGGEST(){

    if(isEmpty){
        std::cout << "failure" << "\n";
        return;
    }

    double max_mean = linked_list->head->data->mean();
    std::string time_series_code_of_biggest_mean = linked_list->head->data->series_code;
    Node *temp = linked_list-> head;

    while(temp){
        double curr_mean = temp->data->mean();
        if(curr_mean > max_mean){
            max_mean = curr_mean;
            time_series_code_of_biggest_mean = temp->data->series_code;
        }
        temp = temp->next;
    }
    std::cout<<time_series_code_of_biggest_mean<<"\n";
}




