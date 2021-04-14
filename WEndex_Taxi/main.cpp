#include <iostream>
#include <vector>
#include <sql.h>

using namespace std;

class Passenger{
    string name;
    string password;
    int rating;
    string address;
    string paymentMethods;
    vector<string> history;

    Passenger(string name, string address, string paymentMethods, string password, vector<string> history){
        this->name = name;
        this->address = address;
        this->paymentMethods = paymentMethods;
        this->rating = 0;
        this->history = history;
    }
};

class PassengerGateway{
    Passenger passenger;
    void logIn(string name,string password){
        // This method reads data base and looking for
        // user with given name and password if found
        // creates new object passenger with data of given passenger
        passenger = new Passenger();
    }

    void getHistory(){
        // This method reads History for authorized
        // user from data base and print it

    }

    void getPaymentMethods(){
        // This method reads Payment Methods for authorized
        // user from data base and print it

    }

    void setPaymentMethods(){
        // This method gets access to Payment Methods for authorized
        // user from data base and updates it
    }

    void getPinnedAddress(){
        // This method reads Pinned Address for authorized
        // user from data base and print it

    }

    void setPinnedAddress(){
        // This method gets access to Pinned Address for authorized
        // user from data base and updates it
    }

    void orderTaxi(){
        // This method processes all actions with ride ordering
        //
        string payment;
        int code;
        int price;
        string carType;
        cout << "Write address from where"<< endl;
        string from;
        cin >> from;
        cout << "Write address to where"<< endl;
        string to;
        cin >> to;
        cout << endl << "Chose car type:" << endl << endl << "[1] Economy" << endl << "[2] Comfort" << endl
        << "[3] ComfortPlus" << endl << "[4] Business" << endl;
        cin >> code;
        switch (code) {
            case 1: carType = "Economy";
                price = 150;
                break;
            case 2: carType = "Comfort";
                price = 300;
                break;
            case 3: carType = "ComfortPlus";
                price = 500;
                break;
            case 4: carType = "Business";
                price = 1000;
                break;
            default:
                cout << "No such option" << endl;
                break;
        }

        cout << "Ride Info:" <<endl <<endl;
        cout << "Ride Departure: " << from << endl;
        cout << "Ride Destination: " << to << endl;
        cout << "Car  Type: " << carType << endl;
        cout << "Ride Price: " << price << endl;

        cout << endl <<"Accept order ?" << endl << endl << "[1] Yes" << endl << "[2] No" << endl << "[3] Change Payment Method" << endl;
        cin >> code;

        switch (code) {
            case 1:
                break;
            case 2:
                cout << "Order has been rejected!" << endl;
                    return;
                break;
            case 3:
                cout << "Enter payment method" << endl;
                cin >> payment;
                break;
            default:
                cout << "No such option" << endl;
                break;
        }
    }

    void getCoordinates(){

    }
};

class DriverGateway{

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
