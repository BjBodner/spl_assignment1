#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"

class Studio{
public:
    Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    Studio& operator=(const Studio& other);
    virtual ~Studio();
    Studio(const Studio& other);
    Studio(Studio&& other);
    Studio& operator=(Studio&& other);
    void steal(Studio& other);

private:
    static void StudioConfigFileParser(std::ifstream& inFile, std::vector<Trainer *> &trainers, std::vector<Workout> &workouts);
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    int customerIDCounter;
    OpenTrainer *ParseOpenTrainerInput(std::vector <std::string> &inputPartials);
};

#endif