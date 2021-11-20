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

/// helper functions
int getBestWorkoutIdx(const vector<Workout> &workout_options, const WorkoutType workouttype, const string price_selection) {
    /// get cheapest workouts
    int i = 0;
    vector<int> workouts_to_order;
    int min_price == 0;
    int lowest_id = 0;
    int workout_to_order = 0;
    int initialized = 0;
    bool correct_type = false;
    bool best_price = false;
    bool same_price_lowest_id = false;
    for (vector<Workout>::iterator it=vector.begin(); it != vector.end(); it++){

        /// check if current workout meets all conditions
        correct_type =  (it->getType() == workouttype)
        same_price_lowest_id = ((best_price == it->getPrice()) and (lowest_id > id.getId()))
        if (price_selection == "lowest") {
            /// sets the flag to true, if the current workout price is lower
            best_price = (best_price > it->getPrice());
        }
        else {
            /// sets the flag to true, if the current workout price is higher
            best_price = (best_price < it->getPrice());
        }

        /// initialize to first item in workout
        if ((initialized == 0) and correct_type){
            best_price = it->getPrice();
            lowest_id = it->getId();
            workout_to_order = i;
            initialized = 1;
        }


        /// order if current workout is correct type, and lowest price or same price and lowest id
        if (correct_type and (best_price or same_price_lowest_id)) {
            best_price = it->getPrice();
            lowest_id = it->getId();
            workout_to_order = i;
        }
        i ++;
    }

    return workout_to_order
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

    /// get cheapest workouts
    int i = 0;
    vector<int> workouts_to_order;
    int min_price == 0;
    int lowest_id = 0;
    int workout_to_order = 0;
    for (vector<Workout>::iterator it=vector.begin(); it != vector.end(); it++){

        /// initialize to first item in workout
        if (i == 0) {
            min_price = it->getPrice();
            lowest_id = it->getId();
            workout_to_order = i;
        }

        /// order if current workout is lowest price AND lowest id
        if (min_price > it->getPrice()) or ((min_price == it->getPrice()) and (lowest_id > id.getId())) {
            min_price = it->getPrice();
                lowest_id = it->getId();
                workout_to_order = i;
        }
        i ++;
    }

    workouts_to_order.push_back(workout_to_order)
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
vector<int> HeavyMuscleCustomer::order(const vector<Workout> &workout_options) {

    /// get anaerobic workouts
//    int i = 0;
    vector<Workout> anaerobic_workouts;
    for (vector<Workout>::iterator it=vector.begin(); it != vector.end(); it++){
        if (it->getType() == ANAEROBIC) {
            anaerobic_workouts.push_back(it);
        }
//        i ++;
    }

    /// TODO sort based on price from most expensive to cheapest
    vector<int> sorted_anaerobic_workouts;


    return sorted_anaerobic_workouts
}



/// full body customer
FullBodyCustomer::FullBodyCustomer(string name, int id);:name(c_name),id(c_id) {}
FullBodyCustomer::FullBodyCustomer(const FullBodyCustomer &other){
    name = other.name;
    id = other.name + 1;
}
FullBodyCustomer::~FullBodyCustomer() {
    delete name;
    delete id;
}
string FullBodyCustomer::toString() {
    return "full body customer, id: " << id << " , name: " << name;
}
vector<int> FullBodyCustomer::order(const vector<Workout> &workout_options) {

    /// get anaerobic workouts
    vector<Workout> workouts_to_order;

    /// TODO do we need to handle cases where such workouts don't exist?
    int cheapest_cardio_idx = getBestWorkoutIdx(vector, CARDIO, "lowest")
    int expensive_mixtype_idx = getBestWorkoutIdx(vector, MIXED, "highest")
    int cheapest_anaerobic_idx = getBestWorkoutIdx(vector, ANAEROBIC, "lowest")

    /// add to vector
    workouts_to_order.push_back(cheapest_cardio_idx)
    workouts_to_order.push_back(expensive_mixtype_idx)
    workouts_to_order.push_back(cheapest_anaerobic_idx)

    return workouts_to_order
}