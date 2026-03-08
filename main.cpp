#include <vector>
#include <list>
#include <string>
#include <iostream>
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
        int getCollisionCount() const;
        double getBucketSize() const;
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
void HashTable::insert(const string& key, int value){
    int index = hashFunction(key);
    
    for(auto& pair : table[index]) {
        if(pair.first == key){
            pair.second = value;
            return;
        }
    }
    if(!table[index].empty()) collisionCount++;
    
    table[index].push_back({key, value});
    currentSize++;

    if (loadFactor() > .75){
        rehash();
    }

}
//Use separate chaining (vector<list<>>)

//If inserting into a non-empty bucket, increment collisionCount
//If key already exists, update value instead of duplicating


//implement remove
bool HashTable::remove(const string& key){
    int index = hashFunction(key);

    for(auto it = table[index].begin(); it != table[index].end(); it++){
        if(it->first == key){
            table[index].erase(it);
            currentSize--;
            return true;
        }
    }
    return false;
}

//implement search
int HashTable::search(const string& key) const{
    int index = hashFunction(key);

    for(const auto&pair: table[index]){
        if(pair.first == key){
            return pair.second;
        }
    }
    return -1;
}

//implement loadFactor

double HashTable::loadFactor() const{
    return currentSize/capacity;
}

// implement size
//Private function need a getter
int HashTable::size() const{
    return currentSize;
}

//implement is empty
bool HashTable::isEmpty() const{
    return currentSize == 0;
}


int HashTable::getCollisionCount() const{
    return collisionCount;
}

double HashTable::getBucketSize() const{
    double size = 0;
    double avg = 0;
    int total = 0;
    for(auto &bucket : table){
        total++;
        avg += bucket.size();
        if(bucket.size() > size){
            size = bucket.size();
        }
    }
    return size, avg/total;
}
//implement printable

void HashTable::printTable() const{
    for (int i =0; i < capacity; i++){
        for(const auto& pair : table[i]){
            cout << "( " << pair.first << ", " << pair.second << " )";
        }
        cout << endl;
    }
}

//implement rehash

void HashTable::rehash() {
    
}

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


