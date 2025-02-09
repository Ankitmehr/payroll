#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

string To_string(int num)
{
	string result = "";
	bool isNegative = false;
	if (num < 0)
	{
		isNegative = true;
		num = -num;
	}
	do
	{
		char digit = (num % 10) + '0';
		result = digit + result;
		num /= 10;
	} while (num > 0);
	if (isNegative)
	{
		result = '-' + result;
	}
	return result;
}
int to_int(string str)
{
	int num = 0, startIndex = 0;
	bool isNegative = false;
	if (str[0] == '-')
	{
		isNegative = true;
		startIndex = 1;
	}
	for (int i = startIndex; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 + (str[i] - '0');
		}
		else
		{
			cout << "Invalid input: non-numeric character found." << endl;
		}
	}
	if (isNegative)
		num = -num;
	return num;
}
void setDateAndTime(string &d, string &t)
{
	// setting date and time
	time_t now = time(0); // Get current time
	tm *localTime = localtime(&now);
	int year = 1900 + localTime->tm_year;
	int month = 1 + localTime->tm_mon;
	int day = localTime->tm_mday;
	int hour = localTime->tm_hour;
	int min = localTime->tm_min;
	int sec = localTime->tm_sec;
	string date = To_string(day) + "-" + To_string(month) + "-" + To_string(year);
	string time = To_string(hour) + ":" + To_string(min) + ":" + To_string(sec);
	d = date;
	t = time;
}

class globalFunctions
{
public:
	// Function to split a string based on a separator
	vector<string> split(const string &str, const string &separator)
	{
		vector<string> result;
		size_t start = 0;
		size_t end = str.find(separator);

		while (end != string::npos)
		{
			result.push_back(str.substr(start, end - start));
			start = end + separator.length(); // Move past the separator
			end = str.find(separator, start);
		}

		// Add the last part of the string
		result.push_back(str.substr(start));

		return result;
	}

	// Function to read file content and return as a string
	string readFileToString(const string &filePath)
	{
		ifstream file(filePath.c_str()); // Open the file
		if (!file.is_open())
		{
			cerr << "Error: Could not open the file." << endl;
			return "";
		}

		string content;
		string line;
		while (getline(file, line))
		{
			content += line + "\n"; // Append each line with a newline character
		}

		file.close();
		return content;
	}

	bool searchKeyword(const string &data, const string &keyword, bool isCaseSensitive)
	{
		string dataCopy = data;
		string keywordCopy = keyword;

		if (!isCaseSensitive)
		{
			// Convert both data and keyword to lowercase
			transform(dataCopy.begin(), dataCopy.end(), dataCopy.begin(), ::tolower);
			transform(keywordCopy.begin(), keywordCopy.end(), keywordCopy.begin(), ::tolower);
		}

		// Check if keyword exists in the data
		return dataCopy.find(keywordCopy) != string::npos;
	}

	int deleteContentFromFile(const string &fileName, const string &contentToDelete, const char* backupFile)
	{
		// Open the file for reading
		ifstream inputFile(fileName.c_str()); // Use c_str() to pass const char*
		if (!inputFile.is_open())
		{
			cerr << "Error: Could not open the file!" << endl;
			return 1;
		}

		// Read the entire content of the file into a single string
		stringstream buffer;
		buffer << inputFile.rdbuf();
		string fileContent = buffer.str();
		inputFile.close(); // Close the input file

		// Find and remove the contentToDelete from the file content
		size_t foundPos = fileContent.find(contentToDelete);
		if (foundPos != string::npos)
		{
			// Remove the contentToDelete if found
			fileContent.erase(foundPos, contentToDelete.length());
		}
		else
		{
			cerr << "Content not found in the file!" << endl;
			return 1;
		}

		// Open the file for writing (this will overwrite the file)
		ofstream outputFile(fileName.c_str());
		if (!outputFile.is_open())
		{
			cerr << "Error: Could not open the file for writing!" << endl;
			return 1;
		}

		// Write the updated content back to the file
		outputFile << fileContent;
		outputFile.close(); // Close the output file

		fstream file(backupFile, ios::app);
		if (!file.is_open())
		{
			cerr << "Failed to open the file." << endl;
			return 1;
		}
		file << contentToDelete << endl;
		file.close();
		return 0;
	}
};

class employee
{
public:
	string name, dob, mob, gender, email, address, jobTitle, department, dateOfJoining, timeOfJoining, employeeId;
	string dateModified, timeModified, isDeleted;
	long int salary;
	vector<string> newData;
	vector<string> updatedPayrollData;
	int employees_tobe_added;
	int tax, insurance, totalSalary;
	void getEdittedData(const string type = "employee")
	{
		cin.ignore(100, '\n'); // Clear input buffer
		cout << "\nEnter New details for Employee:\nEnter name: ";
		getline(cin, name);
		newData.push_back("NAME:- " + name);
		updatedPayrollData.push_back("NAME:- " + name);
		cout << "Enter date of birth (dd-mm-yyyy): ";
		cin >> dob;
		newData.push_back("DATE OF BIRTH:- " + dob);
		cout << "Enter mobile number: ";
		cin >> mob;
		newData.push_back("MOBILE:- " + mob);
		cout << "Enter gender: ";
		cin >> gender;
		newData.push_back("GENDER:- " + gender);
		cout << "Enter email: ";
		cin >> email;
		cin.ignore(100, '\n'); // Clear input buffer
		newData.push_back("EMAIL:- " + email);
		cout << "Enter address: ";
		getline(cin, address);
		newData.push_back("ADDRESS:- " + address);
		cout << "Enter job title: ";
		getline(cin, jobTitle);
		newData.push_back("JOB TITLE:- " + jobTitle);
		updatedPayrollData.push_back("JOB TITLE:- " + jobTitle);
		cout << "Enter department: ";
		getline(cin, department);
		newData.push_back("DEPARTMENT:- " + department);
		updatedPayrollData.push_back("DEPARTMENT:- " + department);
		cout << "Enter salary: ";
		cin >> salary;

		newData.push_back("SALARY:- " + To_string(salary));
		updatedPayrollData.push_back("BASIC SALARY:- " + To_string(salary));
		updatedPayrollData.push_back("TAX DEDUCTION(10%):- " + To_string((10 * salary) / 100));
		updatedPayrollData.push_back("INSURANCE DEDUCTION(5%):- " + To_string((5 * salary) / 100));
		updatedPayrollData.push_back("TOTAL SALARY:- " + To_string(salary - ((15 * salary) / 100)));
		cin.ignore(100, '\n'); // Clear input buffer
		setDateAndTime(dateModified, timeModified);
		newData.push_back("DATE MODIFIED:- " + dateModified);
		newData.push_back("TIME MODIFIED:- " + timeModified);
	}
	void setPayrollSlip()
	{
	}
	void getPayrollslip()
	{
	}
	void getEmployeeData(int i)
	{
		cin.ignore(100, '\n'); // Clear input buffer
		cout << "\nEnter details for Employee " << i << ":\nEnter name: ";
		getline(cin, name);

		cout << "Enter date of birth (dd-mm-yyyy): ";
		cin >> dob;

		cout << "Enter mobile number: ";
		cin >> mob;

		cout << "Enter gender: ";
		cin >> gender;

		cout << "Enter email: ";
		cin >> email;
		cin.ignore(100, '\n'); // Clear input buffer

		cout << "Enter address: ";
		getline(cin, address);

		cout << "Enter job title: ";
		getline(cin, jobTitle);

		cout << "Enter department: ";
		getline(cin, department);

		cout << "Enter salary: ";
		cin >> salary;
		cin.ignore(100, '\n'); // Clear input buffer
		dateModified = "Not Modified";
		timeModified = "Not Modified";
		isDeleted = "false";
		setDateAndTime(dateOfJoining, timeOfJoining);
	}

	int setId()
	{
		// getting current records
		string current_record_count;
		fstream totalRecordsFile;
		totalRecordsFile.open("totalRecords.txt", ios::in);
		if (!totalRecordsFile)
		{
			cerr << "can't open file.\n";
			return 1;
		}
		getline(totalRecordsFile, current_record_count);
		totalRecordsFile.close();
		int num = to_int(current_record_count);
		num++;
		employeeId = name.substr(0, 2) + department.substr(0, 3) + jobTitle.substr(0, 2) + To_string(num + 10000);
	}

	// generating record of employee
	string generateRecord(string request)
	{
		globalFunctions object;
		// getting current records
		string current_record_count;
		fstream totalRecordsFile;
		totalRecordsFile.open("totalRecords.txt", ios::in);
		if (!totalRecordsFile)
		{
			cerr << "can't open records file.\n";
			return "Error";
		}
		string input = object.readFileToString("totalRecords.txt");
		vector<string> result = object.split(input, ",");
		current_record_count = To_string(result.size());
		getline(totalRecordsFile, current_record_count);
		totalRecordsFile.close();
		int num = to_int(current_record_count);
		num++;
		if (request == "Record")
		{
			string record_of_employee = "{\nRECORD NO:- " + To_string(num) + "\nEMPLOYEE ID:- " + employeeId + "\nNAME:- " + name + "\nMOBILE:- " + mob + "\nDATE OF BIRTH:- " + dob + "\nGENDER:- " + gender + "\nEMAIL:- " + email + "\nJOB TITLE:- " + jobTitle + "\nDEPARTMENT:- " + department + "\nSALARY:- " + To_string(salary) + "\nADDRESS:- " + address + "\nDATE MODIFIED:- " + dateModified + "\nTIME MODIFIED:- " + timeModified + "\nJOINING DATE:- " + dateOfJoining + "\nJOINING TIME:- " + timeOfJoining + "\n}\n,";
			return record_of_employee;
		}
		else if (request == "Payroll")
		{
			string payroll_of_employee = "{\nRECORD NO:- " + To_string(num) + "\nEMPLOYEE ID:- " + employeeId + "\nNAME:- " + name + "\nJOB TITLE:- " + jobTitle + "\nDEPARTMENT:- " + department + "\nBASIC SALARY:- " + To_string(salary) + "\nTAX DEDUCTION(10%):- " + To_string((10 * salary) / 100) + "\nINSURANCE DEDUCTION(5%):- " + To_string((5 * salary) / 100) + "\nTOTAL SALARY:- " + To_string(salary - ((15 * salary) / 100)) + "\nJOINING DATE:- " + dateOfJoining + "\nJOINING TIME:- " + timeOfJoining + "\n}\n,";
			return payroll_of_employee;
		}
	}
};

// Updates the count of total records after adding a record
int updateRecordsCount(int count_tobe_added)
{
	// getting current records
	string current_record_count, new_employee_count;
	fstream totalRecordsFile;
	totalRecordsFile.open("totalRecords.txt", ios::in);
	if (!totalRecordsFile)
	{
		cerr << "can't open file.\n";
		return 1;
	}
	getline(totalRecordsFile, current_record_count);
	totalRecordsFile.close();

	// updating records count
	int num = to_int(current_record_count);
	num += count_tobe_added;
	new_employee_count = To_string(num);

	// appending records data
	fstream file("totalRecords.txt", ios::out);
	if (!file.is_open())
	{
		cerr << "Failed to open the file." << endl;
		return 1;
	}
	// Data to append
	file << new_employee_count << endl;
	file.close();
}

// Edit the existing data file
void editLinesInFile(const string &fileName, int startLine, int endLine, const vector<string> &newLines)
{
	// Open the file for reading
	ifstream inputFile(fileName.c_str());
	if (!inputFile.is_open())
	{
		cerr << "Failed to open the file for reading." << endl;
		return;
	}

	vector<string> lines;
	string line;

	// Read all lines into a vector
	while (getline(inputFile, line))
	{
		lines.push_back(line);
	}
	inputFile.close(); // Close the file after reading

	// Modify the specific range of lines
	int lineIndex = 0;
	for (int i = startLine - 1; i <= endLine - 1 && i < lines.size(); ++i)
	{
		if (lineIndex < newLines.size())
		{
			lines[i] = newLines[lineIndex++];
		}
	}

	// Open the file for writing (truncate mode)
	ofstream outputFile(fileName.c_str(), ios::trunc);
	if (!outputFile.is_open())
	{
		cerr << "Failed to open the file for writing." << endl;
		return;
	}

	// Write updated content back to the file
	for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
	{
		outputFile << *it << "\n";
	}
	outputFile.close();
}

// append data of employee to file
int appendEmployee(string record_tobe_added)
{
	fstream file("data.txt", ios::app);
	if (!file.is_open())
	{
		cerr << "Failed to open the file." << endl;
		return 1;
	}
	file << record_tobe_added << endl;
	file.close();
}

// append payroll slip in file
int appendPayroll(string payroll_tobe_added)
{
	fstream file("PayrollSlips.txt", ios::app);
	if (!file.is_open())
	{
		cerr << "Failed to open the file." << endl;
		return 1;
	}
	file << payroll_tobe_added << endl;
	file.close();
}

// printing specific lines from data file
void printLinesFromDataFile(int startLine, int endLine)
{
	fstream file("data.txt", ios::in);
	if (!file)
	{
		cerr << "Error: Could not open file!" << endl;
		return;
	}

	string line;
	int currentLine = 1;

	while (getline(file, line))
	{
		if (currentLine >= startLine && currentLine <= endLine)
		{
			cout << line << endl;
		}
		if (currentLine > endLine)
			break; // Stop reading if past endLine
		currentLine++;
	}

	file.close();
}

// printing specific lines from payrollslips file
void printLinesFromPayrollFile(const string text)
{
	globalFunctions object;
	string input = object.readFileToString("Payrollslips.txt");
	vector<string> result = object.split(input, ",");
	const int resultSize = result.size();
	vector<string> finalResult;
	for (size_t i = 0; i < resultSize; ++i)
	{
		if (object.searchKeyword(result[i], text, true))
		{
			finalResult.push_back(result[i]);
		}
	}
	const int finalResultSize = finalResult.size();
	if (finalResultSize > 0)
	{
		for (size_t i = 0; i < finalResultSize; ++i)
		{
			cout << finalResult[i] << endl;
		}
	}
	else
	{
		cout << "Record not found." << endl;
	}
}

// searching any text in a file and retun line number
int searchStartLine(string &searchText)
{
	fstream file("data.txt", ios::in);
	if (!file.is_open())
	{
		cerr << "Error: Unable to open file " << endl;
		return 1;
	}

	string line;
	int lineNumber = 0; // To track the line number
	bool found = false;

	while (getline(file, line))
	{
		lineNumber++;
		if (line.find(searchText) != string::npos)
		{ // Check if the line contains the search text
			found = true;
			return lineNumber;
		}
	}
	if (!found)
	{
		cout << "Text \"" << searchText << "\" not found in the Database." << endl;
	}
	file.close(); // Close the file
}


// searching any text in data file and return messege 
int searchId(string &searchText)
{
	fstream file("data.txt", ios::in);
	if (!file.is_open())
	{
		//cerr << "Error: Unable to open file " << endl;
		return 404;
	}

	string line;
	int lineNumber = 0; // To track the line number
	bool found = false;

	while (getline(file, line))
	{
		lineNumber++;
		if (line.find(searchText) != string::npos)
		{ // Check if the line contains the search text
			found = true;
			
		}
	}
	if (!found)
	{
		return 505;
	}
	file.close(); // Close the file
}

// Main menu of the Program

void starting_options()
{
	globalFunctions object;

	int choice;
	string text;
	string confirm;
	employee obj;
	string fileName = "data.txt";
	cout << "\nEnter your choice:-\n1. Add Employee\n2. Show Employee\n3. Delete Employee\n4. Edit Employee Data\n5. Payroll slip\n6. Exit" << endl;
	cin >> choice;
	switch (choice)
	{
	case 2:
		cin.ignore(100, '\n'); // Clear input buffer
		cout << "Enter name of the employee(as it is) to search:- " << endl;
		getline(cin, text);
		printLinesFromDataFile(searchStartLine(text) - 3, searchStartLine(text) + 13);
		
		break;
	case 5:
		cin.ignore(100, '\n'); // Clear input buffer
		cout << "Enter the id of the employee:- " << endl;
		getline(cin, text);
		printLinesFromPayrollFile(text);
		
		break;
	case 4:
		fileName = "data.txt";
		cin.ignore(100, '\n'); // Clear input buffer
		cout << "Enter id to search:- " << endl;
		getline(cin, text);
		if(searchId(text) == 404){
			cout<<"Error: Unable to open file."<<endl;
			break;
		}else if(searchId(text) == 505){
			cout<<"Entered ID not found in the Database."<<endl;
			break;
		}else{
				printLinesFromDataFile(searchStartLine(text) - 2, searchStartLine(text) + 14);
			cout << "do you want to edit above data.y/n" << endl;
			cin >> confirm;
			if (confirm == "Y" || confirm == "y")
			{
				obj.getEdittedData();
				editLinesInFile(fileName, searchStartLine(text) + 1, searchStartLine(text) + 11, obj.newData);
				editLinesInFile("PayrollSlips.txt", searchStartLine(text) + 1, searchStartLine(text) + 7, obj.updatedPayrollData);
				cout << "Data updated successfully!" << endl;
			}
			else if (confirm == "n" || confirm == "N")
			{
				break;
			}
		else
		{
			cout << "wrong choice" << endl;
		}
		
			break;
		}
		break;
	case 6:
		exit(0);
		break;
	case 1:
		cout << "Enter the number of employees to be added: " << endl;
		cin >> obj.employees_tobe_added;
		for (int i = 1; i <= obj.employees_tobe_added; ++i)
		{
			obj.getEmployeeData(i);
			obj.setId();
			appendEmployee(obj.generateRecord("Record"));
			appendPayroll(obj.generateRecord("Payroll"));
			// updateRecordsCount(obj.employees_tobe_added);
			updateRecordsCount(1);
			cout << "Record Added successfully." << endl;
		}
		
		break;
	case 3:
		string input = object.readFileToString("data.txt");
		vector<string> result = object.split(input, ",");
		const int resultSize = result.size();
		cout << "Please enter the employee ID :-" << endl;
		string employeeID;
		cin >> employeeID;
		for (size_t i = 0; i < resultSize; ++i)
		{
			if (object.searchKeyword(result[i], employeeID, true))
			{
				cout << result[i] << endl;
				object.deleteContentFromFile("data.txt", result[i] + ",", "deletedData.txt");
				cout << "Record deleted successfully" << endl;
			}
		}
		string payrollInput = object.readFileToString("PayrollSlips.txt");
		vector<string> payrollResult = object.split(payrollInput, ",");
		const int payrollResultSize = payrollResult.size();
		for (size_t i = 0; i < payrollResultSize; ++i)
		{
			if (object.searchKeyword(payrollResult[i], employeeID, true))
			{
				object.deleteContentFromFile("PayrollSlips.txt", payrollResult[i] + ",","deletedPayrolls.txt");
			}
		}
		
		break;
	}
}
int main()
{
	while(1){
		starting_options();
	}
	
	return 0;
}
