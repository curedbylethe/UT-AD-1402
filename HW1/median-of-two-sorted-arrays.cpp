#include <memory>
#include <iostream>
#include <vector>
#include <variant>
#include <cmath>

using IntArray = std::unique_ptr<std::vector<int>>;
using ArraySize = size_t;
using Median = std::variant<int, double>;
auto MakeNewIntArray = [](ArraySize size) -> IntArray {
    return std::make_unique<std::vector<int>>(size);
};

enum class ArraySplit {
    FIRST,
    SECOND
};

namespace Algorithm {
    int findMedianOfASortedArray(const IntArray &array) {
        ArraySize size = array->size();
        if (size % 2 == 0) {
            return (array->at(size / 2 - 1) + array->at(size / 2)) / 2;
        } else {
            return array->at(size / 2);
        }
    }

    IntArray splitArray(const IntArray &array, ArraySplit split) {
        ArraySize oldSize = array->size();
        ArraySize newSize = std::ceil(oldSize / 2.0);
        IntArray newArray = MakeNewIntArray(newSize);
        for (ArraySize i = 0; i < newSize; ++i) {
            if (split == ArraySplit::FIRST) {
                newArray->at(i) = array->at(i);
            } else {
                newArray->at(i) = array->at(oldSize / 2 + i);
            }
        }

        return newArray;
    }

    int findMedian(const IntArray &firstArray, const IntArray &secondArray) {
        if (firstArray->empty()) {
            return findMedianOfASortedArray(secondArray);
        } else if (secondArray->empty()) {
            return findMedianOfASortedArray(firstArray);
        }

        int firstArrayMedian = findMedianOfASortedArray(firstArray);
        int secondArrayMedian = findMedianOfASortedArray(secondArray);

        if (firstArrayMedian == secondArrayMedian) {
            return firstArrayMedian;
        } else if (firstArrayMedian < secondArrayMedian) {
            return findMedian(splitArray(firstArray, ArraySplit::SECOND), splitArray(secondArray, ArraySplit::FIRST));
        } else {
            return findMedian(splitArray(firstArray, ArraySplit::FIRST), splitArray(secondArray, ArraySplit::SECOND));
        }
    }
}

class Solution {
private:
    IntArray firstArray;
    IntArray secondArray;

    Median median;
public:
    Solution() {
        getInput();
        findMedian();
        printMedian();
    }

private:
    void getInput() {
        ArraySize firstArraySize;
        std::cin >> firstArraySize;

        ArraySize secondArraySize;
        std::cin >> secondArraySize;

        firstArray = MakeNewIntArray(firstArraySize);
        for (ArraySize i = 0; i < firstArraySize; ++i) {
            std::cin >> firstArray->at(i);
        }

        secondArray = MakeNewIntArray(secondArraySize);
        for (ArraySize i = 0; i < secondArraySize; ++i) {
            std::cin >> secondArray->at(i);
        }
    }

    void findMedian() {
        median = Algorithm::findMedian(firstArray, secondArray);
    }

    void printMedian() {
        if (std::holds_alternative<int>(median)) {
            std::cout << std::get<int>(median);
        } else {
            std::cout << std::get<double>(median);
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
