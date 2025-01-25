#include <iostream>
#include <string>
#include <iomanip>
#include <openssl/md5.h>
#include <unistd.h> //for sleep
#include "mongodb.cpp"

// class MongoDB;

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
	std::string hashPassword(const std::string& password)
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

	std::string generateUsername()
	{
		MongoDB db = MongoDB::getInstance();
		std::string base = firstName.substr(0,3) + lastName.substr(0,3);

		std::string unique = base;

		while(db.findUser(base))
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

class Food {
public:
    std::string name;
	std::string seller;
    int quantity;
    double price;

    Food(std::string n, std::string seller, double p) : name(n), price(p), seller(seller) {}
	Food(std::string n, double p) : name(n), price(p) {}

	void showFood()
	{
		std::cout << name << " -> " << price;
	}
private:
	std::string getName() {return name;}
	std::string getSeller() {return seller;}
	int getQuantity() {return quantity;}
	double getPrice() {return price;}
};

class Order
{
private:
	std::string costumer;
	Food food;

public:
	Order(std::string un, Food f) : costumer(un), food(f) {}

	std::string getCostumer() {return costumer;}
	Food getFood() {return food;}
};

