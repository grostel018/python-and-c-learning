#include <cctype>
#include<iostream>
#include <string>


void taskDelimeter()
{
    std::cout << "\n********************************************************************************************\n";
}






void welcome()
{
    std::cout << "\t*Welcome to the GPA calculator*" << std::endl;
    std::cout << "\t*You can either compute your GPA or you CGPA*" << std::endl;
    taskDelimeter();
}


double takeNumber()
{
    std::cout << "\nNumbers only : " << std::endl;
    double number{ 0.0 };
    while (true)
    {
        if (std::cin >> number)
        {
            std::cin.ignore(10000, '\n');

            std::cout << "\nInput registered successfully" << std::endl;

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
    std::string text{ "" };

    std::cout << "\nLetters and spaces only): " << std::endl;

    std::cin.clear();           // Clear the error flags
    std::cin.ignore(10000, '\n'); // Discard invalid input

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

            std::cout << "\nInput registered successfully" << std::endl;
            return text;
        }
        else {
            std::cout << "Invalid input! Use only letters and spaces.\n";
        }


    }

    return text;
}




void lectureAdder(double grade, std::string name, double weight)
{
    std::cout << "\nEnter the lecture's name : ";

    name = takeString();

    taskDelimeter();

    std::cout << "\nEnter the lecture's grade : ";

    grade = takeNumber();

    taskDelimeter();

    std::cout << "\nEnter the lecture's weight : ";

    weight = takeNumber();

    taskDelimeter();

}






void lectureGradeCalculator()
{
    std::cout << "\n\tGrade average calculator\n";
    taskDelimeter();

    double midterms, midweight, finals, finalsweight, bonus, bonusweight;

    while (true)
    {
        std::cout << "\nEnter the midterms grade: ";
        midterms = takeNumber();

        std::cout << "Enter the midterms weight (%): ";
        midweight = takeNumber();

        taskDelimeter();

        std::cout << "Enter the finals grade: ";
        finals = takeNumber();

        std::cout << "Enter the finals weight (%): ";
        finalsweight = takeNumber();

        taskDelimeter();

        std::cout << "Enter the bonus/quizz/projects grade: ";
        bonus = takeNumber();

        std::cout << "Enter the bonus/quizz/projects weight (%): ";
        bonusweight = takeNumber();

        taskDelimeter();

        double sum = midweight + finalsweight + bonusweight;

        if (sum != 100)
        {
            std::cout << "\nERROR: Total weight must be 100%. You entered " << sum << "%.\n";
            taskDelimeter();
        }
        else
        {
            break;
        }
    }

    double totalgrade = (finals * finalsweight / 100) +
        (midterms * midweight / 100) +
        (bonus * bonusweight / 100);

    std::cout << "\nThe total grade is: " << totalgrade << "\n";
    std::cout << "\nThe operation is complete\n";
    taskDelimeter();
}



void printCommands()
{
    taskDelimeter();
    std::cout << "\t1- Add a lecture to the current semester\n";
    std::cout << "\t2- Compute a lecture's semester grade (And add it to the lecture)\n";
    std::cout << "\t3- Calculate the current GPA\n";
    std::cout << "\t4- Calculate the current CGPA\n";
    std::cout << "\t5- Delete a lecture\n";
    std::cout << "\t6- Delete an account\n";
    std::cout << "\t7- Log in\n";
    std::cout << "\t8- Register\n";
    std::cout << "\t3- Log out\n";
    taskDelimeter();

}

void choose() 

{
std::cout << "\tYou choosed\n";
}


void menu()
{
    //Explaining the commands
    //doing a loop between choices until the user chooses to stop
    //Using switches inside a loop to perform user's choices
    //1-log in
    //2-register or create an account
    //3-Add a lecture to the current semester or
    //4-calculate the lecture's semester grade and add it to the lecture(if the user doesnt know it)
    //5-calculate the user's current GPA and store it
    //6-calcutate the user's current CGPA and store it
    //7-Delete a lecture
    //8-Delete an account
    //9-log out

}
















































int main()
{
    printCommands();

    return 0;
}
