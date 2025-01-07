/*
* CSCI-B 503 Program 5
* Team 3 - Brahos, Durfey, Kuo, Mohammed, Perera, Singh, Tong
*/

#include "PartFourA.h"

PartFourA::PartFourA() {

    // define ASCII
    const int ASCII_SIZE = 128;

    // calculate ASCII
    std::vector<std::string> codes(ASCII_SIZE, "");

    // open codetable.txt
    std::ifstream inputFile("codetable.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Can not find codetable.txt." << std::endl;
		exit(1);    // Tong - Exit program if file not found
    }

    // read the codetable
    std::string line;
    while (getline(inputFile, line))
    {
        if (line.empty()) continue;

        // Special cases
        if (line.substr(0, 2) == "LF") {

            codes[10] = line.substr(3);
            continue;

        }

        // Tong - Special handling for space
        if (line.substr(0, 5) == "space") {
            codes[32] = line.substr(6);
            continue;
        }

        codes[static_cast<int>(line.at(0))] = line.substr(2, line.length());

    }

    inputFile.close();

    //open clear.txt
    std::ifstream clearFile("clear.txt");
    if (!clearFile.is_open()) {
        std::cerr << "Can not find clear.txt." << std::endl;
        exit(1);
    }

    //open codedalt.txt
    std::ofstream outputFile("codedalt.txt", std::ios::binary);
    if (!outputFile.is_open()) 
    {
        std::cerr << "Can not output file codedalt.txt." << std::endl;
        exit(1);
    }

    // for every character in clear.txt, add the code for that to the output.
    char ch = 0;
    int i = 0;
    std::bitset<8> byte;    
    std::string remainingBits;
    while (clearFile.get(ch)) {
        // Process each bit of the character's Huffman code
        for (char bit : codes[static_cast<unsigned char>(ch)]) {
            remainingBits += bit;

            if (bit == '1') {

                byte.set(7 - i);

            }
            else {

                byte.reset(7 - i);

            }

            i++;

            // Write byte when full
            if (i == 8) {
                outputFile.put(static_cast<unsigned char>(byte.to_ulong()));
                byte.reset();
                i = 0;
                remainingBits.clear();
            }
        }
    }

    // Tong - Handle last incomplete byte
    if (i > 0) {
        outputFile.put(static_cast<unsigned char>(byte.to_ulong()));
        unsigned char validBits = i;
        outputFile.put(validBits);
        outputFile.put(0xAA); // Marker to indicate the end
    }

	clearFile.close();
    inputFile.close();
    outputFile.close();

    std::cout << "Finished PartFourA, please check ./codedalt.txt." << std::endl;

}
