using namespace std;

#include "main.hpp"

// finds a name for the primary opcode
opcode_t findPrimaryCode(const int op) {
    // using unordered maps, find the given opcode
    auto it = primary_code.find(op);    
    opcode_t opcode;
    
    // if it's not found, then return nothing and print an error statement
    if(it == primary_code.end()){
        hasError = true;
        opcode.first = "";
    } else {
        opcode.first = it->second;
    }
    opcode.second = I;
    
    return opcode;
}

// finds a name for the secondary opcode
opcode_t findSecondaryCode(const int op) {
    // using unordered maps, find the given opcode
    auto it = secondary_code.find(op);    
    opcode_t opcode;

    // if it's not found, then return nothing and print an error statement
    if(it == secondary_code.end()){
        hasError = true;
        opcode.first = "";
    } else {
        opcode.first = it->second;
    }
    opcode.second = R;
    
    return opcode;
}

string convertNumToRegisterName(const int reg) {
    auto it = register_names.find(reg);
    // out of bounds error. Return nothing.
    if(it == register_names.end()) {
        hasError = true;
        return "";
    } else
        return it->second;
}

// decompile R-type codes
string decompileR(const string mneomic, const int opcode) {
    string word;

    // get all necessary registers and shamt number
    register_t rs = (opcode & RS_BITMASK) >> RS_BITSHIFT;
    register_t rt = (opcode & RT_BITMASK) >> RT_BITSHIFT;
    register_t rd = (opcode & RD_BITMASK) >> RD_BITSHIFT;
    int shamt = (opcode & SHAMT_BITMASK) >> SHAMT_BITSHIFT;

    // convert register and shamt to strings to be concatinated
    string rsStr = convertNumToRegisterName(rs);
    string rtStr = convertNumToRegisterName(rt);
    string rdStr = convertNumToRegisterName(rd);
    string shamtStr = to_string(shamt);
    // if the instruction is 'sll' or 'srl' then change the word.
    if( (mneomic == "sll") || (mneomic == "srl")) {
        // error check. shamt can only be 16 bits long
        if((shamt >> 4) <= 0) {
            word = "\t" + 
                    mneomic + "\t" + 
                    rdStr + ", " +
                    rtStr + ", " +
                    shamtStr + "\n";
        } else { // if shamt IS larger than 4 bits, then there is an error.
            // DEBUG -------------------
            cout << "shamt out of bounds\t";
            word = "";
        }
    } else {
        // format: mneomic  rd, rt, rs
        word = "\t" + 
                mneomic + "\t" + 
                rdStr + ", " +
                rsStr + ", " +
                rtStr + "\n";
        
        if(rdStr == "" || rsStr == "" || rtStr == "") {
            // DEBUG ---------------------
            cout << "register out of bounds\t";
            word = "";
        }
    }
    return word;
}

// decompile I-type codes
string decompileI(const string mneomic, const int opcode) {
    string word;

    // get all necessary registers and immediate numbers
    register_t rs = (opcode & RS_BITMASK) >> RS_BITSHIFT;
    register_t rt = (opcode & RT_BITMASK) >> RT_BITSHIFT;
    signed short immediate = (opcode & IMM_BITMASK) >> IMM_BITSHIFT;

    // convert to strings to be concatinated
    string rsStr = convertNumToRegisterName(rs);
    string rtStr = convertNumToRegisterName(rt);
    string immStr = to_string(immediate);

    if(((immediate >> 16) <= 0) || rsStr == "" || rtStr == "") {    
        if( (mneomic == "beq") || (mneomic == "bne") ) {    
            int offset = (immediate + (currentLine))*4;

            // error check, if offset is larger than a 16 bit number or if it's negative.
            if(((offset >> 16) <= 0) && offset >= 0) {
                // convert offset into a readable string
                char address[10];
                snprintf(address, 10, "Addr_%04x", offset);

                // add to the list
                branchAddresses.push_back(offset);
            
                // format: mneomic  rs, rt, addr_####
                word = "\t" + 
                        mneomic + "\t" +
                        rsStr + ", " +
                        rtStr + ", " +
                        address + "\n";
            } else {
                
                // DEBUG --------------
                // cout << "address offset too large.";
                word = "";
            }
        } else if( (mneomic == "lbu") || (mneomic == "lhu") || (mneomic == "ll") || (mneomic == "lw") ||
                    (mneomic == "sb") || (mneomic == "sc") || (mneomic == "sh") || (mneomic == "sw")) {     // offset word
            // format: mneomic  rt, imm(rs)
            word = "\t" + 
                    mneomic + "\t" +
                    rtStr + ", " +
                    immStr + "(" + rsStr + ")\n";
        } else {    // standard word
            // format: mneomic  rt, rs, imm
            word = "\t" + 
                    mneomic + "\t" +
                    rtStr + ", " +
                    rsStr + ", " +
                    immStr + "\n";
        }
    } else {
        // error, the registers are out of bounds or the immediate number is larger than 16 bits.
        
        // DEBUG ---------------------
        // cout << "register out of bounds OR imm out of bounds\t";
        
        word == "";
    }

    return word;
}

// modified from https://www.geeksforgeeks.org/check-if-a-string-represents-a-hexadecimal-number-or-not/
bool str_is_hex(string s)
{
    // Size of string
    int n = s.length();
 
    // Iterate over string
    for(int i = 0; i < n; i++)
    {
        char ch = s[i];
        if(!isxdigit(ch))
            return false;
    }
    return true;
}

// read a file and put the contents into a list
list<string> readFile(const string fileName) {
    list<string> list;
    ifstream inFile(fileName);

    if(inFile.is_open()) {
        auto const pos = fileName.find_last_of('.');
        const auto leaf = fileName.substr(pos + 1);
        
        // DEBUG --------------
        // cout << leaf << endl << endl;

        if(leaf != "obj") {
            hasError = true;
            string errorStatement = "\"" + fileName + "\" must have the extension \".obj\"";
            throw invalid_argument(errorStatement);
        }

        while(!inFile.eof()) {
            // get line from file
            string hexnum;
            inFile >> hexnum;

            // check if the line is empty. If so, don't push it on the list.
            if(hexnum != "") {
                // put the word into the list if there are no errors
                list.push_back(hexnum);
            }
        }
    } else {
        // file name error check
        hasError = true;
        string errorStatement = "\"" + fileName + "\" does not exist.";
        throw invalid_argument(errorStatement);
    }
    inFile.close();

    return list;
}

int main(int argc, char** argv) {
    // initialize the lookup table
    initializeMaps();

    list<string> opcodes = readFile(argv[1]);

    vector<string> decompiledCode;

    while(!opcodes.empty()) {
        // figure out the opcode mneomic and format it's in
        stringstream ss;
        unsigned int opcode = 0;
        opcode_t mneomic;
        
        string hexCode = opcodes.front();
        opcodes.pop_front();
        string decompiledStr = "";

        // error if there is a length issue.
        if(!str_is_hex(hexCode)) {
            cout << hexCode << " is not a hexadecimal" << endl;
            hasError = true;
        }
        else if(hexCode.length() > 8) {
            hasError = true;
            cout << "Cannot disassemble " << hexCode << " at line " << currentLine << ": word too long" << endl;   // error printout due to hexcode length > 8
        } else {
            // convert string to hex and put it into opcode
            ss << hex << hexCode;
            ss >> opcode;

            // find the opcode in the hex opcode
            int op = (opcode & OP_BITMASK) >> OP_BITSHIFT;

            // determine if it uses the first(primary) or second(secondary) column.
            if(op == 0x00) {
                int func = (opcode & FUNC_BITMASK) >> FUNC_BITSHIFT;
                mneomic = findSecondaryCode(func);
            } else {
                mneomic = findPrimaryCode(op);
            }
            
            // DEBUG CODE ---------------------------------
            // cout << "hexcode: " << hexCode << " | Code: " << mneomic.first << " | Format: " << ((mneomic.second == R)?"R":"I") << endl;

            if(mneomic.first != "") {
                // calculate the string to be printed and store into an array
                if(mneomic.second == R) {
                    decompiledStr = decompileR(mneomic.first, opcode);  // calculate R formatted word
                }
                else if(mneomic.second == I) {
                    decompiledStr = decompileI(mneomic.first, opcode);  // calculate I formatted word
                }
                
                // decompile error check
                if(decompiledStr == "") {
                    hasError = true;
                    // DEBUG --------------------- remove the ending statement
                    cout << "Cannot disassemble " << hexCode << " at line " << currentLine << ": decompile error" << endl;
                }
            } else {
                hasError = true;
                // DEBUG --------------------- remove the ending statement
                cout << "Cannot disassemble " << hexCode << " at line " << currentLine << ": mneomic not found" << endl; // mneomic error check
            }
            
        }
        // add the decompiled str to the decompiled code list
        decompiledCode.push_back(decompiledStr);

        // increase the line number
        currentLine++;
    }

    // make a file with the same name and .asm at the end
    if(!hasError) {
        // DEBUG ----------------------------
        // cout << endl << "Make file" << endl;

        // sort the branch addresses without duplicates
        branchAddresses.unique();
        branchAddresses.sort();
        while(!branchAddresses.empty()) {
            // iterator to insert at the correct index
            auto it = decompiledCode.begin();
            
            // working from back to front
            int decAddress = branchAddresses.back();
            branchAddresses.pop_back();
            int line = decAddress/4;

            // advance the iterator to the right line
            advance(it, line);

            // calculate the address with the correct name
            char address[10];
            snprintf(address, 10, "Addr_%04x", decAddress);
            string addrStr(address);
            
            // add the line to the assembly code
            decompiledCode.insert(it, addrStr + ":\n");
        }
        // DEBUG ---------------------------
        for(int i = 0; i < decompiledCode.size(); i++) {
            cout << decompiledCode[i];
        }

        // put into a file
    }
    return 0;
}

