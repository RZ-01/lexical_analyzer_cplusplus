struct Student {
    int id;
    char name[50];
    float gpa;
};

int totalStudents = 0;
struct Student database[100];

// Function to add a new student to the database
int addStudent(int id, char name[], float gpa) {
    if (totalStudents >= 100) {
        return 0;  // Database is full
    }
    
    database[totalStudents].id = id;
    // Copy name using loop
    int i = 0;
    while (name[i] != '\0' && i < 49) {
        database[totalStudents].name[i] = name[i];
        i = i + 1;
    }
    database[totalStudents].name[i] = '\0';
    database[totalStudents].gpa = gpa;
    
    totalStudents = totalStudents + 1;
    return 1;  // Success
}

// Function to search for a student by ID
int findStudent(int id) {
    int i = 0;
    while (i < totalStudents) {
        if (database[i].id == id) {
            return i;  // Found the student
        }
        i = i + 1;
    }
    return -1;  // Student not found
}

// Function to calculate average GPA
float calculateAverageGPA() {
    if (totalStudents == 0) {
        return 0.0;
    }
    
    float sum = 0.0;
    int i = 0;
    while (i < totalStudents) {
        sum = sum + database[i].gpa;
        i = i + 1;
    }
    
    return sum / totalStudents;
}

// Function to display student information
void displayStudent(int index) {
    if (index >= 0 && index < totalStudents) {
        write("Student ID: ");
        write(database[index].id);
        write("Name: ");
        write(database[index].name);
        write("GPA: ");
        write(database[index].gpa);
    } else {
        write("Invalid student index");
    }
}

// Main function to run the program
int main() {
    int choice = 0;
    int id;
    char name[50];
    float gpa;
    int result;
    
    while (choice != 5) {
        write("Student Management System");
        write("1. Add Student");
        write("2. Find Student");
        write("3. Calculate Average GPA");
        write("4. Display All Students");
        write("5. Exit");
        write("Enter your choice: ");
        
        read(choice);
        
        if (choice == 1) {
            write("Enter student ID: ");
            read(id);
            write("Enter student name: ");
            read(name);
            write("Enter student GPA: ");
            read(gpa);
            
            result = addStudent(id, name, gpa);
            if (result == 1) {
                write("Student added successfully!");
            } else {
                write("Failed to add student. Database is full.");
            }
        } else if (choice == 2) {
            write("Enter student ID to find: ");
            read(id);
            
            result = findStudent(id);
            if (result != -1) {
                displayStudent(result);
            } else {
                write("Student not found!");
            }
        } else if (choice == 3) {
            gpa = calculateAverageGPA();
            write("Average GPA: ");
            write(gpa);
        } else if (choice == 4) {
            if (totalStudents == 0) {
                write("No students in database.");
            } else {
                int i = 0;
                while (i < totalStudents) {
                    displayStudent(i);
                    i = i + 1;
                }
            }
        } else if (choice == 5) {
            write("Exiting program. Goodbye!");
        } else {
            write("Invalid choice. Please try again.");
        }
    }
    
    return 0;
}