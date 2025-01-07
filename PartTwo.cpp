/*
* CSCI-B 503 Program 5
* Team 3 - Brahos, Durfey, Kuo, Mohammed, Perera, Singh, Tong
*/

#include "PartTwo.h"

// Node structure for the Huffman Tree
struct HuffmanNode
{
    string character;   // The character represented by this node (can be multi-character)
    int frequency;      // Frequency of the character in the input
    HuffmanNode* left;  // Pointer to the left child (for 0 path)
    HuffmanNode* right; // Pointer to the right child (for 1 path)

    // Constructor to initialize a HuffmanNode with a character and its frequency
    HuffmanNode(string c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue (min-heap)
struct Compare
{
    // Returns true if node 'a' has a higher frequency than node 'b'
    bool operator()(HuffmanNode* a, HuffmanNode* b)
    {
        return a->frequency > b->frequency; // Min-heap behavior based on frequency
    }
};

// Recursive function to generate Huffman codes
void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<string, string>& huffmanCodes)
{
    if (!root)
        return; // Base case: If the node is null, return

    // If this is a leaf node (no left or right child)
    if (!root->left && !root->right)
    {
        huffmanCodes[root->character] = code; // Assign the code to the character
    }

    // Recursively generate codes for the left and right subtrees
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);  // Append '0' for left
    generateHuffmanCodes(root->right, code + "1", huffmanCodes); // Append '1' for right
}

// Function to process the input and build the Huffman Tree
PartTwo::PartTwo()
{
    ifstream inputFile("freq.txt"); // Open the input file containing character frequencies
    if (!inputFile)
    {
        cerr << "Error opening file." << endl; // Print error and exit if file cannot be opened
        return;
    }

    vector<string> characters; // Vector to store characters from the file
    vector<int> frequencies;   // Vector to store their corresponding frequencies
    string line;               // Temporary string to read each line of the file

    // Reading the input file line by line
    while (getline(inputFile, line))
    {
        if (line.empty())
            continue; // Skip empty lines in the file

        size_t spacePos = line.find(' '); // Find the position of the first space

        if (line[0] == ' ') // If the line starts with a space
        {
            string characterStr = "space";        // Assign "space" as the character
            int frequency = stoi(line.substr(1)); // Convert the rest of the line to frequency
            characters.push_back(characterStr);   // Add to characters vector
            frequencies.push_back(frequency);     // Add to frequencies vector
        }
        else if (spacePos != string::npos) // Line has a space separator
        {
            string characterStr = line.substr(0, spacePos);  // Extract character(s)
            int frequency = stoi(line.substr(spacePos + 1)); // Extract and convert frequency
            characters.push_back(characterStr);              // Add to characters vector
            frequencies.push_back(frequency);                // Add to frequencies vector
        }
        else // Invalid line format
        {
            cerr << "Invalid line format: " << line << endl;
            continue;
        }
    }

    inputFile.close(); // Close the input file
    // Create a priority queue (min-heap) to build the Huffman Tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (size_t i = 0; i < characters.size(); ++i)
    {
        pq.push(new HuffmanNode(characters[i], frequencies[i])); // Create and push nodes
    }

    // Build the Huffman Tree by combining the two smallest nodes repeatedly
    while (pq.size() > 1)
    {
        HuffmanNode* left = pq.top(); // Get the smallest node
        pq.pop();
        HuffmanNode* right = pq.top(); // Get the second smallest node
        pq.pop();

        // Create a new node with combined frequency of the two smallest nodes
        HuffmanNode* combined = new HuffmanNode("", left->frequency + right->frequency);
        combined->left = left;   // Set the left child
        combined->right = right; // Set the right child
        pq.push(combined);       // Push the combined node back into the queue
    }

    // The remaining node in the queue is the root of the Huffman Tree
    HuffmanNode* root = pq.top();

    // Map to store the Huffman codes for each character
    unordered_map<string, string> huffmanCodes;

    // Generate the Huffman codes starting from the root
    generateHuffmanCodes(root, "", huffmanCodes);

    // Write the Huffman codes to "codetable.txt"
    ofstream outputFile("codetable.txt");
    if (!outputFile)
    {
        cerr << "Error opening output file." << endl;
        return;
    }

    for (const auto& pair : huffmanCodes)
    {
        if (pair.first == " ")
        {
            outputFile << "space\t" << pair.second << endl; // Write "space" for clarity
        }
        else
        {
            outputFile << pair.first << "\t" << pair.second << endl; // Write other characters
        }
    }

    outputFile.close(); // Close the output file

    cout << "Huffman codes have been written to codetable.txt." << endl;
}