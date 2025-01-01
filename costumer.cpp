
class Customer : public User
{
public:
	Customer(std::string fname, std::string lname, std::string pwd) : User(fname, lname, pwd) {}

	void displayMenu()
	{
	}

};
