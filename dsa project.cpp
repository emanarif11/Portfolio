#include <iostream>
#include <string>
using namespace std;

struct WaitingList {
    string names[10];
    int front = 0, rear = -1;

    bool isFull() { return rear == 9; }
    bool isEmpty() { return rear < front; }

    void enqueue(string name) {
        if (isFull()) {
            cout << "Waiting List Full!\n";
            return;
        }
        names[++rear] = name;
        cout << "Passenger added to waiting list.\n";
    }

    void display() {
        if (isEmpty()) {
            cout << "Waiting list is empty.\n";
            return;
        }
        cout << "\n--- Waiting List ---\n";
        for (int i = front; i <= rear; i++)
            cout << names[i] << endl;
    }
};



struct Flight {
    string flightID;
    string fromCountry;
    string toCountry;
    string departureTime;
    string arrivalTime;
    char seats[5][4];
    WaitingList waitlist;
};



struct Node {
    Flight data;
    Node* next;
};

Node* head = NULL;


void initializeSeats(char seats[5][4]) {
    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 4; j++) {
            seats[i][j] = 'O';
        }
    }
}



void addFlight() {
    Node* newNode = new Node();

    cout << "\nEnter Flight ID: ";
    cin >> newNode->data.flightID;

    cout << "From Country: ";
    cin >> newNode->data.fromCountry;

    cout << "To Country: ";
    cin >> newNode->data.toCountry;

    cout << "Departure Time: ";
    cin >> newNode->data.departureTime;

    cout << "Arrival Time: ";
    cin >> newNode->data.arrivalTime;

    initializeSeats(newNode->data.seats);

    newNode->next = head;
    head = newNode;

    cout << "\nFlight added successfully!\n";
}



void deleteFlight() {
    if (!head) {
        cout << "No flights available!\n";
        return;
    }

    string id;
    cout << "\nEnter Flight ID to delete: ";
    cin >> id;

    if (head->data.flightID == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Flight deleted.\n";
        return;
    }

    Node* prev = head;
    Node* curr = head->next;

    while (curr && curr->data.flightID != id) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << "Flight not found!\n";
        return;
    }

    prev->next = curr->next;
    delete curr;
    cout << "Flight deleted.\n";
}


void displayFlights() {
    if (!head) {
        cout << "No flights available!\n";
        return;
    }

    Node* temp = head;
    while (temp) {
        cout << "\nFlight ID: " << temp->data.flightID;
        cout << "\nFrom: " << temp->data.fromCountry;
        cout << "\nTo: " << temp->data.toCountry;
        cout << "\nDeparture: " << temp->data.departureTime;
        cout << "\nArrival: " << temp->data.arrivalTime << "\n";
        temp = temp->next;
    }
}



void searchFlight() {
    string id;
    cout << "\nEnter Flight ID: ";
    cin >> id;

    Node* temp = head;

    while (temp) {
        if (temp->data.flightID == id) {
            cout << "\n--- FLIGHT FOUND ---\n";
            cout << "Flight ID: " << temp->data.flightID << endl;
            cout << "From: " << temp->data.fromCountry << endl;
            cout << "To: " << temp->data.toCountry << endl;
            cout << "Departure: " << temp->data.departureTime << endl;
            cout << "Arrival: " << temp->data.arrivalTime << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Flight not found.\n";
}



void showSeats(Node* flight) {
    cout << "\nSeat Layout (O = free, X = booked)\n\n";
    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 4; j++) {
            cout << flight->data.seats[i][j] << " ";
        }
        cout << endl;
    }
}


void bookSeat() {
    string id, name;
    cout << "\nEnter Flight ID: ";
    cin >> id;

    Node* temp = head;
    while (temp && temp->data.flightID != id)
        temp = temp->next;

    if (!temp) {
        cout << "Flight not found!\n";
        return;
    }

    showSeats(temp);

    int row, col;
    cout << "\nEnter row (1-4): ";
    cin >> row;
    cout << "Enter column (1-3): ";
    cin >> col;

    if (cin.fail()) {
        cout << "Invalid input! Booking cancelled.\n";
        cin.clear();
        return;
    }

    if (row < 1 || row > 3 || col < 1 || col > 2) {
        cout << "Invalid seat selection!\n";
        return;
    }

    cout << "Enter passenger name: ";
    cin >> name;

    if (temp->data.seats[row][col] == 'O') {
        temp->data.seats[row][col] = 'X';
        cout << "Seat booked successfully.\n";
    } else {
        cout << "Seat already booked! Passenger added to waiting list.\n";
        temp->data.waitlist.enqueue(name);
    }
}


void addPassengerToWaitingList() {
    string id, name;

    cout << "\nEnter Flight ID: ";
    cin >> id;

    Node* temp = head;

    while (temp && temp->data.flightID != id)
        temp = temp->next;

    if (!temp) {
        cout << "Flight not found!\n";
        return;
    }

    cout << "Enter passenger name: ";
    cin >> name;

    temp->data.waitlist.enqueue(name);
}


void showWaitingList() {
    string id;
    cout << "\nEnter Flight ID: ";
    cin >> id;

    Node* temp = head;
    while (temp && temp->data.flightID != id)
        temp = temp->next;

    if (!temp) {
        cout << "Flight not found!\n";
        return;
    }

    temp->data.waitlist.display();
}


int main() {
    int choice;

    while (true) {
        cout << "\n===== Flight Management System =====";
        cout << "\n1. Add Flight";
        cout << "\n2. Display Flights";
        cout << "\n3. Search Flight";
        cout << "\n4. Book Seat";
        cout << "\n5. Show Waiting List";
        cout << "\n6. Add Passenger to Waiting List";
        cout << "\n7. Delete Flight";
        cout << "\n8. Exit";

        cout << "\n\nEnter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input! Program exiting.\n";
            break;
        }

        switch (choice) {
            case 1: addFlight(); break;
            case 2: displayFlights(); break;
            case 3: searchFlight(); break;
            case 4: bookSeat(); break;
            case 5: showWaitingList(); break;
            case 6: addPassengerToWaitingList(); break;
            case 7: deleteFlight(); break;
            case 8: return 0;
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}

