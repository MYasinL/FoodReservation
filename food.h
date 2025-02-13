#ifndef FOOD_H
#define FOOD_H

#include <string>
#include <iostream>

class Food {
public:
    std::string name;
	std::string seller;
    int quantity;
    double price;

    Food(std::string n, std::string seller, double p) : name(n), price(p), seller(seller) {}
	Food(std::string n, double p) : name(n), price(p) {}
	Food(){}

	void showFood()
	{
		std::cout << name << " -> " << price;
	}
public:
	std::string getName() {return name;}
	std::string getSeller() {return seller;}
	int getQuantity() {return quantity;}
	double getPrice() {return price;}
};

#endif