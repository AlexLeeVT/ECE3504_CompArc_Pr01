using namespace std;

#include "main.hpp"

queue<int> readFile(string fileName) {
    cout << "File: " << fileName << endl;
    ifstream inFile(fileName);

    queue<int> queue;
    try {
        while(!inFile.eof()) {
            // get line from file
            string hexnum;
            inFile >> hexnum;

            // convert hex to int
            unsigned int x = 0;
            stringstream ss;
            ss << hex << hexnum;
            ss >> x;

            // put it into the queue
            queue.push(static_cast<int>(x));
        }
    } catch(ifstream::failure e) {
        cerr<< "Exception opening/reading/closing file\n";
    }
    inFile.close();

    return queue;
}

int main(int argc, char** argv) {
    queue<int> queue = readFile(argv[1]);

    while(!queue.empty()) {
        int x = queue.front();
        queue.pop();
        cout << endl << x << endl;

        cout << "func: " << (x & FUNC_BITMASK) << endl;
        cout << "rs: " << ((x & RS_BITMASK) >> RS_BITSHIFT) << endl;
        cout << "rt: " << ((x & RT_BITMASK) >> RT_BITSHIFT) << endl;
        cout << "rd: " << ((x & RD_BITMASK) >> RD_BITSHIFT) << endl;
    }
    return 0;
}

