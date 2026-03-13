/**
 * @file Calculs.cpp
 * @brief GPA and grade calculation utilities for the Grades Manager.
 *
 * Provides:
 * - computeGPA: compute a student's semester GPA and cumulative GPA (CGPA).
 * - courseGradeCalculator: interactive weighted grade calculator for a single course.
 *
 * Notes:
 * - This file depends on `Models.h` for the `Student` and `Course` types,
 *   `Input.h` for the `takeNumber()` helper, and `UI.h` for `taskDelimeter()`.
 */

    #include "Calculs.h"
    #include "Input.h"
    #include "UI.h"
    #include <iostream>
    #include "Models.h"



    /**
     * @brief Compute the GPA for the latest semester and the cumulative GPA for a student.
     *
     * Behavior:
     * - If the student has no courses, both `student.gpa` and `student.cgpa` are set to 0.0.
     * - The "current" semester is determined as the maximum `Course::semester` value found
     *   in `student.courses`.
     * - Each course's numeric `finalGrade` (expected 0-100) is converted to a grade point
     *   on a 4.0 scale by dividing by 25.0 (i.e., 100 -> 4.0).
     * - CGPA is the credit-weighted average of all courses with positive credits.
     * - GPA is the credit-weighted average restricted to courses from the latest semester.
     * - Courses with non-positive `credits` are ignored in both calculations.
     *
     * Side effects:
     * - Updates `student.gpa` and `student.cgpa` with the computed values.
     *
     * @param student Reference to the Student whose GPA values will be updated.
     */
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



    /**
     * @brief Interactive weighted grade calculator for a single course.
     *
     * Prompts the user for three component grades (midterms, finals, bonus/quizzes/projects)
     * and their associated weights (as percentages). The function validates that the sum of
     * the weights equals 100% and repeats input until the validation passes.
     *
     * Calculation:
     * total = (finals * finalsWeight/100) + (midterms * midweight/100) + (bonus * bonusweight/100)
     *
     * Uses:
     * - `takeNumber()` from `Input.h` to read numeric user input.
     * - `taskDelimeter()` from `UI.h` to print visual separators.
     *
     * @return double The computed weighted total grade (range typically 0-100).
     */
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