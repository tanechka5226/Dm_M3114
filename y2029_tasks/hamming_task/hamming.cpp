#include <iostream>
#include <string>
#include <vector>

int parityCount(int m) {
    int r = 0;
    while ((1 << r) < m + r + 1)
        r++;
    return r;
}

void encode(int m, int n, std::string data) {
    int r = parityCount(m);
    std::vector<int> p(r, 0);

    for (int i = 0; i < r; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            if (((j + 1) >> i) % 2 == 1)
                sum += (data[j] == '1');
        }
        p[i] = sum % 2;
    }

    std::cout << data;
    for (int i = 0; i < r; i++)
        std::cout << p[i];
    std::cout << '\n';
}

void decode(int n, std::string code) {
    int r = 0;
    while ((1 << r) < n + 1)
        r++;

    int m = n - r;

    std::string data = code.substr(0, m);
    std::string p = code.substr(m, r);

    int error = 0;

    for (int i = 0; i < r; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            if (((j + 1) >> i) % 2 == 1)
                sum += (data[j] == '1');
        }
        if ((sum % 2) != (p[i] == '1'))
            error += (1 << i);
    }

    if (error >= 1 && error <= m) {
        data[error - 1] =
            (data[error - 1] == '1' ? '0' : '1');
    }

    std::cout << r << '\n';
    std::cout << data << '\n';
}

void isValid(int n, std::string code) {
    int r = 0;
    while ((1 << r) < n + 1)
        r++;

    int m = n - r;

    std::string data = code.substr(0, m);
    std::string p = code.substr(m, r);

    for (int i = 0; i < r; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            if (((j + 1) >> i) % 2 == 1)
                sum += (data[j] == '1');
        }
        if ((sum % 2) != (p[i] == '1')) {
            std::cout << 0 << '\n';
            return;
        }
    }

    std::cout << 1 << '\n';
}

int main(int argc, char* argv[]) {
    std::string cmd = argv[1];

    if (cmd == "encode")
        encode(std::stoi(argv[2]), std::stoi(argv[3]), argv[4]);
    else if (cmd == "decode")
        decode(std::stoi(argv[2]), argv[3]);
    else
        isValid(std::stoi(argv[2]), argv[3]);

    return 0;
}
