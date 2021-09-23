#include "gtest/gtest.h"
#include <iostream>
#include "../src/user_input.h"

namespace{

// Test the positive case where we have valid inputs
TEST(UserInput, Positive)
{
    float start_x = 10.0;
    float start_y = 20.0;
    float end_x = 80.0;
    float end_y = 90.0;

    EXPECT_EQ(ValidateUserInput(&start_x, &start_y, &end_x, &end_y), true);
    EXPECT_EQ(start_x, 10.0);
    EXPECT_EQ(start_y, 20.0);
    EXPECT_EQ(end_x, 80.0);
    EXPECT_EQ(end_y, 90.0);
}

// Test the negative case where we have invalid inputs
TEST(UserInput, Negative)
{
    float start_x = -0.1;
    float start_y = 10.0;
    float end_x = 90.0;
    float end_y = 90.0;

    EXPECT_EQ(ValidateUserInput(&start_x, &start_y, &end_x, &end_y), false);

    start_x = 10.0;
    start_y = -0.1;
    end_x = 90.0;
    end_y = 90.0;

    EXPECT_EQ(ValidateUserInput(&start_x, &start_y, &end_x, &end_y), false);

    start_x = 10.0;
    start_y = 100.1;
    end_x = 90.0;
    end_y = 90.0;

    EXPECT_EQ(ValidateUserInput(&start_x, &start_y, &end_x, &end_y), false);

    start_x = 10.0;
    start_y = 10.0;
    end_x = 100.1;
    end_y = 90.0;

    EXPECT_EQ(ValidateUserInput(&start_x, &start_y, &end_x, &end_y), false);

    start_x = 10.0;
    start_y = 10.0;
    end_x = 90.0;
    end_y = -0.01;

    EXPECT_EQ(ValidateUserInput(&start_x, &start_y, &end_x, &end_y), false);
}
}