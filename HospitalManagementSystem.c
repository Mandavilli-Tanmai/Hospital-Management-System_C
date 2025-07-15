#include <stdio.h>
#include <string.h>

#define MAX_SLOTS 6  // Define max slots for each doctor
#define DOCTOR_COUNT 2  // Number of doctors

// Define Appointment structure
typedef struct {
    int id;
    char name[50];
    int age;
    char disease[25];
} Appointment;

// Define Doctor structure
typedef struct {
    char name[20];
    Appointment slots[MAX_SLOTS];
} Doctor;

// Declare doctors
Doctor doctors[DOCTOR_COUNT] = {
    {"Dr.ABC", {{0}}},
    {"Dr.DEF", {{0}}}
};

// Predefined timings for each slot
const char slot_timings[MAX_SLOTS][20] = {
    "11:00 AM - 11:30 AM",
    "11:30 AM - 12:00 PM",
    "12:00 PM - 12:30 PM",
    "12:30 PM - 1:00 PM",
    "1:00 PM - 1:30 PM",
    "1:30 PM - 2:00 PM"
};

// Function to display slots of a specific doctor
void displayDoctorSlots(Doctor *doctor) {
    printf("\nAvailable Slots for %s:\n", doctor->name);
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (doctor->slots[i].id == 0) {
            printf("Slot %d (%s): Available\n", i + 1, slot_timings[i]);
        } else {
            printf("Slot %d (%s): Booked by %s\n", i + 1, slot_timings[i], doctor->slots[i].name);
        }
    }
}

// Function to display all slots for all doctors
void displaySlots() {
    for (int d = 0; d < DOCTOR_COUNT; d++) {
        displayDoctorSlots(&doctors[d]);
    }
}

// Function to book an appointment
void bookSlot() {
    int doctor_choice, slot_no;
    printf("\nSelect Doctor:\n");
    for (int i = 0; i < DOCTOR_COUNT; i++) {
        printf("%d. %s\n", i + 1, doctors[i].name);
    }
    printf("Enter your choice: ");
    scanf("%d", &doctor_choice);
    getchar(); // Clear newline character

    if (doctor_choice < 1 || doctor_choice > DOCTOR_COUNT) {
        printf("Invalid doctor selection!\n");
        return;
    }

    Doctor *selected_doctor = &doctors[doctor_choice - 1];

    // Display available slots for the selected doctor
    displayDoctorSlots(selected_doctor);

    printf("\nEnter slot number (1-%d) to book: ", MAX_SLOTS);
    scanf("%d", &slot_no);
    getchar(); // Clear newline character

    if (slot_no < 1 || slot_no > MAX_SLOTS || selected_doctor->slots[slot_no - 1].id != 0) {
        printf("Invalid slot or already booked!\n");
        return;
    }

    Appointment new_appointment;
    new_appointment.id = slot_no;
    printf("Enter Patient Name: ");
    scanf(" %[^\n]s", new_appointment.name);
    printf("Enter Age: ");
    scanf("%d", &new_appointment.age);
    getchar(); // Clear newline character
    printf("Enter Disease: ");
    scanf(" %[^\n]s", new_appointment.disease);

    selected_doctor->slots[slot_no - 1] = new_appointment;

    printf("\nSlot %d booked successfully for %s with %s (%s)!\n", 
            slot_no, new_appointment.name, selected_doctor->name, slot_timings[slot_no - 1]);
}

// Function to cancel an appointment
void cancelSlot() {
    int doctor_choice, slot_no;
    printf("\nSelect Doctor:\n");
    for (int i = 0; i < DOCTOR_COUNT; i++) {
        printf("%d. %s\n", i + 1, doctors[i].name);
    }
    printf("Enter your choice: ");
    scanf("%d", &doctor_choice);
    getchar(); // Clear newline character

    if (doctor_choice < 1 || doctor_choice > DOCTOR_COUNT) {
        printf("Invalid doctor selection!\n");
        return;
    }

    Doctor *selected_doctor = &doctors[doctor_choice - 1];

    printf("\nEnter slot number to cancel: ");
    scanf("%d", &slot_no);
    getchar(); // Clear newline character

    if (slot_no < 1 || slot_no > MAX_SLOTS || selected_doctor->slots[slot_no - 1].id == 0) {
        printf("Invalid slot or no booking found!\n");
        return;
    }

    printf("Appointment for %s with %s (%s) is canceled.\n", 
           selected_doctor->slots[slot_no - 1].name, selected_doctor->name, slot_timings[slot_no - 1]);
    selected_doctor->slots[slot_no - 1].id = 0; // Reset slot
}

// Function to view booked appointments
void viewAppointments() {
    for (int d = 0; d < DOCTOR_COUNT; d++) {
        printf("\nAppointments for %s:\n", doctors[d].name);
        int found = 0;
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (doctors[d].slots[i].id != 0) {
                printf("Slot %d (%s) -> %s, Age: %d, Disease: %s\n", 
                       i + 1, slot_timings[i], doctors[d].slots[i].name, 
                       doctors[d].slots[i].age, doctors[d].slots[i].disease);
                found = 1;
            }
        }
        if (!found) {
            printf("No appointments booked yet.\n");
        }
    }
}

// Main function to run the program
int main() {
    int choice;
    while (1) {
        printf("\n--- Hospital Slot Booking System ---\n");
        printf("1. View Available Slots\n");
        printf("2. Book a Slot\n");
        printf("3. Cancel a Slot\n");
        printf("4. View Appointments\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySlots();
                break;
            case 2:
                bookSlot();
                break;
            case 3:
                cancelSlot();
                break;
            case 4:
                viewAppointments();
                break;
            case 5:
                printf("Exiting system.\n");
                return 0;
            default:
                printf("Invalid choice! Please select a valid option.\n");
        }
    }
}
