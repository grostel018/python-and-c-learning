# Database module (database.cpp)

Provides a small SQLite-backed data access layer for the Grades Manager application.
The module exposes functions to create and initialize the schema, open the database,
and perform CRUD operations for `Student`, `Course` and `GradeComponent` entities.

Notes
- All functions expect a valid `sqlite3*` database handle unless otherwise documented.
- Errors are logged to `stderr` using the internal helper `logError`.
- The schema enforces foreign keys and constraints (e.g. unique `username`, non-zero `credits`, grade/weight ranges).

---

## Helpers

### `static void logError(const std::string& context, sqlite3* db)`
- Purpose: Log a concise SQLite error message prefixed with `context`.
- Parameters:
  - `context` — short description of the operation (e.g. `"insertStudent prepare"`).
  - `db` — SQLite database handle used to obtain `sqlite3_errmsg`.
- Notes: Writes to `std::cerr`.

---

## Setup

### `void initDatabase(sqlite3* db)`
- Purpose: Enable foreign keys and create the application schema if it doesn't exist.
- Creates tables:
  - `students (id, name, username UNIQUE, password)`
  - `courses (id, student_id FK -> students.id, name, credits CHECK >0, semester CHECK >0, final_grade)`
  - `grade_components (id, course_id FK -> courses.id, label, grade CHECK 0..100, weight CHECK 0..100)`
- Creates indexes:
  - `idx_courses_student_semester` on `(student_id, semester)`
  - `idx_components_course` on `(course_id)`
- Parameters:
  - `db` — open SQLite handle
- Error handling: Logs SQLite errors via `logError` and frees the returned error string.

### `sqlite3* openAndInitDatabase(const std::string& filename)`
- Purpose: Open a SQLite database file, enable extended result codes, initialize schema.
- Parameters:
  - `filename` — path to SQLite database file
- Returns:
  - `sqlite3*` on success, `nullptr` on failure
- Behavior:
  - Calls `sqlite3_open`; on failure logs the error and closes the handle.
  - Calls `sqlite3_extended_result_codes(db, 1)` and `initDatabase(db)`.
  - Prints a success message to `stdout` on success.

---

## Students

### `int insertStudent(sqlite3* db, Student& student)`
- Purpose: Insert a new student row.
- Parameters:
  - `db` — database handle
  - `student` — reference; uses `name`, `username`, `password`; on success sets `student.id`
- Returns:
  - new `id` (>0) on success, `-1` on error
- Notes:
  - Uses a parameterized INSERT with prepared statements.
  - Detects unique-constraint violations and prints "Username already exists."
  - Finalizes statement in all paths.

### `Student getStudent(sqlite3* db, int id)`
- Purpose: Fetch a student by `id`.
- Returns:
  - `Student` populated from the row, or default-constructed `Student` if not found or on error.
- Notes: Does not differentiate "not found" vs error in the return value (both produce a default `Student`).

### `Student getStudentByUsername(sqlite3* db, const std::string& username)`
- Purpose: Fetch a student by `username`.
- Returns:
  - `Student`:
    - `id == 0` → not found
    - `id == -1` → db or input error
    - `id > 0` → found
- Parameter checks:
  - Returns `id == -1` if `db` is `nullptr`.
  - Returns `id == -1` if `username` length > 64.
  - Empty `username` returns `id == 0`.
- Notes: Uses single-exit pattern to ensure statement finalization.

### `bool deleteStudent(sqlite3* db, int id)`
- Purpose: Delete a student row by `id`.
- Returns: `true` if delete statement executed successfully (note: does not explicitly check affected rows).

### `bool studentExists(sqlite3* db, const std::string& username)`
- Purpose: Check whether a username already exists.
- Returns: `true` if count > 0, `false` otherwise.
- Notes: Uses `SELECT COUNT(*)` with a bound parameter.

### `bool updateStudent(sqlite3* db, int id, const std::string& name, const std::string& username, const std::string& password)`
- Purpose: Update `name`, `username`, `password` for a student by `id`.
- Returns: `true` if `sqlite3_changes(db) > 0` after a successful `UPDATE`, `false` on error or no change.

---

## Courses

### `int insertCourse(sqlite3* db, Course& course)`
- Purpose: Insert a `Course` for a student.
- Parameters:
  - Uses `course.studentId`, `course.name`, `course.credits`, `course.semester`, `course.finalGrade`.
  - On success sets `course.id`.
- Returns: new `id` on success, `-1` on error.
- Notes: Parameterized INSERT, finalizes statements on error.

### `std::vector<Course> getCoursesForStudent(sqlite3* db, int studentId, int semester)`
- Purpose: Get courses for a student in a particular semester.
- Returns: Vector of `Course` rows (empty if none or on error).
- Notes: Maps SQL columns to `Course` fields.

### `std::vector<Course> getCoursesByStudentId(sqlite3* db, int studentId)`
- Purpose: Get all courses for a student (ordered by `semester`, `name`).
- Returns: Vector of `Course`.

### `bool deleteCourse(sqlite3* db, int courseId, int studentId)`
- Purpose: Delete a course only if it belongs to the given `studentId`.
- Returns:
  - `true` if DELETE executed successfully and `sqlite3_changes(db) > 0`.
  - `false` on error or if no row was deleted.

### `bool updateCourseGrade(sqlite3* db, int courseId, double finalGrade)`
- Purpose: Set `final_grade` for a course by `id`.
- Returns: `true` if UPDATE statement completed successfully (does not check changed rows).

### `bool updateCourseGradeForStudent(sqlite3* db, int courseId, int studentId, double grade)`
- Purpose: Set `final_grade` for a course, but only when the course belongs to the specified `studentId`.
- Returns: `true` if the UPDATE succeeded and at least one row was changed.

---

## Grade Components

### `int insertGradeComponent(sqlite3* db, GradeComponent& component)`
- Purpose: Insert a `GradeComponent` for a course.
- Parameters:
  - Uses `component.courseId`, `component.label`, `component.grade`, `component.weight`.
  - On success sets `component.id`.
- Returns: new `id` on success, `-1` on error.
- Constraints enforced by DB: `grade` and `weight` must be in [0,100].

### `std::vector<GradeComponent> getComponentsForCourse(sqlite3* db, int courseId)`
- Purpose: Retrieve all grade components for a given course.
- Returns: Vector of `GradeComponent` (empty if none or on error).

---

## Error Handling and Best Practices
- All public functions use prepared statements with bound parameters to avoid SQL injection.
- Statements are finalized on all exit paths to avoid resource leaks.
- Several functions check `sqlite3_step` return codes and call `logError` when appropriate.
- Caller is responsible for closing the `sqlite3*` handle returned by `openAndInitDatabase`.
- Consider using `std::optional` or an explicit error type to distinguish "not found" from "error" for read functions returning structures.

---