# File-Compression-App
This command line application allows you to compress and decompress text files using the **Huffman** coding algorithm. It also includes a binary file viewer and a text file viewer to help you verify the results of the compression and decompression processes.


## Features
+ Build a character frequency map from a text file or string
+ Build an encoding tree based on the character frequency map
+ Build an encoding map based on the encoding tree
+ Encode and decode data using the encoding map
+ Free the memory used by the encoding tree
+ Compress and decompress files
+ View the contents of a binary file
+ View the contents of a text file

## Usage
1. Clone the repository and navigate to the project directory
2. Compile the source code using a C++ compiler
3. Run the executable file
4. Follow the prompts to compress or decompress files, or to view the contents of a binary or text file

## How To Use
Notes
+ Choosing option 1 or C will prompt you to enter a filename or to enter a string. If you enter a filename, the app will build a character frequency map from the contents of the file. If you enter a string, the app will build a character frequency map from the string.
+ Choosing option 2 will build an encoding tree based on the character frequency map.
+ Choosing option 3 will build an encoding map based on the encoding tree.
+ Choosing option 4 will prompt you to enter a message to encode. The encoded message will be displayed on the screen.
+ Choosing option 5 will prompt you to enter an encoded message to decode. The decoded message will be displayed on the screen.
+ Choosing option 6 will free the memory used by the encoding tree.
+ Choosing option C will prompt you to enter a filename to compress. The compressed file will be saved in the same directory as the original file.
+ Choosing option D will prompt you to enter a filename to decompress. The decompressed file will be saved in the same directory as the original file.
+ Choosing option B will prompt you to enter a filename to view as binary. The contents of the file will be displayed on the screen in binary format.
+ Choosing option T will prompt you to enter a filename to view as text. The contents of the file will be displayed on the screen as a string.
+ Choosing option Q will quit the app.

# Custom Hashmap Data Structure
Custom hashmap data structure that maps integer keys to integer values. It uses a hash function to determine which bucket in an array the key/value pair should be placed in. If a collision occurs, the key/value pair is added to a linked list at the end of the bucket's list.


The hashmap class includes the following methods:

+ put(int key, int value): adds a key/value pair to the map
+ get(int key): returns the value associated with the given key
+ containsKey(int key): returns true if the key is in the map, false otherwise
+ keys(): returns a vector of all keys in the map
+ values(): returns a vector of all values in the map
+ size(): returns the number of key/value pairs in the map

## Notes
Notes
The hash function used in this implementation is the modulus of the key by the number of buckets in the map.
If a key/value pair with a key that is already in the map is added using the put method, the value for that key is updated.
The get method throws an error if the key is not in the map.
