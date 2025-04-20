#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <stdexcept>
#include <bitset>
#include <climits>

class BitStreamInterpreter {
public:
    std::string interpret(const std::string& code, const std::string& input) {
        std::vector<bool> inputBits;
        for (char c : input) {
            for (int i = 0; i < CHAR_BIT; ++i) {
                inputBits.push_back((c >> i) & 1);
            }
        }
        
        auto brancketsCheckMap = createBracketsMappings(code);
        std::vector<bool> tape(1, false);
        size_t pointer = 0;
        size_t inputPos = 0;
        std::vector<bool> outputBits;

        for (size_t pc = 0; pc < code.size(); ++pc) {
            char op = code[pc];
            
            switch (op) {
                case '+':
                    if (pointer >= tape.size()) {
                        tape.resize(pointer + 1, false);
                    }
                    tape[pointer] = !tape[pointer];
                    break;
                    
                case ',':
                    if (pointer >= tape.size()) {
                        tape.resize(pointer + 1, false);
                    }
                    tape[pointer] = (inputPos < inputBits.size()) ? inputBits[inputPos++] : false;
                    break;
                    
                case ';':
                    if (pointer >= tape.size()) {
                        tape.resize(pointer + 1, false);
                    }
                    outputBits.push_back(tape[pointer]);
                    break;
                    
                case '<':
                    if (pointer == 0) {
                        // Expand tape to the left
                        tape.insert(tape.begin(), false);
                    } else {
                        --pointer;
                    }
                    break;
                    
                case '>':
                    ++pointer;
                    if (pointer >= tape.size()) {
                        tape.push_back(false);
                    }
                    break;
                    
                case '[':
                    if (pointer >= tape.size()) {
                        tape.resize(pointer + 1, false);
                    }
                    if (!tape[pointer]) {
                        pc = brancketsCheckMap.at(pc);
                    }
                    break;
                    
                case ']':
                    if (pointer >= tape.size()) {
                        tape.resize(pointer + 1, false);
                    }
                    if (tape[pointer]) {
                        pc = brancketsCheckMap.at(pc);
                    }
                    break;
            }
        }
        return bitsToString(outputBits);
    }

private:
    // This function checks for matching brackets for invalid inputs
    std::unordered_map<size_t, size_t> createBracketsMappings(const std::string& code) {
        std::unordered_map<size_t, size_t> brancketsCheckMap;
        std::stack<size_t> stack;
        
        for (size_t i = 0; i < code.size(); ++i) {
            if (code[i] == '[') {
                stack.push(i);
            } else if (code[i] == ']') {
                if (stack.empty()) {
                    throw std::runtime_error("Invalid input for Bracket at position " + std::to_string(i));
                }
                size_t openPos = stack.top();
                stack.pop();
                brancketsCheckMap[openPos] = i;
                brancketsCheckMap[i] = openPos;
            }
        }
        if (!stack.empty()) {
            throw std::runtime_error("Invalid input for Bracket at position " + std::to_string(stack.top()));
        }
        return brancketsCheckMap;
    }
    
    std::string bitsToString(const std::vector<bool>& bits) {
        std::string result;
        for (size_t i = 0; i < bits.size(); i += CHAR_BIT) {
            char c = 0;
            for (size_t j = 0; j < CHAR_BIT && (i + j) < bits.size(); ++j) {
                if (bits[i + j]) {
                    c |= (1 << j);
                }
            }
            result += c;
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    if (argc == 2) {
        try {
            BitStreamInterpreter interpreter;
            auto program = ">,>,>,>,>,>,>,>,>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>>>>>>>>>>,>,>,>,>,>,>,>,>+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>;>;>;>;>;>;>;>;<<<<<<<<+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]";
            
            std::string input = argv[1];
            std::string output = interpreter.interpret(program, input);
            
            std::cout << output << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "Usage: " << argv[0] << " <input_string>" << std::endl;
        return 1;
    }
    return 0;
}