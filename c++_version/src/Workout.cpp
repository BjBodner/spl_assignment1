#include "../include/Workout.h"

Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):id(w_id),name(w_name),price(w_price),type(w_type) {}

//TODO: VALIDATE IMPLEMENTATION
Workout::Workout():id(0),name(""),price(0),type(CARDIO){}

//TODO: MUST IMPLEMENT
Workout &Workout::operator=(const Workout &other) {
    return *this;
}

//Getters

std::string Workout::getName() const {
    return name;
}

int Workout::getId() const {
    return id;
}

int Workout::getPrice() const {
    return price;
}

WorkoutType Workout::getType() const {
    return type;
}

//End Getters