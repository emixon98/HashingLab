#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;
/*
You are NOT allowed to use:
std::unordered_map
std::map
*/
//Using std::unordered_map results in major deduction

class HashTable {
    private:
    //vector containing list that hold pairs in the form of string, int, pairing stores the vals together
    //.first key, .second val

    //need getters for our private vars since requested in part 5, set/incremented inside of other functions

    //Use separate chaining (vector<list<>>) 
        vector<list<pair<string, int>>> table;
        //elements
        int currentSize;
        //#buckets
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
        void getBucketSize() const;
        int getCapacity() const;
};


HashTable::HashTable(int n) {
    capacity = n;
    table.resize(capacity);

    currentSize = 0;
    collisionCount = 0;
}


//Hashes our keys with a prime number for better distribution, modulo by capacity to ensure fits into a valid index
//if capacity doesnt change same key produces same index
int HashTable::hashFunction(const string& key) const {
    const int prime = 31;
    long long hash = 0;
    //each char in string utilized in hash
    for (char c : key) {
        hash = hash * prime + c;
    }

    return hash % capacity;
}


//add a new key-val pair
void HashTable::insert(const string& key, int value){
    int index = hashFunction(key);
    //Check if key already exist     
    for(auto& pair : table[index]) {
        if(pair.first == key){
            pair.second = value;
            return;
        }
    }
    //collision occurence  
    if(!table[index].empty()) collisionCount++;
    //add element to back of list
    table[index].push_back({key, value});
    currentSize++;
    
    if (loadFactor() > .75){
        rehash();
    }
}


bool HashTable::remove(const string& key){
    int index = hashFunction(key);
    //iterator loop, points to elements in bucket
    for(auto i = table[index].begin(); i != table[index].end(); i++){
        //if first part of pair(key) matches desired, remove
        if(i->first == key){
            table[index].erase(i);
            currentSize--;
            return true;
        }
    }
    return false;
}

int HashTable::search(const string& key) const{
    int index = hashFunction(key);
    for(const auto&pair: table[index]){
        if(pair.first == key){
            return pair.second;
        }
    }
    cout << "Not found" << endl;
    return -1;
}

double HashTable::loadFactor() const{
    //make sure to convert to double so I dont get 0
    return (double)currentSize/capacity;
}

int HashTable::size() const{
    return currentSize;
}

bool HashTable::isEmpty() const{
    return currentSize == 0;
}

int HashTable::getCollisionCount() const{
    return collisionCount;
}

int HashTable::getCapacity() const{
    return capacity;
}

// A bucket is just a term used for the container that hold items hashed to same index, hashed coorelated, handled through chaining
// For Part 6, return max and avg in one function
void HashTable::getBucketSize() const{
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
    cout << "Max bucket size: " << size << endl;
    //total elements / number of buckets
    cout << "Average bucket length: " << avg/capacity << endl;
}

void HashTable::printTable() const{
    for (int i =0; i < capacity; i++){
        //got rid of endl outside 2nd for loop, caused weird formatting for empty buckets
        for(const auto& pair : table[i]){
            cout << "( " << pair.first << ", " << pair.second << " )" << endl;
        }
    }
}

void HashTable::rehash() {
    int oldC = capacity;
    //double table          Double the table capacity
    capacity *= 2;
    //temp vector to retain info
    vector<list<pair<string, int>>> oldT = table;
    table.clear();
    table.resize(capacity);
    currentSize = 0;
    //Reset collision counter appropriately
    collisionCount = 0;
    //reinsert everything, which makes a new hash for every key since our capacity changes
    //Reinsert all existing elements
    for(auto &bucket : oldT){
       for(auto &pair : bucket){
        insert(pair.first, pair.second);
       } 
    }
}

string randomHTKeys(int n){
    //random set
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0,25);
    string randString;
    //'a' and (0, 25) are used to ensure we have letters from a-z
    for(int i=0; i < n; i++){
        char c = 'a' + dist(gen);
        randString+=c;
    }
    return randString;
}
/* Part 6: Random, sequential, and prefix test
Record:
Total collisions
Maximum bucket size
Average bucket length
*/
void htTest(vector<string> keys){
    HashTable testHash;
    for(int i = 0;i < keys.size(); i++) testHash.insert(keys[i], i);

    cout << "Collisions: " << testHash.getCollisionCount() << endl;
    testHash.getBucketSize();
}

int main(){
    HashTable ht;
    //Insert at least 100 words
    //Sequential keys (e.g., student1, student2, ...)
    for(int i = 0; i <100; i++){
        string key = "student" + to_string(i);
        ht.insert(key, i);
    }

// Print:
    cout << "Table Capacity: " << ht.getCapacity() << endl;
    cout << "Number of elements: " << ht.size() << endl;
    cout << "Load factor: " << ht.loadFactor() << endl;
    cout << "Total Collisions: " << ht.getCollisionCount() << endl << endl;

//Search for: Existing, Non-Existing
    cout << "Searching for existing: " << endl;
    cout << ht.search("student1") << endl;
    cout << endl << "Searching for non-existing " << endl;
    cout << ht.search("student120") << endl << endl;

//Remove some keys and verify correctness
    cout << "Removing a student and searching for that student: " << endl;
    ht.remove("student50");
    cout << ht.search("student50") << endl << endl;
    //print table for verification as well
    ht.printTable();
    //50 indeed does not show up
    cout << endl;
//Part 6 use existing structure and ht HashTable to handle sequential keys section
    vector<string> randomKeys;
    //7 letter random string keys
    for(int i=0; i < 100; i++) randomKeys.push_back(randomHTKeys(7));
    vector<string> sequential;
    for(int i=0; i < 100; i++) sequential.push_back("student" + to_string(i));
    vector<string> prefix;
    for(int i=0; i< 100; i++) prefix.push_back("data_" + to_string(i));
    cout << "Testing random keys" << endl;
    htTest(randomKeys);
    cout << endl << "Testing sequential keys" << endl;
    htTest(sequential);
    cout << endl << "Testing prefix keys" << endl;
    htTest(prefix);
}


