// ─────────────────────────────────────────
//  Database.cpp
// ─────────────────────────────────────────
#include "Database.h"
#include <iostream>

// ── helpers ──────────────────────────────

/**
 * @brief Log a sqlite3 error to stderr with a context prefix.
 *
 * This helper prints a concise error message including the provided context
 * string and the message returned by sqlite3_errmsg for the given database
 * handle.
 *
 * @param context Short text describing the operation or location where the
 *                error occurred (e.g. "insertStudent prepare").
 * @param db      Pointer to an open sqlite3 database used to obtain the
 *                human-readable error message.
 */
static void logError(const std::string& context, sqlite3* db) {
    std::cerr << "[DB ERROR] " << context << ": " << sqlite3_errmsg(db) << "\n";
}


















// ── setup ────────────────────────────────

/**
 * @brief Initialize database schema and enable foreign keys.
 *
 * Ensures the SQLite PRAGMA for foreign keys is enabled, then creates the
 * three application tables if they do not already exist:
 *  - students
 *  - courses
 *  - grade_components
 *
 * The SQL for table creation is executed as a single multi-statement string.
 * Any sqlite error is logged via logError and the sqlite error string is freed.
 *
 * @param db Pointer to an open sqlite3 database.
 */
void initDatabase(sqlite3* db) {
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    const char* sql =
        "CREATE TABLE IF NOT EXISTS students ("
        "  id       INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  name     TEXT    NOT NULL,"
        "  username    TEXT    NOT NULL UNIQUE,"
        "  password TEXT    NOT NULL"
        ");"
        "CREATE TABLE IF NOT EXISTS courses ("
        "  id          INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  student_id  INTEGER NOT NULL,"
        "  name        TEXT    NOT NULL,"
        "  credits     INTEGER NOT NULL,"
        "  semester    INTEGER NOT NULL,"
        "  final_grade REAL    DEFAULT 0,"
        "  FOREIGN KEY (student_id) REFERENCES students(id)"
        ");"
        "CREATE TABLE IF NOT EXISTS grade_components ("
        "  id        INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  course_id INTEGER NOT NULL,"
        "  label     TEXT    NOT NULL,"
        "  grade     REAL    NOT NULL,"
        "  weight    REAL    NOT NULL,"
        "  FOREIGN KEY (course_id) REFERENCES courses(id)"
        ");";

    char* err = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        logError("initDatabase", db);
        sqlite3_free(err);
    }
}


sqlite3* openAndInitDatabase(const std::string& filename)
{
    sqlite3* db = nullptr;

    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Cannot open database: "
            << sqlite3_errmsg(db) << "\n";

        sqlite3_close(db);
        return nullptr;
    }

    initDatabase(db);

    std::cout << "Database initialized successfully.\n";
    return db;
}









// ── students ─────────────────────────────

/**
 * @brief Insert a new student into the database.
 *
 * Prepares and executes a parameterized INSERT into the `students` table.
 * On success the generated row id is stored into `student.id`.
 *
 * @param db      Pointer to an open sqlite3 database.
 * @param student Reference to a Student object whose `name`, `username`,
 *                and `password` fields will be inserted. `id` will be updated
 *                on success.
 * @return The new student's id on success, or -1 on failure.
 */
int insertStudent(sqlite3* db, Student& student) {
    const char* sql = "INSERT INTO students (name, username, password) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("insertStudent prepare", db); return -1;
    }

    sqlite3_bind_text(stmt, 1, student.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, student.username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, student.password.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        logError("insertStudent step", db);
        sqlite3_finalize(stmt); return -1;
    }

    student.id = (int)sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return student.id;
}

/**
 * @brief Retrieve a Student by id.
 *
 * Executes a SELECT to fetch the student row with the provided id. If no
 * matching row is found an empty Student (default constructed) is returned.
 *
 * @param db Pointer to an open sqlite3 database.
 * @param id The student id to look up.
 * @return A Student populated from the database row, or default Student if not found.
 */
Student getStudent(sqlite3* db, int id) {
    Student student{};
    const char* sql = "SELECT id, name, username, password FROM students WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("getStudent prepare", db); return student;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        student.id = sqlite3_column_int(stmt, 0);
        student.name = (const char*)sqlite3_column_text(stmt, 1);
        student.username = (const char*)sqlite3_column_text(stmt, 2);
        student.password = (const char*)sqlite3_column_text(stmt, 3);
    }

    sqlite3_finalize(stmt);
    return student;
}


// Returns a Student with id==0 if not found (or use std::optional if you want)
Student getStudentByUsername(sqlite3* db, const std::string& username) {
    Student student{};
    const char* sql =
        "SELECT id, name, username, password "
        "FROM students "
        "WHERE username = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("getStudentByUsername prepare", db);
        return student;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        student.id = sqlite3_column_int(stmt, 0);
        student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        student.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        student.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    }

    sqlite3_finalize(stmt);
    return student;
}















/**
 * @brief Delete a student by id.
 *
 * Executes a DELETE statement for the student with the given id.
 *
 * @param db Pointer to an open sqlite3 database.
 * @param id The id of the student to delete.
 * @return true if the deletion completed successfully, false otherwise.
 */
bool deleteStudent(sqlite3* db, int id) {
    const char* sql = "DELETE FROM students WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("deleteStudent prepare", db); return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

/**
 * @brief Check whether a username already exists.
 *
 * Executes a COUNT(*) query to determine if a student with the provided
 * username exists.
 *
 * @param db       Pointer to an open sqlite3 database.
 * @param username Username to check for uniqueness.
 * @return true if the username exists, false otherwise.
 */
bool studentExists(sqlite3* db, const std::string& username) {
    const char* sql = "SELECT COUNT(*) FROM students WHERE username = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("studentExists prepare", db); return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    bool exists = false;

    if (sqlite3_step(stmt) == SQLITE_ROW)
        exists = sqlite3_column_int(stmt, 0) > 0;

    sqlite3_finalize(stmt);
    return exists;
}

// ── courses ──────────────────────────────

/**
 * @brief Insert a Course for a student.
 *
 * Parameterized INSERT into `courses`. On success the generated id is stored
 * into `course.id`.
 *
 * @param db     Pointer to an open sqlite3 database.
 * @param course Reference to a Course object. `studentId`, `name`, `credits`,
 *               `semester`, and `finalGrade` fields are used for insertion.
 *               `id` will be updated on success.
 * @return The new course id on success, or -1 on failure.
 */
int insertCourse(sqlite3* db, Course& course) {
    const char* sql =
        "INSERT INTO courses (student_id, name, credits, semester, final_grade)"
        " VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("insertCourse prepare", db); return -1;
    }

    sqlite3_bind_int(stmt, 1, course.studentId);
    sqlite3_bind_text(stmt, 2, course.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, course.credits);
    sqlite3_bind_int(stmt, 4, course.semester);
    sqlite3_bind_double(stmt, 5, course.finalGrade);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        logError("insertCourse step", db);
        sqlite3_finalize(stmt); return -1;
    }

    course.id = (int)sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return course.id;
}

/**
 * @brief Get all courses for a student in a given semester.
 *
 * Executes a SELECT that returns course rows matching studentId and semester.
 * Each row is mapped to a Course and appended to the returned vector.
 *
 * @param db        Pointer to an open sqlite3 database.
 * @param studentId The student's id to filter courses by.
 * @param semester  The semester number to filter courses by.
 * @return A vector of Course objects (empty if none found or on error).
 */
std::vector<Course> getCoursesForStudent(sqlite3* db, int studentId, int semester) {
    std::vector<Course> courses;
    const char* sql =
        "SELECT id, student_id, name, credits, semester, final_grade"
        " FROM courses WHERE student_id = ? AND semester = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("getCoursesForStudent prepare", db); return courses;
    }

    sqlite3_bind_int(stmt, 1, studentId);
    sqlite3_bind_int(stmt, 2, semester);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Course c{};
        c.id = sqlite3_column_int(stmt, 0);
        c.studentId = sqlite3_column_int(stmt, 1);
        c.name = (const char*)sqlite3_column_text(stmt, 2);
        c.credits = sqlite3_column_int(stmt, 3);
        c.semester = sqlite3_column_int(stmt, 4);
        c.finalGrade = sqlite3_column_double(stmt, 5);
        courses.push_back(c);
    }

    sqlite3_finalize(stmt);
    return courses;
}

/**
 * @brief Delete a course by id.
 *
 * Executes a DELETE on the `courses` table for the provided id.
 *
 * @param db Pointer to an open sqlite3 database.
 * @param id The id of the course to delete.
 * @return true if deletion succeeded, false otherwise.
 */
bool deleteCourse(sqlite3* db, int id) {
    const char* sql = "DELETE FROM courses WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("deleteCourse prepare", db); return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

/**
 * @brief Update the stored final grade for a course.
 *
 * Executes an UPDATE to set the `final_grade` for the course with id
 * `courseId`.
 *
 * @param db        Pointer to an open sqlite3 database.
 * @param courseId  The id of the course to update.
 * @param finalGrade The new final grade value to store.
 * @return true if the update succeeded, false otherwise.
 */
bool updateCourseGrade(sqlite3* db, int courseId, double finalGrade) {
    const char* sql = "UPDATE courses SET final_grade = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("updateCourseGrade prepare", db); return false;
    }

    sqlite3_bind_double(stmt, 1, finalGrade);
    sqlite3_bind_int(stmt, 2, courseId);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

// ── grade components ─────────────────────

/**
 * @brief Insert a grade component for a course.
 *
 * Adds a new row to the `grade_components` table. On success the generated id
 * is stored in `component.id`.
 *
 * @param db        Pointer to an open sqlite3 database.
 * @param component Reference to a GradeComponent whose `courseId`, `label`,
 *                  `grade`, and `weight` will be inserted. `id` will be set
 *                  on success.
 * @return The new grade component id on success, or -1 on failure.
 */
int insertGradeComponent(sqlite3* db, GradeComponent& component) {
    const char* sql =
        "INSERT INTO grade_components (course_id, label, grade, weight)"
        " VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("insertGradeComponent prepare", db); return -1;
    }

    sqlite3_bind_int(stmt, 1, component.courseId);
    sqlite3_bind_text(stmt, 2, component.label.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, component.grade);
    sqlite3_bind_double(stmt, 4, component.weight);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        logError("insertGradeComponent step", db);
        sqlite3_finalize(stmt); return -1;
    }

    component.id = (int)sqlite3_last_insert_rowid(db);
    sqlite3_finalize(stmt);
    return component.id;
}

/**
 * @brief Retrieve grade components for a course.
 *
 * Executes a SELECT for all grade components that belong to the specified
 * course and returns them as a vector.
 *
 * @param db       Pointer to an open sqlite3 database.
 * @param courseId The course id to get components for.
 * @return Vector of GradeComponent objects (empty if none found or on error).
 */
std::vector<GradeComponent> getComponentsForCourse(sqlite3* db, int courseId) {
    std::vector<GradeComponent> components;
    const char* sql =
        "SELECT id, course_id, label, grade, weight"
        " FROM grade_components WHERE course_id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        logError("getComponentsForCourse prepare", db); return components;
    }

    sqlite3_bind_int(stmt, 1, courseId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        GradeComponent gc{};
        gc.id = sqlite3_column_int(stmt, 0);
        gc.courseId = sqlite3_column_int(stmt, 1);
        gc.label = (const char*)sqlite3_column_text(stmt, 2);
        gc.grade = sqlite3_column_double(stmt, 3);
        gc.weight = sqlite3_column_double(stmt, 4);
        components.push_back(gc);
    }

    sqlite3_finalize(stmt);
    return components;
}