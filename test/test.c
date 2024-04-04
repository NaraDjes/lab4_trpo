#include "circle.h"
#include <ctest.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

CTEST(INPUT_CHECK, LEFT_BRACKET_INDEX)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 0;
    int real = left_bracket(str);
    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, RIGHT_BRACKET_INDEX)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 0;
    int real = right_bracket(str);
    ASSERT_EQUAL(expec, real);
}

CTEST(VALUES_ERRORS, CHECK_STRING)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 0;
    int real = is_arguments(str);
    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, CHECK_ENDING_SYMBOL)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 0;
    int real = is_end(str);
    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, SHAPE_NAME_CHECK)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 0;
    int real = is_object(str);
    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, ERROR_CHECKING)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 0;
    int real = print_errors(str, 1);
    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, CHECK_GET_PER)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 9.424778;
    int real = get_per(str);
    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, CHECK_GET_AREA)
{
    char str[] = "circle(0 0, 1.5)";
    int expec = 7.068583;
    int real = get_area(str);
    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, CHECK_GET_CENTER)
{
    char str[] = "circle(0 0, 1.5)";
    circle* circle = calloc(1, sizeof(circle));
    int expec = 0;
    int real = get_center(str, circle);
    ASSERT_EQUAL(expec, real);
}
CTEST(INPUT_CHECK, CHECK_GET_RAD)
{
    char str[] = "circle(0 0, 1.5)";
    circle* circle = calloc(1, sizeof(circle));
    int expec = 0;
    int real = get_radius(str, circle);
    ASSERT_EQUAL(expec, real);
}