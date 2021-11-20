//
// Created by benjy on 11/20/2021.
//

#include "../include/Workout.h"


using namespace std;


Workout::Workout(int w_id, string w_name, int w_price, WorkoutType w_type):id(w_id),name(w_name),price(w_price),type(w_type) {}
Workout::Workout():id(0),name(""),price(0),type(CARDIO){}
Workout &Workout::operator=(const Workout &other) {
    int _id = other.getId() + 1;
    string _name = other.getName();
    int _price = other.getPrice();
    WorkoutType _type = other.getType();

    /// DANGER this may cause a memory leak
    Workout *w = new Workout(_id, _name, _price, _type);
    return *w;

}

//Getters

string Workout::getName() const {
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