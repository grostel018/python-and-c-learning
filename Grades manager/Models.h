#pragma once
#include <string>
#include <vector>

struct GradeComponent {
    std::string label;   // "Midterm", "Final", "Quiz", "project"
    float       grade;   // 0 – 100
    float       weight;  // 0 – 100  (all weights in a course must sum ≤ 100)
};

struct Course {
    int                        id;          // will map to DB primary key later
    std::string                courseName;        // "Calculus II"
    std::string                code;        // "MATH 201"
    int                        credits;     // 3
    std::vector<GradeComponent> components; // the grade breakdown
    float                      finalGrade;  // computed, not stored raw
};

struct Student {
    int                  id;        // DB primary key later
    std::string          stdName;
    std::string          major;
    int                  year;      // 1 = Freshman … 4 = Senior
    std::vector<Course>  courses;
    float                gpa;       // computed field
};

