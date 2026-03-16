
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

    // Const correctness: getter methods should be const
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] int getCourseId() const { return courseId; }
    [[nodiscard]] const std::string& getLabel() const { return label; }
    [[nodiscard]] double getGrade() const { return grade; }
    [[nodiscard]] double getWeight() const { return weight; }

    // Setter methods (non-const)
    void setGrade(double newGrade) { grade = newGrade; }
    void setWeight(double newWeight) { weight = newWeight; }
};

struct Course {
    int                         id;           // DB primary key later
    int                         studentId;    // foreign key → Student
    std::string                 name;         // "Calculus II"
    int                         credits;      // 3
    int                         semester;     // 1, 2, 3 ...
    double                      finalGrade;   // computed
    std::vector<GradeComponent> components;

    // Const correctness: getter methods should be const
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] int getStudentId() const { return studentId; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getCredits() const { return credits; }
    [[nodiscard]] int getSemester() const { return semester; }
    [[nodiscard]] double getFinalGrade() const { return finalGrade; }
    [[nodiscard]] const std::vector<GradeComponent>& getComponents() const { return components; }

    // Setter methods (non-const)
    void setFinalGrade(double grade) { finalGrade = grade; }
    void setCredits(int creds) { credits = creds; }
    void setSemester(int sem) { semester = sem; }
};

struct Student {
    int                  id;       // DB primary key later
    std::string username;          // unique, used for login → "john99"
    std::string          name;
    std::string          password; // will hash later
    std::vector<Course>  courses;
    double               gpa;      // current semester, computed
    double               cgpa;     // cumulative, computed

    // Const correctness: getter methods should be const
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] const std::string& getUsername() const { return username; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] const std::string& getPassword() const { return password; }
    [[nodiscard]] const std::vector<Course>& getCourses() const { return courses; }
    [[nodiscard]] double getGPA() const { return gpa; }
    [[nodiscard]] double getCGPA() const { return cgpa; }

    // Setter methods (non-const)
    void setName(const std::string& n) { name = n; }
    void setUsername(const std::string& user) { username = user; }
    void setPassword(const std::string& pass) { password = pass; }
    void setGPA(double g) { gpa = g; }
    void setCGPA(double cg) { cgpa = cg; }
};
