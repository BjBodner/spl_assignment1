#include "../include/Workout.h"

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