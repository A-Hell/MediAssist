// Common header file for the Hospital Management System

#pragma once
using namespace std;

// Include necessary standard libraries
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// Global constants and type definitions


// ANSI/style codes
// Example : cout << BOLD + GREEN + "Hello World!" + RESET << endl;
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";
const string STRIKETHROUGH = "\033[9m";
const string ITALIC = "\033[3m";
const string GRAY = "\033[90m";
const string RED = "\033[91m";
const string GREEN = "\033[92m";
const string YELLOW = "\033[93m";
const string BLUE = "\033[94m";
const string MAGENTA = "\033[95m";
const string CYAN = "\033[96m";
const string WHITE_ = "\033[97m";
const string DYELLOW = "\033[33m";
const string DCYAN = "\033[36m";


// Global Helper Functions


// Function to validate date format (YYYY-MM-DD)
bool isValidDate(const string& date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	if (!isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3]) ||
		!isdigit(date[5]) || !isdigit(date[6]) ||
		!isdigit(date[8]) || !isdigit(date[9]))
		return false;

	int year = stoi(date.substr(0, 4));
	int month = stoi(date.substr(5, 2));
	int day = stoi(date.substr(8, 2));

	if (year < 1900 || year > 2100)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > 29 || (day == 29 && !isLeapYear))
			return false;
	}

	return true;
}


// Function to validate time format (HH:MM)
bool isValidTime(const string& time)
{
	if (time.length() != 5 || time[2] != ':')
		return false;
	if (!isdigit(time[0]) || !isdigit(time[1]) || !isdigit(time[3]) || !isdigit(time[4]))
		return false;

	int hour = stoi(time.substr(0, 2));
	int minute = stoi(time.substr(3, 2));

	if (hour < 0 || hour > 23)
		return false;
	if (minute < 0 || minute > 59)
		return false;

	return true;
}