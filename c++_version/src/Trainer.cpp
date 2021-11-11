#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity):capacity(t_capacity) {

}

int Trainer::getCapacity() const {
    return capacity;
}

std::vector<Customer*>& Trainer::getCustomers() {
    return customersList;
}

Customer *Trainer::getCustomer(int id) {
    for(int i=0;i<customersList.size();i++){
        if(customersList[i]->getId()==id){
            return customersList[i];
        }
    }
    return nullptr;
}

std::vector <OrderPair> &Trainer::getOrders() {
    return orderList;
}

int Trainer::getSalary() {
    int salary =0;
    for (int i = 0; i < orderList.size(); ++i) {
        salary += orderList[i].second.getPrice();
    }
    return salary;
}