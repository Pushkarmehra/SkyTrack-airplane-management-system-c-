#include <iostream>
#include <stdlib.h>
#include <string.h>
#define FILENAME "flights.dat"
using namespace std;
struct Flight {
    char flightNumber[10];
    char departureCity[30];
    char destinationCity[30];
    char departureDateTime[20];
    char arrivalDateTime[20];
    int firstClassAvailable;
    int firstClassSold;
    int coachAvailable;
    int coachSold;
} ;
void createFlightRecord();
void deleteFlightRecord(const char *flightNumber);
void updateFlightRecord(const char *flightNumber);
void makeReservation(const char *flightNumber, const char *seatClass, int seats);
void cancelReservation(const char *flightNumber, const char *seatClass, int seats);
void displayFlights();
int main() {
    int choice;
    char flightNumber[10], seatClass[10];
    int seats;
    
    do {
        cout<<"\n--- Airline Reservation System ---"<<endl;
        cout<<"1. Create Flight Record"<<endl;
        cout<<"2. Delete Flight Record"<<endl;
        cout<<"3. Update Flight Record"<<endl;
        cout<<"4. Make Reservation"<<endl;
        cout<<"5. Cancel Reservation"<<endl;
        cout<<"6. Display Flights"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
 
        switch (choice) {
            case 1:
                createFlightRecord();
                break;
            case 2:
                cout<<"Enter Flight Number to Delete: ";
                cin>>flightNumber;
                deleteFlightRecord(flightNumber);
                break;
            case 3:
                cout<<"Enter Flight Number to Update: ";
                cin>>flightNumber;
                updateFlightRecord(flightNumber);
                break;
            case 4:
                cout<<"Enter Flight Number: ";
                cin>>flightNumber;
                cout<<"Enter Seat Class (First/Coach): ";
                cin>>seatClass;
                cout<<"Enter Number of Seats: ";
                cin>>seats;
                makeReservation(flightNumber, seatClass, seats);
                break;
            case 5:
                cout<<"Enter Flight Number: ";
                cin>>flightNumber;
                cout<<"Enter Seat Class (First/Coach): ";
                cin>>seatClass;
                cout<<"Enter Number of Seats: ";
                cin>>seats;
                cancelReservation(flightNumber, seatClass, seats);
                break;
            case 6:
                displayFlights();
                break;
            case 0:
                cout<<"Exiting...\n";
                break;
            default:
                cout<<"Invalid choice! Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}
void createFlightRecord() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        perror("Error opening file");
        return;
    }

    struct Flight flight;
    cout<<"Enter Flight Number: ";
    cin>>flight.flightNumber;
    cout<<"Enter Departure City: ";
    cin>>flight.departureCity;
    cout<<"Enter Destination City: ";
    cin>>flight.destinationCity;
    cout<<"Enter Departure Date and Time: ";
    cin>>flight.departureDateTime;
    cout<<"Enter Arrival Date and Time: ";
    cin>>flight.arrivalDateTime;
    cout<<"Enter First Class Seats Available: ";
    cin>>flight.firstClassAvailable;
    flight.firstClassSold = 0;
    cout<<"Enter Coach Seats Available: ";
    cin>>flight.coachAvailable;
    flight.coachSold = 0;
    fwrite(&flight, sizeof(Flight), 1, file);
    fclose(file);
    cout<<"Flight record created successfully."<<endl;
}
void deleteFlightRecord(const char *flightNumber) {
    FILE *file = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!file || !temp) {
        perror("Error opening file");
        return;
    }

    Flight flight;
    int found = 0;
    while (fread(&flight, sizeof(Flight), 1, file)) {
        if (strcmp(flight.flightNumber, flightNumber) != 0) {
            fwrite(&flight, sizeof(Flight), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found)
        cout<<"Flight record deleted successfully."<<endl;
    else
        cout<<"Flight record not found."<<endl;
}

void updateFlightRecord(const char *flightNumber) {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Flight flight;
    int found = 0;
    while (fread(&flight, sizeof(Flight), 1, file)) {
        if (strcmp(flight.flightNumber, flightNumber) == 0) {
            found = 1;
            cout<<"Enter New Departure City: ";
            cin>> flight.departureCity;
            cout<<"Enter New Destination City: ";
            cin>> flight.destinationCity;
            cout<<"Enter New Departure Date and Time: ";
            cin>> flight.departureDateTime;
            cout<<"Enter New Arrival Date and Time: ";
            cin>> flight.arrivalDateTime;
            cout<<"Enter New First Class Seats Available: ";
            cin>>flight.firstClassAvailable;
            cout<<"Enter New Coach Seats Available: ";
            cin>>flight.coachAvailable;

            fseek(file, -sizeof(Flight), SEEK_CUR);
            fwrite(&flight, sizeof(Flight), 1, file);
            break;
        }
    }

    fclose(file);

    if (found)
        cout<<"Flight record updated successfully."<<endl;
    else
        cout<<"Flight record not found."<<endl;
}
void makeReservation(const char *flightNumber, const char *seatClass, int seats) {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Flight flight;
    int found = 0;
    while (fread(&flight, sizeof(Flight), 1, file)) {
        if (strcmp(flight.flightNumber, flightNumber) == 0) {
            found = 1;
            if (strcmp(seatClass, "First") == 0) {
                if (seats <= flight.firstClassAvailable) {
                    flight.firstClassAvailable -= seats;
                    flight.firstClassSold += seats;
                    fseek(file, -sizeof(Flight), SEEK_CUR);
                    fwrite(&flight, sizeof(Flight), 1, file);
                    cout<<"Reservation successful."<<endl;
                } else {
                    cout<<"Not enough First Class seats available."<<endl;
                }
            } else if (strcmp(seatClass, "Coach") == 0) {
                if (seats <= flight.coachAvailable) {
                    flight.coachAvailable -= seats;
                    flight.coachSold += seats;
                    fseek(file, -sizeof(Flight), SEEK_CUR);
                    fwrite(&flight, sizeof(Flight), 1, file);
                    cout<<"Reservation successful."<<endl;
                } else {
                    cout<<"Not enough Coach seats available."<<endl;
                }
            } else {
                cout<<"Invalid seat class."<<endl;
            }
            break;
        }
    }

    fclose(file);

    if (!found)
        cout<<"Flight record not found."<<endl;
}
void cancelReservation(const char *flightNumber, const char *seatClass, int seats) {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Flight flight;
    int found = 0;
    while (fread(&flight, sizeof(Flight), 1, file)) {
        if (strcmp(flight.flightNumber, flightNumber) == 0) {
            found = 1;
            if (strcmp(seatClass, "First") == 0) {
                if (seats <= flight.firstClassSold && flight.firstClassSold > 0) {
                    flight.firstClassAvailable += seats;
                    flight.firstClassSold -= seats;
                    fseek(file, -sizeof(Flight), SEEK_CUR);
                    fwrite(&flight, sizeof(Flight), 1, file);
                    cout<<"Cancellation successful."<<endl;
                } else {
                    cout<<"Not enough First Class reservations to cancel."<<endl;
                }
            } else if (strcmp(seatClass, "Coach") == 0) {
                if (seats <= flight.coachSold) {
                    flight.coachAvailable += seats;
                    flight.coachSold -= seats;
                    fseek(file, -sizeof(Flight), SEEK_CUR);
                    fwrite(&flight, sizeof(Flight), 1, file);
                    cout<<"Cancellation successful."<<endl;
                } else {
                    cout<<"Not enough Coach reservations to cancel."<<endl;
                }
            } else {
                cout<<"Invalid seat class."<<endl;
            }
            break;
        }
    }

    fclose(file);

    if (!found)
        cout<<"Flight record not found."<<endl;
}




void displayFlights() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Flight flight;
    cout<<"\n--- Flight Records ---"<<endl;
    while (fread(&flight, sizeof(Flight), 1, file)) {
        cout<<"\nFlight Number:"<<flight.flightNumber<<endl;
        cout<<"Departure City: "<<flight.departureCity<<endl;
        cout<<"Destination City: "<<flight.destinationCity<<endl;
        cout<<"Departure Date and Time: "<<flight.departureDateTime<<endl;
        cout<<"Arrival Date and Time: "<<flight.arrivalDateTime<<endl;
        cout<<"First Class Seats Available: "<<flight.firstClassAvailable<<"Sold: "<<flight.firstClassSold<<endl;
        cout<<"Coach Seats Available: "<<flight.coachAvailable<< "Sold:"<<flight.coachSold<<endl;
    }

    fclose(file);
}
