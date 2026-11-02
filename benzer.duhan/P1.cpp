#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace benzer {

    bool isEqlSeq(const std::vector<int>& arr) {
        if (arr.empty()) return true;
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] != arr[0]) return false;
        }
        return true;
    }

    bool isMonInc(const std::vector<int>& arr) {
        if (arr.empty()) return true;
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] <= arr[i - 1]) return false;
        }
        return true;
    }

    std::vector<std::vector<int>> transposeMatrix(const std::vector<std::vector<int>>& mat) {
        if (mat.empty()) return {};
        size_t rows = mat.size();
        size_t cols = mat[0].size();
        std::vector<std::vector<int>> result(cols, std::vector<int>(rows));
        
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result[j][i] = mat[i][j];
            }
        }
        return result;
    }

    std::string reverseString(std::string str) {
        std::reverse(str.begin(), str.end());
        return str;
    }
}

int main() {
    std::cout << "--- AIP Lab Tests (Namespace: benzer) ---\n\n";

    std::vector<int> testEql = {5, 5, 5, 5};
    std::vector<int> testMon = {1, 2, 3, 4, 5};
    std::vector<int> testFail = {1, 3, 2};

    std::cout << "[P1] EQL-SEQ Test: " << (benzer::isEqlSeq(testEql) ? "Success" : "Failed") << "\n";
    std::cout << "[P1] MON-INC Test: " << (benzer::isMonInc(testMon) ? "Success" : "Failed") << "\n";

    if (!benzer::isEqlSeq(testEql)) {
        std::cerr << "Error: EQL-SEQ test failed!\n";
        return 1;
    }
    if (!benzer::isMonInc(testMon)) {
        std::cerr << "Error: MON-INC test failed!\n";
        return 2;
    }

    std::cout << "\n[P3] Matrix Transpose Test:\n";
    std::vector<std::vector<int>> mat = {{1, 2, 3}, {4, 5, 6}};
    auto transposed = benzer::transposeMatrix(mat);
    for (const auto& row : transposed) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }

    std::cout << "\n[P4] String Reverse Test:\n";
    std::string isim = "Duhan Benzer";
    std::cout << "Original: " << isim << " | Reversed: " << benzer::reverseString(isim) << "\n\n";

    std::cout << "All tests passed successfully. Exit code: 0\n";
    return 0;
}
