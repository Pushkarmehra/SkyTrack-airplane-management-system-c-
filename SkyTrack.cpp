#include <iostream>
#include <stdlib.h>
#include <string.h>
#define FILENAME "flights.dat"
using namespace std;
struct{
char flightNumber[10];
    char departureCity[30];
    char destinationCity[30];
    char departureDateTime[20];
    char arrivalDateTime[20];
    int firstClassAvailable;
    int firstClassSold;
    int coachAvailable;
    int coachSold;
} Flight;
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
