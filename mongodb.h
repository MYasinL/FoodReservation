#ifndef MONGODB_H
#define MONGODB_H


#include <mongocxx/client.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
// #include <mongocxx/stdx.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>

class Food;
class User;

class MongoDB
{
private:
    static MongoDB* instance;
    mongocxx::client client;
    MongoDB();
public:
    static MongoDB* getInstance();
    void insertUser(const User& user);
    std::unique_ptr<User> validateUser(const std::string& username, const std::string& passwordHash);
    bool findUser(const std::string& username);
    void addFoodMenu(const Food& food);
    void foodMenu();
    std::vector<Food> findFoodBySeller(const std::string& sellername);
    void orderFood(const User& user, const Food& food);
    std::vector<Food> getSoldFood(const std::string& seller);
    std::vector<Food> getCostumerOrder(const std::string& costumer);
};
#endif