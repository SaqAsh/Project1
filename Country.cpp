#include "Country.h"
#include <iostream>
#include <sstream>
#include <fstream>

Country::Country(){
    time_series_linked_list = new LinkedList();
}

Country::~Country() {
    delete time_series_linked_list;
}

void Country::LOAD(std::string file_name) {
    std::ifstream file(file_name);
    std::string line;
    
    delete time_series_linked_list;
    time_series_linked_list = new LinkedList();
    
    while(std::getline(file, line)) {
        TimeSeries* series = new TimeSeries();  
        
        std::stringstream s_stream(line);
        std::string component;
        
        std::getline(s_stream, country_name, ',');
        std::getline(s_stream, country_code, ',');
        
        series->LOAD(line);
        
        time_series_linked_list->HandleInsertIntoLinkedList(*series);
    }
    
    file.close();
}

void Country::ADD(double Y, double D, std::string series_code){
    Node *temp = time_series_linked_list->head;
    while(temp!=NULL && temp->data.series_code != series_code){
        temp = temp->next;
    }
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data.ADD(Y,D);
}   

void Country::UPDATE(double Y, double D, std::string series_code){
    Node *temp = time_series_linked_list->head;
    while(temp!=NULL && temp->data.series_code != series_code){
        temp = temp->next;
    }
    if(!temp){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data.UPDATE(Y,D);
}

void Country::PRINT(std::string series_code){
    Node * temp = time_series_linked_list->head;

    while(temp !=NULL && temp->data.series_code !=series_code){
        temp = temp->next;
    }
    // now that we are at the point where we may have found the series, we can print that series
    if(temp == NULL){
        std::cout<<"failure"<<"\n";
        return;
    }
    temp->data.PRINT();
}

void Country::LIST(){
    std::cout<<country_name<<" " << country_code << " ";
    Node * temp = time_series_linked_list->head;
    while(temp){
        std::cout<<temp->data.series_name<<" ";
        temp = temp->next;
    }
    std::cout<<"\n";
}

void Country::DELETE(std::string series_code){
    // Special case for deleting head
    if (time_series_linked_list->head && time_series_linked_list->head->data.series_code == series_code) {
        Node* temp = time_series_linked_list->head;
        time_series_linked_list->head = time_series_linked_list->head->next;
        delete temp;
        std::cout << "success" << "\n";
        return;
    }

    Node* temp = time_series_linked_list->head;
    while(temp && temp->next && temp->next->data.series_code != series_code){
        temp = temp->next;
    }
    
    if(!temp || !temp->next){
        std::cout << "failure" << "\n";
        return;
    }
    
    Node* node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    delete node_to_delete;
    std::cout << "success" << "\n";
}
//have not handled the case where no time series has valid data
void Country::BIGGEST(){
    //finding the max via the voting against the first value
    double max_mean = time_series_linked_list ->head->data.mean();
    std::string time_series_code_of_biggest_mean = time_series_linked_list->head->data.series_code;
    Node *temp = time_series_linked_list-> head;

    while(temp){
        double curr_mean = temp->data.mean();
        if(curr_mean > max_mean){
            max_mean = curr_mean;
            time_series_code_of_biggest_mean = temp->data.series_code;
        }
        temp = temp->next;
    }
    std::cout<<time_series_code_of_biggest_mean<<"\n";
}




