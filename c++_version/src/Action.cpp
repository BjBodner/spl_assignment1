#include "../include/Action.h"
#include "../include/Studio.h"
#include "../include/Customer.h"

//TODO:CHECK IF NEEDS TO IMPLEMENT
BaseAction::BaseAction():errorMsg("Default error message"),status(ERROR) {}

//TODO:CHECK IF NEEDS TO IMPLEMENT
BaseAction::~BaseAction() throw() {}

//TODO:IF NEEDS TO IMPLEMENT
void BaseAction::error(std::string errorMsg) {}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id),customers(customersList) {}

//TODO: MUST CHECK IF NULLPTR IS THROWN WHEN NEEDED
void OpenTrainer::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer== nullptr || trainer->isOpen()){
        error("Workout session does not exist or is already open");
        return;
    }
    for (size_t i = 0; i < customers.size(); ++i) {
        Customer* curr = customers[i];
        trainer->order(curr->getId(),curr->order(studio.getWorkoutOptions()),studio.getWorkoutOptions());
    }
    trainer->openTrainer();
}

//TODO: MUST IMPLEMENT
std::string OpenTrainer::toString() const {
    return "Not implemented";
}

//TODO: MUST IMPLEMENT
Order::Order(int id):trainerId(id) {

}

//TODO: MUST IMPLEMENT
void Order::act(Studio &studio) {

}

//TODO: MUST IMPLEMENT
std::string Order::toString() const {
    return "Not Implemented";
}