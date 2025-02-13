#include "mongodb.h"

MongoDB::MongoDB()
{
    mongocxx::instance instance{};
    client = mongocxx::client{mongocxx::uri{}};
}

static MongoDB* MongoDB::getInstance() {
    if (!instance) {
        instance = new MongoDB();
    }
    return instance;
}
/**
 * Add new user(costumer or seller) to the database[users]
 * @param user the user you want to add.
 */
void MongoDB::insertUser(const User& user)
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

    collection.insert_one(document.view());
}

/**
 *Validate user for the entery by username and password
 * @return the user that is found.
 */
std::unique_ptr<User> MongoDB::validateUser(const std::string& username, const std::string& passwordHash)
{
    auto db = client["food_order_system"];
    auto collection = db["users"];

    bsoncxx::builder::stream::document filter_builder{};
    filter_builder << "username" << username 
                    << "passwordHash" << passwordHash 
                    << bsoncxx::builder::stream::finalize;

    auto result = collection.find_one(filter_builder.view());
    if(result)
    {
        auto doc = result.value();
        std::string fname = doc["firstname"].get_utf8().value.to_string();
        std::string lname = doc["lastname"].get_utf8().value.to_string();
        std::string role = doc["role"].get_utf8().value.to_string();
        double wallet = doc["wallet"].get_double();

        if(role == "costumer")
        {
            return std::make_unique<Costumer>(fname, lname, username, wallet, passwordHash);
        }
        else
        {
           return std::make_unique<Seller>(fname, lname, username, wallet, passwordHash);

        }
        
    }
    else
    {
        std::cerr << "User not found!\n";
        return User();
    }
}   

/**
 * check for the user existance in database by its username.
 * @param username username of the user how want to be find.
 * @return true if exist and false if not exist
 */
bool MongoDB::findUser(const std::string& username)
{
    auto db = client["food_order_system"];
    auto collection = db["users"];

    bsoncxx::builder::stream::document filter;
    filter << "username" << username << bsoncxx::builder::stream::finalize;

    auto result = collection.find_one(filter.view());
    return result.has_value();
}

/**
 * This is for adding food to the food menu by seller.
 * @param food the food that seller wants to add to menu.
 */
void MongoDB::addFoodMenu(const Food& food) 
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

/**
 * Shows the menu list with foodName , seller and quantity.
 */
void MongoDB::foodMenu()
{
    auto db = client["food_order_system"];
    auto collection = db["foodMenu"];
    auto cursor = collection.find({}, BSON("foodName" << 1 << "foodSeller" << 1 << "foodQuantity" << 1));

    for(auto&& doc :: cursor)
    {
        std::cout << bsoncxx::to_json(doc) << '\n';
    }
}

/**
 * find the foods of the special seller
 * @param sellername name of the seller who wants foods
 * @return vector of the foods of this seller by name and price
 */
std::vector<Food> MongoDB::findFoodBySeller(const std::string& sellername)
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

void MongoDB::orderFood(const User& user, const Food& food)
{
    auto db = client["food_order_system"];
    auto collection = db["soldFood"];

    bsoncxx::builder::stream::document doc{};
    doc << "costumer" << user.getFirstName() + " " + user.getLastName()
        << "seller" << food.getSeller()
        << "foodname" << food.getName()
        << "price" << food.getPrice()
        << bsoncxx::builder::stream::finalize;

    collection.insert_one(doc.view());
}

std::vector<Food> MongoDB::getSoldFood(const std::string& seller)
{
    auto db = client["food_order_system"];
    auto collection = db["soldFood"];
    std::vector<Food> soldFoods;

    bsoncxx::builder::stream::document filter;
    filter << "seller" << seller;

    auto cursor = collection.find(filter.view());

    for(auto&& doc : cursor)
    {
        std::string foodName = doc["foodname"].get_utf8().value.to_string();
        double foodPrice = doc["price"].get_double();
        soldFoods.emplace_back(foodName, foodPrice);
    }
    return soldFoods;
}

std::vector<Food> MongoDB::getCostumerOrder(const std::string& costumer)
{
    auto db = client["food_order_system"];
    auto collection = db["soldFood"];
    std::vector<Order> orders;

    bsoncxx::builder::stream::document filter;
    filter << "costumer" << costumer;

    auto cursor = collection.find(filter.view());

    for(auto&& doc : cursor)
    {
        std::string foodName = doc["foodname"].get_utf8().value.to_string();
        double foodPrice = doc["price"].get_double();
        orders.emplace_back(foodName, foodPrice);
    }
    return orders;
}