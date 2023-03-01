using namespace std;

#include "main.hpp"

queue<int> readFile(string fileName) {
    // cout << "File: " << fileName << endl;
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
        int opcode = queue.front();
        queue.pop();
        cout << "code: " << opcode << endl;

        short op = (opcode & OP_BITMASK) >> OP_BITSHIFT;
        short rs = (opcode & RS_BITMASK) >> RS_BITSHIFT;
        short rt = (opcode & RT_BITMASK) >> RT_BITSHIFT;
        short rd = (opcode & RD_BITMASK) >> RD_BITSHIFT;
        short shamt = (opcode & SHAMT_BITMASK) >> SHAMT_BITSHIFT;
        short func = (opcode & FUNC_BITMASK) >> FUNC_BITSHIFT;

        cout << "op: " << op << endl;
        cout << "rs: " << rs << endl;
        cout << "rt: " << rt << endl;
        cout << "rd: " << rd << endl;
        cout << "shamt: " << shamt << endl;
        cout << "func: " << func << endl;
    }
    return 0;
}

