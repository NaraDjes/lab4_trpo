#include "circle.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int left_bracket(char* str)
{
    int j = str[6];
    if (j == ASCII_BRACKET_RIGHT) {
        return 1;
    }
    return 0;
}

int right_bracket(char* str)
{
    int j = ASCII_BRACKET_LEFT;
    for (int i = 9; i < ASCII_BRACKET_LEFT; i++) {
        if (str[i] == j)
            return i + 1;
    }
    return 0;
}

void str_to_lower(char* str)
{
    for (int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}

int is_arguments(char* str)
{
    int ret = 0;
    int count = 0;
    int j = 0;
    int z = 0;
    for (int i = 7; str[i] != ',' && i < strlen(str); i++) {
        if ((str[i] != '.' && str[i] != ' ')
            && !(str[i] >= ZERO && str[i] <= NINE)) {
            printf("Error at column %d: expected '<double>'\n", i + 1);
            j = i + 1;
            ret++;
            return 1;
        }
        if (str[i] >= ZERO && str[i] <= NINE && str[i + 1] == ' ') {
            count++;
            j = i + 1;
        }
        if (str[i] == '.' && str[i + 1] == ')') {
            count += 2;
            j = i + 1;
        }
    }
    if (count + 1 != 2) {
        printf("Error at column %d: expected '<double>'\n", j);
        ret++;
        return ret;
    }
    int index = 0;
    for (int i = 0; i != strlen(str); i++) {
        if (str[i] == ',') {
            index = i + 1;
            i = strlen(str) - 1;
        }
    }
    for (; str[index] != ')' && index < strlen(str); index++) {
        if ((str[index] != '.' && str[index] != ' ')
            && !(str[index] >= ZERO && str[index] <= NINE)) {
            printf("Error at column %d: expected radius '<double>'\n",
                   index + 1);
            z = index + 1;
            ret++;
            return 1;
        }
        if (str[index] >= ZERO && str[index] <= NINE && str[index + 1] == ' ') {
            count++;
            z = index + 1;
        }
        if (str[index] == '.' && str[index + 1] == ' ') {
            count += 2;
            z = index + 1;
        }
    }
    if (count != 1) {
        printf("Error at column %d: expected radius '<double>'\n", z);
        ret++;
    }
    return ret;
}

int is_end(char* str)
{
    int ret = 1;
    int firstBracket = 0;
    long int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
            firstBracket = i;
            break;
        }
    }
    if (firstBracket == endingSymbol)
        ret = 0;
    return ret;
}

int error_ending_symbol(char* str)
{
    long int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
        }
    }
    return endingSymbol;
}

int is_object(char* str)
{
    int ret = 1;
    char rec[100];
    for (int i = 0; i < 6; i++) {
        rec[i] = str[i];
    }
    char figure[] = "circle";
    if (strcmp(rec, figure) == 0) {
        ret = 0;
    }
    return ret;
}

int print_errors(char* str, int countObj)
{
    int z = right_bracket(str);
    int s = error_ending_symbol(str) - 1;
    int count = 0;
    if (is_object(str)) {
        count++;
        printf("Error at column 0: expected 'circle'\n");
    } else if (left_bracket(str)) {
        count++;
        printf("Error at column 7: expected '('\n");
    } else if (right_bracket(str)) {
        count++;
        printf("Error at column %d: expected ')'\n", z);
    } else if (is_arguments(str)) {
        count++;
        return count;
    } else if (is_end(str)) {
        count++;
        printf("Error at column %d: unexpected token\n", s);
    }
    return count;
}

double get_per(char* str)
{
    char radius[10];
    for (int i = 7; i != strlen(str); i++) {
        if (str[i] == ',') {
            int j = 0;
            i = i + 1;
            for (int z = i; str[z] != ')'; z++) {
                radius[j] = str[z];
                j++;
            }
        }
    }
    double rad = atof(radius);
    double per = 2 * M_PI * rad;
    init_array(radius);
    return per;
}
double get_area(char* str)
{
    char radius[10];
    for (int i = 7; i != strlen(str); i++) {
        if (str[i] == ',') {
            int j = 0;
            i = i + 1;
            for (int z = i; str[z] != ')'; z++) {
                radius[j] = str[z];
                j++;
            }
        }
    }
    double rad = atof(radius);
    double area = M_PI * rad * rad;
    init_array(radius);
    return area;
}
void init_array(char* mass)
{
    for (int i = 0; i < 10; i++) {
        mass[i] = 0;
    }
}

int intersects(circle* figures, int index, int length)
{
    printf("Position %d:\ncircle(%.1lf %.1lf, %.1lf)\n  perimeter = %lf\n  "
           "area = "
           "%lf\n  intersects:\n",
           index + 1,
           figures[index].center.x,
           figures[index].center.y,
           figures[index].radius,
           figures[index].perimeter,
           figures[index].area);
    if (length <= 1)
        printf("Недостаточно объектов, чтобы посчиатать пересечения\n");
    double x1 = figures[index].center.x;
    double y1 = figures[index].center.y;
    double r1 = figures[index].radius;
    for (int i = 0; i < length; i++) {
        if (i == index)
            continue;
        else {
            double x2 = figures[i].center.x;
            double y2 = figures[i].center.y;
            double r2 = figures[i].radius;
            double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            if (d < r1 + r2)
                printf("  %d. circle\n", i + 1);
        }
    }
    return 0;
}

int get_center(char* str, circle* circle)
{
    char* number = malloc(10);
    int bracket = 0;
    for (int i = 0;; i++) {
        if (str[i] == '(') {
            bracket = i;
            break;
        }
    }
    int index = 0;
    for (int i = bracket + 1; str[i] != ','; i++)
        number[index++] = str[i];
    if (sscanf(number, "%lf %lf", &(circle->center.x), &(circle->center.y))
        == 2) {
        free(number);
        return 0;
    } else {
        free(number);
        return -1;
    }
}

int get_radius(char* str, circle* circle)
{
    char* number = malloc(10);
    int comma = 0;
    for (int i = 0; str[i] != ','; i++)
        comma = i + 2;
    int index = 0;
    for (int i = comma; str[i] != ')'; i++)
        number[index++] = str[i];
    if (sscanf(number, "%lf", &(circle->radius)) == 1) {
        free(number);
        return 0;
    } else {
        free(number);
        return -1;
    }
}