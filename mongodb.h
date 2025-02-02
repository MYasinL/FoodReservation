#include <mongocxx/client.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
// #include <mongocxx/stdx.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>
#include "user.h"

class MongoDB
{
private:
    static MongoDB* instance;
    mongocxx::client client;
    MongoDB();
public:
    static MongoDB* getInstance();
    void insertUser(const User user);
    User validateUser(const std::string& username, const std::string& passwordHash);
    bool findUser(const std::string& username);
    void addFoodMenu(const Food food);
    void foodMenu();
    std::vector<Food> findFoodBySeller(const std::string& sellername);
    void orderFood(const User user, const Food food);
    std::vector<Food> getSoldFood(const std::string& seller);
    std::vector<Food> getCostumerOrder(const std::string& costumer);


};