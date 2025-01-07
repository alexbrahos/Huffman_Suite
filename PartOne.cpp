/*
* CSCI-B 503 Program 5
* Team 3 - Brahos, Durfey, Kuo, Mohammed, Perera, Singh, Tong
*/

#include "PartOne.h"

using namespace std;

PartOne::PartOne()
{

    // define ASCII
    const int ASCII_SIZE = 128;

    // calculate ASCII
    vector<int> freq(ASCII_SIZE, 0);

    // open clear.txt
    ifstream inputFile("clear.txt");
    if (!inputFile.is_open())
    {
        cerr << "Can not find clear.txt." << endl;
        //return 1;
    }

    // read the content
    char ch;
    while (inputFile.get(ch))
    {
        // calculate
        freq[static_cast<int>(ch)]++;
    }

    inputFile.close();

    // open freq.txt
    ofstream outputFile("freq.txt");
    if (!outputFile.is_open())
    {
        cerr << "Can not output file freq.txt." << endl;
        //return 1;
    }

    // calculate
    for (int i = 0; i < ASCII_SIZE; ++i)
    {
        if (freq[i] > 0)
        {
            if (i == 10)
            {
                outputFile << "LF " << freq[i] << endl;
            }
            else
            {
                outputFile << static_cast<char>(i) << " " << freq[i] << endl;
            }
        }
    }

    // Close
    outputFile.close();

    cout << "Finished PartOne, please check ./freq.txt." << endl;

    //return 0;

}