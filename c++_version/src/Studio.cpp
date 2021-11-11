#include "../include/Studio.h"
#include <iostream>
#include <fstream>

void Studio::start() {

}

Studio::Studio() {

}

Studio::Studio(const std::string &configFilePath) {
    std::ifstream inFile;
    std::cout << "trying to open the file at path :" << configFilePath << std::endl;
    inFile.open(configFilePath);
    if (!inFile) {
        std::cout << "Unable to open file" << std::endl;;
    }
    StudioConfigFileParser(inFile,trainers,workout_options);
    inFile.close();
}

enum ParserState {
        NumOfTrainers,
        TrainersCapacities,
        Workouts
};

static void StudioConfigFileParser(const std::ifstream &inFile,std::vector<Trainer *> &trainers,std::vector<Workout> &workouts){
    //The state of the parser representing the next type
    //that the parser expects from the config file
    ParserState parserState = ParserState::NumOfTrainers;
    std::string x;
    int numOfTrainers = 0;
    while (std::getline(inFile,x)) {
        if(x == ""){
            //Empty line. ignoring
        }
        else if(x.at(0) == "#") {
            //Comment. ignoring
        }
        else {
            switch (parserState) {
                case ParserState::NumOfTrainers{
                    numOfTrainers = std::stoi(x);
                    parserState = ParserState::TrainersCapacities;
                    break;
                }
                case ParserState::TrainersCapacities{
                    for(int i=0;i<numOfTrainers;i++){
                        int capacity = std::stoi(x.substr(i,x.find(',')));
                        trainers.push_back(new Trainer(capacity));
                    }
                    parserState = ParserState::Workouts;
                }
                case ParserState::Workouts{

                }
            }
        }
        std::cout << "Line:" << x << std::endl;
    }
}