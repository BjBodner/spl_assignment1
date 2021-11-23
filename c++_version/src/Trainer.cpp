//
// Created by benjy on 11/20/2021.
//

//#include "../include/Trainer.h"
#include "../include/Trainer.h"
#include <iostream>

using namespace std;


Trainer::~Trainer() {
    for (::size_t i = 0; i < customersList.size(); i++) {
        if (customersList[i])
            delete (customersList[i]);
    }
}

Trainer &Trainer::operator=(const Trainer &other) {
    if (this != &other) {
        //Delete customer's from heap, nobody should have access to them anymore
        for (::size_t i = 0; i < customersList.size(); i++) {
            delete (customersList[i]);
        }
        this->customersList.clear();
        this->customersList = other.customersList;
        //Deep copy to other.orderPair , because Workout doesn't have operator=
        for (::size_t i = 0; i < other.orderList.size(); i++) {
            this->orderList.push_back(OrderPair(other.orderList.at(i)));
        }
        this->open = other.open;
        this->salary = other.salary;
        this->capacity = other.capacity;
    }
    return *this;
}

Trainer::Trainer(Trainer &&other) : capacity(other.capacity), open(other.open), customersList(vector<Customer *>()),
                                    orderList(vector<OrderPair>()), salary(other.salary) {
    for (::size_t i = 0; i < other.customersList.size(); i++) {
        this->customersList.push_back(other.customersList[i]);
        other.customersList[i] = nullptr;
    }
    //Deep copy to other.orderPair , because Workout doesn't have operator=
    for (::size_t i = 0; i < other.orderList.size(); i++) {
        this->orderList.push_back(OrderPair(other.orderList.at(i)));
    }
}

Trainer &Trainer::operator=(Trainer &&other) {
    if (this != &other) {
        //delete the customer, nobody should have access to them anymore
        for (::size_t i = 0; i < customersList.size(); i++) {
            if (customersList[i])
                delete customersList[i];
        }
        customersList.clear();
        for (::size_t i = 0; i < other.customersList.size(); ++i) {
            customersList[i] = other.customersList[i];
            //So he doesn't erase my object later on
            other.customersList[i] = nullptr;
        }
        //Deep copy to other.orderPair , because Workout doesn't have operator=
        for (::size_t i = 0; i < other.orderList.size(); i++) {
            this->orderList.push_back(OrderPair(other.orderList.at(i)));
        }
        this->open = other.open;
        this->capacity = other.capacity;
        this->salary = other.salary;
    }
    return *this;
}

Trainer::Trainer(const Trainer &other) : capacity(other.capacity), open(other.open),
                                         customersList(vector<Customer *>()), orderList(vector<OrderPair>()),
                                         salary(other.salary) {
    //Deep copy to other.customers
    for (::size_t i = 0; i < other.customersList.size(); i++) {
        this->customersList.push_back(other.customersList.at(i)->clone());
    }
    //Deep copy to other.orderPair , because Workout doesn't have operator=
    for (::size_t i = 0; i < other.orderList.size(); i++) {
        this->orderList.push_back(OrderPair(other.orderList.at(i)));
    }
}

Trainer::Trainer(int t_capacity) : capacity(t_capacity), open(false), customersList(std::vector<Customer *>()),
                                   orderList(std::vector<OrderPair>()), salary(0) {

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

/// Removes a customer from the customers list,
/// and all of the workouts he ordered, and cutting the salary accordingly
/// if no customers left, the trainer closes its session
/// \attention This function doesnt remove the customer from the heap
/// \param id The customer id
void Trainer::removeCustomer(int id) {

    /// remove customer from customer list
    for (size_t i = 0; i < customersList.size(); i++) {
        if (customersList[i]->getId() == id) {
            // removes from container and calls destructor
            customersList.erase(customersList.begin() + i);
            break;
        }
    }

    ///remove orders the  customer made
    vector<int> orders_to_erase;
    for (size_t i = 0; i < orderList.size(); i++) {
        if (orderList[i].first == id) {
            orders_to_erase.push_back(i);
        }
    }
    for (size_t i = 0; i < orders_to_erase.size(); i++) {
        int order_to_erase = orders_to_erase[i];
        orderList.erase(orderList.begin() + order_to_erase);
    }

    ///If no customers left, close trainer
    if (customersList.size() == 0) {
        closeTrainer();
    }
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids,
                    const std::vector <Workout> &workout_options) {

    for (size_t i = 0; i < workout_ids.size(); i++) {
        for (size_t j = 0; j < workout_options.size(); j++) {
            Workout current_workout = workout_options[j];
            int requested_workout_id = workout_ids[i];

            if (current_workout.getId() == requested_workout_id) {
                orderList.push_back(OrderPair(customer_id, workout_options[j]));
                cout << this->getCustomer(customer_id)->getName() + " Is Doing " + current_workout.getName() << endl;
                break;
            }
        }
    }
}

///Closes the trainer's session and accumulates its salary
void Trainer::closeTrainer() {
    //Accumulate salary
    for (size_t i = 0; i < orderList.size(); i++) {
        salary += orderList[i].second.getPrice();
    }
    //Remove orders and customers
    orderList.clear();

    for (::size_t i = 0; i < customersList.size(); i++) {
        delete (customersList[i]);
    }
    customersList.clear();
    open = false;
}

///Opens the trainer's session
void Trainer::openTrainer() {
    open = true;
}

