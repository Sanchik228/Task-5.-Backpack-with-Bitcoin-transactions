#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Transaction {
    std::string id;
    int size;
    int fee;

    double feePerByte() const {
        return static_cast<double>(fee) / size;
    }
};

std::vector<Transaction> readTransaction(const std::string& f) {
    std::vector<Transaction> transactions;
    std::ifstream file(f);
    std::string line;

        if (!file) {
            std::cerr << "Cannot open file: " << f << std::endl;
            return transactions;
        }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, size_str, fee_str;

        if (std::getline(ss, id, ',') && std::getline(ss, size_str, ',') && std::getline(ss, fee_str, ',')) {
            try {
                int size = std::stoi(size_str);
                int fee = std::stoi(fee_str);
                transactions.push_back({ id, size, fee });
            }
            catch(const std::exception& e){
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
    }
    return transactions;
}

int main() {
    std::string filename = "transactions.csv";
    auto transactions = readTransaction(filename);

    std::cout << "Read transactions: " << transactions.size() << std::endl;

    return 0;
}