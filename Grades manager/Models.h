

// ─────────────────────────────────────────
//  Structs
// ─────────────────────────────────────────
#pragma once
#include <string>
#include <vector>

struct GradeComponent {
    int         id;        // DB primary key later
    int         courseId;  // foreign key → Course
    std::string label;     // "Midterm", "Final", "Quiz"
    double      grade;     // 0 – 100
    double      weight;    // 0 – 100
};

struct Course {
    int                         id;           // DB primary key later
    int                         studentId;    // foreign key → Student
    std::string                 name;         // "Calculus II"
    int                         credits;      // 3
    int                         semester;     // 1, 2, 3 ...
    double                      finalGrade;   // computed
    std::vector<GradeComponent> components;
};

struct Student {
    int                  id;       // DB primary key later
    std::string username;          // unique, used for login → "john99"
    std::string          name;
    std::string          password; // will hash later
    std::vector<Course>  courses;
    double               gpa;      // current semester, computed
    double               cgpa;     // cumulative, computed
};