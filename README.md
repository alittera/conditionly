# Conditionly

Conditionly is a technological project developed by a group of students of La Sapienza University for the Internet Of Things course (2019).

Conditionly provides an intuitive and easy tool to send remote controls to your apartment A/C machine in any moment of the day in order to find the perfect temperature once you get home.

### Hardware components
This projects use the following hardware components provided by STM32:
* NUCLEO_F401RE board
* X-NUCLEO-IDW01M1 WiFi expansion board

### Software technologies
This projects use the following software languages and frameworks:
* Android application
	* Flutter framework
	* Dart
	* Kotlin 
* Nucleo Board
	* C
	* C++
* AWS Backend
	* AWS IoT
	* AWS DynamoDB
	* AWS Lambda (Python)
	* AWS API Gateway

### Repository tree
This repository is organized with the following structure:
* **conditionly-app:** This folder contains the code of our Android application. The applications connects to AWS in order to send the requested commands of the user. 
* **conditionly-board:** This folder contains the code used for the Nucleo board. The board is polling the AWS Server in order to get the last commands received from the conditionly-app. 
* **conditionly-aws:** This folder contains the code used for our lambda function in AWS in order to read from the DB the last command received and return a response to conditionly-board




