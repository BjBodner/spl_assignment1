#include "../include/Trainer.h"

//TODO: VALIDATE IF IMPLEMENTATION WITH EMPTY VECTORS IS CORRECT
Trainer::Trainer(int t_capacity) : capacity(t_capacity), open(false),customersList(std::vector<Customer*>()),orderList(std::vector<OrderPair>()),salary(0) {

}

//Getters

int Trainer::getCapacity() const {
    return capacity;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

Customer *Trainer::getCustomer(int id) {
    for (size_t i = 0; i < customersList.size(); i++) {
        if (customersList[i]->getId() == id) {
            return customersList[i];
        }
    }
    return nullptr;
}

std::vector <OrderPair> &Trainer::getOrders() {
    return orderList;
}

int Trainer::getSalary() {
    return salary;
}

//End Getters

bool Trainer::isOpen() {
    return open;
}

//TODO: ENSURE WHETHER NEEDS TO CHECK CAPACITY BEFORE ADDING CUSTOMER
void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
}

//TODO: Assumes that the trainer is open. Need to check if its right
void Trainer::removeCustomer(int id) {
    for (size_t i = 0; i < customersList.size(); i++) {
        if (customersList[i]->getId() == id) {
            customersList.erase(customersList.begin()+i);
            break;
        }
    }
    for (size_t i = 0; i < orderList.size(); i++) {
        if (orderList[i].first == id) {
            //Order that the customer ordered
            //TODO: Check if I can erase objects from vector while iterating on it
            orderList.erase(orderList.begin()+i);
        }
    }
    //If no customers left, close trainer
    if (customersList.size() == 0) {
        closeTrainer();
    }
}

//TODO: Ensure the function doesnt need to check if trainer is closed
void Trainer::order(const int customer_id, const std::vector<int> workout_ids,
                    const std::vector <Workout> &workout_options) {
    for (size_t i = 0; i < workout_ids.size(); i++) {
        for (size_t j = 0; j < workout_options.size(); j++) {
            if (workout_options[j].getId() == workout_ids[i]) {
                orderList.push_back(OrderPair(customer_id, workout_options[j]));
                break;
            }
        }
    }
}

///Closes the trainer's session
void Trainer::closeTrainer() {
    //Accumulate salary
    for (size_t i = 0; i < orderList.size(); i++) {
        salary += orderList[i].second.getPrice();
    }
    //Remove orders and customers
    orderList.clear();
    //TODO: ENSURE DELETION OF CUSTOMER'S
    for (size_t i = 0; i < customersList.size(); i++) {
        delete customersList[i];
    }
    customersList.clear();
    open = false;
}

///Opens the trainer's session
void Trainer::openTrainer() {
    open = true;
}

