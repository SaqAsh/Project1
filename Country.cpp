#include "Country.h"
#include <iostream>
#include <sstream>
#include <fstream>

// This is the constructor for the country class
Country::Country(){
    isEmpty = true;
    linked_list = new LinkedList();
}

// This is the destructor for the country class
Country::~Country() {
    delete linked_list;
}
// This is the load function that loads the data from the file into the country class
void Country::LOAD(std::string country_name, std::string file_name) {
    std::ifstream file(file_name);
    std::string line;
    bool found = false;
    while(std::getline(file, line)) {
        std::stringstream s_stream(line);
        std::string country;
        std::getline(s_stream, country, ',');
        // if we have found the country we are looking for then we can start loading the data and initializing the country name
        if (country == country_name && !found) {
            found = true;
            this->country_name = country;
            std::getline(s_stream, country_code, ',');
            isEmpty = false;
            TimeSeries* series = new TimeSeries();
            series->LOAD(line);
            linked_list->handle_insert(series);
        }
        // if we have found the country we are looking for and we are still in the same country then we can keep loading the data
        else if (found && country == country_name) {
            isEmpty = false;
            TimeSeries* series = new TimeSeries();
            std::getline(s_stream, country_code, ',');
            series->LOAD(line);
            linked_list->handle_insert(series);
        }
        // if we have found the country we are looking for and we are no longer in the same country then we can break out of the loop
        else if (found && country != country_name) {
            break;
        }
    }
}
// This is the add function that adds a new time series to the linked list
void Country::ADD(double Y, double D, std::string series_code){
    Node *temp = linked_list->head;
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }
    // goes through the linked list to find the time series of interest
    while(temp!=NULL && temp->data->series_code != series_code){
        temp = temp->next;
    }
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data->ADD(Y,D);
}   
// This is the update function that updates the time series in the linked list
void Country::UPDATE(double Y, double D, std::string series_code){
    Node *temp = linked_list->head;
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }  
    // goes through the linked list to find the time series of interest 
    while(temp!=NULL && temp->data->series_code != series_code){
        temp = temp->next;
    }
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data->UPDATE(Y,D);
}
// This is the print function that prints the time series of interest
void Country::PRINT(std::string series_code){
    Node * temp = linked_list->head;
    // goes through the linked list to find the time series of interest
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
// This is the list function that lists the country's time series details
void Country::LIST(){
    std::cout<<country_name<<" " << country_code << " ";
    Node * temp = linked_list->head;
    while(temp){
        std::cout<<temp->data->series_name<<" ";
        temp = temp->next;
    }
    std::cout<<"\n";
}
// This is the delete function that deletes the time series of interest
void Country::DELETE(std::string series_code){

    if(!linked_list->head){
        std::cout<<"failure"<<"\n";
        return;
    }
    if (linked_list->head && linked_list->head->data->series_code == series_code) {
        Node* temp = linked_list->head; 
        linked_list->head = linked_list->head->next;
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
// This is the biggest function that prints the time series with the biggest mean
void Country::BIGGEST(){

    if(isEmpty){
        std::cout << "failure" << "\n";
        return;
    }
    //initializing the max mean and the time series code of the biggest mean
    // so we have something to vote against
    double max_mean = linked_list->head->data->mean();
    std::string time_series_code_of_biggest_mean = linked_list->head->data->series_code;
    Node *temp = linked_list-> head;

    while(temp){
        double curr_mean = temp->data->mean();
        //update the max_mean
        if(curr_mean > max_mean){
            max_mean = curr_mean;
            time_series_code_of_biggest_mean = temp->data->series_code;
        }
        temp = temp->next;
    }
    std::cout<<time_series_code_of_biggest_mean<<"\n";
}




