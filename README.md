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
