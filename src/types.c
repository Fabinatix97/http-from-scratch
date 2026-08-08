#include <stdio.h>

typedef struct {
    int id;
    char model[10];
    int year;
} Car;

int main() {
    Car car1 = {0, "A1", 2021};
    Car car2 = {1, "A2", 2020};

    Car cars[2] = {car1, car2};

    for(int i = 0; i < 2; i++) {
        printf("Car with id %d is of model %s and was built in %d.\n", cars[i].id, cars[i].model, cars[i].year);
    }

    return 0;
}
