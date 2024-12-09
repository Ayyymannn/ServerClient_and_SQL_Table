**Q1) Weather Service Client-Server Application: Design a simple client-server application where the 
server provides weather information for a specific city, and the client requests weather details by 
providing the city name.**

**Server Output**
```
~$ gcc weather_server.c -o weather_server.o
~$ ./weather_server.o 
Chat server started. Waiting for clients...
New client connected: Client 1
```
**Client Output**
```
~$ gcc weather_client.c -o weather_client.o
~$ ./weather_client.o
Connected to weather server.
victoria
15°C
70%
Cloudy
calgary
-2°C
50%
Snowy
london 
City not found
```

**Q2) Library Database Management System: You are tasked with creating a simple Library Database 
Management System using a C program that connects to a MySQL database. The program will allow the 
user to perform basic operations like adding, viewing, and searching books in the library.**

**Create SQL Database**
```
sudo mysql -u root -p
CREATE DATABASE library_db;
USE library_db;
```
**Create SQL Table**
```
CREATE TABLE books ( 
id INT PRIMARY KEY AUTO_INCREMENT, 
title VARCHAR(255) NOT NULL, 
author VARCHAR(255) NOT NULL, 
year INT NOT NULL 
); 
```
**mysqlfile Output**
```
aymanalrubaey@LAPTOP-6ERAS26B:~$ gcc -o mysqlfile mysqlfile.c -lmysqlclient
aymanalrubaey@LAPTOP-6ERAS26B:~$ ./mysqlfile
Book Added
Book Added
Book Added
Book Added
Book Added

Connected to the MySQL database successfully.
Press 1: Add new book
Press 2: View all books
Press 3: Search for a book by title
Press 4: Exit
2
Query Results:
1       book1   author1 2019
2       book2   author2 2020
3       book3   author3 2021
4       book4   author4 2022
5       book5   author5 2023

Connected to the MySQL database successfully.
Press 1: Add new book
Press 2: View all books
Press 3: Search for a book by title
Press 4: Exit
1
Insert title: book6
Insert author: author6
Insert year: 2024
Book Added

Connected to the MySQL database successfully.
Press 1: Add new book
Press 2: View all books
Press 3: Search for a book by title
Press 4: Exit
2
Query Results:
1       book1   author1 2019
2       book2   author2 2020
3       book3   author3 2021
4       book4   author4 2022
5       book5   author5 2023
6       book6   author6 2024

Connected to the MySQL database successfully.
Press 1: Add new book
Press 2: View all books
Press 3: Search for a book by title
Press 4: Exit
3
Insert title: book2
Query Results:
2       book2   author2 2020

Connected to the MySQL database successfully.
Press 1: Add new book
Press 2: View all books
Press 3: Search for a book by title
Press 4: Exit
4
Connection closed
```

