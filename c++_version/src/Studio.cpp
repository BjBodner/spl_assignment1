#include "../include/Studio.h"
#include <iostream>
#include <fstream>

void Studio::start() {

}

int Studio::getNumOfTrainers() const {
    return trainers.size();
}

Trainer *Studio::getTrainer(int tid) {
    return trainers.at(tid);
}

Studio::Studio() : open(false) {

}

Studio::Studio(const std::string &configFilePath) {
    std::ifstream inFile;
    std::cout << "trying to open the file at path :" << configFilePath << std::endl;
    inFile.open(configFilePath);
    if (!inFile) {
        std::cout << "Unable to open file" << std::endl;;
    }

    Studio::StudioConfigFileParser(inFile, trainers, workout_options);
    inFile.close();
}

enum ParserState {
    NumOfTrainers,
    TrainersCapacities,
    Workouts
};

/// Removes all spaces from a string and returns a pointer to it
/// \param str The string to trim
/// \return A pointer to the trimmed string
static std::string *TrimString(const std::string& str) {
    std::string *ans = new std::string("");
    for (size_t i = 0; i < str.length(); i++) {
        if (str.at(i) != ' ') {
            (*ans) += (str.at(i));
        }
    }
    //Returning a pointer to the string by value so it will 'live' after pop
    return ans;
}

/// Splits a string by a char
/// \param str The string to split
/// \param delimiter The char that will split the string
/// \return A pointer to the vector of splitted strings
static std::vector <std::string> *SplitString(const std::string& str, const char delimiter) {
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