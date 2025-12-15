#include <cmath>
#include <iostream>
#include <string>

bool checkPowerTwo(int x) {
    if (x <= 0) {
        return false;
    }
    return (x & (x - 1)) == 0;
}

std::string makeCode(int m, int n, const std::string& data) {
    if (data.length() != static_cast<size_t>(m)) {
        return "";
    }
    
    int r = 0;
    while ((1 << r) < n + 1) {
        r++;
    }
    
    if (n != m + r) {
        return "";
    }
    
    std::string code(n, '0');
    int data_pos = 0;
    
    for (int i = 1; i <= n; ++i) {
        if (!checkPowerTwo(i)) {
            code[i - 1] = data[data_pos];
            data_pos++;
        }
    }
    
    for (int p = 1; p <= n; p <<= 1) {
        int sum = 0;
        
        for (int i = 1; i <= n; ++i) {
            if (i & p) {
                if (code[i - 1] == '1') {
                    sum++;
                }
            }
        }
        
        if (sum % 2 == 1) {
            code[p - 1] = '1';
        } else {
            code[p - 1] = '0';
        }
    }
    
    return code;
}

void readCode(int n, const std::string& code) {
    if (code.length() != static_cast<size_t>(n)) {
        return;
    }
    
    int syndrome = 0;
    
    for (int p = 1; p <= n; p <<= 1) {
        int sum = 0;
        
        for (int i = 1; i <= n; ++i) {
            if (i & p) {
                if (code[i - 1] == '1') {
                    sum++;
                }
            }
        }
        
        if (sum % 2 == 1) {
            syndrome += p;
        }
    }
    
    std::string fixed = code;
    
    if (syndrome > 0 && syndrome <= n) {
        if (fixed[syndrome - 1] == '0') {
            fixed[syndrome - 1] = '1';
        } else {
            fixed[syndrome - 1] = '0';
        }
    }
    
    std::string data;
    for (int i = 1; i <= n; ++i) {
        if (!checkPowerTwo(i)) {
            data += fixed[i - 1];
        }
    }
    
    int check_bits = 0;
    while ((1 << check_bits) < n + 1) {
        check_bits++;
    }
    
    std::cout << check_bits << "\n";
    std::cout << data << "\n";
}

void checkCode(int n, const std::string& code) {
    if (code.length() != static_cast<size_t>(n)) {
        std::cout << "0\n";
        return;
    }
    
    bool is_valid = true;
    
    for (int p = 1; p <= n; p <<= 1) {
        if (!is_valid) {
            break;
        }
        
        int sum = 0;
        
        for (int i = 1; i <= n; ++i) {
            if (i & p) {
                if (code[i - 1] == '1') {
                    sum++;
                }
            }
        }
        
        if (sum % 2 == 1) {
            is_valid = false;
        }
    }
    
    if (is_valid) {
        std::cout << "1\n";
    } else {
        std::cout << "0\n";
    }
}

bool validateBinaryString(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        if (c != '0' && c != '1') {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    std::string command = argv[1];
    
    if (command == "encode") {
        if (argc != 5) {
            return 1;
        }
        
        int m = std::stoi(argv[2]);
        int n = std::stoi(argv[3]);
        std::string data = argv[4];
        
        if (!validateBinaryString(data)) {
            return 1;
        }
        
        if (m <= 0 || n <= 0) {
            return 1;
        }
        
        std::string code = makeCode(m, n, data);
        if (code.empty()) {
            return 1;
        }
        
        std::cout << code << "\n";
    }
    else if (command == "decode") {
        if (argc != 4) {
            return 1;
        }
        
        int n = std::stoi(argv[2]);
        std::string code = argv[3];
        
        if (!validateBinaryString(code)) {
            return 1;
        }
        
        if (n <= 0) {
            return 1;
        }
        
        readCode(n, code);
    }
    else if (command == "is_valid") {
        if (argc != 4) {
            return 1;
        }
        
        int n = std::stoi(argv[2]);
        std::string code = argv[3];
        
        if (!validateBinaryString(code)) {
            return 1;
        }
        
        if (n <= 0) {
            return 1;
        }
        
        checkCode(n, code);
    }
    else {
        return 1;
    }
    
    return 0;
}
