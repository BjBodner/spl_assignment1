#include "../include/Action.h"
#include "../include/Studio.h"
#include "../include/Customer.h"

extern Studio *backup;

//TODO:CHECK IF NEEDS TO IMPLEMENT
BaseAction::BaseAction() : errorMsg("Default error message"), status(ERROR) {}

//TODO:CHECK IF NEEDS TO IMPLEMENT
BaseAction::~BaseAction() throw() {}

void BaseAction::error(std::string errorMsg) {
    std::cout << errorMsg << std::endl;
    this->errorMsg = errorMsg;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    this->status = COMPLETED;
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
    this->complete();
}

//TODO: NEED TO IMPLEMENT CUSTOMER TOSTRING
std::string OpenTrainer::toString() const {
    std::string ans = "open " + std::to_string(trainerId) + " ";
    for (size_t i = 0; i < customers.size(); i++) {
        ans += customers.at(i)->toString() + " ";
    }
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
}

Order::Order(int id) : trainerId(id) {}

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer->isOpen()) {
        error("Trainer does not exists or is not open");
        return;
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
    this->complete();
}

std::string Order::toString() const {
    std::string ans = "order " + std::to_string(trainerId) + " ";
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
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
    this->complete();
}

std::string MoveCustomer::toString() const {
    std::string ans =
            "move " + std::to_string(srcTrainer) + " " + std::to_string(dstTrainer) + " " + std::to_string(id) + " ";
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
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
    this->complete();
}

std::string Close::toString() const {
    std::string ans = "close " + std::to_string(trainerId) + " ";
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
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
    this->complete();
}

std::string CloseAll::toString() const {
    return "closeall Completed";
}

PrintWorkoutOptions::PrintWorkoutOptions() {}

void PrintWorkoutOptions::act(Studio &studio) {
    std::vector <std::string> workoutTypesStrings = std::vector<std::string>(3);
    workoutTypesStrings[WorkoutType::CARDIO] = "Cardio";
    workoutTypesStrings[WorkoutType::MIXED] = "Mixed";
    workoutTypesStrings[WorkoutType::ANAEROBIC] = "Anaerobic";
    for (size_t i = 0; i < studio.getWorkoutOptions().size(); i++) {
        Workout currWorkout = studio.getWorkoutOptions()[i];
        std::cout << currWorkout.getName() << ", " << workoutTypesStrings[currWorkout.getType()] << ", "
                  << currWorkout.getPrice() << std::endl;
    }
    this->complete();
}

//TODO: CHECK IF NEEDS TO IMPLEMENT
std::string PrintWorkoutOptions::toString() const {
    return "workout_options Completed";
}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    std::cout << "Trainer " << trainerId << " status: " << trainer->isOpen() << std::endl;
    if (!trainer->isOpen())
        return;
    std::cout << "Customers:" << std::endl;
    std::vector < Customer * > customers = trainer->getCustomers();
    for (size_t i = 0; i < customers.size(); i++) {
        std::cout << customers.at(i)->getId() << customers.at(i)->getName() << std::endl;
    }
    std::vector <OrderPair> orders = trainer->getOrders();
    for (size_t i = 0; i < orders.size(); i++) {
        std::cout << orders.at(i).second.getName() << orders.at(i).second.getPrice() << orders.at(i).first << std::endl;
    }
    std::cout << "Current Trainer's Salary: " << trainer->getSalary() << "NIS" << std::endl;
    this->complete();
}

std::string PrintTrainerStatus::toString() const {
    return "status " + std::to_string(trainerId) + " Completed";
}

PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(Studio &studio) {
    std::vector < BaseAction * > actions = studio.getActionsLog();
    for (size_t i = 0; i < actions.size(); i++) {
        std::cout << actions.at(i)->toString() << std::endl;
    }
    this->complete();
}

std::string PrintActionsLog::toString() const {
    return "log Completed";
}

BackupStudio::BackupStudio() {}

void BackupStudio::act(Studio &studio) {
    if (backup != nullptr)
        delete backup;
    backup = new Studio(studio);
    this->complete();
}

std::string BackupStudio::toString() const {
    return "backup Completed";
}

RestoreStudio::RestoreStudio() {}

void RestoreStudio::act(Studio &studio) {
    if (backup == nullptr) {
        error("No backup available");
        return;
    }
    studio = *backup;
    backup = nullptr;
    this->complete();
}

std::string RestoreStudio::toString() const {
    std::string ans = "restore ";
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
}