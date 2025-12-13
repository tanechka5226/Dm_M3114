#include <iostream>
#include <string>

bool checkPowerTwo(int x) {
    int y = 1;
    while (y < x) {
        y = y * 2;
    }
    return y == x;
}

std::string makeCode(int m, int n, std::string data) {
    if (data.length() != m) {
        return "";
    }
    
    std::string code(n, '0');
    int pos = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!checkPowerTwo(i)) {
            code[i-1] = data[pos];
            pos++;
        }
    }
    
    for (int p = 1; p <= n; p = p * 2) {
        if (p > n) break;
        
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (i == p) continue;
            if ((i & p) != 0) {
                if (code[i-1] == '1') {
                    sum = sum + 1;
                }
            }
        }
        
        if (sum % 2 == 1) {
            code[p-1] = '1';
        } else {
            code[p-1] = '0';
        }
    }
    
    return code;
}

void readCode(int n, std::string code) {
    if (code.length() != n) {
        return;
    }
    
    int wrong = 0;
    
    for (int p = 1; p <= n; p = p * 2) {
        if (p > n) break;
        
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if ((i & p) != 0) {
                if (code[i-1] == '1') {
                    sum = sum + 1;
                }
            }
        }
        
        if (sum % 2 == 1) {
            wrong = wrong + p;
        }
    }
    
    std::string fixed = code;
    if (wrong > 0 && wrong <= n) {
        if (fixed[wrong-1] == '0') {
            fixed[wrong-1] = '1';
        } else {
            fixed[wrong-1] = '0';
        }
    }
    
    std::string data = "";
    for (int i = 1; i <= n; i++) {
        if (!checkPowerTwo(i)) {
            data = data + fixed[i-1];
        }
    }
    
    int check = 0;
    for (int p = 1; p <= n; p = p * 2) {
        if (p > n) break;
        check++;
    }
    
    std::cout << check << std::endl;
    std::cout << data << std::endl;
}

void checkCode(int n, std::string code) {
    if (code.length() != n) {
        std::cout << "0" << std::endl;
        return;
    }
    
    int good = 1;
    
    for (int p = 1; p <= n; p = p * 2) {
        if (p > n) break;
        
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if ((i & p) != 0) {
                if (code[i-1] == '1') {
                    sum = sum + 1;
                }
            }
        }
        
        if (sum % 2 == 1) {
            good = 0;
            break;
        }
    }
    
    std::cout << good << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    std::string what = argv[1];
    
    if (what == "encode") {
        if (argc != 5) {
            return 1;
        }
        int m = std::stoi(argv[2]);
        int n = std::stoi(argv[3]);
        std::string data = argv[4];
        std::string code = makeCode(m, n, data);
        std::cout << code << std::endl;
    }
    else if (what == "decode") {
        if (argc != 4) {
            return 1;
        }
        int n = std::stoi(argv[2]);
        std::string code = argv[3];
        readCode(n, code);
    }
    else if (what == "is_valid") {
        if (argc != 4) {
            return 1;
        }
        int n = std::stoi(argv[2]);
        std::string code = argv[3];
        checkCode(n, code);
    }
    
    return 0;
}
