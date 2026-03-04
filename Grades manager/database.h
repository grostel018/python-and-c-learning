
// ─────────────────────────────────────────
//  Database
// ─────────────────────────────────────────
#pragma once
#include "Models.h"
#include "src/sqlite3.h"
#include <string>
#include <vector>

// Setup
sqlite3* openAndInitDatabase(const std::string& filename);
void    initDatabase(sqlite3* db);




// Students
int     insertStudent(sqlite3* db, Student& student);          // returns new id
Student getStudent(sqlite3* db, int id);
Student getStudentByUsername(sqlite3* db, const std::string& username);
bool    deleteStudent(sqlite3* db, int id);
bool    studentExists(sqlite3* db, const std::string& username);



// Courses
int              insertCourse(sqlite3* db, Course& course);
std::vector<Course> getCoursesForStudent(sqlite3* db, int studentId, int semester);
bool             deleteCourse(sqlite3* db, int courseId, int studentId);
bool             updateCourseGrade(sqlite3* db, int courseId, double finalGrade);



// Grade Components
int  insertGradeComponent(sqlite3* db, GradeComponent& component);
std::vector<GradeComponent> getComponentsForCourse(sqlite3* db, int courseId);