#include <iostream>
#include <string>
#include <vector>

bool isPowerOfTwo(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

void encode(int m, int n, std::string bits) {
    std::vector<int> code(n, 0);
    
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (!isPowerOfTwo(i + 1)) {
            if (idx < m) {
                code[i] = bits[idx] - '0';
                idx++;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (isPowerOfTwo(i + 1)) {
            int parity = 0;
            for (int j = 0; j < n; j++) {
                if (((j + 1) & (i + 1)) != 0) {
                    parity ^= code[j];
                }
            }
            code[i] = parity;
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << code[i];
    }
    std::cout << std::endl;
}

void decode(int n, std::string bits) {
    std::vector<int> code(n);
    for (int i = 0; i < n; i++) {
        code[i] = bits[i] - '0';
    }
    
    int error = 0;
    for (int i = 0; i < n; i++) {
        if (isPowerOfTwo(i + 1)) {
            int parity = 0;
            for (int j = 0; j < n; j++) {
                if (((j + 1) & (i + 1)) != 0) {
                    parity ^= code[j];
                }
            }
            if (parity) {
                error += (i + 1);
            }
        }
    }
    
    if (error > 0 && error <= n) {
        code[error - 1] ^= 1;
    }
    
    std::string result;
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (!isPowerOfTwo(i + 1)) {
            result += (code[i] + '0');
        } else {
            r++;
        }
    }
    
    std::cout << r << std::endl;
    std::cout << result << std::endl;
}

void is_valid(int n, std::string bits) {
    std::vector<int> code(n);
    for (int i = 0; i < n; i++) {
        code[i] = bits[i] - '0';
    }
    
    bool valid = true;
    for (int i = 0; i < n; i++) {
        if (isPowerOfTwo(i + 1)) {
            int parity = 0;
            for (int j = 0; j < n; j++) {
                if (((j + 1) & (i + 1)) != 0) {
                    parity ^= code[j];
                }
            }
            if (parity) {
                valid = false;
                break;
            }
        }
    }
    
    std::cout << (valid ? "1" : "0") << std::endl;
}

int main(int argc, char* argv[]) {
    std::string cmd = argv[1];
    
    if (cmd == "encode") {
        encode(std::stoi(argv[2]), std::stoi(argv[3]), argv[4]);
    }
    else if (cmd == "decode") {
        decode(std::stoi(argv[2]), argv[3]);
    }
    else if (cmd == "is_valid") {
        is_valid(std::stoi(argv[2]), argv[3]);
    }
    
    return 0;
}
