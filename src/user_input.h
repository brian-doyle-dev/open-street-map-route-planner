
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
bool GetUserInput(float *start_x, float *start_y, float *end_x, float *end_y);

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
bool ValidateUserInput(float *start_x, float *start_y, float *end_x, float *end_y);