#include <iostream>
#include "user_input.h"

/** 

 * @brief Get user input
 * 
 * @param start_x x-coordinate of start point
 * @param start_y y-coordinate of start point
 * @param end_x x-coordinate of end point
 * @param end_y y-coordinate of end point
 * 
 * @return true if valid input, otherwise false
 */
bool GetUserInput(float *start_x, float *start_y, float *end_x, float *end_y)
{
    std::cout << "Coordinates must be in the range {0, 0} -> {100, 100}\n";
    std::cout << "Please enter the start coordinates for the search\n";
    std::cout << "Start X: ";
    std::cin >> *start_x;
    std::cout << "Start Y: ";
    std::cin >> *start_y;

    std::cout <<"Please enter the end coordinates for the search\n";
    std::cout << "End X: ";
    std::cin >> *end_x;
    std::cout << "End Y: ";
    std::cin >> *end_y;

    bool valid_input = ValidateUserInput(start_x, start_y, end_x, end_y);

    if (!valid_input)
    {
        std::cout << "Invalid input. Coordinates outside of the range {0, 0} -> {100, 100}\n"            ;
    }

    return valid_input;
}

/**
 * @brief Validate user input
 * 
 * @param start_x x-coordinate of start point
 * @param start_y y-coordinate of start point
 * @param end_x x-coordinate of end point
 * @param end_y y-coordinate of end point
 * 
 * @return true if valid input, otherwise false
 */
bool ValidateUserInput(float *start_x, float *start_y, float *end_x, float *end_y)
{
    constexpr float MinCoordValue = 0.0;
    constexpr float MaxCoordValue = 100.0;

    bool valid_input = true;

    if ((*start_x < MinCoordValue) || (*start_y < MinCoordValue) || 
        (*end_x < MinCoordValue) || (*end_y < MinCoordValue) || 
        (*start_x > MaxCoordValue) || (*start_y > MaxCoordValue) ||
        (*end_x > MaxCoordValue) || (*end_y > MaxCoordValue)) {

            valid_input = false;
    }

    return valid_input;
}