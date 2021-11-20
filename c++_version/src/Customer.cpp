#include "../include/Customer.h"
using namespace std;

//TODO: MUST IMPLEMENT
Customer::~Customer() throw() {}

int Customer::getId() const {
    return id;
}

string Customer::getName() const {
    return name;
}

//TODO: MUST IMPLEMENT
Customer::Customer(string c_name, int c_id):name(c_name),id(c_id) {

}

/// Sweaty customer class
SweatyCustomer::SweatyCustomer(string name, int id);:name(c_name),id(c_id) {}
SweatyCustomer::SweatyCustomer(const SweatyCustomer &other){
        name = other.name;
        id = other.name + 1;
    }
SweatyCustomer::~SweatyCustomer() {
    delete name;
    delete id;
}
string SweatyCustomer::toString() {
    return "sweaty customer, id: " << id << " , name: " << name;
}
vector<int> SweatyCustomer::order(const vector<Workout> &workout_options) {

        /// get cardio workouts
        int i = 0;
        vector<int> workouts_to_order;
        for (vector<Workout>::iterator it=vector.begin(); it != vector.end(); it++){
            if (it->getType() == CARDIO) {
                workouts_to_order.push_back(i);
            }
            i ++;
        }

        return workouts_to_order
    }




/// Cheap Customer class
CheapCustomer::CheapCustomer(string name, int id);:name(c_name),id(c_id) {}
CheapCustomer::CheapCustomer(const CheapCustomer &other){
    name = other.name;
    id = other.name + 1;
}
CheapCustomer::~CheapCustomer() {
    delete name;
    delete id;
}
string CheapCustomer::toString() {
    return "cheap customer, id: " << id << " , name: " << name;
}
vector<int> CheapCustomer::order(const vector<Workout> &workout_options) {

    /// get cardio workouts
    int i = 0;
    vector<int> workouts_to_order;
    int min_price == 0;
    int lowest_id = 0;

    int workout_to_order = 0;
    for (vector<Workout>::iterator it=vector.begin(); it != vector.end(); it++){

        /// initialize to first item in workout
        if (i == 0) {
            min_type = it->getPrice();
            lowest_id = it->getId();
            workout_to_order = i;
        }

        /// order if current workout is lowest price AND lowest id
        if (min_type => it->getPrice()) and (lowest_id > id.getId()) {
                min_type = it->getPrice();
                lowest_id = it->getId();
                workout_to_order = i;
        }
        i ++;
    }

    return workouts_to_order
}


/// Heavy muscle customer
HeavyMuscleCustomer::HeavyMuscleCustomer(string name, int id);:name(c_name),id(c_id) {}
HeavyMuscleCustomer::HeavyMuscleCustomer(const HeavyMuscleCustomer &other){
    name = other.name;
    id = other.name + 1;
}
HeavyMuscleCustomer::~HeavyMuscleCustomer() {
    delete name;
    delete id;
}
string HeavyMuscleCustomer::toString() {
    return "heavy muscle customer, id: " << id << " , name: " << name;
}
vector<int> SweatyCustomer::order(const vector<Workout> &workout_options) {

    /// get anaerobic workouts
    int i = 0;
    vector<int> anaerobic;
    for (vector<Workout>::iterator it=vector.begin(); it != vector.end(); it++){
        if (it->getType() == ANAEROBIC) {
            anaerobic.push_back(i);
        }
        i ++;
    }

    return workouts_to_order
}