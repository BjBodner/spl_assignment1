#include "../include/Studio.h"
#include "../include/Trainer.h"
#include <iostream>
#include <fstream>

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return actionsLog;
}

//TODO: CHECK IF STATIC IMPLEMENTATION IS CORRECT AND LEGAL
/// Splits a string by a char
/// \param str The string to split
/// \param delimiter The char that will split the string
/// \return A pointer to the vector of splitted strings
static std::vector <std::string> *SplitString(const std::string &str, const char delimiter) {
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
Studio::~Studio(){
    for (size_t i = 0; i < this->trainers.size(); i++) {
        delete trainers.at(i);
        this->trainers.at(i) = nullptr;
    }
    this->trainers.clear();
    this->workout_options.clear();
    for (size_t i = 0; i < actionsLog.size(); i++) {
        delete actionsLog.at(i);
        this->actionsLog.at(i) = nullptr;
    }
    this->actionsLog.clear();
};

Studio::Studio(const Studio& other):open(other.open), trainers(std::vector<Trainer *>()), workout_options(std::vector<Workout>()),
                                    actionsLog(std::vector<BaseAction *>()){

    /// copy trainers from other
    for (size_t i = 0; i < other.trainers.size(); i++) {
        Trainer *t = other.trainers.at(i);
        this->trainers.push_back(new Trainer(*t));
    }
    for (size_t i = 0; i < other.workout_options.size(); i++) {
        this->workout_options.push_back(Workout(other.workout_options[i]));
    }
    this->open = other.open;
    for (size_t i = 0; i < other.actionsLog.size(); i++) {
        this->actionsLog.push_back(other.actionsLog.at(i)->clone());
    }
}


Studio::Studio(Studio&& other):open(other.open), trainers(std::vector<Trainer *>()), workout_options(std::vector<Workout>()),
                               actionsLog(std::vector<BaseAction *>()){

    /// copy trainers from other
    for (size_t i = 0; i < other.trainers.size(); i++) {
        this->trainers.push_back(other.trainers.at(i));
        other.trainers[i] = nullptr;
    }
//    this->trainers = other.trainers;
    for (size_t i = 0; i < other.workout_options.size(); i++) {
        this->workout_options.push_back(Workout(other.workout_options[i]));
    }
    for (size_t i = 0; i < other.actionsLog.size(); i++) {
        this->actionsLog.push_back(other.actionsLog.at(i));
        other.actionsLog[i] = nullptr;
    }
}

Studio &Studio::operator=(const Studio &other) {
    if (&other != this) {
        this->open = other.open;

        /// delete original trainers
        for (size_t i = 0; i < this->trainers.size(); i++) {
            delete trainers.at(i);
            this->trainers.at(i) = nullptr;
        }
        this->trainers.clear();

        /// copy trainers from other
        for (size_t i = 0; i < other.trainers.size(); i++) {
            this->trainers.push_back(other.trainers.at(i));
        }

        /// delete original workouts and copy from other
        this->workout_options.clear();
        for (size_t i = 0; i < other.workout_options.size(); i++) {
            this->workout_options.push_back(other.workout_options.at(i));
        }

        /// delete original action log
        for (size_t i = 0; i < actionsLog.size(); i++) {
            delete this->actionsLog.at(i);
            this->actionsLog.at(i) = nullptr;
        }
        this->actionsLog.clear();

        /// copy action log from other
        for (size_t i = 0; i < other.actionsLog.size(); i++) {
            this->actionsLog.push_back(other.actionsLog.at(i));
        }
    }
    return *this;
}



Studio &Studio::operator=(Studio&& other) {
    if (&other != this) {
        this->open = other.open;

        /// delete original trainers
        for (size_t i = 0; i < this->trainers.size(); i++) {
            delete trainers.at(i);
            this->trainers.at(i) = nullptr;
        }
        this->trainers.clear();

        /// move pointers of trainers and remove them in other
        for (size_t i = 0; i < trainers.size(); i++) {
            this->trainers.push_back(other.trainers.at(i));
            other.trainers.at(i) = nullptr;
        }

        /// copy workout options
        this->workout_options.clear();
        for (size_t i = 0; i < workout_options.size(); i++) {
            this->workout_options.push_back(other.workout_options.at(i));
        }

        /// delete action log
        for (size_t i = 0; i < this->actionsLog.size(); i++) {
            delete this->actionsLog.at(i);
            this->actionsLog.at(i) = nullptr;
        }
        this->actionsLog.clear();

        /// move pointers to action log and remove in source
        for (size_t i = 0; i < actionsLog.size(); i++) {
            this->actionsLog.push_back(other.actionsLog.at(i));
            other.actionsLog.at(i) = nullptr;
        }
    }
    return *this;
}

int customerIDCounter = 0;

OpenTrainer* ParseOpenTrainerInput(std::vector <std::string> &inputPartials) {
    std::string trainerID = inputPartials[1];
    std::vector < Customer * > customers = std::vector<Customer *>();
    for (size_t i = 2; i < inputPartials.size(); i++) {
        std::vector <std::string> *customerPartials = SplitString(inputPartials[i], ',');
        if (customerPartials->at(1) == "swt") {
            SweatyCustomer *sweatyCustomer = new SweatyCustomer(customerPartials->at(0), customerIDCounter);
            customers.push_back(sweatyCustomer);
        } else if (customerPartials->at(1) == "chp") {
            CheapCustomer *cheapCustomer = new CheapCustomer(customerPartials->at(0), customerIDCounter);
            customers.push_back(cheapCustomer);
        } else if (customerPartials->at(1) == "mcl") {
            HeavyMuscleCustomer *heavyMuscleCustomer = new HeavyMuscleCustomer(customerPartials->at(0),
                                                                               customerIDCounter);
            customers.push_back(heavyMuscleCustomer);
        } else if (customerPartials->at(1) == "fbd") {
            FullBodyCustomer *fullBodyCustomer = new FullBodyCustomer(customerPartials->at(0), customerIDCounter);
            customers.push_back(fullBodyCustomer);
        }
        customerIDCounter++;
        delete customerPartials;
    }
    return new OpenTrainer(std::stoi(trainerID), customers);
}

//TODO: MAKE IT PRETTIER
void Studio::start() {
    open = true;
    std::cout << "Studio is now open!" << std::endl;
    std::string input = "";
    std::getline(std::cin, input);
    std::vector <std::string> *inputPartials;
    while (input != "closeall") {
        inputPartials = SplitString(input, ' ');
        std::string firstWord = inputPartials->at(0);
        if (firstWord == "open") {
            OpenTrainer *openTrainer = ParseOpenTrainerInput(*inputPartials);
            openTrainer->act(*this);
            this->actionsLog.push_back(openTrainer);

        } else if (firstWord == "order") {
            Order *order = new Order(std::stoi(inputPartials->at(1)));
            order->act(*this);
            this->actionsLog.push_back(order);

        } else if (firstWord == "move") {
            MoveCustomer *moveCustomer = new MoveCustomer(std::stoi(inputPartials->at(1)), std::stoi(inputPartials->at(2)),
                                                          std::stoi(inputPartials->at(3)));
            moveCustomer->act(*this);
            this->actionsLog.push_back(moveCustomer);

        } else if (firstWord == "close") {
            Close *close = new Close(std::stoi(inputPartials->at(1)));
            close->act(*this);
            this->actionsLog.push_back(close);

        } else if (firstWord == "workout_options") {
            PrintWorkoutOptions *print_workout_options = new PrintWorkoutOptions();
            print_workout_options->act(*this);
            this->actionsLog.push_back(print_workout_options);

        } else if (firstWord == "status") {
            PrintTrainerStatus *print_trainer_status = new PrintTrainerStatus(std::stoi(inputPartials->at(1)));
            print_trainer_status->act(*this);
            this->actionsLog.push_back(print_trainer_status);

        } else if (firstWord == "log") {
            PrintActionsLog *print_actions_log = new PrintActionsLog();
            print_actions_log->act(*this);
            this->actionsLog.push_back(print_actions_log);

        } else if (firstWord == "backup") {
            BackupStudio *backupStudio = new BackupStudio();
            backupStudio->act(*this);
            this->actionsLog.push_back(backupStudio);

        } else if (firstWord == "restore") {
            RestoreStudio *restoreStudio = new RestoreStudio();
            restoreStudio->act(*this);
            this->actionsLog.push_back(restoreStudio);

        }
        std::getline(std::cin, input);
        delete inputPartials;
    }
    CloseAll closeAll = CloseAll();
    closeAll.act(*this);
}

//Getters

std::vector <Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    if ((size_t)tid >= trainers.size()){
        return nullptr;
    }
    return trainers.at(tid);
}

//End Getters

//TODO: MUST IMPLEMENT
Studio::Studio() : open(false), trainers(std::vector<Trainer *>()), workout_options(std::vector<Workout>()),
                   actionsLog(std::vector<BaseAction *>()) {

}

Studio::Studio(const std::string &configFilePath) : Studio() {
    std::ifstream inFile;
    std::cout << "Reading config file at path :" << configFilePath << std::endl;
    inFile.open(configFilePath);
    if (!inFile) {
        std::cout << "Unable to open config file." << std::endl;
    } else {
        Studio::StudioConfigFileParser(inFile, trainers, workout_options);
    }
    inFile.close();
}

//TODO: CHECK IF STATIC IMPLEMENTATION IS CORRECT AND LEGAL
/// Removes all spaces from a string and returns a pointer to it
/// \param str The string to trim
/// \return A pointer to the trimmed string
static std::string *TrimString(const std::string &str) {
    std::string *ans = new std::string("");
    for (size_t i = 0; i < str.length(); i++) {
        if (str.at(i) != ' ') {
            (*ans) += (str.at(i));
        }
    }
    //Returning a pointer to the string by value so it will 'live' after pop
    return ans;
}

enum ParserState {
    NumOfTrainers,
    TrainersCapacities,
    Workouts
};

/// Parses a Studio config file and populates the trainers vector and workouts vector by the parsed value
/// \param inFile The stream file
/// \param trainers The trainers vector
/// \param workouts The workouts vector
void Studio::StudioConfigFileParser(std::ifstream &inFile, std::vector<Trainer *> &trainers,
                                    std::vector <Workout> &workouts) {
    //The state of the parser representing the next type
    //that the parser expects from the config file
    ParserState parserState = ParserState::NumOfTrainers;
    int currWorkoutID = 0;
    int numOfTrainers = 0;
    std::string x = "";
    while (std::getline(inFile, x)) {
        if (x == "") {
            //Empty line. ignoring
        } else if (x.at(0) == '#') {
            //Comment. ignoring
        } else {
            switch (parserState) {
                case ParserState::NumOfTrainers: {
                    //Update numOfTrainers
                    numOfTrainers = std::stoi(x);
                    //advance parserState
                    parserState = ParserState::TrainersCapacities;
                }
                    break;
                case ParserState::TrainersCapacities: {
                    //Split capacities string
                    std::vector <std::string> *capacitiesArr = SplitString(x, ',');
                    //Create trainers by capacities
                    for (int i = 0; i < numOfTrainers; i++) {
                        int capacity = std::stoi(capacitiesArr->at(i));
                        trainers.push_back(new Trainer(capacity));
                    }
                    //advance parserState
                    parserState = ParserState::Workouts;
                    delete capacitiesArr;
                }
                    break;
                case ParserState::Workouts: {
                    //Split workout string
                    std::vector <std::string> *workoutProps = SplitString(x, ',');
                    std::string name = workoutProps->at(0);
                    int price = std::stoi(workoutProps->at(2));
                    //Trim type string
                    std::string *stringType = TrimString(workoutProps->at(1));
                    //Parse workout type from string to WorkoutType
                    WorkoutType type;
                    if (*stringType == "Anaerobic") {
                        type = WorkoutType::ANAEROBIC;
                    } else if (*stringType == "Mixed") {
                        type = WorkoutType::MIXED;
                    } else if (*stringType == "Cardio") {
                        type = WorkoutType::CARDIO;
                    }
                    //Create the Workout instance
                    Workout currWorkout(currWorkoutID, name, price, type);
                    //Increment the workout id
                    currWorkoutID++;
                    //Add workout to workouts vector
                    workouts.push_back(currWorkout);
                    //Delete pointers
                    delete workoutProps;
                    delete stringType;
                }
                    break;
            }
        }
    }
}