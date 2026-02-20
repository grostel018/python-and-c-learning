#include "Calculs.h"
#include "Input.h"
#include "UI.h"
#include <iostream>




void lectureAdder(double& grade, std::string& name, double& weight) {
    std::cout << "\nEnter the lecture's name : ";

    name = takeString();

    taskDelimeter();

    std::cout << "\nEnter the lecture's grade : ";

    grade = takeNumber();

    taskDelimeter();

    std::cout << "\nEnter the lecture's weight : ";

    weight = takeNumber();

    taskDelimeter();
}






void lectureGradeCalculator() {
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
}