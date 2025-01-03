#include "user.cpp"

class Seller : public User 
{
public:
    Seller(std::string fname, std::string lname, std::string pwd) : User(fname, lname, pwd) {};

    void displayMenu()
    {
        std::cout << "1.Add food\n"
                << "2.View sold foods\n"
                << "3.View wallet balance\n"
                << "4.View profile\n"
                << "5.Edit profile\n\n";
    }

    void menuAction()
    {
        displayMenu();
        std::cout << "Enter a command: ";
        int command = getCommand();

        switch(command)
        {
            case 1:
                addFood();
                break;
            case 2:
                soldFoodList();
                break;
            case 3:
                viewBalance();
                break;
            case 4:
                viewProfile();
                break;
            case 5:
                editProfile();
                break;
            default:
                std::cout << "The command is not exist.\n";
                break;
        }
    }

private:
    void addFood()
    {

    }

    void soldFoodList()
    {

    }

    void viewBalance()
    {

    }

    
};