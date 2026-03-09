# HashingLab
Hashing Lab for Week 5 CISC 197
### Part 1: Class Structure
Most of this was given, I added the following to meet the task labeled in Part 5 and Part 6.
```cpp
        int getCollisionCount() const;
        void getBucketSize() const;
        int getCapacity() const;
```
### Part 2
Given, no changes made.

### Part 3: Insert and Collision Handling
Separate Chaining was utilized in our given Hash Table class for collision handling. We created buckets through our list chaining, allowing us to handle collisions through a different bucket per index. Multiple key-val pairs can then be stored in the same bucket when a collision does occur. When two or more keys produce the same index a collision occurs, but we handle it through storing the new pair at the list at that index. Our goal is even distribution with our hash function if we exceed a favorable distribution/loadfactor the table is rehashed to reduce our collisions.
1. Compute hash index
2. Search bucket to see if key exists already
3. Update value if so
4. else append a new pair to list and increase size
5. rehash if load factor exceed .75
```cpp
void HashTable::insert(const string& key, int value){
    int index = hashFunction(key);
    
    //Check if key already exist. If key already exists, update value instead of duplicating
    for(auto& pair : table[index]) {
        if(pair.first == key){
            pair.second = value;
            return;
        }
    }
    //collision occurence, already contains 1 element. 2 or more keys produced same hash index.
    if(!table[index].empty()) collisionCount++;
    
    //add element to back of list
    table[index].push_back({key, value});
    currentSize++;
    
    if (loadFactor() > .75){
        rehash();
    }

}
```
### Part 4: Resizing(Rehashing)
As asked in the task, if we need to rehash we want to double table capacity and reinsert all existing elements, resetting our collision counter before running our insert function, in the case we have collisions in this process. To do so we need to store the old tables information into temp vars, allowing us to reinsert through iteration each key-value in the old table. For each bucket in the old table, in the case of shared indices, and for each pair in each bucket, we insert that key-value pair into our new doubled in size table. Each key will have a new indice since capacity has changed (hash % capacity). 
```cpp
void HashTable::rehash() {
    int oldC = capacity;
    //double table      
    capacity *= 2;

    //temp vector to retain info
    vector<list<pair<string, int>>> oldT = table;

    table.clear();
    table.resize(capacity);
    currentSize = 0;
    //Reset collision counter appropriately
    collisionCount = 0;
    //reinsert everything, which makes a new hash for every key since our capacity changes
    for(auto &bucket : oldT){
       for(auto &pair : bucket){
        insert(pair.first, pair.second);
       } 
    }
}

```

### Part 5: Testing
The comments within this code block coincide with each required task of this section, some of which relate to getter functions implemented from the starting code. These are rather simple and follow the traditional structure of:

```cpp
int HashTable::size() const{
    return currentSize;
}
```

```cpp
int main(){
    HashTable ht;
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
    cout << "Removing student and searching for student" << endl;
    ht.remove("student50");
    cout << ht.search("student50") << endl << endl;
    //print table for verification as well
    ht.printTable();
    cout << endl;
}
```

### Part 6: Experimental Analysis and Functions created for recording
Created Random strings through the following function: 
```cpp
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
```

Tested all requested input types through the following function:
```cpp
void htTest(vector<string> keys){
    HashTable testHash;

    for(int i = 0;i < keys.size(); i++) testHash.insert(keys[i], i);

    cout << "Collisions: " << testHash.getCollisionCount() << endl;
    testHash.getBucketSize();
}
```

main() implementation/addition
```cpp
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
```
#### Part 6: Explanation/Analysis
All 3 input types produced the same average bucket length because the polynomial hash inherently distributes fairly even throughout the table. Sequential and prefix keys differ only in their prefix, but each character still is used in calculation of the hash value, allowing even distribution across buckets. Random keys had more collisions because randomnly generated strings may have the same index with the modulo operation for our hash function. 

I know a video wasn't necesarry, but revisiting the material and calling back on information learned helps me remember better, so I made one regardless.
Please let me know if there are any clarifications or improvements I can make, thank you. 
Youtube Link: https://youtu.be/Dh2zwBYmFps
