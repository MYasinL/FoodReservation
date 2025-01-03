#include <mongocxx/client.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>


class MongoDB
{
private:
    static MongoDB* instance;
    mongocxx::client client;
    MongoDB()
    {
        mongocxx::instance instance{};
        client : mongocxx::client{mongo::uri{}};
    }
public:
    static MongoDB* getInstance() {
        if (!instance) {
            instance = new MongoDB();
        }
        return instance;
    }

    void insertUser(const User user)
    {
        auto db = client["food_order_system"];
        auto collection = db["users"];

        bsoncxx::builder::stream::document document{};
        document << "username" << user.getUsername()
                << "firstname" << user.getFirstName()
                << "lastname" << user.getLastName()
                << "passwordHash" << user.getPasswordHash()
                << "role" << user.getRole()
                << "wallet" << 0.0
                << bsoncxx::builder::stream::finalize;

        collection.insert_one(document.view())
    }

    bool validateUser(const std::string& username, const std::string& passwordHash)
    {
        auto db = client["food_order_system"];
        auto collection = db["users"];

        bsoncxx::builder::stream::document filter_builder{};
        filter_builder << "username" << username << "passwordHash" << passwordHash << bsoncxx::builder::stream::finalize;

        auto result = collection.find_one(filter_builder.view());
        return result.has_value();
    }   

    bool findUser(const std::string& username)
    {
        auto db = client["food_order_system"];
        auto collection = db["users"];

        bsoncxx::builder::stream::document filter;
        filter << "username" << username << bsoncxx::builder::stream::finalize;

        auto result = collection.find_one(filter_builder.view());
        return result.has_value();

    }

    void addFoodMenu(const Food food) 
    {
        auto db = client["food-order-system"];
        auto collection = db["foodMenu"];

        bsoncxx::builder::stream::document filter_builder;
        filter_builder << "foodName" << food.getName();
        auto filter = filter_builder.view();

        bsoncxx::builder::stream::document update;
        update << "$inc" << bsoncxx::builder::stream::open_document
                << "foodQuantity" << 1 
                << bsoncxx::builder::stream::close_document;

        auto result = collection.update_one(filter, update.view());

        if(result->modified_count() == 0)
        {
            bsoncxx::builder::stream::document doc{};
            doc << "foodName" << food.getName()
                << "foodSeller" << food.getSeller()
                << "foodPrice" << food.getPrice()
                << "foodQuantity" << 1;

            collection.insert_one(doc.view());
        }
    }

    // shows the menu list with just foodName
    std::list foodMenu()
    {
        auto db = client["food_order_system"];
        auto collection = db["foodMenu"];
        auto cursor = collection.find({}, BSON("foodName" << 1 << "foodSeller" << 1 << "foodQuantity" << 1));

        for(auto&& doc :: cursor)
        {
            std::cout << bsoncxx::to_json(doc) << '\n';
        }
    }

    std::vector<Food> findFoodBySeller(const std::string& sellername)
    {
        std::vector<Food> foods;

        auto db = client["food_order_system"];
        auto collection = db["foodMenu"];

        bsoncxx::builder::stream::document filter;
        filter << "foodSeller" << sellername;

        auto cursor = collection.find(filter.view());

        for(auto&& doc : cursor)
        {
            std::string foodName = doc["foodName"].get_utf8().value.to_string();
            double foodPrice = doc["foodPrice"].get_double();
            foods.emplace_back(foodName, foodPrice);
        }
        return foods;
    }



};