#include "../include/Action.h"
#include "../include/Studio.h"
#include "../include/Customer.h"

//TODO:CHECK IF NEEDS TO IMPLEMENT
BaseAction::BaseAction() : errorMsg("Default error message"), status(ERROR) {}

//TODO:CHECK IF NEEDS TO IMPLEMENT
BaseAction::~BaseAction() throw() {}

void BaseAction::error(std::string errorMsg) {
    std::cout << errorMsg << std::endl;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {}

//TODO: MUST CHECK IF NULLPTR IS GIVEN WHEN NEEDED
//TODO: ENSURE WHETHER NEEDS TO CHECK CAPACITY BEFORE ADDING CUSTOMERS
void OpenTrainer::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || trainer->isOpen()) {
        error("Workout session does not exist or is already open");
        return;
    }
    //Add customers to the trainer
    for (size_t i = 0; i < customers.size(); i++) {
        trainer->addCustomer(customers[i]);
    }
    //Open trainer's session
    trainer->openTrainer();
}

//TODO: CHECK IF NEEDS TO IMPLEMENT
std::string OpenTrainer::toString() const {
    return "Not implemented";
}

Order::Order(int id) : trainerId(id) {}

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer->isOpen()) {
        error("Trainer does not exists or is not open");
    }
    std::vector < Customer * > customers = trainer->getCustomers();
    for (size_t i = 0; i < customers.size(); i++) {
        Customer *curr = customers[i];
        std::vector<int> orders = curr->order(studio.getWorkoutOptions());
        //Print log to screen
        for (size_t j = 0; j < orders.size(); j++) {
            for (size_t k = 0; k < studio.getWorkoutOptions().size(); k++) {
                if (studio.getWorkoutOptions()[k].getId() == orders[j]) {
                    std::cout << curr->getName() << " is doing " << studio.getWorkoutOptions()[k].getName()
                              << std::endl;
                }
            }
        }
        //Add orders to trainer
        trainer->order(curr->getId(), orders, studio.getWorkoutOptions());
    }
}

//TODO: CHECK IF NEEDS TO IMPLEMENT
std::string Order::toString() const {
    return "Not Implemented";
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) : srcTrainer(src), dstTrainer(dst), id(customerId) {}

void MoveCustomer::act(Studio &studio) {
    Trainer *srcTrainerPTR = studio.getTrainer(srcTrainer);
    Trainer *dstTrainerPTR = studio.getTrainer(dstTrainer);
    Customer *customer = srcTrainerPTR->getCustomer(id);
    if (srcTrainerPTR == nullptr || dstTrainerPTR == nullptr || !srcTrainerPTR->isOpen()
        || !dstTrainerPTR->isOpen() || customer == nullptr) {
        error("Cannot move customer");
        return;
    }
    //Transfer customer's orders from one trainer to the other
    std::vector <OrderPair> srcOrders = srcTrainerPTR->getOrders();
    std::vector<int> customerOrders = std::vector<int>();
    for (size_t i = 0; i < srcOrders.size(); i++) {
        if (srcOrders[i].first == id) {
            //It's an order of the customer
            customerOrders.push_back(srcOrders[i].second.getId());
        }
    }
    //Transfer the customer
    srcTrainerPTR->removeCustomer(id);
    dstTrainerPTR->addCustomer(customer);
    dstTrainerPTR->order(id, customerOrders, studio.getWorkoutOptions());
}

//TODO: CHECK IF NEEDS TO IMPLEMENT
std::string MoveCustomer::toString() const {
    return "Not Implemented";
}

Close::Close(int id) : trainerId(id) {}

void Close::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer->isOpen()) {
        error("Trainer does not exist or is not open");
        return;
    }
    trainer->closeTrainer();
    std::cout << "Trainer " << trainerId << "closed. Salary " << trainer->getSalary() << "NIS" << std::endl;
}

//TODO: CHECK IF NEEDS TO IMPLEMENT
std::string Close::toString() const {
    return "Not Implemented";
}

CloseAll::CloseAll() {}

void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); i++) {
        Trainer *trainer = studio.getTrainer(i);
        if (trainer->isOpen()) {
            trainer->closeTrainer();
            std::cout << "Trainer " << i << "closed. Salary " << trainer->getSalary() << "NIS" << std::endl;
        }
    }
}

//TODO: CHECK IF NEEDS TO IMPLEMENT
std::string CloseAll::toString() const {
    return "Not Implemented";
}

PrintWorkoutOptions::PrintWorkoutOptions() {}

void PrintWorkoutOptions::act(Studio &studio) {
    std::vector<std::string> workoutTypesStrings = std::vector<std::string>(3);
    workoutTypesStrings[WorkoutType::CARDIO] = "Cardio";
    workoutTypesStrings[WorkoutType::MIXED] = "Mixed";
    workoutTypesStrings[WorkoutType::ANAEROBIC] = "Anaerobic";
    for (size_t i = 0; i < studio.getWorkoutOptions().size(); i++) {
        Workout currWorkout = studio.getWorkoutOptions()[i];
        std::cout << currWorkout.getName() << ", " << workoutTypesStrings[currWorkout.getType()] << ", " << currWorkout.getPrice() << std::endl;
    }
}

//TODO: CHECK IF NEEDS TO IMPLEMENT
std::string PrintWorkoutOptions::toString() const {
    return "Not Implemented";
}