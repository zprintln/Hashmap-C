// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf output. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
// - You may add any helper functions that you think you need
//   (if any, or otherwise for debugging)
// ==================================================
#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// An entry consisting of a key-value pair.
// This is specifically for a (char*, char*) key-value pair
typedef struct pair {
    char* key;
    char* value;
} pair_t;

// Each node holds a key and a value
typedef struct node {
    pair_t* kv; // key/value pair
    struct node* next;
} node_t;


//hash function that will put a key into a bucket
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hashFunctionPointer)(char*, int); 

//Chained implementation of a hashmap
typedef struct hashmap {
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way -- an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
} hashmap_t;

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
// The algorithm is:
//  - allocate memory for our hashmap
//  - set the number of buckets
//  - initialize our array of lists for each bucket
//  - setup our hash function to point to our stringHash function
//  - return new map that we have created
hashmap_t* hashmap_create(unsigned int _buckets) {
    
    //malloc the hashmap
	hashmap_t* map = (hashmap_t*)malloc(sizeof(hashmap_t));

    //set the number of buckets in our hashmap
    map -> buckets = _buckets;

    //malloc the array of nodes for the hashmap
    map -> arrayOfLists = (node_t**)malloc(sizeof(node_t*) * map -> buckets);
   
    //initialize each bucket in the hashmap to NULL
    for(int i = 0; i < map -> buckets; i++){
        map -> arrayOfLists[i] = NULL;
    }

    //initialize the hashmap hash function 
    map -> hashFunction = stringHash;

    //return our hashmap
    return map;
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap) {

   //if hashmap is NULL, return
   if(_hashmap == NULL){
        return;
   }

   //iterate through entire list
   for( int i = 0; i < _hashmap -> buckets; i++){
        //create a temp node to represent the head of this list of nodes
        node_t* head = _hashmap -> arrayOfLists[i];

        //if bucket is not NULL, free each node in each bucket
	    //for each node in the list, free the data from memory
	    while(head != NULL){
		    //create a temp itr node to delete
            node_t* deleteNode = head;
            //set head to the next node 
		    head = head -> next;
            //free the key
            free(deleteNode->kv->key);
            //free the value
            free(deleteNode->kv->value);
            //free the key/value pair
            free(deleteNode->kv);
            //free the entire node
		    free(deleteNode);
	    }
    }
    //free the array of buckets
    free(_hashmap -> arrayOfLists);

    //free the entire hashmap
    free(_hashmap);
}


// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' if the hashmap is NULL
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key) {

	if(_hashmap == NULL){
        return -9999;
    }

    //call the _hashmap's hash function on the key
    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    
    //create an iterator node
    node_t* itr = _hashmap->arrayOfLists[bucket];

    //check if the key exists in the bucket yet
    while(itr != NULL){
        //if it does, return 1
        if(strcmp(itr->kv->key, key) == 0){
            return 1;
        }
        //if it is not there, check next node
        itr = itr -> next;
    }
    //if end of list is reached, and key is not found
    //key does not exist in the list yet, return 0
    return 0;
}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
   //If key has already been entered, return
   if(hashmap_hasKey(_hashmap, key) == 1){
        return;
    }
    // Create / malloc a new 'pair_t'
    pair_t* newPair = (pair_t*)malloc(sizeof(pair_t));

    //malloc the attributes of the pair 
    newPair-> key = (char*)malloc(strlen(key) * sizeof(char)+1); // Adding +1 for the null terminator
    newPair-> value = (char*)malloc(strlen(value) * sizeof(char)+1); // Adding +1 for the null terminator

    // Copy the string passed by the user to our node using strcpy
    strcpy(newPair->key, key); 
    strcpy(newPair->value, value); 

    // Create a new node
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->next = NULL;
    newNode->kv = newPair;

    // Determine bucket to place newNode in using hashMap hashFunction
    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);

    //create an iterator node and set it to head of the list
    node_t* itr = _hashmap->arrayOfLists[bucket];

    //if there are no nodes in the list yet, add the first value
    if(itr == NULL){

        _hashmap->arrayOfLists[bucket] = newNode;
    }
    //if there is already a list of values in the bucket, 
    //insert value into the bucket at the end of the list 
    else{
        
        //iterate through the list till the end of list is reached and insert newNode
        while(itr -> next != NULL){
            itr = itr -> next;
        }
        //insert new node at end of the list
        itr -> next = newNode;
    }
}

// Return a value from a key 
// Returns NULL if the _hashmap is NULL
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key) {
	//check if hashmap is null
    if(_hashmap == NULL){
        return NULL;
    }
    //if the key exists in the hashmap
    if(hashmap_hasKey(_hashmap, key) == 1){
        //call the _hashmap's hash function on the key
        unsigned int bucket = _hashmap->hashFunction(key, _hashmap -> buckets);

        //create an iterator node
        node_t* itr = _hashmap -> arrayOfLists[bucket];

        //iterate through the list of nodes until key is found
        while(itr != NULL){
            //check if the itr node key matches the input key
            if(strcmp(itr->kv->key, key) == 0){
                //if it does, return the value from the key 
                return itr->kv->value;
            }
            //otherwise, iterate to next node in bucket
            itr = itr -> next;
        }
    }
    //if here, key does not exist in the bucket
    return NULL;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key) {
    if(_hashmap == NULL){
        return;
    }
    //call hashmap_hasKey function to determine if key exists
    if(hashmap_hasKey(_hashmap, key) == 0){
        //key does not exist
        return;
    }
    //call the _hashmap's hash function on the key to determine bucket it is in
    unsigned int bucket = _hashmap -> hashFunction(key, _hashmap -> buckets);

    //create an two ptrs to nodes
    //one represents the node to be deleted and one represents the node before the delete node
    node_t* deleteNode = _hashmap -> arrayOfLists[bucket];
    node_t* nodeBefore = NULL;

    //iterate through list until key is reached
    while(deleteNode != NULL && strcmp(deleteNode->kv->key, key) != 0){
        //set node before to delete node and move delete node to the next node in the list 
        nodeBefore = deleteNode;
        deleteNode = deleteNode -> next;
    }
    if(nodeBefore == NULL){
        //if node to be deleted is the first node in the list, set the head of the list to NULL 
        _hashmap -> arrayOfLists[bucket] = deleteNode -> next;

    }
    else{
        //if it's not the first node in the list,
        //rewire nodeBefore to the deleteNode's next node
        nodeBefore -> next = deleteNode -> next;
    }
    //finally,
    //free the deleteNode from memory 
    free(deleteNode->kv->key);
    free(deleteNode->kv->value);
    free(deleteNode->kv);
    free(deleteNode);
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue) {
    //If hashmap is null, return immediately
	if(_hashmap == NULL){
        return;
    }
    //Call hashmap_hasKey function to determine if key exists
    if(hashmap_hasKey(_hashmap, key) == 0){
        //key does not exist
        return;
    }
    //if here, key does exist in hashmap!
    else{
        //call the _hashmap's hash function on the key to determine the bucket it is in
        unsigned int bucket = _hashmap -> hashFunction(key, _hashmap -> buckets);

        //create an iterator node
        node_t* itr = _hashmap -> arrayOfLists[bucket];

        //iterate through the list of nodes until key is reached
        while(itr != NULL && strcmp(itr->kv->key, key) != 0){

            itr = itr -> next;
        }
        //free the old value
        free(itr->kv->value);
        //malloc for the size of the new value 
        itr->kv->value = malloc(strlen(newValue) * sizeof(char)+1); // Adding +1 for the null terminator
        //update key with new value 
        strcpy(itr->kv->value, newValue); 
    }

}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	for(int i = 0; i < _hashmap -> buckets; i++){
        printf("Bucket # %d \n", i);
        //create an iterator node
        node_t* itr = _hashmap -> arrayOfLists[i];
        while(itr != NULL){
            //iterate through list to print each key
           printf("\tKey = %s\tValue = %s\n",itr->kv->key,itr->kv->value);
            itr = itr->next;
        }
    }
}

#endif
