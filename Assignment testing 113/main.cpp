#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Person.h"
#include "DietProtocol.h"
using namespace std;

const int Max_Person = 100;
const int MAX_WORKOUTS = 20; // maximum workout activity
const int MAX_MEALS = 100;

void PersonInfo(Person person[], int userCount, int loggedInIndex);
void viewCurrentProgress(const string& username);

string normalizeName(string name){
    if (!name.empty()){
        if(name[0] >= 'a' && name[0] <= 'z')
            name[0] -= ('a' - 'A');
        for (size_t i = 1; i < name.length(); ++i){
            if (name[i] >= 'A' && name[i] <= 'Z')
                name[i] += ('a' - 'A');
        }
    }
    return name;
}

bool isAlphabetic(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) 
          return false;
    }
    return true;
}


void generateAutoMealPlan(const string& gender){
    struct Meal {
    string type;
    string name;
    int calories;
    };

  Meal breakfasts[MAX_MEALS], lunches[MAX_MEALS], dinners[MAX_MEALS], snacks[MAX_MEALS];
    int breakfastCount = 0, lunchCount = 0, dinnerCount = 0, snackCount = 0;

    ifstream file("diet_plans.txt");
    if (!file) {
        cout << "Cannot open file: diet_plans.txt\n";
        return;
    }

    string mealType, description;
    int calories;

    while (getline(file, mealType, ',')) {
        getline(file, description, ',');
        file >> calories;
        file.ignore(); // Skip newline

        if (mealType == "Breakfast" && breakfastCount < MAX_MEALS) {
            breakfasts[breakfastCount++] = {mealType, description, calories};
        } else if (mealType == "Lunch" && lunchCount < MAX_MEALS) {
            lunches[lunchCount++] = {mealType, description, calories};
        } else if (mealType == "Dinner" && dinnerCount < MAX_MEALS) {
            dinners[dinnerCount++] = {mealType, description, calories};
        } else if (mealType == "Snack" && snackCount < MAX_MEALS) {
            snacks[snackCount++] = {mealType, description, calories};
        }
    }

    file.close();

    if (breakfastCount == 0 || lunchCount == 0 || dinnerCount == 0 || snackCount == 0) {
        cout << "Insufficient meal data to generate a meal plan.\n";
        return;
    }

    srand(time(0));
    int minCalories = (gender == "female" || gender == "F" || gender == "f") ? 1200 : 1500;
    int totalCalories = 0;

    cout << "\n======= Auto-Generated Meal Plan =======\n";

    int bIndex = rand() % breakfastCount;
    cout << "Breakfast: " << breakfasts[bIndex].name << " (" << breakfasts[bIndex].calories << " cal)\n";
    totalCalories += breakfasts[bIndex].calories;

    int lIndex = rand() % lunchCount;
    cout << "Lunch: " << lunches[lIndex].name << " (" << lunches[lIndex].calories << " cal)\n";
    totalCalories += lunches[lIndex].calories;

    int dIndex = rand() % dinnerCount;
    cout << "Dinner: " << dinners[dIndex].name << " (" << dinners[dIndex].calories << " cal)\n";
    totalCalories += dinners[dIndex].calories;

    while (totalCalories < minCalories && snackCount > 0) {
        int sIndex = rand() % snackCount;
        cout << "Snack: " << snacks[sIndex].name << " (" << snacks[sIndex].calories << " cal)\n";
        totalCalories += snacks[sIndex].calories;
    }

    cout << "Total Calories: " << totalCalories << " cal\n";
}


int main() {
    Person person[Max_Person];
    int userCount = 0;

    // Load from userInfo.txt
    ifstream file("userInfo.txt");
    if (file.is_open()) {
        string name, goal;
        int age;
        char gender;
        float weight, height;

        while (file >> name >> age >> gender >> weight >> height >> goal) {
            person[userCount].setUsername(name);
            person[userCount].setAge(age);
            person[userCount].setGender(gender);
            person[userCount].setWeight(weight);
            person[userCount].setHeight(height);
            person[userCount].setGoal(goal);
            ++userCount;
        }
        file.close();
    } else {
        cout << "Error opening userInfo.txt.\n";
    }

    // Login
    int loggedInIndex = -1;
    string inputName;
    while (loggedInIndex == -1) {
        cout << "+===============================+\n";
        cout << "|  My Health Journal Login Page |\n";
        cout << "+===============================+\n";
        cout << "Please enter your username: ";
        cin >> inputName;

        inputName = normalizeName(inputName);

      // ✅ Validate alphabet-only username
      if (!isAlphabetic(inputName)) {
        cout << "❌ Username must contain only letters (A-Z or a-z). Please try again.\n\n";
        continue;
      }

        // Search for name
        for (int i = 0; i < userCount; ++i) {
            if (person[i].getUsername() == inputName) {
                loggedInIndex = i;
                break;
            }
        }

        if (loggedInIndex == -1) {
            cout << "Username not found. Would you like to register? (Y/N): ";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                if (userCount >= Max_Person) {
                    cout << "User limit reached.\n";
                    break;
                }

                int age;
                char gender;
                float weight, height;
                string goal;
                while (true) {
                  cout << "Enter age: ";
                  cin >> age;
                  if (cin.fail() || age < 1) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid age. Please enter a positive number.\n";
                    continue;
                  }
                  break;
                }

                while (true) {
                  cout << "Enter gender (M/F): ";
                  cin >> gender;
                  if (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
                      cin.clear();
                      cin.ignore(100, '\n');
                      cout << "Invalid gender. Please enter 'M' or 'F'.\n";
                      continue;
                  }
                  break;
                }

               while (true) {
                  cout << "Enter weight (kg): ";
                  cin >> weight;
                  if (cin.fail() || weight < 1) {
                      cin.clear();
                      cin.ignore(100, '\n');
                      cout << "Invalid weight. Please enter a positive number.\n";
                      continue;
                  }
                  break;
                }

                while (true) {
                  cout << "Enter height (m): ";
                  cin >> height;
                  if (cin.fail() || height < 1) {
                      cin.clear();
                      cin.ignore(100, '\n');
                      cout << "Invalid height. Please enter a positive number.\n";
                      continue;
                  }
                  break;
                }

                while (true) {
                  cout << "Enter goal (lose/maintain/gain): ";
                  cin >> goal;
                  if (goal != "lose" && goal != "maintain" && goal != "gain") {
                      cin.clear();
                      cin.ignore(100, '\n');
                      cout << "Invalid goal. Please enter only 'lose', 'maintain', or 'gain'.\n";
                      continue;
                  }
                  break;  
                }

                // Save to array
                person[userCount].setUsername(inputName);
                person[userCount].setAge(age);
                person[userCount].setGender(gender);
                person[userCount].setWeight(weight);
                person[userCount].setHeight(height);
                person[userCount].setGoal(goal);

                // Append to file
                ofstream outFile("userInfo.txt", ios::app);
                if (outFile.is_open()) {
                    outFile << inputName << " " << age << " " << gender << " "
                            << weight << " " << height << " " << goal << "\n";
                    outFile.close();
                } else {
                    cout << "Error saving to file.\n";
                }

                loggedInIndex = userCount;
                ++userCount;
                cout << "User added successfully!\n";
            } else {
                char quitChoice;
                do {
                  cout << "Do you want to quit? (Y/N): ";
                  cin >> quitChoice;
                  if (quitChoice == 'Y' || quitChoice == 'y') {
                    cout << "Exiting My Health Journal..." << endl;
                    return 0; // Exit the program
                  } else if (quitChoice == 'N' || quitChoice == 'n') {
                    cout << "Try again.\n";
                    break;
                  } else {
                    cout << "Invalid input. Please enter Y or N.\n";
                  }
                } while (true);
            }
        }
    }

    // Continue with the rest of the program
    cout << "\nWelcome, " << person[loggedInIndex].getUsername() << "!" << endl;

    // Prompt for activity level
    int activityLevel = 0;
    do {
      cout << "\n===========================================\n";
      cout << "||        Select Your Activity Level      ||\n";
      cout << "===========================================\n";
      cout << "| 1. Sedentary (little or no exercise)     |\n";
      cout << "| 2. Lightly Active (light exercise)       |\n";
      cout << "| 3. Moderately Active (moderate exercise) |\n";
      cout << "| 4. Very Active (hard exercise)           |\n";
      cout << "| 5. Super Active (very intense activity)  |\n";
      cout << "===========================================\n";
      cout << "Enter choice (1-5): ";
      cin >> activityLevel;
      person[loggedInIndex].setIntensityLevel(activityLevel);

      cout<<endl;

      if (activityLevel < 1 || activityLevel > 5) {
        cin.clear();
        cin.ignore(100,'\n');
        cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        continue;
      }
    } while (activityLevel < 1 || activityLevel > 5);

    //Proceed to menu
    PersonInfo(person, userCount, loggedInIndex);

    // Save updated data back to file
    ofstream outFile("userInfo.txt");
    for (int i = 0; i < userCount; ++i) {
        outFile << person[i].getUsername() << " "
                << person[i].getAge() << " "
                << person[i].getGender() << " "
                << person[i].getWeight() << " "
                << person[i].getHeight() << " "
                << person[i].getGoal() << endl;
    }
    outFile.close();

    return 0;
}

void PersonInfo(Person person[], int userCount, int loggedInIndex) {
    char cont = 'Y';   // Initialize with 'Y' to enter loop
    char Choice;       // For user to choose the My Health Journal option
    bool quit = false;

    do {
        cout << "=====================================\n";
        cout << "||     My Health Journal           ||\n";
        cout << "=====================================\n";
        cout << "| 1. View All Users' Details        |\n";
        cout << "| 2. User Personal Profile          |\n";
        cout << "| 3. Diet Protocol                  |\n";
        cout << "| 4. Workout Plan                   |\n";
        cout << "| 5. Healthy Leaderboard            |\n";
        cout << "| 6. Progress Tracking              |\n";
        cout << "| 7. Exit                           |\n";
        cout << "=====================================\n";

        do {
            cout << "Enter your choice: ";
            cin >> Choice;
            if (Choice < '1' || Choice > '7') {
                cin.clear();
                cin.ignore(100,'\n');
                cout << "Invalid Choice. Please enter a number between 1 and 7." << endl;
                continue;
            }
        } while (Choice < '1' || Choice > '7');

        switch (Choice) {
            case '1':
                cout << "\n========= All Users' Details =========\n";
                for (int i = 0; i < userCount; ++i) {
                    cout << "User #" << i + 1 << endl;
                    person[i].displayUserDetails();
                    cout << "--------------------------------------\n";
                }
                break;

            case '2': {
                // Display full profile
                person[loggedInIndex].displayProfile();

                // Pause here — wait for user to press Enter before continuing
                cout << "\nPress Enter to continue...";
                cin.ignore(100, '\n');  // flush input buffer
                cin.get();

                // Sub Menu
                int subMenu1 = 0;
                do {
                cout << "\n===========================================\n";
                cout << "||        User Profile's Sub Menu         ||\n";
                cout << "===========================================\n";
                cout << "| 1. Update Personal Info                 |\n";
                cout << "| 2. Compare BMI                          |\n";
                cout << "| 3. Back To Main Menu                    |\n";
                cout << "===========================================\n";
                cout << "Enter choice (1-3): ";
                cin >> subMenu1;

                if (subMenu1 < 1 || subMenu1 > 3) {
                  cin.clear();
                  cin.ignore(100,'\n');
                  cout << "Invalid choice. Please enter a number between 1 and 3.\n";
                  continue;
                }
                } while (subMenu1 < 1 || subMenu1 > 3);

                if (subMenu1 == 3) break;

                switch (subMenu1) {
                case 1: {//update personal info

                string goal;
                double weight, height;

                cout<<"Enter new weight(kg): ";
                cin>>weight;

                cout<<"Enter new height (m): ";
                cin>>height;

                cin.ignore(); //clear newline from input beffer

                //Restrict goal to specific options
                while (true){
                    cout<<"Enter new goal (lose / maintain / gain): ";
                    getline(cin,goal);

                    //Convert to lowercase to make it case-insensitive

                    if (goal == "lose" || goal == "maintain" ||goal == "gain"){
                        break;
                    }else{
                        cout<<"Invalid goal. Please enter only 'lose', 'maintain', or 'gain'.\n";
                    }
                }
                person[loggedInIndex].setWeight(weight);
                person[loggedInIndex].setHeight(height);
                person[loggedInIndex].setGoal(goal);

                cout << "User information updated successfully.\n";
                break;
                }
                break;
                case 2:{ // compare BMI
                cout << "\n===========================================\n";
                cout << "||         Standard BMI Categories        ||\n";
                cout << "===========================================\n";
                cout << "===========================================\n";
                cout << "|    BMI     |       Weight Status        | \n";
                cout << "===========================================\n";
                cout << "| Below 18.5 |        Underweight         |\n";
                cout << "| Below 25.0 |       Normal Weight        |\n";
                cout << "| Below 30.0 |         Overweight         |\n";
                cout << "| Above 30   |           Obese            |\n";
                cout << "===========================================\n";
                person[loggedInIndex].displayBMI();
                break;
                }
                }
            break;
            }
            case '3':{
              // read from file
              ifstream file("diet_plans.txt");
              if (!file) {
                cout << "Cannot open file: " << "diet_plans.txt" << endl;
                break;
              }

              // Arrays to store meal descriptions and calories
              string breakfastDesc[MAX_MEALS], lunchDesc[MAX_MEALS], dinnerDesc[MAX_MEALS], snackDesc[MAX_MEALS];
              int breakfastCal[MAX_MEALS], lunchCal[MAX_MEALS], dinnerCal[MAX_MEALS], snackCal[MAX_MEALS];
              int breakfastCount = 0, lunchCount = 0, dinnerCount = 0, snackCount = 0;

              string mealType, description;
              int calories;

              // Read file line-by-line
              while (getline(file, mealType, ',')) {
              getline(file, description, ',');
              file >> calories;
              file.ignore(); // Ignore the newline

              if (mealType == "Breakfast" && breakfastCount < MAX_MEALS) {
              breakfastDesc[breakfastCount] = description;
              breakfastCal[breakfastCount++] = calories;
              } else if (mealType == "Lunch" && lunchCount < MAX_MEALS) {
                lunchDesc[lunchCount] = description;
                lunchCal[lunchCount++] = calories;
              } else if (mealType == "Dinner" && dinnerCount < MAX_MEALS) {
                dinnerDesc[dinnerCount] = description;
                dinnerCal[dinnerCount++] = calories;
              } else if (mealType == "Snack" && snackCount < MAX_MEALS) {
                snackDesc[snackCount] = description;
                snackCal[snackCount++] = calories;
              }
            }
            file.close();

            // Display grouped meals
            cout << "\n=========== Breakfast Options ===========\n";
            for (int i = 0; i < breakfastCount; i++) {
              cout << "Breakfast " << i + 1 << ": " << breakfastDesc[i];
              cout << " (" << breakfastCal[i] << " kcal)\n";
            }

            cout << "\n============= Lunch Options =============\n";
            for (int i = 0; i < lunchCount; i++) {
              cout << "Lunch " << i + 1 << ": " << lunchDesc[i];
              cout << " (" << lunchCal[i] << " kcal)\n";
            }

            cout << "\n============= Dinner Options ============\n";
            for (int i = 0; i < dinnerCount; i++) {
              cout << "Dinner " << i + 1 << ": " << dinnerDesc[i];
              cout << " (" << dinnerCal[i] << " kcal)\n";
            }

            cout << "\n============= Snack Options =============\n";
            for (int i = 0; i < snackCount; i++) {
              cout << "Snack " << i + 1 << ": " << snackDesc[i];
              cout << " (" << snackCal[i] << " kcal)\n";
            }
            // Pause here — wait for user to press Enter before continuing
            cout << "\nPress Enter to continue...";
            cin.ignore(100, '\n');  // flush input buffer
            cin.get();

            // Sub Menu
              int subMenu3 = 0;
              do {
              cout << "\n===========================================\n";
              cout << "||         Diet Plan's Sub Menu          ||\n";
              cout << "===========================================\n";
              cout << "| 1. Manual Choice                        |\n";
              cout << "| 2. Back To Main Menu                    |\n";
              cout << "===========================================\n";
              cout << "Enter choice (1-2): ";
              cin >> subMenu3;

                if (subMenu3 < 1 || subMenu3 > 2) {
                cin.clear();
                cin.ignore(100,'\n');
                cout << "Invalid choice. Please enter a number between 1 and 2.\n";
                continue;
              }

              if(subMenu3 == 2) break;

              string genderStr(1, person[loggedInIndex].getGender()); // Use 1 char only: 'M' or 'F'

             int b, l, d;

             // 🥣 Validate breakfast choice
            while (true) {
                cout << "\nSelect your Breakfast (1-" << breakfastCount << "): ";
                cin >> b;
                if (b >= 1 && b <= breakfastCount) break;
                    cout << "❌ Invalid breakfast choice. Please enter a number between 1 and " << breakfastCount << ".\n";
            }

            // 🍛 Validate lunch choice
            while (true) {
                cout << "Select your Lunch (1-" << lunchCount << "): ";
                cin >> l;
                if (l >= 1 && l <= lunchCount) break;
                    cout << "❌ Invalid lunch choice. Please enter a number between 1 and " << lunchCount << ".\n";
            }

            // 🍲 Validate dinner choice
            while (true) {
                cout << "Select your Dinner (1-" << dinnerCount << "): ";
                cin >> d;
                if (d >= 1 && d <= dinnerCount) break;
                    cout << "❌ Invalid dinner choice. Please enter a number between 1 and " << dinnerCount << ".\n";
            }

          int total = 0;

           // ✅ Show selected meals
          cout << "\nYour Selected Meals:\n";

          Breakfast selectedBreakfast(breakfastDesc[b - 1], breakfastCal[b - 1]);
          selectedBreakfast.displayMeal();
          total += selectedBreakfast.getCalories();

          Lunch selectedLunch(lunchDesc[l - 1], lunchCal[l - 1]);
          selectedLunch.displayMeal();
          total += selectedLunch.getCalories();

          Dinner selectedDinner(dinnerDesc[d - 1], dinnerCal[d - 1]);
          selectedDinner.displayMeal();
          total += selectedDinner.getCalories();

        char snackChoice;

        // ✅ Ask if the user wants snacks
        while (true) {
        cout << "\nWould you like to add snacks? (Y/N): ";
        cin >> snackChoice;

       if (snackChoice == 'Y' || snackChoice == 'y' || snackChoice == 'N' || snackChoice == 'n') {
          break;
        } else {
          cout << "Invalid choice. Please enter 'Y' / 'y' or 'N' / 'n'.\n";
        }
      }

        if (snackChoice == 'Y' || snackChoice == 'y') {
          cout << "\nAvailable Snacks:\n";
        for (int i = 0; i < snackCount; ++i) {
          cout << i + 1 << ". " << snackDesc[i] << " (" << snackCal[i] << " cal)\n";
        }

        cout << "Enter the numbers of the snacks you want to add (0 to stop):\n";

        while (true) {
          int snackIndex;
          cout << "Snack number: ";
          cin >> snackIndex;

          if (snackIndex == 0) break;

          if (snackIndex >= 1 && snackIndex <= snackCount) {
            Snack addedSnack(snackDesc[snackIndex - 1], snackCal[snackIndex - 1]);
            addedSnack.displayMeal();
            total += addedSnack.getCalories();
          } else {
            cout << "Invalid snack number. Try again.\n";
        }
    }
}

        cout << "Total Calories: " << total << " cal\n";

      // 🔍 Check minimum requirement
      int minCalories = (genderStr == "F" || genderStr == "f") ? 1200 : 1500;

      if (total < minCalories) {
        cout << "⚠ Warning: Your total calorie intake is below the recommended minimum of "
         << minCalories << " cal for your gender.\n";
      } else {
        cout << "✅ Your meal selection meets the minimum calorie requirement.\n";
      }

      // Ask to continue in submenu
      char subCont;
      do {
          cout << "\nReturn to Diet Plan submenu? (Y/N): ";
          cin >> subCont;
          if (subCont == 'N' || subCont == 'n') {
              subMenu3 = 2; // Will exit to main menu
              break;
          } else if (subCont != 'Y' && subCont != 'y') {
              cout << "Invalid input. Please enter Y or N.\n";
          }
      } while (subCont != 'Y' && subCont != 'y' && subCont != 'N' && subCont != 'n');

              } while (subMenu3 != 2);
            break;
            }

            case '4':{
              string workoutNames[MAX_WORKOUTS];
              int workoutLevels[MAX_WORKOUTS];
              int workoutCalories[MAX_WORKOUTS];
              int workoutCount = 0;

              // Get user intensity level and map 4 & 5 to workout level 4
              int userLevel = person[loggedInIndex].getIntensityLevel();
              int mappedLevel = (userLevel >= 4) ? 4 : userLevel;

              // read from file
              ifstream file("workout_plans.txt");
              if (!file) {
                cout << "Cannot open file: " << "workout_plans.txt" << endl;
                break;
              }

              workoutCount=0;
              string name;
              int level, calories;

              cout << "\n==========================================================\n";
              cout << "||  Workout Intensity  |  Suggested TDEE Activity Level  ||\n";
              cout << "==========================================================\n";
              cout << "|        Level 1       |         Sedentary Level         |\n";
              cout << "|        Level 2       |         Lightly Active          |\n";
              cout << "|        Level 3       |         Moderately Active       |\n";
              cout << "|        Level 4       |    Very Active / Super Active   |\n";
              cout << "==========================================================\n";

              cout << "\n===========================================\n";
              cout << "||       Workout Activity Available       ||\n";
              cout << "===========================================\n";

              while (workoutCount < MAX_WORKOUTS && getline(file, name, ',')) {
                file >> level;
                file.ignore(); // ignore comma
                file >> calories;
                file.ignore(); // ignore newline

                if (level == mappedLevel) {
                  workoutNames[workoutCount] = name;
                  workoutLevels[workoutCount] = level;
                  workoutCalories[workoutCount] = calories;

                  cout << "Activity " << workoutCount + 1 << "\n";
                  cout << "Activity name        : " << name << "\n";
                  cout << "Intensity level      : " << level << "\n";
                  cout << "Calories per minute  : " << calories << "\n";
                  cout << "----------------------------------------\n";

                  workoutCount++;
                }
              }
              file.close();

              // Pause here — wait for user to press Enter before continuing
              cout << "\nPress Enter to continue...";
              cin.ignore(100, '\n');  // flush input buffer
              cin.get();

              // Sub Menu
              int subMenu2 = 0;

              do {
              cout << "\n===========================================\n";
              cout << "||         Workout Plan's Sub Menu        ||\n";
              cout << "===========================================\n";
              cout << "| 1. Manual Choice                        |\n";
              cout << "| 2. Back To Main Menu                    |\n";
              cout << "===========================================\n";
              cout << "Enter choice (1-2): ";
              cin >> subMenu2;

              if (subMenu2 < 1 || subMenu2 > 2) {
                cin.clear();
                cin.ignore(100,'\n');
                cout << "Invalid choice. Please enter a number between 1 and 2.\n";
                continue;
              }

              if(subMenu2 == 2) break;

              // Manual Workout Selection
              char gender = person[loggedInIndex].getGender();
              int calLimit = (gender == 'F' || gender == 'f') ? 400 : 500;

              cout << "\n===========================================\n";
              cout << "||       Workout Activity Available       ||\n";
              cout << "===========================================\n";

              for (int i = 0; i < workoutCount; i++) {
                  cout << i + 1 << ". " << workoutNames[i];
                  cout << " (Level " << workoutLevels[i];
                  cout << ", " << workoutCalories[i] << " cal/min)\n";
              }

              int choice;
              cout << "Select a workout (1-" << workoutCount << "): ";
              cin >> choice;

              if (choice < 1 || choice > workoutCount) {
                  cin.clear();
                  cin.ignore(100, '\n');
                  cout << "Invalid choice. Please enter a valid number.\n";
                  continue;
              }

              int index = choice - 1;
              int duration = calLimit / workoutCalories[index];
              int totalBurn = duration * workoutCalories[index];

              cout << "\nSelected Workout     : " << workoutNames[index] << "\n";
              cout << "Max Duration         : " << duration << " minutes\n";
              cout << "Total Calories Burn  : " << totalBurn << " kcal\n";

              // Ask to continue in submenu
              char subCont;
              do {
                  cout << "\nReturn to Workout Plan submenu? (Y/N): ";
                  cin >> subCont;
                  if (subCont == 'N' || subCont == 'n') {
                      subMenu2 = 2; // Will exit to main menu
                      break;
                  } else if (subCont != 'Y' && subCont != 'y') {
                      cout << "Invalid input. Please enter Y or N.\n";
                  }
              } while (subCont != 'Y' && subCont != 'y' && subCont != 'N' && subCont != 'n');

              } while (subMenu2 != 2);
              break;
              }

            case '5':{
                Person users[Max_Person];
                int userCount = 0;

                ifstream infile("userInfo.txt");
                if (!infile) {
                    cerr << "Error: Could not open userInfo.txt\n";
                    break;
                }

                string name, goal;
                int age;
                char gender;
                float weight, height;

                while (infile >> name >> age >> gender >> weight >> height >> goal && userCount < Max_Person) {
                    users[userCount] = Person(name, age, gender, weight, height, goal);
                    userCount++;
                }
                infile.close();

                cout << "\n====================================================\n";
                cout << "||                Healthy Leaderboard              ||\n";
                cout << "====================================================\n";
                cout << "| Rank |  Username  |   BMI   |     Status      |\n";
                cout << "======================================================\n";
                createBMIRanking(users, userCount);
                cout << "======================================================\n";
                break;
            }
            case '6': {
    fstream file("progress_records.txt", ios::in);
    string line;
    bool userFound = false;
    int CurrentDay = 1;
    float targetWeight = 0;
    float weights[7] = {0};
    string currentUser = person[loggedInIndex].getUsername();

    // Step 1: Read existing record
    while (getline(file, line)) {
        istringstream iss(line);
        string name;
        iss >> name;

        if (name == currentUser) {
            userFound = true;
            iss >> CurrentDay >> targetWeight;
            for (int i = 0; i < 7; ++i) {
                if (!(iss >> weights[i])) break;
            }
        }
    }
    file.close();

    if (!userFound) {
        // First time user setup
        cout << "\nWelcome, first-time user!\n";
        cout << "Enter target weight (kg): ";
        cin >> targetWeight;

        float day1Weight = person[loggedInIndex].getWeight();
        cout << "Your Day 1 weight is automatically recorded as: " << day1Weight << " kg\n";

        ofstream outfile("progress_records.txt", ios::app);
        if (outfile.is_open()) {
            outfile << currentUser << " 1 " << targetWeight << " " << day1Weight << endl;
            outfile.close();
            cout << "Target weight and Day 1 weight recorded!\n";
        } else {
            cout << "Error saving progress.\n";
        }
    } else {
        // Existing user update
        float currentWeight;
        cout << "\nWelcome back, " << currentUser << "!\n";
        cout << "Day " << CurrentDay + 1 << " Progress Tracking\n";
        cout << "Enter current weight (kg): ";
        cin >> currentWeight;

        weights[CurrentDay] = currentWeight;

        // Update file
        ifstream infile("progress_records.txt");
        ofstream temp("temp.txt");
        while (getline(infile, line)) {
            istringstream iss(line);
            string name;
            iss >> name;

            if (name == currentUser) {
                temp << name << " " << (CurrentDay + 1) << " " << targetWeight;
                for (int i = 0; i <= CurrentDay; ++i)
                    temp << " " << weights[i];
                temp << endl;
            } else {
                temp << line << endl;
            }
        }
        infile.close();
        temp.close();
        remove("progress_records.txt");
        rename("temp.txt", "progress_records.txt");
        cout << "Weight recorded for Day " << CurrentDay + 1 << "!\n";

        if (CurrentDay + 1 == 7) {
            // Evaluate progress
            float initialWeight = weights[0];
            float finalWeight = weights[6];
            bool achieved = (targetWeight < initialWeight) ? finalWeight <= targetWeight
                          : (targetWeight > initialWeight) ? finalWeight >= targetWeight
                          : finalWeight == targetWeight;

            // Display results
            cout << "\n============== Current Progress ==============\n";
            cout << "Username      : " << currentUser << endl;
            cout << "Target Weight : " << targetWeight << " kg\n";
            cout << "----------------------------------------------\n";
            cout << "Day\tWeight (kg)\tDifference from Target\n";
            cout << "----------------------------------------------\n";
            for (int i = 0; i < 7; ++i) {
                float diff = weights[i] - targetWeight;
                cout << "Day " << (i + 1) << "\t" << weights[i] << "\t\t";
                if (diff == 0)
                    cout << "Reached goal\n";
                else
                    cout << (diff > 0 ? "+" : "") << diff << " kg\n";
            }
            cout << "----------------------------------------------\n";
            cout << (achieved ? "🎉 Congratulations! You have achieved your weight goal!\n"
                             : "You did not reach your goal within 7 days. Keep trying!\n");
            cout << "==============================================\n";

            // Start new cycle
            float newTargetWeight;
            cout << "\nLet's start a new 7-day journey!\n";
            cout << "Enter your new target weight (kg): ";
            cin >> newTargetWeight;

            ofstream appendFile("progress_records.txt", ios::app);
            if (appendFile.is_open()) {
                appendFile << currentUser << " 1 " << newTargetWeight << " " << weights[6] << endl;
                appendFile.close();
                cout << "New target and starting weight (Day 1) recorded!\n";
            } else {
                cout << "Error starting new journey.\n";
            }

            break;
        }
    }

    // Step 3: Submenu
    int subMenu4 = 0;
    do {
        cout << "\n===========================================\n";
        cout << "||         Progress Tracking Menu         ||\n";
        cout << "===========================================\n";
        cout << "| 1. View Current Progress                |\n";
        cout << "| 2. Auto-Generated Meal Plan             |\n";
        cout << "| 3. Suggested Workout Plan               |\n";
        cout << "| 4. Back To Main Menu                    |\n";
        cout << "===========================================\n";
        cout << "Enter choice (1-4): ";
        cin >> subMenu4;

        if (cin.fail() || subMenu4 < 1 || subMenu4 > 4) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid choice. Please enter 1-4.\n";
            continue;
        }

        switch (subMenu4) {
            case 1:
                viewCurrentProgress(currentUser);
                break;
            case 2: {
                string genderStr(1, person[loggedInIndex].getGender());
                generateAutoMealPlan(genderStr);
                break;
            }
            case 3: {
                char gender = person[loggedInIndex].getGender();
                int calLimit = (gender == 'F' || gender == 'f') ? 400 : 500;
                int userLevel = person[loggedInIndex].getIntensityLevel();
                int mappedLevel = (userLevel >= 4) ? 4 : userLevel;

                ifstream file("workout_plans.txt");
                string workoutNames[MAX_WORKOUTS];
                int workoutCalories[MAX_WORKOUTS];
                int workoutCount = 0;
                string name;
                int level, calories;

                while (workoutCount < MAX_WORKOUTS && getline(file, name, ',')) {
                    file >> level;
                    file.ignore();
                    file >> calories;
                    file.ignore();
                    if (level == mappedLevel) {
                        workoutNames[workoutCount] = name;
                        workoutCalories[workoutCount++] = calories;
                    }
                }
                file.close();

                if (workoutCount > 0) {
                    srand(time(0));
                    int randomIndex = rand() % workoutCount;
                    int duration = calLimit / workoutCalories[randomIndex];
                    cout << "\nSuggested Workout:\n";
                    cout << "Activity: " << workoutNames[randomIndex] << "\n";
                    cout << "Duration: " << duration << " minutes\n";
                    cout << "Calories Burn: " << (duration * workoutCalories[randomIndex]) << " kcal\n";
                } else {
                    cout << "No workouts available for your activity level.\n";
                }
                break;
            }
            case 4:
                break;
        }

        if (subMenu4 != 4) {
            char cont;
            cout << "\nReturn to Progress Tracking? (Y/N): ";
            cin >> cont;
            if (toupper(cont) == 'N') subMenu4 = 4;
        }

    } while (subMenu4 != 4);

  break;
}

            case '7':
                cout << "Exiting My Health Journal...\n";
                return;
        }

        // Main menu continuation prompt
        cout << "\nReturn to Main Menu? (Y/N): ";
        cin >> cont;
    } while (toupper(cont) == 'Y');
}

void viewCurrentProgress(const string& username) {
    ifstream file("progress_records.txt");
    string line;
    int CurrentDay = 1;
    float targetWeight = 0;
    float weights[7] = {0};
    bool userFound = false;

    while (getline(file, line)) {
        int pos = 0;
        string name = "";
        while (pos < (int)line.size() && line[pos] != ' ') {
            name += line[pos++];
        }
        while (pos < (int)line.size() && line[pos] == ' ') pos++;

        if (name == username) {
            userFound = true;

            // Parse CurrentDay
            string dayStr = "";
            while (pos < (int)line.size() && line[pos] != ' ') {
                dayStr += line[pos++];
            }
            while (pos < (int)line.size() && line[pos] == ' ') pos++;

            CurrentDay = 0;
            for (int i = 0; i < (int)dayStr.size(); ++i)
                CurrentDay = CurrentDay * 10 + (dayStr[i] - '0');

            // Parse targetWeight
            string targetStr = "";
            while (pos < (int)line.size() && line[pos] != ' ') {
                targetStr += line[pos++];
            }
            while (pos < (int)line.size() && line[pos] == ' ') pos++;

            targetWeight = 0.0f;
            float decimalPlace = 0.1f;
            bool decimalFound = false;
            for (int i = 0; i < (int)targetStr.size(); ++i) {
                if (targetStr[i] == '.') {
                    decimalFound = true;
                } else if (!decimalFound) {
                    targetWeight = targetWeight * 10 + (targetStr[i] - '0');
                } else {
                    targetWeight += (targetStr[i] - '0') * decimalPlace;
                    decimalPlace *= 0.1f;
                }
            }

            // Parse weights
            int weightCount = 0;
            while (pos < (int)line.size() && weightCount < 7) {
                string weightStr = "";
                while (pos < (int)line.size() && line[pos] != ' ') {
                    weightStr += line[pos++];
                }
                while (pos < (int)line.size() && line[pos] == ' ') pos++;

                float w = 0.0f;
                decimalPlace = 0.1f;
                decimalFound = false;
                for (int i = 0; i < (int)weightStr.size(); ++i) {
                    if (weightStr[i] == '.') {
                        decimalFound = true;
                    } else if (!decimalFound) {
                        w = w * 10 + (weightStr[i] - '0');
                    } else {
                        w += (weightStr[i] - '0') * decimalPlace;
                        decimalPlace *= 0.1f;
                    }
                }
                weights[weightCount++] = w;
            }
        }
    }
    file.close();

    if (!userFound) {
        cout << "No progress record found for user: " << username << endl;
        return;
    }

    cout << "\n============== Current Progress ==============\n";
    cout << "Username      : " << username << endl;
    cout << "Target Weight : " << targetWeight << " kg\n";
    cout << "----------------------------------------------\n";
    cout << "Day\tWeight (kg)\tDifference from Target\n";
    cout << "----------------------------------------------\n";

    for (int i = 0; i < CurrentDay; ++i) {
        float diff = weights[i] - targetWeight;
        cout << "Day " << (i + 1) << "\t" << weights[i] << "\t\t";
        if (diff == 0)
            cout << "Reached goal\n";
        else
            cout << (diff > 0 ? "+" : "") << diff << " kg\n";
    }
    cout << "----------------------------------------------\n";

    if (CurrentDay == 7) {
        float initialWeight = weights[0];
        float finalWeight = weights[6];
        bool achieved = false;

        if (targetWeight < initialWeight) {
            achieved = (finalWeight <= targetWeight);
        } else if (targetWeight > initialWeight) {
            achieved = (finalWeight >= targetWeight);
        } else {
            achieved = (finalWeight == targetWeight);
        }

        if (achieved)
            cout << "🎉 Congratulations! You have achieved your weight goal!\n";
        else
            cout << "You did not reach your goal within 7 days. Keep trying!\n";

        cout << "==============================================\n";
}