#include "../include/Customer.h"

//TODO: MUST IMPLEMENT
Customer::~Customer() throw() {}

int Customer::getId() const {
    return id;
}

std::string Customer::getName() const {
    return name;
}

//TODO: MUST IMPLEMENT
Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id) {

}