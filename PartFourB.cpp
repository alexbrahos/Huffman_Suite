/*
* CSCI-B 503 Program 5
* Team 3 - Brahos, Durfey, Kuo, Mohammed, Perera, Singh, Tong
*/

/*
 * PartFourB.cpp
 * Author: Mingzhao Tong
 * Date: Nov 7th 2024
 * Description: Decode the codedalt.txt file using the codetable.txt, and output to decodedalt.txt.
 */

#include "PartFourB.h"

PartFourB::PartFourB() {
    const int ASCII_SIZE = 128;
    std::unordered_map<std::string, char> reverseCodeTable;

    std::ifstream codeTableFile("codetable.txt");
    if (!codeTableFile.is_open()) {
        std::cerr << "Cannot find codetable.txt." << std::endl;
        exit(1);
    }

    // Read and create reverse code table
    std::string line;
    while (getline(codeTableFile, line)) {
        if (line.empty()) continue;

        // Handle LF (Line Feed) special case
        if (line.substr(0, 2) == "LF") {
            reverseCodeTable[line.substr(3)] = '\n';
            continue;
        }

        // Special handling for space
        if (line.substr(0, 5) == "space") {
            reverseCodeTable[line.substr(6)] = ' ';
            continue;
        }

        // Normal character processing
        if (line.length() >= 3) {
            char character = line.at(0);
            std::string code = line.substr(2);
            reverseCodeTable[code] = character;
        }
    }
    codeTableFile.close();

    // Open codedalt.txt for reading
    std::ifstream inputFile("codedalt.txt", std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Cannot find codedalt.txt." << std::endl;
        exit(1);
    }

    // Open decodedalt.txt for writing
    std::ofstream outputFile("decodedalt.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Cannot create decodedalt.txt." << std::endl;
        exit(1);
    }

    // Decoding process
    std::string currentCode;
    unsigned char byte, marker, magicByte;
    int validBits = 8;
    std::vector<unsigned char> lastBytes;

    while (inputFile.read(reinterpret_cast<char*>(&byte), 1)) {
        lastBytes.push_back(byte);
    }

    // Check for special marker at the end
    if (lastBytes.size() >= 3 &&
        lastBytes[lastBytes.size() - 1] == 0xAA) {
        marker = lastBytes[lastBytes.size() - 2];
        validBits = marker;

        lastBytes.pop_back();
        lastBytes.pop_back();
    }

    // Process all bytes except the last one
    for (size_t byteIndex = 0; byteIndex < lastBytes.size(); ++byteIndex) {
        unsigned char currentByte = lastBytes[byteIndex];
        int processBits = (byteIndex == lastBytes.size() - 1) ? validBits : 8;

        for (int i = 7; i >= 8 - processBits; --i) {
            // Extract current bit
            int bit = (currentByte >> i) & 1;
            currentCode += std::to_string(bit);

            auto it = reverseCodeTable.find(currentCode);
            if (it != reverseCodeTable.end()) {
                outputFile.put(it->second);
                currentCode.clear();
            }
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Finished PartFourB, please check ./decodedalt.txt." << std::endl;
}