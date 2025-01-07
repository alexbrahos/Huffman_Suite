/*
* CSCI-B 503 Program 5
* Team 3 - Brahos, Durfey, Kuo, Mohammed, Perera, Singh, Tong
*/

#include "PartThreeB.h"

//////////////////////////
// Part Three B: Decoding
// Convert the encoded text back to its original format
// Input: The encoded text file from part 3a
// Output: Original text file after decoding
//////////////////////////
PartThreeB::PartThreeB()
{
    const string PT1_INPUT_FILE = "clear.txt";
    const string PT1_OUTPUT_FILE = "freq.txt";
    const string PT2_OUTPUT_FILE = "codetable.txt";
    const string PT3A_OUTPUT_FILE = "coded.txt";
    const string PT3B_OUTPUT_FILE = "decoded.txt";

    // Read the code table file with the huffman codes
    ifstream codeTableFile(PT2_OUTPUT_FILE);
    if (!codeTableFile.is_open())
    {
        cerr << "Cannot open:" << PT2_OUTPUT_FILE << endl;
        return;
    }
    map<string, char> revHuffmanCodeMap;
    string chStr, code;
    while (codeTableFile >> chStr >> code)
    {
        char character;
        // Process new lin characters
        if (chStr == "LF")
            character = '\n';
        else if (chStr == "space")
            character = ' ';
        else
            character = chStr[0];
        // Use map to get the character for the code
        revHuffmanCodeMap[code] = character;
    }
    codeTableFile.close();
    // Open coded.txt for reading
    ifstream encodedTextFile(PT3A_OUTPUT_FILE);
    if (!encodedTextFile.is_open())
    {
        cerr << "Cannot open: " << PT3A_OUTPUT_FILE << endl;
        return;
    }
    // Open a new file to write the decoded text
    // Should match the original input file
    ofstream outputFile(PT3B_OUTPUT_FILE);
    if (!outputFile.is_open())
    {
        cerr << "Cannot create:" << PT3B_OUTPUT_FILE << endl;
        return;
    }
    string currentCode = "";
    char ch;
    while (encodedTextFile.get(ch))
    {
        currentCode += ch;
        if (revHuffmanCodeMap.find(currentCode) != revHuffmanCodeMap.end())
        {
            outputFile << revHuffmanCodeMap[currentCode];
            currentCode = "";
        }
    }
    encodedTextFile.close();
    outputFile.close();
    cout << "Finished Part Three B. Decoded data written to: " << PT3B_OUTPUT_FILE << endl;
}