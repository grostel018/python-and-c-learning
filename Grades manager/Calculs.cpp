#include "Calculs.h"
#include "Input.h"
#include "UI.h"
#include <iostream>
#include "Models.h"



void computeGPA(Student& student)
{
    if (student.courses.empty()) {
        student.gpa = 0.0;
        student.cgpa = 0.0;
        return;
    }

    int currentSemester = 0;

    // Find the latest semester
    for (const Course& c : student.courses) {
        if (c.semester > currentSemester) {
            currentSemester = c.semester;
        }
    }

    double semesterWeightedSum = 0.0;
    int semesterCredits = 0;

    double cumulativeWeightedSum = 0.0;
    int cumulativeCredits = 0;

    for (const Course& c : student.courses) {
        if (c.credits <= 0) continue;

        double gradePoint = c.finalGrade / 25.0;

        // CGPA = all courses
        cumulativeWeightedSum += gradePoint * c.credits;
        cumulativeCredits += c.credits;

        // GPA = only current/latest semester
        if (c.semester == currentSemester) {
            semesterWeightedSum += gradePoint * c.credits;
            semesterCredits += c.credits;
        }
    }

    student.gpa = (semesterCredits > 0)
        ? (semesterWeightedSum / semesterCredits)
        : 0.0;

    student.cgpa = (cumulativeCredits > 0)
        ? (cumulativeWeightedSum / cumulativeCredits)
        : 0.0;
}







double courseGradeCalculator() {
    std::cout << "\n\tGrade average calculator\n";
    taskDelimeter();

    double midterms, midweight, finals, finalsweight, bonus, bonusweight;

    while (true)
    {
        std::cout << "\nEnter the midterms grade: ";
        midterms = takeNumber();

        std::cout << "Enter the midterms weight (%): ";
        midweight = takeNumber();

        taskDelimeter();

        std::cout << "Enter the finals grade: ";
        finals = takeNumber();

        std::cout << "Enter the finals weight (%): ";
        finalsweight = takeNumber();

        taskDelimeter();

        std::cout << "Enter the bonus/quizz/projects grade: ";
        bonus = takeNumber();

        std::cout << "Enter the bonus/quizz/projects weight (%): ";
        bonusweight = takeNumber();

        taskDelimeter();

        double sum = midweight + finalsweight + bonusweight;

        if (sum != 100)
        {
            std::cout << "\nERROR: Total weight must be 100%. You entered " << sum << "%.\n";
            taskDelimeter();
        }
        else
        {
            break;
        }
    }

    double totalgrade = (finals * finalsweight / 100) +
        (midterms * midweight / 100) +
        (bonus * bonusweight / 100);

    std::cout << "\nThe total grade is: " << totalgrade << "\n";
    std::cout << "\nThe operation is complete\n";
    taskDelimeter();

    return totalgrade;
}