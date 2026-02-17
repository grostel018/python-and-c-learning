//plan 
//make a welcome function
//for gpa : 
//make an input function that only takes numbers and displays an error otherwise
//make an input function that only takes strings and displays an error otherwise
// 
//make a lecture adder function that takes the lecture name and the total grade scored on that lecture
//plus the weight of that lecture
// 
//implement my semester lecture average grade calculator to help doing this task (total grade scored on that lecture)
//make a lecturescount that count the number of lectures taken in the semester
// 
// calculate cgpa based on the total semesters added : semester 1 gpa + semester 2 gpa + ... +n / n

#include <cctype>
#include<iostream>
#include <string>




void welcome()
{
    std::cout << "\t*Welcome to the GPA calculator*" << std::endl;
    std::cout << "\t*You can either compute your GPA or you CGPA*" << std::endl;
}

double takeNumber()
{
    std::cout << "Enter a number" << std::endl;
    double number{ 0.0 };
    while (true)
    {
        if (std::cin >> number)
        {
            std::cin.ignore(10000, '\n');
            return number;  // No need for static_cast, number is already double
        }
        else
        {
            std::cout << "Enter a valid input (must be a number)" << std::endl;
            std::cin.clear();           // Clear the error flags
            std::cin.ignore(10000, '\n'); // Discard invalid input
        }

    }

}


std::string takeString()
{   
    std::string text  {""};
    
    std::cout << "Enter the lecture name (letters and spaces only):" << std::endl;

    while (true)

    {

        std::getline(std::cin, text);
    
        bool valid = !text.empty();

        for (char c : text) {
            if (!std::isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
        }

        if (valid) {
            return text;
        }
        else {
            std::cout << "Invalid input! Use only letters and spaces.\n";
        }


    }

    return text;
}



















int main()
{
    welcome();
    takeNumber();
    takeString();

    return 0;
}
