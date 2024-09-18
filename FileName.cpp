#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Define the structure for a Car
typedef struct Car {
    char reg[9];
    char model[50];
    char Colour[20];
    int owners;
    bool reserved;
    float reserve_amt;
    struct Car* next;
} Car;

// Function to make a new car
Car* createCar(char reg[], char model[], char Colour[], int owners, bool reserved, float reserve_amt) {
    Car* newCar = (Car*)malloc(sizeof(Car));
    if (newCar != NULL) {
        strcpy(newCar->reg, reg);
        strcpy(newCar->model, model);
        strcpy(newCar->Colour, Colour);
        newCar->owners = owners;
        newCar->reserved = reserved;
        newCar->reserve_amt = reserve_amt;
        newCar->next = NULL;
    }
    return newCar;
}

int carCount = 0;
Car* head = NULL;

/*void loadCarsFromFile() {
    FILE* file = fopen("car.dat", "rb");
    if (file == NULL) {
        printf("List of cars doesn't exist. Please input the cars.\n");
        return;
    }
    while (!feof(file)) {
        Car car;
        if (fread(&car, sizeof(Car), 1, file) == 1) {
            Car* newCar = createCar(car.reg, car.model, car.Colour, car.owners, car.reserved, car.reserve_amt);
            if (head == NULL) {
                head = newCar;
            }
            else {
                Car* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newCar;
            }
            carCount++;
        }
    }
    fclose(file);
    printf("System has been populated with cars from the data file.\n");
}
*/  //I tried to add it to a file but wasnt sure on how to add the file to the folder and connect it to this source.

//Function to reserve and unreserve cars

void reserveCar() {
    char reg[9];
    bool found = false;
    Car* temp = head;

    printf("\nEnter car registration to reserve/unreserve: ");
    scanf("%s", reg);

    while (temp != NULL) {
        if (strcmp(temp->reg, reg) == 0) {
            temp->reserved = !temp->reserved;
            found = true;
            printf("\nReservation status updated for car with registration %s.\n", reg);
            break;
        }
        temp = temp->next;
    }

    if (!found)
        printf("\nCar with registration %s not found.\n", reg);
}

//Function to view All cars
void viewAllCars() {
    if (head == NULL) {
        printf("\nThe showroom is empty.\n");
        return;
    }

    printf("\n===== Cars in the showroom =====\n");
    Car* current = head;
    while (current != NULL) {
        printf("Registration: %s\n", current->reg);
        printf("Model: %s\n", current->model);
        printf("Colour: %s\n", current->Colour);
        printf("Number of owners: %d\n", current->owners);
        printf("Reserved: %s\n", current->reserved ? "Yes" : "No");
        printf("Reserve amount: %.2f\n", current->reserve_amt);
        printf("\n");
        current = current->next;
    }
}
//Function to change car detaild
void updateCar() {
    char reg[9];
    printf("\nEnter car registration to update details: ");
    scanf("%s", reg);

    Car* current = head;
    bool found = false;

    while (current != NULL) {
        if (strcmp(current->reg, reg) == 0) {
            found = true;
            int choice;
            printf("\nChoose which attribute to update:\n");
            printf("1. Model\n");
            printf("2. Color\n");
            printf("3. Number of owners\n");
            printf("4. Reservation status\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter new model: ");
                scanf("%s", current->model);
                break;
            case 2:
                printf("Enter new color: ");
                scanf("%s", current->color);
                break;
            case 3:
                printf("Enter new number of owners: ");
                scanf("%d", &current->owners);
                break;
            case 4:
                printf("Is the car reserved? (1 for yes, 0 for no): ");
                scanf("%d", &current->reserved);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }

            printf("\nCar details updated successfully.\n");
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("\nCar with registration %s not found.\n", reg);
    }
}

void displayMenu() {
    printf("\n===== Car Showroom Menu =====\n");
    printf("1. Add a new car to the showroom\n");
    printf("2. Sell a car from the showroom\n");
    printf("3. Reserve/Unreserve a car in the showroom\n");
    printf("4. View all cars in the showroom\n");
    printf("5. View a specific car in the showroom\n");
    printf("6. Additional option\n");
    printf("7. Exit the system\n");
}

void addCar() {
    if (carCount >= 5) {
        printf("\nCannot add more cars. Showroom is full.\n");
        return;
    }

    char reg[9], model[50], Colour[20];
    int owners;
    bool reserved;
    float reserve_amt;

    printf("\nEnter car registration: ");
    scanf("%s", reg);
    printf("Enter car make and model: ");
    scanf("%s", model);
    printf("Enter car Colour: ");
    scanf("%s", Colour);
    printf("Enter number of previous owners: ");
    scanf("%d", &owners);
    printf("Is the car reserved? (1 for yes, 0 for no): ");
    scanf("%d", &reserved);
    printf("Enter reserve amount: ");
    scanf("%f", &reserve_amt);

    Car* newCar = createCar(reg, model, Colour, owners, reserved, reserve_amt);
    if (head == NULL) {
        head = newCar;
    }
    else {
        Car* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newCar;
    }
    carCount++;
    printf("\nCar added successfully.\n");
}

void viewSpecificCar() {
    char reg[9];
    printf("\nEnter car registration to view details: ");
    scanf("%s", reg);

    Car* current = head;
    bool found = false;

    while (current != NULL) {
        if (strcmp(current->reg, reg) == 0) {
            found = true;
            printf("\n===== Car Details =====\n");
            printf("Registration: %s\n", current->reg);
            printf("Model: %s\n", current->model);
            printf("Colour: %s\n", current->Colour);
            printf("Number of owners: %d\n", current->owners);
            printf("Reserved: %s\n", current->reserved ? "Yes" : "No");
            printf("Reserve amount: %.2f\n", current->reserve_amt);
            printf("\n");
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("\nCar with registration %s not found.\n", reg);
    }
}

void sellCar() {
    if (head == NULL) {
        printf("\nNo cars in the showroom to sell.\n");
        return;
    }

    char reg[9];
    printf("\nEnter the registration of the car to sell: ");
    scanf("%s", reg);

    Car* current = head;
    Car* prev = NULL;
    bool found = false;

    while (current != NULL) {
        if (strcmp(current->reg, reg) == 0) {
            found = true;
            if (current->reserved) {
                if (prev == NULL) {
                    head = current->next;
                }
                else {
                    prev->next = current->next;
                }
                free(current);
                carCount--;
                printf("\nCar with registration %s sold successfully.\n", reg);
            }
            else {
                printf("\nCar with registration %s is not reserved and cannot be sold.\n", reg);
            }
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        printf("\nCar with registration %s not found.\n", reg);


        int main() {
            int choice;

            do {
                displayMenu();
                printf("\nEnter your choice: ");
                scanf(" %d", &choice);

                switch (choice) {
                case 1:
                    addCar();
                    break;
                case 2:
                    sellCar();
                    break;
                case 3:
                    reserveCar();
                    break;
                case 4:
                    viewAllCars();
                    break;
                case 5:
                    viewSpecificCar();
                    break;
                case 6:
                    updateCar();
                    break;
                case 7:
                    printf("\nColsing the system. Goodbye!\n");
                    break;
                default:
                    printf("\nWrong choice. Please enter a number between 1 and 7.\n");
                }
            } while (choice != 7);

            printf("\nPress to close the window");
            getchar();

            return 0;
        }


