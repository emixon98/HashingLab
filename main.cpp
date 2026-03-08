#include <vector>
#include <list>
#include <string>
using namespace std;


/*You will implement a HashTable class that stores:

string keys
int values
You are NOT allowed to use:
std::unordered_map
std::map
*/

// Part 1 (Given)
class HashTable {
    private:
        vector<list<pair<string, int>>> table;
        int currentSize;
        int capacity;
        int collisionCount;

        int hashFunction(const string& key) const;
        void rehash();

    public:
        HashTable(int size = 11);

        void insert(const string& key, int value);
        bool remove(const string& key);
        int search(const string& key) const;
        double loadFactor() const;
        int size() const;
        bool isEmpty() const;
        void printTable() const;
};

HashTable::HashTable(int n) {
    capacity = n;
    table.resize(capacity);

    currentSize = 0;
    collisionCount = 0;
}

// Part 2 (Given)
int HashTable::hashFunction(const string& key) const {
    const int prime = 31;
    long long hash = 0;

    for (char c : key) {
        hash = hash * prime + c;
    }

    return hash % capacity;
}

//Part 3 To-do

//implement insert and chaining

//Use separate chaining (vector<list<>>)

//If inserting into a non-empty bucket, increment collisionCount
//If key already exists, update value instead of duplicating


//implement remove


//implement search


//implement loadFactor



// implement size


//implement is empty


//implement printable



//implement rehash

//Part 4 To -do
/* 
When: loadFactor() > 0.75
You must:
Double the table capacity
Reinsert all existing elements
Reset collision counter appropriately
*/





int main(){

// Part 5

/*
In main():

Insert at least 100 words
Print:
    Table capacity
    Number of elements
    Load factor
    Total collisions
Search for:
    Existing key
    Non-existing key
    Remove some keys and verify correctness

/* Part 6
Test three input types:
Random strings
Sequential keys (e.g., student1, student2, ...)
Same prefix keys (e.g., data_0001, data_0002, ...)

Record:
Total collisions
Maximum bucket size
Average bucket length
Write a short explanation (1--2 paragraphs) describing what you observe.

*/
//Using std::unordered_map results in major deduction

}


