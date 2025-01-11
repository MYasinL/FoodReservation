#include <string>
#include "user.cpp"

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
		MongoDB* db = MongoDB::getInstance();
		std::string seller;
		std::string foodname;
		Food buyFood;

		std::cout << "Which seller you want? ";
		std::cin >> seller;

		std::vector<Food> foods = db->findFoodBySeller(seller);
		if(foods.empty())
		{
			std::cout << "no seller or no food.\n";
			return;
		}
		std::cout << "**Foods by " << seller << " **\n";

		for(Food food : foods)
		{
			std::cout << food.getName() << ":  " << food.getPrice();
		}

		std::cout << "which food do you want: ";
		std::cin >> foodname;

		for(Food food : foods)
		{
			if (food.getName == foodname)
			{
				buyFood = food;
				break;
			}
		}
		if(buyFood == nullptr)
		{
			std::cout << "This food is not valid.\n";
			return;
		}

		db->orderFood(this, buyFood);

	}

	void orderHistoryList()
	{
		MongoDB* db = MongoDB::getInstance();
		std::vector<Food> orders = db->getCostumerOrder(this.getfirstName + this.getLastName);
		if(orders.empty())
		{
			std::cout << "NO Order!\n";
			return;
		}

		std::cout << "**Orders**\n";
		for(Food food : orders)
		{
			std::cout << food.getName() << ":  " << food.getPrice();
		}
	}

	void increaseBalance()
	{

	}

};
