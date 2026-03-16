#pragma once
#include <string>
#include "Models.h"

// Const correctness: functions that modify parameters should take non-const references
// Functions that only read should take const references where possible
void courseAdder(double& grade, std::string& name, double& weight);
double courseGradeCalculator();
void computeGPA(Student& student);

// Const versions where applicable
[[nodiscard]] double calculateGradePoint(double finalGrade);
[[nodiscard]] double computeSemesterGPA(const std::vector<Course>& courses, int currentSemester);
[[nodiscard]] double computeCumulativeGPA(const std::vector<Course>& courses);
