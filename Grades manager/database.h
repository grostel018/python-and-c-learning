
// ─────────────────────────────────────────
//  Database
// ─────────────────────────────────────────
#pragma once
#include "Models.h"
#include "src/sqlite3.h"
#include <string>
#include <vector>
#include <memory>

// ── Constants ────────────────────────────
namespace Constants {
    // Database
    constexpr const char* DATABASE_FILENAME = "gpa.db";

    // Student validation
    constexpr int MIN_USERNAME_LENGTH = 3;
    constexpr int MAX_USERNAME_LENGTH = 20;
    constexpr int MIN_PASSWORD_LENGTH = 6;
    constexpr std::size_t MAX_USERNAME_SIZE = 64;

    // Course validation
    constexpr int MIN_CREDITS = 1;
    constexpr int MAX_CREDITS = 30;
    constexpr int MIN_SEMESTER = 1;
    constexpr int MAX_SEMESTER = 20;

    // Grade validation
    constexpr double MIN_GRADE = 0.0;
    constexpr double MAX_GRADE = 100.0;

    // UI
    constexpr int MAX_COURSE_ID_LOOKUP = 1000000;
}

// ── RAII Database Handle ─────────────────
/**
 * @brief RAII wrapper for SQLite database connection.
 *
 * Automatically closes the database when the wrapper goes out of scope.
 * Provides exception-safe database management.
 */
class Database {
public:
    /**
     * @brief Construct a new Database by opening and initializing the database file.
     * @param filename Path to the SQLite database file.
     * @throws std::runtime_error if the database cannot be opened or initialized.
     */
    explicit Database(const std::string& filename);

    /**
     * @brief Destroy the Database object, closing the connection.
     */
    ~Database();

    // Non-copyable, non-movable
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database&&) = delete;

    /**
     * @brief Get raw pointer to the underlying sqlite3 handle.
     * @return sqlite3* pointer to the database handle.
     */
    sqlite3* get() const { return db_.get(); }

    /**
     * @brief Check if the database is open.
     * @return true if the database is open, false otherwise.
     */
    explicit operator bool() const { return db_ != nullptr; }

private:
    std::unique_ptr<sqlite3, int(*)(sqlite3*)> db_;
};
// ── Database Functions ───────────────────
// Old-style functions for backward compatibility

// Setup
sqlite3* openAndInitDatabase(const std::string& filename);
void    initDatabase(sqlite3* db);

// Students
int     insertStudent(sqlite3* db, Student& student);
Student getStudent(sqlite3* db, int id);
Student getStudentByUsername(sqlite3* db, const std::string& username);
bool    deleteStudent(sqlite3* db, int id);
bool    studentExists(sqlite3* db, const std::string& username);
bool    updateStudent(sqlite3* db, int id, const std::string& name, const std::string& username, const std::string& password);

// Courses
int              insertCourse(sqlite3* db, Course& course);
std::vector<Course> getCoursesForStudent(sqlite3* db, int studentId, int semester);
bool             deleteCourse(sqlite3* db, int courseId, int studentId);
bool             updateCourseGrade(sqlite3* db, int courseId, double finalGrade);
bool             updateCourseGradeForStudent(sqlite3* db, int courseId, int studentId, double grade);

// Grade Components
int  insertGradeComponent(sqlite3* db, GradeComponent& component);
std::vector<GradeComponent> getComponentsForCourse(sqlite3* db, int courseId);
std::vector<Course> getCoursesByStudentId(sqlite3* db, int studentId);
