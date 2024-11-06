#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility> // for std::pair
using namespace std;

class UserHashTable {
public:
    // Constructor initializes the hash table with a fixed size
    UserHashTable(size_t size = 100) : table(size) {}

    // Method to add or update a user profile
    void addUser(const string& username, const string& profileData) {
        size_t index = hash(username);
        
        // Check if username already exists in the chain and update if found
        for (auto& pair : table[index]) {
            if (pair.first == username) {
                pair.second = profileData;
                return;
            }
        }
        
        // If username not found, add new entry
        table[index].emplace_back(username, profileData);
    }

    // Method to retrieve user profile data by username
    string getUser(const string& username) const {
        size_t index = hash(username);
        
        // Search the chain at this index for the username
        for (const auto& pair : table[index]) {
            if (pair.first == username) {
                return pair.second;
            }
        }
        
        // Return empty string if user not found
        return "User not found";
    }

private:
    // Hash function that returns an index for a given username
    size_t hash(const string& username) const {
        size_t hashValue = 0;
        for (char ch : username) {
            hashValue = hashValue * 31 + ch;
        }
        return hashValue % table.size();
    }

    vector<list<pair<string, string>>> table; // Each slot holds a list of (username, profileData) pairs
};

int main() {
    // Create a user hash table
    UserHashTable userTable;

    // Add users
    userTable.addUser("alice123", "Alice, Age: 30");
    userTable.addUser("bob456", "Bob, Age: 25");

    // Retrieve user profiles
    cout << userTable.getUser("alice123") << endl;  // Output: Alice, Age: 30
    cout << userTable.getUser("bob456") << endl;    // Output: Bob, Age: 25
    cout << userTable.getUser("unknown") << endl;   // Output: User not found

    return 0;
}
