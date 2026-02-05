#include <iostream>
#include <set>
#include <cstdlib>
using namespace std;

class ParkingTicket {
private:
    int ticketNumber;
    int parkingSpotNumber;
public:
    ParkingTicket(int ticketNumber, int parkingSpotNumber) : ticketNumber(ticketNumber), parkingSpotNumber(parkingSpotNumber) {}   

    int getTicketNumber() const {
        return ticketNumber;
    }

    int getParkingSpotNumber() const {
        return parkingSpotNumber;
    }
};

class ParkingLot {
private:
    int totalSpots;
    set<int> availableSpots;
public:
    ParkingLot(int totalSpots) : totalSpots(totalSpots) {
        for(int i=1;i<=totalSpots;i++){
            availableSpots.insert(i);
        }
    }

    bool hasAvailableSpots() const {
        return !availableSpots.empty();
    }

    int allocateSpot() {
        int spotNumber = *availableSpots.begin();
        availableSpots.erase(spotNumber);
        return spotNumber;
    }

    bool isSpotOccupied(ParkingTicket* ticket) const {
        return availableSpots.find(ticket->getParkingSpotNumber()) == availableSpots.end();
    }

    void freeSpot(int spotNumber) {
        availableSpots.insert(spotNumber);
    }
};

class ParkingManager {
private: 
    ParkingLot* parkingLot;
public:
    ParkingManager(ParkingLot* parkingLot) : parkingLot(parkingLot) {}
    ParkingManager(int totalSpots) {
        parkingLot = new ParkingLot(totalSpots);
    }

    ParkingTicket* park(){
        if(parkingLot->hasAvailableSpots() == false){
            return nullptr; 
        }
        int spotNumber = parkingLot->allocateSpot();
        return new ParkingTicket(rand(), spotNumber);
    }

    bool unpark(ParkingTicket* ticket){
        if(ticket == nullptr) return false;

        if(parkingLot->isSpotOccupied(ticket) == false){
            return false; 
        }
        parkingLot->freeSpot(ticket->getParkingSpotNumber());
        return true;    
    }
};

int main() {

    ParkingManager* parkingManager = new ParkingManager(10);
    ParkingTicket* t1 = parkingManager->park();
    if(t1 == nullptr){
        cout<<"Parking lot is full. Cannot park the car."<<endl;    
    } else {
        cout<<"Vehicle parked successfully. Ticket number: "<<t1->getTicketNumber()<<", Parking spot number: "<<t1->getParkingSpotNumber()<<endl;
    }

    ParkingTicket* t2 = parkingManager->park();
    if(t2 == nullptr){
        cout<<"Parking lot is full. Cannot park the car."<<endl;    
    } else {
        cout<<"Vehicle parked successfully. Ticket number: "<<t2->getTicketNumber()<<", Parking spot number: "<<t2->getParkingSpotNumber()<<endl;
    }

    ParkingTicket* t3 = parkingManager->park();
    if(t3 == nullptr){
        cout<<"Parking lot is full. Cannot park the car."<<endl;    
    } else {
        cout<<"Vehicle parked successfully. Ticket number: "<<t3->getTicketNumber()<<", Parking spot number: "<<t3->getParkingSpotNumber()<<endl;
    }

    bool status = parkingManager->unpark(t1);
    if(status){
        cout<<"Vehicle unparked successfully."<<endl;
    } else {
        cout<<"Invalid ticket. Cannot unpark the car."<<endl;
    }
    
    status = parkingManager->unpark(t1);
    if(status){
        cout<<"Vehicle unparked successfully."<<endl;
    } else {
        cout<<"Invalid ticket. Cannot unpark the car."<<endl;
    }

    return 0;
}