#include <iostream>
#include <string>
#include <unistd.h> //for sleep

class User
{
protected:
	std::string firstName;
	std::string lastName;
	std::string passwordHash;
	std::string username;
	std::string role; //"customer" or "seller"
	double wallet;
public:
	User(std::string firstName, std::string lastName, std::string password): firstName(firstName), lastName(lastName), wallet(0.0)
	{
		passwordHash = hashPassword(password);
		username = generateUsername();
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

	std::string getUsername() {return username;}
	double getBalance() {return wallet;}

protected:
	virtual void displayMenu() = 0;
	virtual void menuAction() = 0;
	std::string hashPassword(const std::string& password);
	std::string generateUsername();
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

};


