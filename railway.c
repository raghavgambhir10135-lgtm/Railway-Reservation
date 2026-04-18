#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Train {
    int trainNo;
    char route[100];
    char timing[20];
    int totalSeats;
    int availableSeats;
    char location[50];
    struct Train *next;
} Train;

typedef struct Passenger {
    int ticketNo;
    char name[50];
    int trainNo;
    int seatsBooked;
    float payment;
    struct Passenger *next;
} Passenger;

Train *trainHead = NULL;
Passenger *passengerHead = NULL;
int ticketCounter = 5000; // unique ticket number generator

// Add train
void addTrain(int trainNo, char *route, char *timing, int seats, char *location) {
    Train *newTrain = (Train*)malloc(sizeof(Train));
    newTrain->trainNo = trainNo;
    strcpy(newTrain->route, route);
    strcpy(newTrain->timing, timing);
    newTrain->totalSeats = seats;
    newTrain->availableSeats = seats;
    strcpy(newTrain->location, location);
    newTrain->next = NULL;

    if(trainHead == NULL) trainHead = newTrain;
    else {
        Train *temp = trainHead;
        while(temp->next != NULL) temp = temp->next;
        temp->next = newTrain;
    }
    printf("Train %d added: %s (%s) | Seats: %d | Location: %s\n",
           newTrain->trainNo, route, timing, seats, location);
}

// Display trains
void displayTrains() {
    Train *temp = trainHead;
    if(temp == NULL) {
        printf("No trains available.\n");
        return;
    }
    printf("\n--- Train List ---\n");
    while(temp != NULL) {
        printf("Train %d | Route: %s | Timing: %s | Seats: %d/%d | Location: %s\n",
               temp->trainNo, temp->route, temp->timing,
               temp->availableSeats, temp->totalSeats, temp->location);
        temp = temp->next;
    }
}

// Book ticket (unique ticket number generated)
void bookTicket(char *name, int trainNo, int seats) {
    Train *t = trainHead;
    while(t != NULL && t->trainNo != trainNo) t = t->next;
    if(t == NULL) {
        printf("Train not found!\n");
        return;
    }
    if(t->availableSeats < seats) {
        printf("Not enough seats available!\n");
        return;
    }
    t->availableSeats -= seats;

    Passenger *newP = (Passenger*)malloc(sizeof(Passenger));
    newP->ticketNo = ticketCounter++; // unique ticket number
    strcpy(newP->name, name);
    newP->trainNo = trainNo;
    newP->seatsBooked = seats;
    newP->payment = seats * 100.0; // basic fare: 100 per seat
    newP->next = NULL;

    if(passengerHead == NULL) passengerHead = newP;
    else {
        Passenger *temp = passengerHead;
        while(temp->next != NULL) temp = temp->next;
        temp->next = newP;
    }
    printf("Ticket booked: %s | Train %d | Ticket No: %d | Seats: %d | Payment: %.2f\n",
           name, trainNo, newP->ticketNo, seats, newP->payment);
}

// Cancel ticket
void cancelTicket(int ticketNo) {
    Passenger *temp = passengerHead, *prev = NULL;
    while(temp != NULL && temp->ticketNo != ticketNo) {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL) {
        printf("Ticket not found!\n");
        return;
    }
    // restore seats
    Train *t = trainHead;
    while(t != NULL && t->trainNo != temp->trainNo) t = t->next;
    if(t != NULL) t->availableSeats += temp->seatsBooked;

    if(prev == NULL) passengerHead = temp->next;
    else prev->next = temp->next;
    printf("Ticket %d cancelled for %s.\n", temp->ticketNo, temp->name);
    free(temp);
}

// Display passengers
void displayPassengers() {
    Passenger *temp = passengerHead;
    if(temp == NULL) {
        printf("No passengers booked.\n");
        return;
    }
    printf("\n--- Passenger List ---\n");
    while(temp != NULL) {
        printf("Ticket: %d | Name: %s | Train: %d | Seats: %d | Payment: %.2f\n",
               temp->ticketNo, temp->name, temp->trainNo, temp->seatsBooked, temp->payment);
        temp = temp->next;
    }
}

// Initialize trains for 2026
void initializeTrains() {
    // Rajdhani Express Trains
    addTrain(12002, "Delhi-Mumbai", "15:30", 600, "Delhi Central");
    addTrain(12016, "Delhi-Kolkata", "16:45", 650, "Delhi Central");
    addTrain(12030, "Delhi-Bangalore", "22:00", 620, "Delhi Central");
    addTrain(12008, "Mumbai-Delhi", "17:00", 600, "Mumbai Central");
    addTrain(12301, "Mumbai-Bangalore", "18:30", 550, "Mumbai Central");
    addTrain(12041, "New Delhi-Bangalore", "20:15", 630, "New Delhi");
    
    // Shatabdi Express Trains
    addTrain(12004, "Delhi-Jaipur", "06:00", 500, "Delhi");
    addTrain(12015, "Delhi-Chandigarh", "07:30", 480, "Delhi");
    addTrain(12011, "Mumbai-Pune", "07:15", 520, "Mumbai");
    addTrain(12010, "Chennai-Bangalore", "06:00", 540, "Chennai");
    
    // Mail/Express Trains
    addTrain(14015, "Delhi-Varanasi", "19:45", 700, "Delhi");
    addTrain(14018, "Mumbai-Hyderabad", "19:00", 640, "Mumbai");
    addTrain(14022, "Kolkata-Delhi", "18:30", 680, "Kolkata");
    addTrain(14031, "Bangalore-Chennai", "22:00", 620, "Bangalore");
    addTrain(14035, "Delhi-Agra", "06:45", 480, "Delhi");
    addTrain(14045, "Mumbai-Goa", "17:30", 450, "Mumbai");
    addTrain(14055, "Chennai-Hyderabad", "21:15", 600, "Chennai");
    addTrain(14062, "Kolkata-Guwahati", "20:00", 710, "Kolkata");
    
    // Local & Regional Trains
    addTrain(15001, "Delhi-Noida", "06:15", 800, "Delhi New Delhi");
    addTrain(15002, "Delhi-Ghaziabad", "06:30", 820, "Delhi");
    addTrain(15010, "Mumbai-Thane", "07:00", 900, "Mumbai Central");
    addTrain(15015, "Mumbai-Pune Local", "08:00", 750, "Mumbai");
    addTrain(15020, "Bangalore-Mysore", "06:30", 600, "Bangalore");
    addTrain(15030, "Chennai-Mylapore", "07:15", 700, "Chennai");
    addTrain(15040, "Kolkata-Howrah", "06:00", 850, "Kolkata");
    addTrain(15050, "Hyderabad-Secunderabad", "07:30", 750, "Hyderabad");
    
    // Premium Trains
    addTrain(12951, "Mumbai Rajdhani", "16:00", 400, "Mumbai Central");
    addTrain(12957, "Delhi Rajdhani", "15:00", 420, "Delhi");
    addTrain(12807, "Falaknuma Express", "12:00", 350, "Hyderabad");
    addTrain(12621, "Tamil Nadu Express", "10:30", 380, "Chennai");
    addTrain(12222, "West Bengal Samanta Kranti", "14:45", 390, "Kolkata");
    
    // Special Trains
    addTrain(13001, "Taj Express (Delhi-Agra Circuit)", "08:00", 500, "Delhi");
    addTrain(13005, "Gateway of India Express", "09:00", 480, "Mumbai");
    addTrain(13010, "Deccan Queen Express", "07:10", 520, "Pune");
    addTrain(13015, "Shivshahi Express", "06:30", 550, "Mumbai");
    addTrain(13020, "Netravati Express", "16:30", 480, "Thiruvananthapuram");
    
    printf("\n=== 2026 Railway System Initialized ===\n");
    printf("Total Trains Loaded: 35 trains with comprehensive routes\n");
    printf("System Ready for Reservations\n\n");
}

// Save records to file (lifelong storage)
void saveToFile() {
    FILE *fp = fopen("railway_reservation.txt", "w");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Train *t = trainHead;
    while(t != NULL) {
        fprintf(fp, "Train,%d,%s,%s,%d,%d,%s\n", t->trainNo, t->route, t->timing,
                t->totalSeats, t->availableSeats, t->location);
        t = t->next;
    }
    Passenger *p = passengerHead;
    while(p != NULL) {
        fprintf(fp, "Passenger,%d,%s,%d,%d,%.2f\n", p->ticketNo, p->name,
                p->trainNo, p->seatsBooked, p->payment);
        p = p->next;
    }
    fclose(fp);
    printf("Records saved (lifelong).\n");
}

int main() {
    int choice, seats, trainNo, ticketNo;
    char name[50], route[100], timing[20], location[50];

    // Initialize with 2026 trains
    initializeTrains();

    while(1) {
        printf("\n--- Railway Reservation Menu ---\n");
        printf("1. Add Train\n2. Display Trains\n3. Book Ticket\n4. Cancel Ticket\n5. Display Passengers\n6. Save Records\n7. Exit\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter train number: ");
                scanf("%d", &trainNo);
                printf("Enter route: ");
                scanf("%s", route);
                printf("Enter timing (HH:MM): ");
                scanf("%s", timing);
                printf("Enter total seats: ");
                scanf("%d", &seats);
                printf("Enter train location: ");
                scanf("%s", location);
                addTrain(trainNo, route, timing, seats, location);
                break;
            case 2:
                displayTrains();
                break;
            case 3:
                printf("Enter passenger name: ");
                scanf("%s", name);
                printf("Enter train number: ");
                scanf("%d", &trainNo);
                printf("Enter seats to book: ");
                scanf("%d", &seats);
                bookTicket(name, trainNo, seats);
                break;
            case 4:
                printf("Enter ticket number to cancel: ");
                scanf("%d", &ticketNo);
                cancelTicket(ticketNo);
                break;
            case 5:
                displayPassengers();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                saveToFile(); // auto-save before exit
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
