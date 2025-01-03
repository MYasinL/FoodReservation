#include <unordered_map>
#include <string>
#include "user.cpp"
#include <iostream>
#include <regex>

class UserSystem
{
private:
	std::unordered_map <std::string, User*> users;

	std::string getPassword()
	{
		std::string password;
		char ch;

		std::cout << "Enter Password: ";

		while((ch = getchar()) != '\n' && ch != EOF)
		{
			password.push_back(ch);
			std::cout << '*';
		}

		std::cout << '\n';

		return password;
	}

	void registerUser()
	{
		std::string fname, lname, username, password, role;
		getUserDetails(fname, lname, username, password, role);
		// not complete
	}

	bool checkPassword(std::string pwd)
	{
		std::cout << "Confirm password: ";
		std::string pwdconfirm = getPassword();
		std::regex pwdPattern ("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.{8,})");

		if(pwd != pwdconfirm)
		{
			std::cout << "Password mismatch!\nTry again.\n";
			return false;
		}
		if(!regex_match(pwd, pwdPattern))
		{
			std::cout << "Invalid Password\n";
			return false;
		}
		return true;
	}

	bool charUp3(std::string str)
	{
		
		if(str.length() < 3)
		{
			std::cout << "Length should be at least 3 chars!\n";
			return false;
		}
		return true;
	}

	bool isRoleValid(std::string role)
	{
		if(!(role == "costumer" || role == "seller"))
		{
			std::cout << "Role can be \"costumer\" or \"seller\"\n";
			return false;
		}
		return true;
	}

	void getUserDetails(std::string fname, std::string lname, std::string username, std::string password, std::string role)
	{
		do
		{
			std::cout << "First name: ";
			std::cin >> fname;
			std::cout << "LastName: ";
			std::cin >> lname;
		}while(!charUp3(fname) || !charUp3(lname));

		do
		{
			std::cout << "Role: ";
			std::cin >> role;
		}while(!isRoleValid(role));
		
		do
		{
			std::cout << "Password: ";
			password = getPassword();
		}while(!checkPassword(password));

	}
};


