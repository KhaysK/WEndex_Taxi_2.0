
# Home assigment #5, Khabib Khaysadykov B20-03
# Wendex taxi project

![logo](https://pngimg.com/uploads/taxi_logos/taxi_logos_PNG23.png)
<hr>
<h3>About project:</h3>
This project is an implementation of taxi system for both passenger and driver. 
Project has server part based on SQLite data base. There are available two operating
modes of the system: <br>
1 - Real mode - Here program waiting for information from user and interact with user
<br>
2 - Story mode - Here user just a viewer, you can not interact. <h3>Work of all functions was shown in Story mode</h3>
<br>
<hr>
<h3>Tables in data base</h3>
<li>Admin</li>
<pre>
    1 admin available :
          <b>Name</b>       <b>Password</b>
       John Wick - UKilledMyDog
</pre>
<li>Passenger</li>
<pre>
    4 passengers available :
           <b>Name</b>         <b>Password</b>
       Frolov Nikita - nikita_krut
       Ivan Inchin   - 12345
       Andrey Vagin  - qwerty1234
       Khabib Khays  - remag
</pre>
<li>Driver</li>
<pre>
    3 drivers available :
            <b>Name</b>         <b>Password</b>
       Vagif Khalilov - azerbaijan
       Nikolai Shilov - math
       Oleg Bulichev  - dich
</pre>
<li>Car</li>
<pre>
    8 cars available :
          <b>Model</b>        <b>CarType</b>
       Lada Priora  - Economy       
       Kia rio      - Comfort
       Toyota Camry - ComfortPlus
       BMW x5       - Business
</pre>
<li>Map</li>
<pre>
    6 streets available :
        Universitetskaya 1/4
        Sportivnaya 126
        Pribreznaya 2
        Nabereznaya 48A
        Sportivnaya 106
        Kombinat Zdorovie 23
</pre>
<li>Orders</li>
<pre>
    10 order available :
            <b>Departure</b>           <b>Destination</b>     <b>Car type</b>            <b>Payment</b>       <b>Price</b>    <b>Time</b>
       Universitetskaya 1/4   Nabereznaya 48A   Comfort     4356 3452 3456 2354    300      12
       Sportivnaya 126        Sportivnaya 106   Business    6773 8894 6289 3929    1000      1
</pre>
<i>P.S. abow was mentioned some date not all</i>
<br>
<hr>
Programm by itself is a terminal program where available 3 options: passenger menu and driver menu and admin menu
<br>
<br>
In passenger menu 
 passenger can choose actions:

```bash
Get history of orders
Get payment methods
Update payment methods
Get pinned address
Update pinned address
Order a taxi
Get last bill
Get Coordinates
Exit
```
In driver
menu driver can choose actions:
```bash
Get history of orders
Get car
Get car info
Update status
Get available orders
Exit
```
In admin
menu admin can choose actions:
```bash
Block passenger
Unblock passenger
Block driver
Unblock driver
Cars for validation
Exit
```

<hr>
<h5>Remark:</h5>
It supposed that table map is a real map and you can use only streets from this table. You must write names of this 
streets the same as in data base.
<br>

For example:
<br>

"Universitetskaya 1/4" - good name
<br>
<br>
"Universitetskaya" - bad name. No such street in Data Base
<hr>

<h3>Dependencies:</h3>
<li>GNU Make minimum (VERSION 3.17) </li>
<li>clang (Version 6.0.0)</li>
<li>IDE Visual Studio</li>
<li>sqlite3_c_plus_plus - package</li>

<hr>

<h3>Building:</h3>

To build the project, use the following command in bash terminal:

```bash
cd <source path of Project>
gcc -o WEndex_Taxi_02 WEndex_Taxi_02.cpp 
```

