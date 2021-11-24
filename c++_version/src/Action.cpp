#include "../include/Action.h"
#include "../include/Studio.h"
#include "../include/Customer.h"
#include <bits/stdc++.h>

using namespace std;

extern Studio *backup = nullptr;

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

void BaseAction::complete() {
    this->status = COMPLETED;
}
ActionStatus BaseAction::getStatus() const  {
    return this->status;
}
OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {}
//OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {}

OpenTrainer::~OpenTrainer() {
    for (::size_t i = 0; i < customers.size(); i++) {
        delete (customers[i]);
    }
    customers.clear();
}

BaseAction *OpenTrainer::clone() {
    OpenTrainer *ot = new OpenTrainer(this->trainerId, this->customers);
    if (this->getStatus() == COMPLETED){
        ot->complete();
    };
    return ot;
}

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
        if (i < trainer->getCapacity()){
            trainer->addCustomer(customers[i]->clone());
        }
        else {
            error("Warning did not add customer: " + customers[i]->toString() + ", trainer: "  + to_string(trainerId) + ", is at full capacity");
        }

    }
    //Open trainer's session
    trainer->openTrainer();
    this->complete();
}

//TODO: NEED TO IMPLEMENT CUSTOMER TOSTRING
std::string OpenTrainer::toString() const {
    std::string ans = "open " + to_string(trainerId) + " ";
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

static std::vector <std::string>* SplitString(const std::string &str, const char delimiter) {
    std::vector <std::string> *ans = new std::vector<std::string>();
    std::string tempSum = "";
    for (size_t i = 0; i < str.length(); i++) {
        if (str.at(i) != delimiter) {
            tempSum += str.at(i);
        } else {
            ans->push_back(tempSum);
            tempSum = "";
        }
    }
    ans->push_back(tempSum);
    //Returning a pointer to the vector by value so it will 'live' after pop
    return ans;
}

//std::vector <std::string> s = SplitString("adsf", ",");
//
//OpenTrainer ParseOpenTrainerInput(std::vector <std::string> &inputPartials) {
//    std::string trainerID = inputPartials[1];
//    std::vector < Customer * > customers = std::vector<Customer *>();
//    for (size_t i = 2; i < inputPartials.size(); i++) {
//        std::vector <std::string> *customerPartials = SplitString(inputPartials[i], ',');
//        if (customerPartials->at(1) == "swt") {
//            SweatyCustomer *sweatyCustomer = new SweatyCustomer(customerPartials->at(0), customers.size());
//            customers.push_back(sweatyCustomer);
//        } else if (customerPartials->at(1) == "chp") {
//            CheapCustomer *cheapCustomer = new CheapCustomer(customerPartials->at(0), customers.size());
//            customers.push_back(cheapCustomer);
//        } else if (customerPartials->at(1) == "mcl") {
//            HeavyMuscleCustomer *heavyMuscleCustomer = new HeavyMuscleCustomer(customerPartials->at(0),
//                                                                               customers.size());
//            customers.push_back(heavyMuscleCustomer);
//        } else if (customerPartials->at(1) == "fbd") {
//            FullBodyCustomer *fullBodyCustomer = new FullBodyCustomer(customerPartials->at(0), customers.size());
//            customers.push_back(fullBodyCustomer);
//        }
//        delete customerPartials;
//    }
//
//    return OpenTrainer(stoi(trainerID), customers);
//}


Order::Order(int id) : trainerId(id) {}

BaseAction *Order::clone() {
    Order *o = new Order(this->trainerId);
    if (this->getStatus() == COMPLETED){
        o->complete();
    };
    return o;
}

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
//        for (size_t j = 0; j < orders.size(); j++) {
//            for (size_t k = 0; k < studio.getWorkoutOptions().size(); k++) {
//                if (studio.getWorkoutOptions()[k].getId() == orders[j]) {
//                    std::cout << curr->getName() << " is doing " << studio.getWorkoutOptions()[k].getName()
//                              << std::endl;
//                }
//            }
//        }
        //Add orders to trainer
        trainer->order(curr->getId(), orders, studio.getWorkoutOptions());
    }
    this->complete();
}

std::string Order::toString() const {
    std::string ans = "order " + to_string(trainerId) + " ";
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) : srcTrainer(src), dstTrainer(dst), id(customerId) {}

BaseAction *MoveCustomer::clone() {
    MoveCustomer *mc = new MoveCustomer(this->srcTrainer, this->dstTrainer, this->id);
    if (this->getStatus() == COMPLETED){
        mc->complete();
    };
    return mc;
}

void MoveCustomer::act(Studio &studio) {
    Trainer *srcTrainerPTR = studio.getTrainer(srcTrainer);
    Trainer *dstTrainerPTR = studio.getTrainer(dstTrainer);
    Customer *customer = srcTrainerPTR->getCustomer(id);
    if (srcTrainerPTR == nullptr || dstTrainerPTR == nullptr || !srcTrainerPTR->isOpen()
        || !dstTrainerPTR->isOpen() || customer == nullptr || dstTrainerPTR->getCapacity() == dstTrainerPTR->getCustomers().size()) {
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
    if (srcTrainerPTR->getCustomers().size() == 0) {
        srcTrainerPTR->closeTrainer();
    }
    dstTrainerPTR->addCustomer(customer);
    dstTrainerPTR->order(id, customerOrders, studio.getWorkoutOptions());
    this->complete();
}

std::string MoveCustomer::toString() const {
    std::string ans = "move " + to_string(srcTrainer) + " " + to_string(dstTrainer) + " " + to_string(id) + " ";
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
}

Close::Close(int id) : trainerId(id) {}

BaseAction *Close::clone() {
    Close *c = new Close(this->trainerId);
    if (this->getStatus() == COMPLETED){
        c->complete();
    };
    return c;
}

void Close::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer->isOpen()) {
        error("Trainer does not exist or is not open");
        return;
    }
    trainer->closeTrainer();
    std::cout << "Trainer " << trainerId << " closed. Salary " << trainer->getSalary() << "NIS" << std::endl;
    this->complete();
}

std::string Close::toString() const {
    std::string ans = "close " + to_string(trainerId) + " ";
    if (getStatus() == ERROR) {
        ans += "Error: " + getErrorMsg();
    } else {
        ans += "Completed";
    }
    return ans;
}


CloseAll::CloseAll() {}

BaseAction *CloseAll::clone() {
    CloseAll *ca = new CloseAll();
    if (this->getStatus() == COMPLETED){
        ca->complete();
    };
    return ca;
}

void CloseAll::act(Studio &studio) {

    std::vector<int> salaries;

    for (int i = 0; i < studio.getNumOfTrainers(); i++) {
        Trainer *trainer = studio.getTrainer(i);
        if (trainer->isOpen()) {
            trainer->closeTrainer();
            salaries.push_back(trainer->getSalary());
//            std::cout << "Trainer " << i << " closed. Salary " << trainer->getSalary() << "NIS" << std::endl;
        }
    }

    /// sort in descending order
    sort( salaries.begin(), salaries.end());
    for (int i = salaries.size() - 1; i >= 0 ; i--) {
        for (int j = 0; j < studio.getNumOfTrainers(); j++) {
            if (studio.getTrainer(j)->getSalary() == salaries.at(i)){
                std::cout << "Trainer " << j << " closed. Salary " << salaries.at(i) << "NIS" << std::endl;
            }
        }
    }
    this->complete();
}

std::string CloseAll::toString() const {
    return "closeall Completed";
}

PrintWorkoutOptions::PrintWorkoutOptions() {}

BaseAction *PrintWorkoutOptions::clone() {
    PrintWorkoutOptions *pwo = new PrintWorkoutOptions();
    if (this->getStatus() == COMPLETED){
        pwo->complete();
    };
    return pwo;
}

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

BaseAction *PrintTrainerStatus::clone() {
    PrintTrainerStatus *pts = new PrintTrainerStatus(this->trainerId);
    if (this->getStatus() == COMPLETED){
        pts->complete();
    };
    return pts;
}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);

    if (trainer == nullptr)
        return;

//    string trainer_status = "closed";
//    if (trainer->isOpen())
//        string trainer_status = "open";

    if (trainer->isOpen())
        std::cout << "Trainer " << trainerId << " status: open" << std::endl;
    else {
        std::cout << "Trainer " << trainerId << " status: closed" << std::endl;
        return;
    }


    /// print customers
    std::cout << "Customers:" << std::endl;
    std::vector < Customer * > customers = trainer->getCustomers();
    for (size_t i = 0; i < customers.size(); i++) {
        std::cout << customers.at(i)->getId() << " "  << customers.at(i)->getName() << std::endl;
    }

    /// print Orders
    std::cout << "Orders:" << std::endl;
    std::vector <OrderPair> orders = trainer->getOrders();
    for (size_t i = 0; i < orders.size(); i++) {
        std::cout << orders.at(i).second.getName() << " " << orders.at(i).second.getPrice() << " " << orders.at(i).first << std::endl;
    }

    /// print Salary
    std::cout << "Current Trainer's Salary: " << trainer->getSalary() << "NIS" << std::endl;
    this->complete();
}

std::string PrintTrainerStatus::toString() const {
    return "status " + to_string(trainerId) + " Completed";
}
//
PrintActionsLog::PrintActionsLog() {}

BaseAction *PrintActionsLog::clone() {
    PrintActionsLog *pal = new PrintActionsLog();
    if (this->getStatus() == COMPLETED){
        pal->complete();
    };
    return pal;
}

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

BaseAction *BackupStudio::clone() {
    BackupStudio *bs = new BackupStudio();
    if (this->getStatus() == COMPLETED){
        bs->complete();
    };
    return bs;
}

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

BaseAction *RestoreStudio::clone() {
    RestoreStudio *rs = new RestoreStudio();
    if (this->getStatus() == COMPLETED){
        rs->complete();
    };
    return rs;
}

void RestoreStudio::act(Studio &studio) {
    if(backup== nullptr){
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