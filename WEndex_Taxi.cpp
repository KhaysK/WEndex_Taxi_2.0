#include <iostream>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>
#include <string>  
#include <cmath> 
#include <thread> 
#include <chrono>

using namespace std;
int getHistory(void* NotUsed, int argc, char** argv, char** azColName);
int getCar(void* NotUsed, int argc, char** argv, char** azColName);
int getUser(void* NotUsed, int resultNum, char** values, char** colNames);
int getCoordinates(void* NotUsed, int resultNum, char** values, char** colNames);
int getDriver(void* NotUsed, int resultNum, char** values, char** colNames);
int selectData(const char* dir, string query, int code);
int updateData(const char* dir, string query);


class Ride {
public:
    string departure;
    string destination;
    string carType;
    string payment;
    int price;
    int time;
    int id;

    Ride(string departure, string destination, string carType, string payment, int price, int time, int id) {
        this->departure = departure;
        this->destination = destination;
        this->carType = carType;
        this->price = price;
        this->payment = payment;
        this->time = time;
        this->id = id;
    }
    Ride() {
    }
};

class Passenger {
public:
    int id;
    string name;
    string password;
    int rating;
    string address;
    string payment1;
    string payment2;
    vector<Ride> history;

    Passenger(string name, string address, string payment1, string payment2, string password, vector<Ride> history) {
        this->name = name;
        this->address = address;
        this->payment1 = payment1;
        this->payment2 = payment2;
        this->rating = 0;
        this->history = history;
        this->password = password;
    }
    Passenger(string name, string address, string payment1, string payment2, string password, vector<Ride> history, int rating, int id) {
        this->name = name;
        this->address = address;
        this->payment1 = payment1;
        this->payment2 = payment2;
        this->rating = rating;
        this->history = history;
        this->id = id;
        this->password = password;
    }
    Passenger() {

    }
};

class Car {
public:
    string model;
    string color;
    string carType;
    string number;
    string status;
    int latitude;
    int longitude;

    Car(string model, string color, string carType, string number, string status, int latitude, int longitude) {
        this->model = model;
        this->color = color;
        this->carType = carType;
        this->number = number;
        this->status = status;
        this->latitude = latitude;
        this->longitude = longitude;
    }
    Car() {}
};
class ComfortCar : public Car {
public:
    int freeBottleOfwater = 10;
    ComfortCar(string model, string color, string carType, string number, string status, int latitude, int longitude) :
        Car(model, color, carType, number, status, latitude, longitude)
    {

    }
    ComfortCar() {

    }
    void usageBottleOfwater() {
        freeBottleOfwater -= rand() % 4;
    }
};

class BussnessCar :public Car {
public:
    BussnessCar(string model, string color, string carType, string number, string status, int latitude, int longitude) :
        Car(model, color, carType, number, status, latitude, longitude)
    {

    }
    BussnessCar() {

    }
    void parkRightInFrontOfTheEntrance() {
        cout << endl;
        cout << "Car infront of the entrance" << endl;
        cout << endl;
    }
};

class Driver {
public:
    int id;
    int rating;
    string name;
    string password;
    vector<Ride> history;
    Car car;
    ComfortCar comfortCar;
    BussnessCar bussnesCar;
    string status;
    
    Driver(int id, int rating, string name, string password, vector<Ride> history, Car car, string status){
        this->id = id;
        this->rating = rating;
        this->name = name;
        this->password = password;
        this->history = history;
        this->car = car;
        this->status = status;
        this->bussnesCar = BussnessCar();
        this->comfortCar = ComfortCar();
    }

    Driver(){}
};



Passenger tmpPassenger;
Driver tmpDriver;
Car tmpCar;
Ride tmpOrder;
int tmpDepartureX;
int tmpDepartureY;
int tmpDestinationX;
int tmpDestinationY;
vector<Ride> tmpHistory;
vector<Ride> tmpOrders;
string tmpStatusOfLast;
bool isTaxiOrdered;
ComfortCar tmpComfortCar;
BussnessCar tmpBussnesCar;
int idOfDriver;

class PassengerGateway {
    Ride ride;
    int departureX;
    int departureY;
    int destinationX;
    int destinationY;
    int lastX;
    int lastY;

public:
    Passenger passenger;
    PassengerGateway() {
    }

    void logIn(string name, string password) {
        // This method reads data base and looking for
        // user with given name and password if found
        // fills variable passenger with data of given passenger

        string sql_query = "SELECT * FROM passenger WHERE name = '" + name + "' AND password = '" + password + "';";
        selectData("WEndex_Taxi_BD.db", sql_query,1);
        passenger = tmpPassenger;
        if (passenger.name != "") {
            cout << endl << "Authorization was successful" << endl;
            cout << "Hello, " + passenger.name << endl;
        }
        else cout << endl << "Wrong name or password" << endl;
        cout << "History of orders" << endl;
        getHistory();
    }

    void logInStory() {
        // This method reads data base and looking for
        // user with given name and password if found
        // fills variable passenger with data of given passenger
        string name = "Khabib Khays";
        string password = "remag";
        cout << endl << "-----------Passenger " << name << " logging in to the system-----------" << endl;

        string sql_query = "SELECT * FROM passenger WHERE name = '" + name + "' AND password = '" + password + "';";
        selectData("WEndex_Taxi_BD.db", sql_query, 1);
        passenger = tmpPassenger;
        if (passenger.name != "") {
            cout << endl << "Authorization was successful" << endl;
            cout << "Hello, " + passenger.name << endl;
        }
        else cout << endl << "Wrong name or password" << endl;
    }

    void getHistory() {
        // This method reads History for authorized
        // user from data base and save it
        tmpHistory = vector<Ride>();
        string sql_query = "SELECT * FROM orders WHERE passenger_id = " + to_string(passenger.id) + " AND status = 'done';";
        selectData("WEndex_Taxi_BD.db", sql_query, 3);
        passenger.history = tmpHistory;
        tmpHistory = vector<Ride>(); 

        cout << endl << endl;
        for (int i = 0; i < passenger.history.size(); i++)
        {
            cout << i + 1 << " | " << passenger.history[i].departure << " | " << passenger.history[i].destination << " | " <<
                passenger.history[i].carType << " | " << passenger.history[i].price << "rub | " << passenger.history[i].payment <<
                " | " << passenger.history[i].time << "sec" << endl;

        }
    }

    void getHistoryStory() {
        // This method reads History for authorized
        // user from data base and save it
        tmpHistory = vector<Ride>();
        cout << endl << "-----------Passenger " << passenger.name << " asking for history-----------" << endl;
        string sql_query = "SELECT * FROM orders WHERE passenger_id = " + to_string(passenger.id) + " AND status = 'done';";
        selectData("WEndex_Taxi_BD.db", sql_query, 3);
        passenger.history = tmpHistory;
        tmpHistory = vector<Ride>();

        cout << endl << endl;
        for (int i = 0; i < passenger.history.size(); i++)
        {
            cout << i + 1 << " | " << passenger.history[i].departure << " | " << passenger.history[i].destination << " | " <<
                passenger.history[i].carType << " | " << passenger.history[i].price << "rub | " << passenger.history[i].payment <<
                " | " << passenger.history[i].time << "sec" << endl;

        }
    }

    string getPayment1() {
        // This method returns First Payment Methods for authorized user
        return passenger.payment1;
    }

    void getPaymentStory() {
        cout << endl << "-----------Passenger " << passenger.name << " asking for payment methods-----------" << endl;
        // This method returns First Payment Methods for authorized user
        cout << endl <<"First payment method: " << passenger.payment1 << endl;
        cout << endl <<"Second payment method: " << passenger.payment2 << endl;
    }

    string getPayment2() {
        // This method returns Second Payment Methods for authorized user
        return passenger.payment2;
    }

    void setPayment1(string newPayment) {
        // This method gets access to Payment Methods for authorized
        // user from data base and updates it
        string sql_query = "UPDATE passenger SET payment1 = '" + newPayment + "' WHERE name = '" + 
            passenger.name + "' AND password = '" + passenger.password + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
        passenger.payment1 = newPayment;
    }
    void setPayment1Story () {
        // This method gets access to Payment Methods for authorized
        // user from data base and updates it
        string newPayment = "2458 2332 5612 7328";
        cout << endl << "-----------Passenger " << passenger.name << " changing firts payment methods to 2458 2332 5612 7328-----------" << endl;

        string sql_query = "UPDATE passenger SET payment1 = '" + newPayment + "' WHERE name = '" +
            passenger.name + "' AND password = '" + passenger.password + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
        passenger.payment1 = newPayment;

        cout << "First payment method was changed to " << newPayment << endl;
    }

    void setPayment2(string newPayment) {
        // This method gets access to Payment Methods for authorized
        // user from data base and updates it
        string sql_query = "UPDATE passenger SET payment2 = '" + newPayment + "' WHERE name = '" +
            passenger.name + "' AND password = '" + passenger.password + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
        passenger.payment2 = newPayment;
    }

    string getPinnedAddress() {
        // This method returns Pinned Address for authorized user
        return passenger.address;
    }

    void getPinnedAddressStory() {
        cout << endl << "-----------Passenger " << passenger.name << " asking for pinned address-----------" << endl;

        // This method returns Pinned Address for authorized user
        cout << endl << "Pinned address: " << passenger.address << endl;
    }

    void setPinnedAddress(string newAddress) {
        // This method gets access to Pinned Address for authorized
        // user from data base and updates it

        string sql_query = "UPDATE passenger SET address = '" + newAddress + "' WHERE name = '" +
            passenger.name + "' AND password = '" + passenger.password + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
        passenger.address = newAddress;
    }

    void setPinnedAddressStory() {
        // This method gets access to Pinned Address for authorized
        // user from data base and updates it
        cout << endl << "-----------Passenger " << passenger.name << " changing pinned address to Pribreznaya 2-----------" << endl;

        string newAddress = "Pribreznaya 2"; 
        string sql_query = "UPDATE passenger SET address = '" + newAddress + "' WHERE name = '" +
            passenger.name + "' AND password = '" + passenger.password + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
        passenger.address = newAddress;

        cout << "Pinned address was changed to " << newAddress << endl;
    }

    int countTime(string departure, string destination) {
        //This method calculete approximate time of the ride it take
        // coordinates of departure and destination find distance and divide it by average speed

        string sql_query = "SELECT * FROM map WHERE street = '" + departure + "' OR street = '" + destination + "';";
        selectData("WEndex_Taxi_BD.db", sql_query, 2);

        departureX = tmpDepartureX;
        departureY = tmpDepartureY;
        destinationX = tmpDestinationX;
        destinationY = tmpDestinationY;

        tmpDepartureX = 0;
        tmpDepartureY = 0;
        tmpDestinationX = 0;
        tmpDestinationY = 0;

        return sqrt(pow(departureX - destinationX, 2) + pow(departureY - destinationY, 2)) / 40; 
        // approximate time, I take length of road and divide by overage speed 40 km/h
    }

    void getCoordinates() {
        // This method gets start street and finish street take their coordinates
        // and generate new coordinates in this 
        string destination = ride.destination;
        string departure = ride.departure;

        string sql_query = "SELECT * FROM orders WHERE destination = '" + destination + "' AND passenger_id = " +
            to_string(passenger.id) + " AND  departure = '" + departure  + "' AND driver_id = " + to_string(idOfDriver) + " ;";
        selectData("WEndex_Taxi_BD.db", sql_query, 3);

        if (tmpStatusOfLast == "work") {
            string sql_query = "SELECT * FROM map WHERE street = '" + departure + "' OR street = '" + destination + "';";
            selectData("WEndex_Taxi_BD.db", sql_query, 2);

            int newX;
            int newY;
            if (lastX != 0 && lastY != 0)
            {
                if (tmpDepartureX > lastX) {
                    int maxX = tmpDepartureX - tmpDestinationX;
                    int maxY = tmpDepartureY - tmpDestinationY;

                    newX = tmpDepartureX + (rand() % maxX) + 1;
                    newY = tmpDepartureY + (rand() % maxY) + 1;
                }
                else {
                    int maxX = lastX - tmpDepartureX;
                    int maxY = lastY - tmpDepartureY;

                    newX = tmpDepartureX - (rand() % maxX) + 1;
                    newY = tmpDepartureY - (rand() % maxY) + 1;
                }
            }
            else
            {
                if (tmpDepartureX > tmpDestinationX) {
                    int maxX = tmpDepartureX - tmpDestinationX;
                    int maxY = tmpDepartureY - tmpDestinationY;

                    newX = tmpDepartureX + (rand() % maxX) + 1;
                    newY = tmpDepartureY + (rand() % maxY) + 1;
                }
                else {
                    int maxX = tmpDestinationX - tmpDepartureX;
                    int maxY = tmpDestinationY - tmpDepartureY;

                    newX = tmpDepartureX - (rand() % maxX) + 1;
                    newY = tmpDepartureY - (rand() % maxY) + 1;
                }
            }
            sql_query = "UPDATE cars SET latitude = " + to_string(newX) + " WHERE carType = '"
                + ride.carType + "' AND departure ='" + ride.departure + "' AND status = 'busy' ;";
            updateData("WEndex_Taxi_BD.db", sql_query);
            sql_query = "UPDATE cars SET longitude = " + to_string(newY) + " WHERE carType = '"
                + ride.carType + "' AND departure ='" + ride.departure + "' AND status = 'busy' ;";
            updateData("WEndex_Taxi_BD.db", sql_query);

            cout << endl;
            cout << "Car coordinates:" << endl << endl;
            cout << "Latitude (X coordinate): 55." << newX << endl;
            cout << "Longitude (Y coordinate): 48." << newY << endl;
            cout << endl;
        }
        else if ("new") cout << "Still has no driver" << endl;
        else if ("done") cout << "Ride has been finished" << endl;
    }

    void getCoordinatesStory() {
        // This method gets start street and finish street take their coordinates
        // and generate new coordinates in this 

        cout << endl << "-----------Passenger " << passenger.name << " asking for coordinates of car-----------" << endl;
        string departure = "Universitetskaya 1/4";
        string destination = "Pribreznaya 2";
        lastX = 0; lastY = 0;

        string sql_query = "SELECT * FROM orders WHERE destination = '" + destination + "' AND passenger_id = " +
            to_string(passenger.id) + " AND  departure = '" + departure + "' AND driver_id = " + to_string(idOfDriver) + " ;";
        selectData("WEndex_Taxi_BD.db", sql_query, 3);

        if (tmpStatusOfLast == "work") {
            string sql_query = "SELECT * FROM map WHERE street = '" + departure + "' OR street = '" + destination + "';";
            selectData("WEndex_Taxi_BD.db", sql_query, 2);

            int newX;
            int newY;
            if (lastX != 0 && lastY != 0)
            {
                if (tmpDepartureX > lastX) {
                    int maxX = tmpDepartureX - tmpDestinationX;
                    int maxY = tmpDepartureY - tmpDestinationY;

                    newX = tmpDepartureX + (rand() % maxX) + 1;
                    newY = tmpDepartureY + (rand() % maxY) + 1;
                }
                else {
                    int maxX = lastX - tmpDepartureX;
                    int maxY = lastY - tmpDepartureY;

                    newX = tmpDepartureX - (rand() % maxX) + 1;
                    newY = tmpDepartureY - (rand() % maxY) + 1;
                }
            }
            else
            {
                if (tmpDepartureX > tmpDestinationX) {
                    int maxX = tmpDepartureX - tmpDestinationX;
                    int maxY = tmpDepartureY - tmpDestinationY;

                    newX = tmpDepartureX + (rand() % maxX) + 1;
                    newY = tmpDepartureY + (rand() % maxY) + 1;
                }
                else {
                    int maxX = tmpDestinationX - tmpDepartureX;
                    int maxY = tmpDestinationY - tmpDepartureY;

                    newX = tmpDepartureX - (rand() % maxX) + 1;
                    newY = tmpDepartureY - (rand() % maxY) + 1;
                }
            }
            sql_query = "UPDATE cars SET latitude = " + to_string(newX) + " WHERE carType = '"
                + ride.carType + "' AND status = 'busy' ;";
            updateData("WEndex_Taxi_BD.db", sql_query);
            sql_query = "UPDATE cars SET longitude = " + to_string(newY) + " WHERE carType = '"
                + ride.carType + "' AND status = 'busy' ;";
            updateData("WEndex_Taxi_BD.db", sql_query);

            cout << endl;
            cout << "Car coordinates:" << endl << endl;
            cout << "Latitude (X coordinate): 55." << newX << endl;
            cout << "Longitude (Y coordinate): 48." << newY << endl;
            cout << endl;
        }
        else if ("new") cout << "Still has no driver" << endl;
        else if ("done") cout << "Ride has been finished" << endl;
    }

    void getBill() {
        // This method prints bill of the last order in order history
        if (!passenger.history.empty()) {
            int last = passenger.history.size() - 1;

            cout << endl;
            cout << "Ride Bill:" << endl << endl;
            cout << "Ride Departure: " << passenger.history[last].departure << endl;
            cout << "Ride Destination: " << passenger.history[last].destination << endl;
            cout << "Car  Type: " << passenger.history[last].carType << endl;
            cout << "Ride Price: " << passenger.history[last].price << endl;
            cout << "Ride Payment: " << passenger.history[last].payment << endl;
            cout << "Ride Time: " << passenger.history[last].time << endl;
            cout << endl;
        }
        else cout << "No availiable history" << endl;
        
    }

    void getBillStory() {
        // This method prints bill of the last order in order history
        cout << endl << "-----------Passenger " << passenger.name << " asking for bill of last order-----------" << endl;

        if (!passenger.history.empty()) {
            int last = passenger.history.size() - 1;

            cout << endl;
            cout << "Ride Bill:" << endl << endl;
            cout << "Ride Departure: " << passenger.history[last].departure << endl;
            cout << "Ride Destination: " << passenger.history[last].destination << endl;
            cout << "Car  Type: " << passenger.history[last].carType << endl;
            cout << "Ride Price: " << passenger.history[last].price << endl;
            cout << "Ride Payment: " << passenger.history[last].payment << endl;
            cout << "Ride Time: " << passenger.history[last].time << endl;
            cout << endl;
        }
        else cout << "No availiable history" << endl;

    }



    void orderTaxi() {

        // This method processes all actions with ride ordering
        if (!isTaxiOrdered) {
            string payment;
            int code = 0;
            int price;
            string carType;
            string from;
            string to;
            int time;

            while (code == 0) {
                cout << "Do you wanna use pinned address: " << getPinnedAddress() << endl << endl;
                cout << "[1] Yes" << endl;
                cout << "[2] No" << endl;
                cin >> code;
                if (code == 1)
                    from = getPinnedAddress();
                else if (code == 2) {
                    cout << "Write address from where" << endl;
                    cin.ignore();
                    getline(cin, from);
                    code = -1;
                }
                else {
                    cout << "No such option!" << endl;
                    code = 0;
                }
            }

            cout << "Write address to where" << endl;
            if (code != -1)
                cin.ignore();
            getline(cin, to);

            code = 0;
            while (code == 0) {
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
                    code = 0;
                    break;
                }
            }

            code = 0;
            while (code == 0) {
                cout << endl << "What Payment Method you want to use:" << endl;
                cout << "[1] Paymet method 1: " << getPayment1() << endl;
                cout << "[2] Paymet method 2: " << getPayment2() << endl;
                cout << "[3] Enother method" << endl;

                cin >> code;

                switch (code) {
                case 1:
                    payment = getPayment1();
                    break;
                case 2:
                    payment = getPayment2();
                    break;
                case 3:
                    cout << "Enter payment method" << endl;
                    cin.ignore();
                    getline(cin, payment);
                    break;
                default:
                    cout << "No such option" << endl;
                    code = 0;
                    break;
                }
            }


            code = 0;
            while (code == 0) {

                time = countTime(from, to);

                cout << endl;
                cout << "Ride Info:" << endl << endl;
                cout << "Ride Departure: " << from << endl;
                cout << "Ride Destination: " << to << endl;
                cout << "Car  Type: " << carType << endl;
                cout << "Ride Price: " << price << endl;
                cout << "Ride Payment: " << payment << endl;
                cout << "Ride Time: " << time << endl;

                string sql_query = "INSERT INTO orders(passenger_id, departure, destination, carType, payment, status, price, time) VALUES("
                    + to_string(passenger.id) + ", '" + from + "' , '" + to + "' , '" + carType + "' , '" + payment + "' , 'new' ," + to_string(price) + ", " + to_string(time) + ");";

                cout << endl << "Accept order ?" << endl << endl << "[1] Yes" <<
                    endl << "[2] No" << endl << "[3] Change Payment Method" << endl;
                cin >> code;


                switch (code) {
                case 1:
                    updateData("WEndex_Taxi_BD.db", sql_query);
                    cout << "Order has been ordered!" << endl;
                    ride = Ride(from, to, carType, payment, price, time, passenger.id);
                    isTaxiOrdered = true;
                    break;
                case 2:
                    cout << "Order has been rejected!" << endl;
                    return;
                    break;
                case 3:
                    cout << "Enter payment method" << endl;
                    cin.ignore();
                    getline(cin, payment);
                    code = 0;
                    break;
                default:
                    cout << "No such option" << endl;
                    code = 0;
                    break;
                }
            }
        }else
        cout << " You can not order 2 taxi at the same time" << endl;
    }

    void orderTaxiStory() {

        cout << endl << "-----------Passenger " << passenger.name << " order taxi-----------" << endl;

        // This method processes all actions with ride ordering
        if (!isTaxiOrdered) {
            string payment;
            int code = 0;
            int price ;
            string carType;
            string from;
            string to;
            int time;

                cout << "Do you wanna use pinned address: " << getPinnedAddress() << endl << endl;
                cout << "[1] Yes" << endl;
                cout << "[2] No" << endl;
                cout << endl;
                cout << "2" << endl;
                cout << "Write address from where" << endl;
                from = "Universitetskaya 1/4";
                cout << endl << from << endl;

            cout << "Write address to where" << endl;
            to = "Pribreznaya 2";
            cout << endl << to << endl;

            cout << endl << "Chose car type:" << endl << endl << "[1] Economy" << endl << "[2] Comfort" << endl
                << "[3] ComfortPlus" << endl << "[4] Business" << endl;

            carType = "Business";
            cout << endl << "4" << endl;
            price = 1000;

            cout << endl << "What Payment Method you want to use:" << endl;
            cout << "[1] Paymet method 1: " << getPayment1() << endl;
            cout << "[2] Paymet method 2: " << getPayment2() << endl;
            cout << "[3] Enother method" << endl;

            cout << endl << "1" << endl;
            payment = getPayment1();

            time = countTime(from, to);

            cout << endl;
            cout << "Ride Info:" << endl << endl;
            cout << "Ride Departure: " << from << endl;
            cout << "Ride Destination: " << to << endl;
            cout << "Car  Type: " << carType << endl;
            cout << "Ride Price: " << price << endl;
            cout << "Ride Payment: " << payment << endl;
            cout << "Ride Time: " << time << endl;

            string sql_query = "INSERT INTO orders(passenger_id, departure, destination, carType, payment, status, price, time) VALUES("
                + to_string(passenger.id) + ", '" + from + "' , '" + to + "' , '" + carType + "' , '" + payment + "' , 'new' ," + to_string(price) + ", " + to_string(time) + ");";

            cout << endl << "Accept order ?" << endl << endl << "[1] Yes" <<
                endl << "[2] No" << endl << "[3] Change Payment Method" << endl;
            cout << endl << "1" << endl;

            updateData("WEndex_Taxi_BD.db", sql_query);
            cout << "Order has been ordered!" << endl;
            ride = Ride(from, to, carType, payment, price, time, passenger.id);
            isTaxiOrdered = true;

        }
        else
            cout << " You can not order 2 taxi at the same time" << endl;
    }
};



class DriverGateway {
public:
    Driver driver;
    vector<Ride> orders;
    void logIn(string name, string password) {
        // This method reads data base and looking for
        // user with given name and password if found
        // fills variable driver with data of given driver

        string sql_query = "SELECT * FROM driver WHERE name = '" + name + "' AND password = '" + password + "';";
        selectData("WEndex_Taxi_BD.db", sql_query, 5);
        driver = tmpDriver;
        if (driver.name != "") {
            cout << endl << "Authorization was successful" << endl;
            cout << "Hello, " + driver.name << endl;
        }
        else cout << endl << "Wrong name or password" << endl;
        cout << "History of orders" << endl;
        getHistory();
    }

    void logInStory() {
        // This method reads data base and looking for
        // user with given name and password if found
        // fills variable driver with data of given driver
        string name; string password;
        name = "Vagif Khalilov";
        password = "azerbaijan";
        cout << endl << "-----------Driver " << name << " logginig in to the system-----------" << endl;

        string sql_query = "SELECT * FROM driver WHERE name = '" + name + "' AND password = '" + password + "';";
        selectData("WEndex_Taxi_BD.db", sql_query, 5);
        driver = tmpDriver;
        getHistory();
        if (driver.name != "") {
            cout << endl << "Authorization was successful" << endl;
            cout << "Hello, " + driver.name << endl;
        }
        else cout << endl << "Wrong name or password" << endl;
    }
    void logout() {

        string sql_query = "UPDATE driver SET status = 'Not In Work' WHERE id = " + to_string(driver.id) + " ;";
        updateData("WEndex_Taxi_BD.db", sql_query);

        sql_query = "UPDATE cars SET status = 'free' WHERE number = '" + driver.car.number + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
    }

    void logoutStory(){
        cout << endl << "-----------Driver " << driver.name << " logginig out to the system-----------" << endl;

        string sql_query = "UPDATE driver SET status = 'Not In Work' WHERE id = " + to_string(driver.id) + " ;";
        updateData("WEndex_Taxi_BD.db", sql_query);

        sql_query = "UPDATE cars SET status = 'free' WHERE number = '" + driver.car.number + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
    }

    void getCar(){
        // This method ask for car with given car type
        // from data base and save it
        int code = 0;
        string carType;
        while (code == 0) {
            cout << "Choose car type:" << endl << endl;
            cout << "[1] Economy" << endl;
            cout << "[2] Comfort" << endl;
            cout << "[3] ComfortPlus" << endl;
            cout << "[4] Business" << endl;
            cin >> code;
            switch (code)
            {
            case 1:
                carType = "Economy";
                break;
            case 2:
                carType = "Comfort";
                break;
            case 3:
                carType = "ComfortPlus";
                break;
            case 4:
                carType = "Business";
                break;
            default:
                cout << "Wrong Input" << endl;
                code = 0;
                break;
            }
        }
        
        string sql_query = "SELECT * FROM cars WHERE carType = '" + carType + "' AND status = 'free';";
        
        selectData("WEndex_Taxi_BD.db", sql_query, 4);
        if (carType == "Business")
            driver.bussnesCar = tmpBussnesCar;
        else if (carType == "Comfort")
            driver.comfortCar = tmpComfortCar;
        else
            driver.car = tmpCar;
        tmpCar = Car();
        tmpComfortCar = ComfortCar();
        tmpBussnesCar = BussnessCar();

        if (driver.bussnesCar.number != "")
            sql_query = "UPDATE cars SET status = 'busy' WHERE number = '" + driver.bussnesCar.carType + "';";
        else if (driver.comfortCar.number != "")
            sql_query = "UPDATE cars SET status = 'busy' WHERE number = '" + driver.comfortCar.number + "';";
        else
            sql_query = "UPDATE cars SET status = 'busy' WHERE number = '" + driver.car.number + "';";

        updateData("WEndex_Taxi_BD.db", sql_query);
        if (driver.car.number == "" && driver.bussnesCar.number == "" && driver.comfortCar.number == "")
            cout << "There is no availible car of this car type" << endl;
        else cout << "You got a car" << endl;
    }

    void getCarStory() {
        // This method ask for car with given car type
        // from data base and save it
        cout << endl << "-----------Driver " << driver.name << " asking for car-----------" << endl;

        string carType;
        cout << "Choose car type:" << endl << endl;
        cout << "[1] Economy" << endl;
        cout << "[2] Comfort" << endl;
        cout << "[3] ComfortPlus" << endl;
        cout << "[4] Business" << endl;

        cout << endl << "4" << endl;
        carType = "Business";

        string sql_query = "SELECT * FROM cars WHERE carType = '" + carType + "' AND status = 'free';";

        selectData("WEndex_Taxi_BD.db", sql_query, 4);
        if (carType == "Business")
            driver.bussnesCar = tmpBussnesCar;
        else if (carType == "Comfort")
            driver.comfortCar = tmpComfortCar;
        else
            driver.car = tmpCar;
        tmpCar = Car();
        tmpComfortCar = ComfortCar();
        tmpBussnesCar = BussnessCar();

        if (driver.bussnesCar.number != "")
            sql_query = "UPDATE cars SET status = 'busy' WHERE number = '" + driver.bussnesCar.carType + "';";
        else if (driver.comfortCar.number != "")
            sql_query = "UPDATE cars SET status = 'busy' WHERE number = '" + driver.comfortCar.number + "';";
        else
            sql_query = "UPDATE cars SET status = 'busy' WHERE number = '" + driver.car.number + "';";

        updateData("WEndex_Taxi_BD.db", sql_query);
        if (driver.car.number == "" && driver.bussnesCar.number == "" && driver.comfortCar.number == "")
            cout << "There is no availible car of this car type" << endl;
        else cout << "You got a car" << endl;
    }

    void getHistory() {
        // This method reads History for authorized
        // user from data base and save it

        string sql_query = "SELECT * FROM orders WHERE driver_id = " + to_string(driver.id) + " AND status = 'done';";
        selectData("WEndex_Taxi_BD.db", sql_query, 3);
        driver.history = tmpHistory;
        tmpHistory = vector<Ride>();

        cout << endl << endl;
        for (int i = 0; i < driver.history.size(); i++)
        {
            cout << i + 1 << " | " << driver.history[i].departure << " | " << driver.history[i].destination << " | " <<
                driver.history[i].carType << " | " << driver.history[i].price << "rub | " << driver.history[i].payment <<
                " | " << driver.history[i].time << "sec" << endl;

        }
    }

    void getHistoryStory() {
        // This method reads History for authorized
        // user from data base and save it
        cout << endl << "-----------Driver " << driver.name << " asking for history of orders-----------" << endl;
        string sql_query = "SELECT * FROM orders WHERE driver_id = " + to_string(driver.id) + " AND status = 'done';";
        selectData("WEndex_Taxi_BD.db", sql_query, 3);
        driver.history = tmpHistory;
        tmpHistory = vector<Ride>();

        cout << endl << endl;
        for (int i = 0; i < driver.history.size(); i++)
        {
            cout << i + 1 << " | " << driver.history[i].departure << " | " << driver.history[i].destination << " | " <<
                driver.history[i].carType << " | " << driver.history[i].price << "rub | " << driver.history[i].payment <<
                " | " << driver.history[i].time << "sec" << endl;

        }
    }

    void updateStatus() {
        // This method read new status and update it in data base

        int code = 0;
        string status;

        while (code == 0) {
            cout << endl;
            cout << "Chose status:" << endl << endl;
            cout << "[1] In Work" << endl;
            cout << "[2] Not In Work" << endl;
            cout << endl;

            cin >> code;

            if (code == 1) {
                code = 0;

                cout << endl;
                cout << "Chose status:" << endl << endl;
                cout << "[1] In Ride" << endl;
                cout << "[2] Not In Ride" << endl;
                cout << endl;
                
                cin >> code;

                if (code == 1)
                    status = "Working - In Ride";
                else if (code == 2)
                    status = "Working - Not In Ride";
                else {
                    cout << "Wrong input" << endl;
                    code = 0;
                }
            } else if(code == 2) status = "Not Working";
            else {
                cout << "Wrong input" << endl;
                code = 0;
            }
        }

        cout << endl << "Your status: " << status << endl;
        string sql_query = "UPDATE driver SET status = '" + status + "' WHERE id = " + to_string(driver.id) + " ;";
        updateData("WEndex_Taxi_BD.db", sql_query);
    }

    void updateStatusStory() {
        // This method read new status and update it in data base

        cout << endl << "-----------Driver " << driver.name << " updating his status-----------" << endl;

        string status;

        cout << "Chose status:" << endl << endl;
        cout << "[1] In Work" << endl;
        cout << "[2] Not In Work" << endl;
        cout << endl;
        cout << endl << "1" << endl;

        cout << endl;
        cout << "Chose status:" << endl << endl;
        cout << "[1] In Ride" << endl;
        cout << "[2] Not In Ride" << endl;
        cout << endl;
        cout << endl << "1" << endl;
        status = "Working - In Ride";

        cout << endl << "Your status: " << status << endl;
        string sql_query = "UPDATE driver SET status = '" + status + "' WHERE id = " + to_string(driver.id) + " ;";
        updateData("WEndex_Taxi_BD.db", sql_query);
    }

    void startRide() {
        // This method takes time of ride from data base and 
        // waitng for this time and after updates status
        
        if (driver.bussnesCar.number != "")
            driver.bussnesCar.parkRightInFrontOfTheEntrance();
        else if (driver.comfortCar.number != "")
            driver.comfortCar.usageBottleOfwater();
        cout << "Ride started ..." << endl ;
        this_thread::sleep_for(chrono::seconds(tmpOrder.time));

        string sql_query = "UPDATE orders SET status = 'done' WHERE passenger_id = " + to_string(tmpOrder.id) +
            + " AND destination = '" + tmpOrder.destination + "' AND driver_id = " + to_string(driver.id) + " ;";
        updateData("WEndex_Taxi_BD.db", sql_query);
        isTaxiOrdered = false;
        cout << "Ride finished" << endl ;

        if (driver.comfortCar.number != "")
            cout << "Number of bottles remaining: " << driver.comfortCar.freeBottleOfwater << endl;
        tmpOrder = Ride();
    }

    void startRideStory() {
        // This method takes time of ride from data base and 
        // waitng for this time and after updates status

        if (driver.bussnesCar.number != "")
            driver.bussnesCar.parkRightInFrontOfTheEntrance();
        else if (driver.comfortCar.number != "")
            driver.comfortCar.usageBottleOfwater();
        cout << endl << "-----------Driver " << driver.name << " started the ride-----------" << endl;
        cout << "Ride started..." << endl;
        this_thread::sleep_for(chrono::seconds(tmpOrder.time));

        string sql_query = "UPDATE orders SET status = 'done' WHERE passenger_id = " + to_string(tmpOrder.id) +
            +" AND destination = '" + tmpOrder.destination + "' AND driver_id = " + to_string(driver.id) + " ;";
        updateData("WEndex_Taxi_BD.db", sql_query);
        isTaxiOrdered = false;
        cout << "Ride finished" << endl;

        if (driver.comfortCar.number != "")
            cout << "Number of bottles remaining: " << driver.comfortCar.freeBottleOfwater << endl;
        tmpOrder = Ride();
    }

    void getOrder() {
        // This method takes all available orders from data base
        // and if driver accept update data in data base and call startRide function

        string sql_query;
        if (driver.bussnesCar.number != "")
            sql_query = "SELECT * FROM orders WHERE carType = '" + driver.bussnesCar.carType + "' AND status = 'new';";
        else if (driver.comfortCar.number != "")
            sql_query = "SELECT * FROM orders WHERE carType = '" + driver.comfortCar.carType + "' AND status = 'new';";
        else
            sql_query = "SELECT * FROM orders WHERE carType = '" + driver.car.carType + "' AND status = 'new';";

        selectData("WEndex_Taxi_BD.db", sql_query, 3);
        orders = tmpHistory;
        tmpHistory = vector<Ride>();

        int code = 0;
        bool isInWork = false;
        for (int i = 0; i < orders.size(); i++)
        {
            cout << endl;
            cout << "Available Order Number " << i+1 <<" :"<< endl << endl;
            cout << "Ride Departure: " << orders[i].departure << endl;
            cout << "Ride Destination: " << orders[i].destination << endl;
            cout << "Car  Type: " << orders[i].carType << endl;
            cout << "Ride Price: " << orders[i].price << endl;
            cout << "Ride Payment: " << orders[i].payment << endl;
            cout << "Ride Time: " << orders[i].time << endl;
            cout << endl;

            while (code == 0)
            {
                cout << "[1]Accept" << endl;
                cout << "[2]Decline" << endl;
                cin >> code;
                    
                if (code != 1 && code != 2) {
                    code = 0;
                    cout << "Invalid Input" << endl;
                }
            }
            if (code == 1) {
                string sql_query = "UPDATE orders SET status = 'work' WHERE passenger_id = " +
                     to_string(orders[i].id) +" AND destination = '"+ orders[i].destination +"';";
                updateData("WEndex_Taxi_BD.db", sql_query);

                sql_query = "UPDATE orders SET driver_id = " + to_string(driver.id) +" WHERE passenger_id = " +
                    to_string(orders[i].id) + " AND destination = '" + orders[i].destination + "';";
                updateData("WEndex_Taxi_BD.db", sql_query);
                tmpOrder = orders[i];
                isInWork = true;
                idOfDriver = driver.id;
                code = 0;
                break;
            }
            else if (code == 2) {
                code = 0;
                continue;
            }
        }
        if(isInWork)
            startRide();
    }

    void getOrderStory() {
        // This method takes all available orders from data base
        // and if driver accept update data in data base and call startRide function
         cout << endl << "-----------Driver " << driver.name << " asking for availible orders-----------" << endl;
         string sql_query;
         if (driver.bussnesCar.number != "")
             sql_query = "SELECT * FROM orders WHERE carType = '" + driver.bussnesCar.carType + "' AND status = 'new';";
         else if (driver.comfortCar.number != "")
             sql_query = "SELECT * FROM orders WHERE carType = '" + driver.comfortCar.carType + "' AND status = 'new';";
         else
             sql_query = "SELECT * FROM orders WHERE carType = '" + driver.car.carType + "' AND status = 'new';";
        selectData("WEndex_Taxi_BD.db", sql_query, 3);
        orders = tmpHistory;
        tmpHistory = vector<Ride>();

        cout << endl;
        cout << "Available Order Number " << 0 + 1 << " :" << endl << endl;
        cout << "Ride Departure: " << orders[0].departure << endl;
        cout << "Ride Destination: " << orders[0].destination << endl;
        cout << "Car  Type: " << orders[0].carType << endl;
        cout << "Ride Price: " << orders[0].price << endl;
        cout << "Ride Payment: " << orders[0].payment << endl;
        cout << "Ride Time: " << orders[0].time << endl;
        cout << endl;

        cout << "[1]Accept" << endl;
        cout << "[2]Decline" << endl;

        if (orders.size() > 1) {
            cout << endl << "2" << endl;

            cout << endl;
            cout << "Available Order Number " << 1 + 1 << " :" << endl << endl;
            cout << "Ride Departure: " << orders[1].departure << endl;
            cout << "Ride Destination: " << orders[1].destination << endl;
            cout << "Car  Type: " << orders[1].carType << endl;
            cout << "Ride Price: " << orders[1].price << endl;
            cout << "Ride Payment: " << orders[1].payment << endl;
            cout << "Ride Time: " << orders[1].time << endl;
            cout << endl;

            cout << "[1]Accept" << endl;
            cout << "[2]Decline" << endl;
        }
        cout << endl << "1" << endl;
        
        sql_query = "UPDATE orders SET status = 'work' WHERE passenger_id = " +
            to_string(orders[1].id) + " AND destination = '" + orders[1].destination + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);

        sql_query = "UPDATE orders SET driver_id = " + to_string(driver.id) + " WHERE passenger_id = " +
            to_string(orders[1].id) + " AND destination = '" + orders[1].destination + "';";
        updateData("WEndex_Taxi_BD.db", sql_query);
        idOfDriver = driver.id;
        
        tmpOrder = orders[1];
    }


    void seeCar() {
        
        if (driver.car.number == "" && driver.bussnesCar.number == "" && driver.comfortCar.number == "") cout << "You have no car" << endl;
        else {
            if (driver.bussnesCar.number != "") {
                cout << endl;
                cout << "Car Info:" << endl << endl;
                cout << "Car Model:" << driver.bussnesCar.model << endl;
                cout << "Car type:" << driver.bussnesCar.carType << endl;
                cout << "Car color:" << driver.bussnesCar.color << endl;
                cout << "Car number:" << driver.bussnesCar.number << endl;
                cout << endl;
            }
            else if (driver.comfortCar.number != "") {
                cout << endl;
                cout << "Car Info:" << endl << endl;
                cout << "Car Model:" << driver.comfortCar.model << endl;
                cout << "Car type:" << driver.comfortCar.carType << endl;
                cout << "Car color:" << driver.comfortCar.color << endl;
                cout << "Car number:" << driver.comfortCar.number << endl;
                cout << endl;
            }
            else {
                cout << endl;
                cout << "Car Info:" << endl << endl;
                cout << "Car Model:" << driver.car.model << endl;
                cout << "Car type:" << driver.car.carType << endl;
                cout << "Car color:" << driver.car.color << endl;
                cout << "Car number:" << driver.car.number << endl;
                cout << endl;
            }
        }
    }

    void seeCarStory() {
        cout << endl << "-----------Driver " << driver.name << " asking for car info-----------" << endl;

        if (driver.car.number == "" && driver.bussnesCar.number == "" && driver.comfortCar.number == "") cout << "You have no car" << endl;
        else {
            if (driver.bussnesCar.number != "") {
                cout << endl;
                cout << "Car Info:" << endl << endl;
                cout << "Car Model:" << driver.bussnesCar.model << endl;
                cout << "Car type:" << driver.bussnesCar.carType << endl;
                cout << "Car color:" << driver.bussnesCar.color << endl;
                cout << "Car number:" << driver.bussnesCar.number << endl;
                cout << endl;
            }
            else if (driver.comfortCar.number != "") {
                cout << endl;
                cout << "Car Info:" << endl << endl;
                cout << "Car Model:" << driver.comfortCar.model << endl;
                cout << "Car type:" << driver.comfortCar.carType << endl;
                cout << "Car color:" << driver.comfortCar.color << endl;
                cout << "Car number:" << driver.comfortCar.number << endl;
                cout << endl;
            }
            else {
                cout << endl;
                cout << "Car Info:" << endl << endl;
                cout << "Car Model:" << driver.car.model << endl;
                cout << "Car type:" << driver.car.carType << endl;
                cout << "Car color:" << driver.car.color << endl;
                cout << "Car number:" << driver.car.number << endl;
                cout << endl;
            }
        }
    }
};


int main() {
    DriverGateway driverSesion;
    PassengerGateway passengerSesion;
    int code = 0;
    string name;
    string password;
    string tmpTxt;

    while (code == 0)
    {
        cout << endl << "Choose scenario:" << endl << endl;
        cout << "[1] Real mode" << endl;
        cout << "[2] Story mode" << endl;
        cin >> code;

        if (code == 1)
        {
            code = 0;
            while (code == 0)
            {
                cout << endl << "Choose type of user:" << endl << endl;
                cout << "[1] Passenger" << endl;
                cout << "[2] Driver" << endl;
                cout << "[0] Exit program" << endl;
                cin >> code;

                switch (code)
                {
                case 1:         
                    code = 0;
                    cout << endl << "Log in" << endl << "Enter name:" << endl;
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter password:" << endl;
                    getline(cin, password);
                    passengerSesion.logIn(name, password);

                    while (code == 0) {
                        cout << endl << "Choose option:" << endl << endl;
                        cout << "[1] History of orders " << endl;
                        cout << "[2] Payment methods" << endl;
                        cout << "[3] Update payment methods" << endl;
                        cout << "[4] Pinned address" << endl;
                        cout << "[5] Update pinned address" << endl;
                        cout << "[6] Order a taxi" << endl;
                        cout << "[7] Get last bill" << endl;
                        if(isTaxiOrdered)
                            cout << "[8] Get Coordinates" << endl;
                        cout << "[0] Exit" << endl;
                        cin >> code;

                        switch (code)
                        {
                        case 1:
                            passengerSesion.getHistory();
                            code = 0;
                            break;
                        case 2:
                            cout << endl << "First payment method: " << passengerSesion.getPayment1() << endl;
                            cout << endl << "Second payment method: " << passengerSesion.getPayment2() << endl;
                            code = 0;
                            break;
                        case 3:
                            cout << endl << "Choose what method update: " << endl << endl;
                            cout << endl << "[1] First payment method: " << passengerSesion.getPayment1() << endl;
                            cout << endl << "[2] Second payment method: " << passengerSesion.getPayment2() << endl;
                            cin >> code;
                            if (code == 1) {
                                cout << endl << "Enter new payment method: " << endl;
                                cin.ignore();
                                getline(cin, tmpTxt);
                                passengerSesion.setPayment1(tmpTxt);
                            }
                            else if (code == 2) {
                                cout << endl << "Enter new payment method: " << endl;
                                cin.ignore();
                                getline(cin, tmpTxt);
                                passengerSesion.setPayment2(tmpTxt);
                            }
                            else
                            {
                                cout << endl << "Wrong Input" << endl;
                                code = 0;
                            }
                            code = 0;
                            break;
                        case 4:
                            cout << endl << "Pinned address: " << passengerSesion.getPinnedAddress() << endl;
                            code = 0;
                            break;
                        case 5:
                            cout << endl << "Enter new address: " << endl;
                            cin.ignore();
                            getline(cin, tmpTxt);
                            passengerSesion.setPinnedAddress(tmpTxt);
                            code = 0;
                            break;
                        case 6:
                            passengerSesion.orderTaxi();
                            code = 0;
                            break;
                        case 7:
                            passengerSesion.getBill();
                            code = 0;
                            break;
                        case 8:
                            passengerSesion.getCoordinates();
                            code = 0;
                            break;
                        case 0:
                            cout << endl << "Bye..." << endl;
                            code = -1;
                            break;
                        default:
                            cout << endl << "Wrong Input" << endl;
                            code = 0;
                            break;
                        }
                    }
                    code = 0;
                    break;
                case 2: 
                    cout << "Log in:" << endl << "Enter name:" << endl;
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter password:" << endl;
                    getline(cin, password);
                    driverSesion.logIn(name, password);
                    code = 0;
                    while (code == 0) {
                        cout << endl << "Choose option:" << endl << endl;
                        cout << "[1] History of orders " << endl;
                        cout << "[2] Get car" << endl;
                        cout << "[3] Car info" << endl;
                        cout << "[4] Update status" << endl;
                        cout << "[5] Available orders" << endl;
                        cout << "[0] Exit" << endl;
                        cin >> code;

                        switch (code)
                        {
                        case 1:
                            driverSesion.getHistory();
                            code = 0;
                            break;
                        case 2:
                            driverSesion.getCar();
                            code = 0;
                            break;
                        case 3:
                            driverSesion.seeCar();
                            code = 0;
                            break;
                        case 4:
                            driverSesion.updateStatus();
                            code = 0;
                            break;
                        case 5:
                            driverSesion.getOrder();
                            code = 0;
                            break;
                        case 0:
                            cout << endl << "Bye..." << endl;
                            code = -1;
                            driverSesion.logout();
                            break;
                        default:
                            cout << endl << "Wrong Input" << endl;
                            code = 0;
                            break;
                        }
                    }
                    code = 0;
                    break;
                case 0:
                    code = -1;
                    break;
                default:
                    cout << endl << "Wrong Input" << endl;
                    code = 0;
                    break;
                }
            }
           
        }
        else if (code == 2) {
            passengerSesion.logInStory();
            passengerSesion.getHistoryStory();
            passengerSesion.getPaymentStory();
            passengerSesion.setPayment1Story();
            passengerSesion.getPinnedAddressStory();
            passengerSesion.setPinnedAddressStory();
            passengerSesion.orderTaxiStory();
            passengerSesion.getCoordinatesStory();
            driverSesion.logInStory();
            driverSesion.getCarStory();
            driverSesion.seeCarStory();
            driverSesion.getHistoryStory();
            driverSesion.getOrderStory();
            driverSesion.updateStatusStory();
            passengerSesion.getCoordinatesStory();
            driverSesion.startRideStory();
            passengerSesion.getBillStory();
            passengerSesion.getHistoryStory();
            driverSesion.logoutStory();
        }
        else {
            cout << endl << "Wrong Input!" << endl;
            code = 0;
        }
    }



    return 0;
}



int selectData(const char* dir, string query, int code) {
    // This function connects with data base , sends 
    // query to sqlite and calls function that prints output

    sqlite3* DB;
    int exit = sqlite3_open(dir, &DB);
    if(code == 1)
        sqlite3_exec(DB, query.c_str(), getUser, NULL, NULL);
    else if(code == 2)
        sqlite3_exec(DB, query.c_str(), getCoordinates, NULL, NULL);
    else if(code == 3)
        sqlite3_exec(DB, query.c_str(), getHistory, NULL, NULL);
    else if(code == 4)
        sqlite3_exec(DB, query.c_str(), getCar, NULL, NULL);
    else if (code == 5)
        sqlite3_exec(DB, query.c_str(), getDriver, NULL, NULL);
    
    return 0;
}

int getCar(void* NotUsed, int resultNum, char** values, char** colNames) {
    // This function takes values that selectData() got creates new Car 
    // object and saves it into global vactor car
    
    string model;
    string color;
    string carType;
    string number;
    string status;
    int latitude;
    int longitude;

    model = values[0];
    color = values[1];
    carType = values[2];
    number = values[3];
    status = values[4];
    latitude = stoi(values[5]);
    longitude = stoi(values[6]);
   
    if (carType == "Comfort") {
        ComfortCar newCar(model, color, carType, number, status, latitude, longitude);
        tmpComfortCar = newCar;
    }
    else if (carType == "Business") {
        BussnessCar newCar(model, color, carType, number, status, latitude, longitude);
        tmpBussnesCar = newCar;
    }
    else {
        Car newCar(model, color, carType, number, status, latitude, longitude);
        tmpCar = newCar;
    }
    return 0;
}

int getHistory(void* NotUsed, int resultNum, char** values, char** colNames) {
    // This function take all values that selectData() got creates new Ride 
    // object and saves it into global vactor history

    vector<Ride> history;
    string departure;
    string destination;
    string carType;
    string payment;
    string status;
    int price;
    int time;
    int id;
    
    id = stoi(values[0]);
    departure = values[1];
    destination = values[2];
    carType = values[3];
    payment = values[4];
    status = values[5];
    price = stoi(values[6]);
    time = stoi(values[7]);

    Ride newRide(departure, destination, carType, payment, price, time, id);
    tmpHistory.push_back(newRide);
    tmpStatusOfLast = status;
    
    return 0;
}
int getCoordinates(void* NotUsed, int resultNum, char** values, char** colNames) {
    // This function prints all values that selectData() got
    int X;
    int Y;

    X = stoi(values[1]);
    Y = stoi(values[2]);

    if (tmpDepartureX == 0)
        tmpDepartureX = X;
    else tmpDestinationX = X;

    if (tmpDepartureY == 0)
        tmpDepartureY = Y;
    else tmpDestinationY = Y;

    return 0;
}
int getUser(void* NotUsed, int resultNum, char** values, char** colNames) {
    // This function prints all values that selectData() got
    string name;
    string password;
    string address;
    string payment1;
    string payment2;
    vector<Ride> history;
    int rating;
    int id;

    id = stoi(values[0]);
    name = values[1];
    password = values[2];
    payment1 = values[3];
    payment2 = values[4];
    address  = values[5];
    rating   = stoi(values[6]);
    
    Passenger newPass(name, address, payment1, payment2, password, history, rating, id);
    tmpPassenger = newPass;
        
    return 0;
}
int getDriver (void* NotUsed, int resultNum, char** values, char** colNames) {
    // This function prints all values that selectData() got
    int id;
    int rating;
    string name;
    string password;
    vector<Ride> history;
    Car car;
    string status;

    id = stoi(values[0]);
    rating = stoi(values[1]);
    name = values[2];
    password = values[3];
    status = values[4];

    Driver newDriver(id, rating, name, password, history, car, status);
    tmpDriver = newDriver;

    return 0;
}

int updateData(const char* dir, string query) {
    // This method update specific data from data base 

    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open(dir, &DB);

    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << "Error update!" << endl;
        sqlite3_free(messageError);
    }
    return 0;
}

/*
SQL COMMANDS 

    int id;
    int rating;
    string name;
    string password;
    vector<Ride> history;
    Car car;
    string status;
    (id, rating, name, password, history, car, status);

CREATE TABLE driver(
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    rating      INTEGER,
    name        VARCHAR(100), 
    password    VARCHAR(100),
    status      VARCHAR(100) 
);

INSERT INTO cars(model, color, carType, number, status, latitude, longitude)
VALUES('BMW x5', 'black','Business', 'В777ОР777', 'free', 0, 0);

INSERT INTO map(street, coordinateX, coordinateY)
VALUES('Namereznaya 48A', 7558, 6913);

coordinate
SELECT * FROM passenger ;
SELECT * FROM passenger WHERE name = 'Khabib Khays' AND password = 'remag';
SELECT * FROM passenger ORDER BY name;
SELECT * FROM passenger ORDER BY name DESC;

DELETE FROM passenger
WHERE id = 2;

UPDATE map
SET street = 'Nabereznaya 48A'
WHERE street = 'Nabereeznaya 48A';

.mode line
.open WEndex_Taxi_BD.db
.mode column
.headers on
.width 2 2 2
.quit
*/