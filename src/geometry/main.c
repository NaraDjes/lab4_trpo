#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circle.h"

int main()
{
    FILE* file;
    file = fopen("./data.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        exit(0);
    }
    char str1[100];
    int countObj = 0;
    circle circ_pos;
    circle* cir_cle = calloc(100, sizeof(circle));
    while (fgets(str1, 99, file)) {
        str_to_lower(str1);
        if (print_errors(str1, countObj) == 0) {
            countObj++;
            get_center(str1, &circ_pos);
            get_radius(str1, &circ_pos);
            circ_pos.perimeter = get_per(str1);
            circ_pos.area = get_area(str1);
            cir_cle[countObj - 1] = circ_pos;
        } else {
            printf("%s\n", str1);
        }
    }
    for (int i = 0; i < countObj; i++) {
        intersects(cir_cle, i, countObj);
    }
    fclose(file);
    free(cir_cle);
    return 0;
}