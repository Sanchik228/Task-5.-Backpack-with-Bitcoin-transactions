#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>

const int MAX_BLOCK_SIZE = 1000000;

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
            catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
    }
    return transactions;
}

int main() {
    std::string filename = "transactions.csv";
    auto transactions = readTransaction(filename);

    int cBlockSize = 0, totalFee = 0;

    std::vector<Transaction> block;
    auto start = std::chrono::high_resolution_clock::now();

    std::sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
        return a.feePerByte() > b.feePerByte();
        });

    for (const auto& tx : transactions) {
        if (cBlockSize + tx.size <= MAX_BLOCK_SIZE) {
            block.push_back(tx);
            cBlockSize += tx.size;
            totalFee += tx.fee;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Block constructed!\n" << "Transactions in block : " << block.size() << std::endl
        << "Block size: " << cBlockSize << " bytes\n" << "Total fee: " << totalFee << " satoshis\n"
        << "Construction time: " << elapsed_us.count() << " ms" << std::endl
        << "Read transactions: " << transactions.size() << std::endl;

    return 0;
}