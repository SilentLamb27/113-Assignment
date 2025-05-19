#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <string>
using namespace std;

class Workout {
public:
    string name;
    int intensityLevel;
    int caloriesPerMin;

    Workout();
    Workout(string name, int level, int calories);
    void printAllWorkouts(const string& filename);
};

#endif