#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <openssl/md5.h>
#include <unistd.h> //for sleep
#include "mongodb.h"
#include "food.h"

// class MongoDB;

class User
{
protected:
	std::string firstName;
	std::string lastName;
	std::string passwordHash;
	std::string username;
	std::string role; //"costumer" or "seller"
	double wallet;

public:
	User(std::string firstName, std::string lastName, std::string password)
	: firstName(firstName), lastName(lastName), wallet(0.0)
	{
		passwordHash = hashPassword(password);
		username = generateUsername();
	}

	User(std::string firstName, std::string lastName, std::string role, double wallet, std::string username)
	: firstName(firstName), lastName(lastName), role(role), wallet(wallet), username(username)
	{}

	User(std::string firstName, std::string lastName, std::string role, double wallet, std::string username, std::string hashPwd)
	: firstName(firstName), lastName(lastName), role(role), wallet(wallet), username(username), passwordHash(hashPwd)
	{}

	User() {}

	virtual void displayMenu() = 0;
	virtual void menuAction() = 0;


	static std::string hashPassword(const std::string& password)
	{
		unsigned char digest[MD5_DIGEST_LENGTH];
		MD5(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), digest);

		std::ostringstream os;
		for(int i = 0; i < MD5_DIGEST_LENGTH; ++i)
		{
			os << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
		}
		return os.str();
	}

	virtual void viewProfile()
	{
		std::cout << "Username: " << username << "\n"
			<< "Name: " << firstName << " " << lastName << "\n"
			<< "Wallet: " << wallet << "\n";
	}
	virtual void editProfile()
	{

		
	}

protected:
	
	std::string generateUsername()
	{
		MongoDB* db = MongoDB::getInstance();
		std::string base = firstName.substr(0,3) + lastName.substr(0,3);

		std::string unique = base;

		while(db->findUser(base))
		{
			unique = base + std::to_string(std::rand());
		}
		return unique;
	}
	int getCommand()
	{
		std::string input;
		int number;

		while(true)
		{
			std::getline(std::cin, input);
			try
			{
				number = std::stoi(input);
				break;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << ' ' << "Enter a valid number please!" << '\n';
			}
			sleep(1);
			std::cout << "\033[A\033[K"; // del the line error and the entry line
            std::cout << "\033[A\033[K";

		}
		return number;
	}
	//getters
	std::string getFirstName() {return firstName;}
	std::string getLastName() {return lastName;}
	std::string getPasswordHash() {return passwordHash;}
	std::string getUsername() {return username;}
	std::string getRole() {return role;}
	double getWallet() {return wallet;}

};

#endif