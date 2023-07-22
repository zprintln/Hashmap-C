Apologies for that oversight. Here's the updated README.md, including information about the test suite:

# Hashmap Data Structure - C Implementation

![image](https://github.com/zprintln/Hashmap-C/assets/98183566/51980ddb-e09b-4a7f-b1af-2eb8bfa52b4e)


This repository contains a custom implementation of a hashmap data structure in C. A hashmap, also known as a hash table, is a powerful data structure that allows efficient storage, retrieval, and modification of key-value pairs. It utilizes a hash function to map keys to specific positions (buckets) in an array, enabling fast access to values based on their associated keys.

## Features

- **Creation and Deletion:** The hashmap supports dynamic creation and deletion, allowing you to allocate memory for a new hashmap and deallocate it after use.

- **Insertion and Retrieval:** You can easily insert new key-value pairs into the hashmap and retrieve the value associated with a given key.

- **Key Existence Check:** The hashmap provides a function to check whether a specific key exists in the hashmap.

- **Key Update and Removal:** You can update the value of an existing key or remove a key-value pair from the hashmap.

- **Customizable Hash Function:** The hashmap allows you to specify a custom hash function for mapping keys to buckets, giving you flexibility in adapting the data structure to different use cases.

- **Test Suite:** The repository includes a comprehensive test suite to ensure the correctness and functionality of the hashmap implementation.

## Getting Started

To use the hashmap in your C project, follow these steps:

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/your-username/hashmap-data-structure-c.git
   ```

2. Include the `my_hashmap.h` header file in your C source file:
   ```c
   #include "my_hashmap.h"
   ```

3. Compile your C code along with the hashmap implementation:
   ```bash
   gcc -Wall your_code.c my_hashmap.c -o your_executable
   ```

4. Run the compiled executable:
   ```bash
   ./your_executable
   ```

## Example Usage

```c
#include <stdio.h>
#include "my_hashmap.h"

int main() {
    // Create a new hashmap with 5 buckets
    hashmap_t* myHashmap = hashmap_create(5);

    // Insert a key-value pair into the hashmap
    hashmap_insert(myHashmap, "name", "John Doe");

    // Check if a key exists in the hashmap
    int keyExists = hashmap_hasKey(myHashmap, "name");
    printf("Key 'name' exists: %s\n", keyExists ? "true" : "false");

    // Retrieve the value associated with a key
    char* value = hashmap_getValue(myHashmap, "name");
    printf("Value for key 'name': %s\n", value);

    // Update the value of an existing key
    hashmap_update(myHashmap, "name", "Jane Smith");

    // Remove a key-value pair from the hashmap
    hashmap_removeKey(myHashmap, "name");

    // Free the hashmap memory after use
    hashmap_delete(myHashmap);

    return 0;
}
```

## Test Suite

The repository includes a test suite `hashmap_test.c` that thoroughly tests the functionalities of the hashmap implementation. To run the test suite, compile it along with the hashmap implementation:

```bash
gcc -g -Wall hashmap_test.c my_hashmap.c -o hashmap_test
```

Run the compiled test suite:

```bash
./hashmap_test
```

The test suite will execute various unit tests to check the correctness of the hashmap's creation, insertion, retrieval, key existence, key update, and key removal operations.

## Contributing

Contributions to this Hashmap Data Structure implementation are welcome! If you find any bugs, have suggestions for improvements, or want to add new features, feel free to open an issue or submit a pull request.

## Acknowledgments

- The implementation of the hashmap data structure is based on a custom design and inspired by the concepts of hash tables.
- The support code and test suite provided in this repository were adapted from a sample assignment in a 5008 programming course.
