#include <string>
#include "user.cpp"
// #include "mongodb.cpp"

class Customer : public User
{
public:
	Customer(std::string fname, std::string lname, std::string pwd) : User(fname, lname, pwd) {}

	void displayMenu()
	{
		std::cout << "1.Available food menu\n" 
                << "2.Order by spicific seller\n"
                << "3.Order history\n"
                << "4.Increase wallet balance\n"
                << "5.View profile\n"
                << "6.Edit profile\n\n";
	}

	void menuAction()
	{
		displayMenu();
		std::cout << "Enter command: ";
		int command = getCommand();

		switch(command)
		{
			case 1:
				availableFoodList();
				break;
			case 2:
				orderBySeller();
				break;
			case 3:
				orderHistoryList();
				break;
			case 4:
				increaseBalance();
				break;
			case 5:
				viewProfile();
				break;
			case 6:
				editProfile();
				break;
			default:
				std::cout << "The command is not exist.\n";
                break;
		}
	}

private:
	void availableFoodList()
	{
		MongoDB* db = MongoDB::getInstance();

		db->foodMenu(); // this is for printing food in data base(name & quantity)
	}

	void orderBySeller()
	{

	}

	void orderHistoryList()
	{

	}

	void increaseBalance()
	{

	}

};
