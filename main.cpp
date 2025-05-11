#include "BodyMetric.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

// Maximum number of users, meals, and workouts supported
#define MAX_USERS 20
#define MAX_MEALS 20
#define MAX_WORKOUTS 20

// Struct to store meal information
struct Meal {
    char name[50];    // Name of the meal
    int calories;     // Calories in the meal
};

// Struct to store workout information
struct Workout {
    char activity[30];    // Name of the workout activity
    int intensity;        // Intensity level (1-4)
    int caloriesPerMin;   // Calories burned per minute
};

// Loads user data from a file into the users array
void loadUsers(const char* filename, BodyMetric users[], int& count) {
    ifstream fin(filename);
    count = 0;
    char name[50], gender, goal[10], activityLevel[20];
    int age;
    float weight, height;
    // Read each user's data from the file
    while (fin >> name >> age >> gender >> weight >> height >> goal >> activityLevel) {
        users[count].setInfo(name, age, gender[0], goal, activityLevel);
        users[count].setMetrics(weight, height);
        count++;
    }
    fin.close();
}

// Saves user data from the users array to a file
void saveUsers(const char* filename, BodyMetric users[], int count) {
    ofstream fout(filename);
    for (int i = 0; i < count; ++i) {
        fout << users[i].getName() << " " << users[i].getAge() << " " << users[i].getGender() << " "
             << users[i].getWeight() << " " << users[i].getHeight() << " "
             << users[i].getGoal() << " " << users[i].getActivityLevel() << endl;
    }
    fout.close();
}

// Loads meal data from a file into the meals array
void loadMeals(const char* filename, Meal meals[], int& mealCount) {
    ifstream fin(filename);
    mealCount = 0;
    char line[100];
    // Read each meal's data from the file
    while (fin.getline(line, 100)) {
        char* token = strtok(line, ",");
        if (!token) continue;
        strcpy(meals[mealCount].name, token);
        token = strtok(NULL, ",");
        if (token) meals[mealCount].calories = atoi(token);
        mealCount++;
    }
    fin.close();
}

// Displays all meals in the meals array
void displayMeals(const Meal meals[], int mealCount) {
    for (int i = 0; i < mealCount; ++i)
        cout << i+1 << ". " << meals[i].name << " (" << meals[i].calories << " cal)" << endl;
}

// Suggests meals that meet or exceed the minimum calorie requirement
void suggestMeals(const Meal meals[], int mealCount, int minCalories) {
    cout << "Suggested meals (>= " << minCalories << " cal):" << endl;
    for (int i = 0; i < mealCount; ++i)
        if (meals[i].calories >= minCalories)
            cout << meals[i].name << " (" << meals[i].calories << " cal)" << endl;
}

// Loads workout data from a file into the workouts array
void loadWorkouts(const char* filename, Workout workouts[], int& workoutCount) {
    ifstream fin(filename);
    workoutCount = 0;
    char line[100];
    // Read each workout's data from the file
    while (fin.getline(line, 100)) {
        char* token = strtok(line, ",");
        if (!token) continue;
        strcpy(workouts[workoutCount].activity, token);
        token = strtok(NULL, ",");
        if (token) workouts[workoutCount].intensity = atoi(token);
        token = strtok(NULL, ",");
        if (token) workouts[workoutCount].caloriesPerMin = atoi(token);
        workoutCount++;
    }
    fin.close();
}

// Displays all workouts in the workouts array
void displayWorkouts(const Workout workouts[], int workoutCount) {
    for (int i = 0; i < workoutCount; ++i)
        cout << i+1 << ". " << workouts[i].activity << " (Intensity: " << workouts[i].intensity
             << ", " << workouts[i].caloriesPerMin << " cal/min)" << endl;
}

// Suggests workouts that do not exceed the maximum calorie burn per minute
void suggestWorkouts(const Workout workouts[], int workoutCount, int maxBurn) {
    cout << "Suggested workouts (<= " << maxBurn << " cal/min):" << endl;
    for (int i = 0; i < workoutCount; ++i)
        if (workouts[i].caloriesPerMin <= maxBurn)
            cout << workouts[i].activity << " (" << workouts[i].caloriesPerMin << " cal/min)" << endl;
}

int main() {
    // Arrays to store users, meals, and workouts
    BodyMetric users[MAX_USERS];
    int userCount = 0;
    Meal meals[MAX_MEALS];
    int mealCount = 0;
    Workout workouts[MAX_WORKOUTS];
    int workoutCount = 0;

    // Load data from files
    loadUsers("userInfo.txt", users, userCount);
    loadMeals("diet_plans.txt", meals, mealCount);
    loadWorkouts("workout_plans.txt", workouts, workoutCount);

    int choice;
    do {
        // Display the main menu
        cout << "\n--- My Health Journal Menu ---\n";
        cout << "1. View all users\n";
        cout << "2. View user details\n";
        cout << "3. Add new user\n";
        cout << "4. Update user weight/height\n";
        cout << "5. Suggest meals for user\n";
        cout << "6. Suggest workouts for user\n";
        cout << "7. Compare BMI of two users\n";
        cout << "8. Save and Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            // List all users by name
            for (int i = 0; i < userCount; ++i)
                cout << i+1 << ". " << users[i].getName() << endl;
        }
        else if (choice == 2) {
            // Show details for a specific user
            int idx;
            cout << "Enter user index: "; cin >> idx; idx--;
            if (idx >= 0 && idx < userCount)
                users[idx].displayMetrics();
            else
                cout << "Invalid index.\n";
        }
        else if (choice == 3) {
            // Add a new user
            if (userCount >= MAX_USERS) { cout << "User limit reached.\n"; continue; }
            char name[50], gender, goal[10], activityLevel[20];
            int age;
            float weight, height;
            cout << "Enter name: "; cin >> name;
            cout << "Enter age: "; cin >> age;
            cout << "Enter gender (M/F): "; cin >> gender;
            cout << "Enter weight (kg): "; cin >> weight;
            cout << "Enter height (m): "; cin >> height;
            cout << "Enter goal (lose/maintain/gain): "; cin >> goal;
            cout << "Enter activity level (Sedentary/LightlyActive/ModeratelyActive/VeryActive/SuperActive): "; cin >> activityLevel;
            users[userCount].setInfo(name, age, gender[0], goal, activityLevel);
            users[userCount].setMetrics(weight, height);
            userCount++;
            cout << "User added.\n";
        }
        else if (choice == 4) {
            // Update weight and height for a specific user
            int idx;
            cout << "Enter user index: "; cin >> idx; idx--;
            if (idx >= 0 && idx < userCount) {
                float w, h;
                cout << "Enter new weight (kg): "; cin >> w;
                cout << "Enter new height (m): "; cin >> h;
                users[idx].setMetrics(w, h);
                cout << "Updated.\n";
            } else cout << "Invalid index.\n";
        }
        else if (choice == 5) {
            // Suggest meals for a specific user based on their suggested calories
            int idx;
            cout << "Enter user index: "; cin >> idx; idx--;
            if (idx >= 0 && idx < userCount) {
                float minCal = users[idx].getSuggestedCalories();
                suggestMeals(meals, mealCount, (int)minCal);
            } else cout << "Invalid index.\n";
        }
        else if (choice == 6) {
            // Suggest workouts for a specific user based on their gender
            int idx;
            cout << "Enter user index: "; cin >> idx; idx--;
            if (idx >= 0 && idx < userCount) {
                int maxBurn = (users[idx].getGender() == 'F' || users[idx].getGender() == 'f') ? 400 : 500;
                suggestWorkouts(workouts, workoutCount, maxBurn);
            } else cout << "Invalid index.\n";
        }
        else if (choice == 7) {
            // Compare BMI between two users
            int idx1, idx2;
            cout << "Enter first user index: "; cin >> idx1; idx1--;
            cout << "Enter second user index: "; cin >> idx2; idx2--;
            if (idx1 >= 0 && idx1 < userCount && idx2 >= 0 && idx2 < userCount) {
                if (compareBMI(users[idx1], users[idx2]))
                    cout << users[idx1].getName() << " has higher BMI than " << users[idx2].getName() << endl;
                else
                    cout << users[idx2].getName() << " has higher BMI than " << users[idx1].getName() << endl;
            } else cout << "Invalid indices.\n";
        }
        else if (choice == 8) {
            // Save all user data and exit
            saveUsers("userInfo.txt", users, userCount);
            cout << "Data saved. Exiting...\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
} 