#include <iostream>
#include <fstream>
#include "WorkoutPlan.h"
using namespace std;

Workout::Workout(){
  name="";
  intensityLevel=0;
  caloriesPerMin=0;
}

Workout::Workout(string n, int level, int cal){
  name=n;
  intensityLevel=level;
  caloriesPerMin=cal;
}

void Workout::printAllWorkouts(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    string name;
    int level, calories;
    while (getline(file, name, ',')) {
        file >> level;
        file.ignore(); // ignore comma
        file >> calories;
        file.ignore(); // ignore comma

        cout << "Activity name        : " << name << "\n";
        cout << "Intensity level      : " << level << "\n";
        cout << "Calories per minute  : " << calories << "\n";
        cout << "-----------------------------\n";
    }
    file.close();
}