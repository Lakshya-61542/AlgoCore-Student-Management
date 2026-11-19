
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>

#include <cctype>

// Student data structure
struct Student {
    std::string name;
    int roll;
    double marks;
};

// Stores student records
std::vector<Student> students;

// Reads and validates an integer
int readInteger(const std::string& prompt) {
    std::string input;
    int value;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        std::stringstream ss(input);

        if (ss >> value && !(ss >> std::ws && !ss.eof())) {
            return value;
        }

        std::cout << "Invalid input! Please enter a valid integer.\n";
    }
}

// Reads and validates student marks
double readMarks() {
    std::string input;
    double marks;

    while (true) {
        std::cout << "Enter marks (0-100): ";
        std::getline(std::cin, input);

        std::stringstream ss(input);

        if (ss >> marks && std::isfinite(marks)
            && !(ss >> std::ws && !ss.eof())) {

            if (marks >= 0 && marks <= 100) {
                return marks;
            }
        }

        std::cout << "Invalid marks! Enter a value between 0 and 100.\n";
    }
}

// Checks whether roll number already exists
bool rollExists(int roll) {
    for (const Student& student : students) {
        if (student.roll == roll) {
            return true;
        }
    }

    return false;
}


// Validates student names
bool isValidName(const std::string& name) {
    bool hasLetter = false;

    if (name.empty()) {
        return false;
    }

    for (unsigned char ch : name) {
        if (std::isalpha(ch)) {
            hasLetter = true;
        }
        else if (ch != ' ' && ch != '-' && ch != '\'') {
            return false;
        }
    }

    return hasLetter;
}


// Adds a new student
void addStudent() {
    Student student;

    
while (true) {
    std::cout << "\nEnter student name: ";
    std::getline(std::cin, student.name);

    if (isValidName(student.name)) {
        break;
    }

    std::cout << "Invalid name! Use letters, spaces, "
                 "hyphens or apostrophes only.\n";
}


    while (true) {
        student.roll = readInteger("Enter roll number: ");

        if (student.roll <= 0) {
            std::cout << "Roll number must be positive.\n";
        }
        else if (rollExists(student.roll)) {
            std::cout << "This roll number already exists.\n";
        }
        else {
            break;
        }
    }

    student.marks = readMarks();

    students.push_back(student);

    std::cout << "\nStudent added successfully!\n";
}

// Displays all student records
void printAll(const std::vector<Student>& records) {
    if (records.empty()) {
        std::cout << "\nNo student records available.\n";
        return;
    }

    std::cout << "\n";
    std::cout << std::left
              << std::setw(12) << "Roll No."
              << std::setw(22) << "Name"
              << std::setw(10) << "Marks" << '\n';

    std::cout << std::string(44, '-') << '\n';

    for (const Student& student : records) {
        std::cout << std::left
                  << std::setw(12) << student.roll
                  << std::setw(22) << student.name
                  << std::fixed << std::setprecision(2)
                  << student.marks << '\n';
    }

    std::cout << std::string(44, '-') << '\n';
}


void showTopScorer() {
    if (students.empty()) {
        std::cout << "\nNo student records available.\n";
        return;
    }

    const Student* topScorer = &students[0];

    for (const Student& student : students) {
        if (student.marks > topScorer->marks) {
            topScorer = &student;
        }
    }

    std::cout << "\n========== TOP SCORER ==========\n";

    std::cout << "Name: " << topScorer->name << '\n';
    std::cout << "Roll Number: " << topScorer->roll << '\n';

    std::cout << "Marks: "
              << std::fixed << std::setprecision(2)
              << topScorer->marks << '\n';

    std::cout << "================================\n";
}


// Displays application menu
void displayMenu() {
    std::cout << "\n========== ALGOCORE ==========\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. Show All Students\n";
    std::cout << "3. Quit\n";
    std::cout << "4. Show Top Scorer\n";
    std::cout << "==============================\n";
}

// Main function
int main() {
    std::cout << "Welcome to AlgoCore!\n";

    int choice;

    do {
        displayMenu();
        choice = readInteger("Enter your choice: ");

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                printAll(students);
                break;

            case 3:
                std::cout << "\nThank you for using AlgoCore!\n";
                break;

            case 4:
    showTopScorer();
    break;

           default:
    std::cout << "\nInvalid choice! Select 1, 2, 3 or 4.\n";
        }

    } while (choice != 3);

    return 0;
}
