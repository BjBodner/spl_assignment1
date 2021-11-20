#include "../include/Workout.h"
using namespace std
Workout::Workout(int w_id, string w_name, int w_price, WorkoutType w_type):id(w_id),name(w_name),price(w_price),type(w_type) {}
Workout::Workout():id(0),name(""),price(0),type(CARDIO){}
Workout::Workout(const Workout &other):{
    id = other.id + 1
    name = other.name
    price = other.price
    type = other.type
}
Workout &Workout::operator=(const Workout &other) {
    /// Note, we might get an error here, since these fields are supposed to be const
    id = other.id + 1
    name = other.name
    price = other.price
    type = other.type
    return *this;
}
Workout::~Workout() {
    delete id;
    delete name;
    delete price;
    delete type;
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