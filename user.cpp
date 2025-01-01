
class User
{
private:
	std::string firstName;
	std::string lastName;
	std::string passwordHash;
	std::string username;
	std::string role; //"customer" or "seller"
	double wallet;
public:
	User(std::string firstName, std::string lastName, std::string password): firstName(firstName), lastName(lastName), wallet(0.0)
	{
		passwordHass = hashPassword(password);
		username = generateUsername();
	}

	virtual void displayMenu() = 0;
	virtual void viewProfile()
	{
		std::cout << "Username: " << username << "\n"
			<< "Name: " << firstName << " " << lastName << "\n"
			<< "Wallet: " << wallet << "\n";
	}

	std::string getUsername() {return username;}
	double getBalance() {return wallet;}

private:
	std::string hashPassword(const std::string& password);
	std::string generateUsername();

};


