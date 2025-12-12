#include <iostream>
#include <string>

bool isPowerOfTwo(int num) {
    while (num > 1) {
        if (num % 2 != 0) {
            return false;
        }
        num = num / 2;
    }
    return true;
}

void encode(int m, int n, std::string bits) {
    if (bits.length() != m) {
        return;
    }
    
    std::string result(n, '0');
    
    int bit_index = 0;
    for (int i = 1; i <= n; i++) {
        if (!isPowerOfTwo(i)) {
            if (bit_index < m) {
                result[i-1] = bits[bit_index];
                bit_index++;
            }
        }
    }
    
    for (int p = 1; p <= n; p *= 2) {
        int count_ones = 0;
        
        for (int i = p; i <= n; i++) {
            if ((i & p) != 0 && result[i-1] == '1') {
                count_ones++;
            }
        }
        
        if (count_ones % 2 == 1) {
            result[p-1] = '1';
        } else {
            result[p-1] = '0';
        }
    }
    
    std::cout << result << std::endl;
}

void decode(int n, std::string bits) {
    if (bits.length() != n) {
        return;
    }
    
    int error_position = 0;
    
    for (int p = 1; p <= n; p *= 2) {
        int count_ones = 0;
        
        for (int i = p; i <= n; i++) {
            if ((i & p) != 0 && bits[i-1] == '1') {
                count_ones++;
            }
        }
        
        if (count_ones % 2 == 1) {
            error_position += p;
        }
    }
    
    std::string corrected = bits;
    if (error_position > 0 && error_position <= n) {
        if (corrected[error_position-1] == '0') {
            corrected[error_position-1] = '1';
        } else {
            corrected[error_position-1] = '0';
        }
    }
    
    std::string data_bits = "";
    for (int i = 1; i <= n; i++) {
        if (!isPowerOfTwo(i)) {
            data_bits += corrected[i-1];
        }
    }
    
    int check_bits = 0;
    for (int p = 1; p <= n; p *= 2) {
        check_bits++;
    }
    
    std::cout << check_bits << std::endl;
    std::cout << data_bits << std::endl;
}

void is_valid(int n, std::string bits) {
    if (bits.length() != n) {
        return;
    }
    
    bool has_error = false;
    
    for (int p = 1; p <= n; p *= 2) {
        int count_ones = 0;
        
        for (int i = p; i <= n; i++) {
            if ((i & p) != 0 && bits[i-1] == '1') {
                count_ones++;
            }
        }
        
        if (count_ones % 2 == 1) {
            has_error = true;
            break;
        }
    }
    
    if (has_error) {
        std::cout << "0" << std::endl;
    } else {
        std::cout << "1" << std::endl;
    }
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
        std::string bits = argv[4];
        encode(m, n, bits);
    } 
    else if (command == "decode") {
        if (argc != 4) {
            return 1;
        }
        int n = std::stoi(argv[2]);
        std::string bits = argv[3];
        decode(n, bits);
    }
    else if (command == "is_valid") {
        if (argc != 4) {
            return 1;
        }
        int n = std::stoi(argv[2]);
        std::string bits = argv[3];
        is_valid(n, bits);
    }
    
    return 0;
}
