/*
* CSCI-B 503 Program 5
* Team 3 - Brahos, Durfey, Kuo, Mohammed, Perera, Singh, Tong
*/

#include "PartThreeA.h"

//////////////////////////
// Part Three A: Encoding
// Replace character with huffman codes
// Reads the characters in the input file
// Then uses the codes in the codetable file saved from the previous part
// Finally write the binary strings to coded.txt
//////////////////////////
PartThreeA::PartThreeA()
{

    const string PT1_INPUT_FILE = "clear.txt";
    const string PT1_OUTPUT_FILE = "freq.txt";
    const string PT2_OUTPUT_FILE = "codetable.txt";
    const string PT3A_OUTPUT_FILE = "coded.txt";
    const string PT3B_OUTPUT_FILE = "decoded.txt";

    // Read codetable.txt and store Huffman codes in a map
    ifstream codeTableFile(PT2_OUTPUT_FILE);
    if (!codeTableFile.is_open())
    {
        cerr << "Cannot open: " << PT2_OUTPUT_FILE << endl;
        return;
    }
    // Open the previous output file and map all the huffman codes
    // to a map structure for referencing 
    map<char, string> huffmanCodes;
    string chStr, code;
    while (codeTableFile >> chStr >> code)
    {
        char character;
        // Process new line characters correctly
        if (chStr == "LF")
            character = '\n';
        else if (chStr == "space") // Add this condition
            character = ' ';
        else
            character = chStr[0];
        huffmanCodes[character] = code;
    }
    codeTableFile.close();
    // Open original input file with ASCII for reading
    ifstream originalTextFile(PT1_INPUT_FILE);
    if (!originalTextFile.is_open())
    {
        cerr << "Cannot open: " << PT1_INPUT_FILE << endl;
        return;
    }
    // Open a new fle to which we can write the encoded text
    ofstream encodedOutputFile(PT3A_OUTPUT_FILE);
    if (!encodedOutputFile.is_open())
    {
        cerr << "Cannot create: " << PT3A_OUTPUT_FILE << endl;
        return;
    }
    // Read the input from the original file line by line and
    // convert to huffman encoding use the map
    char ch;
    while (originalTextFile.get(ch))
    {
        if (huffmanCodes.find(ch) != huffmanCodes.end())
        {
            encodedOutputFile << huffmanCodes[ch];
        }
        else
        {
            cerr << "Character '" << ch << "' not found in Huffman codes during encoding." << endl;
        }
    }
    // Close all files
    originalTextFile.close();
    encodedOutputFile.close();
    cout << "Finished Part Three A. Encoded data written to coded.txt." << endl;
}