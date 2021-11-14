#include "../include/Customer.h"

Customer::~Customer() throw() {}

int Customer::getId() const {
    return id;
}

std::string Customer::getName() const {
    return name;
}

std::vector<int> Customer::order(const std::vector <Workout> &workout_options) {
    return std::vector<int>();
}

std::string Customer::toString() const {
    return "";
}

Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id) {

}