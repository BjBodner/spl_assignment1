//
// Created by benjy on 11/20/2021.
//


#include <iostream>
#include "../include/Customer.h"
#include <bits/stdc++.h>
using namespace std;

//TODO: MUST IMPLEMENT
Customer::~Customer() {}

int Customer::getId() const {
    return id;
}

string Customer::getName() const {
    return name;
}

//TODO: MUST IMPLEMENT
Customer::Customer(string c_name, int c_id):name(c_name),id(c_id) {

}


void printWorkout(const Workout current_workout, string prefix){
    string workout_description = prefix + "name: " + current_workout.getName() + ", id: " + to_string(current_workout.getId()) + ", type: " + to_string(current_workout.getType()) + ", price: " + to_string(current_workout.getPrice());
    cout << workout_description << endl;
}


/// Sweaty customer class
SweatyCustomer::SweatyCustomer(string c_name, int c_id): Customer(c_name, c_id) {}
string SweatyCustomer::toString() const{
    return "sweaty customer, id: " + to_string(this->getId()) + " , name: " + this->getName();
}
vector<int> SweatyCustomer::order(const vector<Workout> &workout_options) {

    /// get cardio workouts
    vector<int> workouts_to_order;

    for (int i=0; i < workout_options.size(); i++) {

        Workout current_workout = workout_options[i];
        if (current_workout.getType() == CARDIO) {
            workouts_to_order.push_back(i);

            /// for debugging
            printWorkout(current_workout, "sweaty customer: " + this->getName() + " , id: " + to_string(this->getId()) + " added ");
        }

    }

    return workouts_to_order;
}


///// Cheap Customer class
CheapCustomer::CheapCustomer(string c_name, int c_id):Customer(c_name, c_id) {}
string CheapCustomer::toString() const{
    return "cheap customer, id: " + to_string(this->getId()) + " , name: " + this->getName();

}
vector<int> CheapCustomer::order(const vector<Workout> &workout_options) {

    /// get cheapest workouts
    int min_price = 0;
    int lowest_id = 0;
    int workout_to_order = 0;
    for (int i=0; i < workout_options.size(); i++) {

        Workout current_workout = workout_options[i];
        /// initialize to first item in workout
        if (i == 0) {
            min_price = current_workout.getPrice();
            lowest_id = current_workout.getId();
            workout_to_order = i;
        }

        /// order if current workout is lowest price AND lowest id
        if ((min_price > current_workout.getPrice()) or ((min_price == current_workout.getPrice()) and (lowest_id > current_workout.getId()))) {
            min_price = current_workout.getPrice();
            lowest_id = current_workout.getId();
            workout_to_order = i;
        }
    }

    /// add the cheapest workout to the vector
    vector<int> workouts_to_order;
    workouts_to_order.push_back(workout_to_order);

    Workout current_workout = workout_options[workout_to_order];
    printWorkout(current_workout, "cheap customer: " + this->getName() + " , id: " + to_string(this->getId()) + " added ");

    return workouts_to_order;

}


///// Heavy muscle customer
HeavyMuscleCustomer::HeavyMuscleCustomer(string c_name, int c_id):Customer(c_name, c_id) {}
string HeavyMuscleCustomer::toString() const {
    return "heavy muscle customer, id: " + to_string(this->getId()) + " , name: " + this->getName();

}
vector<int> HeavyMuscleCustomer::order(const vector<Workout> &workout_options) {

    /// get anaerobic workouts

    vector<int> workouts_to_order;

    for (int i=0; i < workout_options.size(); i++) {
        Workout current_workout = workout_options[i];

        if (current_workout.getType() == ANAEROBIC) {
            printWorkout(current_workout, "BEFORE SORTING heavy customer: " + this->getName() + " , id: " + to_string(this->getId()) + " added ");
            workouts_to_order.push_back(i);
        }
    }


    /// TODO sort based on price from most expensive to cheapest

    return workouts_to_order;
}



///// helper functions
int getBestWorkoutIdx(const vector<Workout> &workout_options, const WorkoutType workouttype, const string price_selection) {
    /// get cheapest workouts
    int i = 0;
    vector<int> workouts_to_order;
    int min_price = 0;
    int lowest_id = 0;
    int workout_to_order = 0;
    int initialized = 0;
    bool is_correct_type = false;
    bool is_best_price = false;
    int best_price = 0;
    bool is_same_price_lowest_id = false;


    for (int i=0; i < workout_options.size(); i++) {
        Workout current_workout = workout_options[i];

        /// check if current workout meets all conditions
        is_correct_type =  (current_workout.getType() == workouttype);
        is_same_price_lowest_id = ((best_price == current_workout.getPrice()) and (lowest_id > current_workout.getId()));
        if (price_selection == "lowest") {
            /// sets the flag to true, if the current workout price is lower
            is_best_price = (best_price > current_workout.getPrice());
        }
        else {
            /// sets the flag to true, if the current workout price is higher
            is_best_price = (best_price < current_workout.getPrice());
        }

        /// initialize to first item in workout
        if ((initialized == 0) and is_correct_type){
            best_price = current_workout.getPrice();
            lowest_id = current_workout.getId();
            workout_to_order = i;
            initialized = 1;
        }


        /// order if current workout is correct type, and lowest price or same price and lowest id
        if (is_correct_type and (is_best_price or is_same_price_lowest_id)) {
            best_price = current_workout.getPrice();
            lowest_id = current_workout.getId();
            workout_to_order = i;
        }
    }

    return workout_to_order;
}



///// full body customer
FullBodyCustomer::FullBodyCustomer(string c_name, int c_id):Customer(c_name, c_id) {}

string FullBodyCustomer::toString() const{
    return "full body customer, id: " + to_string(this->getId()) + " , name: " + this->getName();
}
vector<int> FullBodyCustomer::order(const vector<Workout> &workout_options) {

    /// get anaerobic workouts
    vector<int> workouts_to_order;

    /// TODO do we need to handle cases where such workouts don't exist?
    int cheapest_cardio_idx = getBestWorkoutIdx(workout_options, CARDIO, "lowest");
    int expensive_mixtype_idx = getBestWorkoutIdx(workout_options, MIXED, "highest");
    int cheapest_anaerobic_idx = getBestWorkoutIdx(workout_options, ANAEROBIC, "lowest");

    /// add to vector
    workouts_to_order.push_back(cheapest_cardio_idx);
    workouts_to_order.push_back(expensive_mixtype_idx);
    workouts_to_order.push_back(cheapest_anaerobic_idx);

    /// for debugging
    for (int i=0; i < workouts_to_order.size(); i++) {
        Workout current_workout = workout_options[workouts_to_order[i]];
        printWorkout(current_workout,
                     "fully body customer: " + this->getName() + " , id: " + to_string(this->getId()) + " added ");
    }
    return workouts_to_order;
}


//
