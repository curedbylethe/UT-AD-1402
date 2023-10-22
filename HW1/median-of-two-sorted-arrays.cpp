#include <memory>
#include <iostream>
#include <vector>
#include <variant>

using IntArray = std::unique_ptr<std::vector<int>>;
using ArraySize = size_t;
using Median = std::variant<int, double>;

namespace Utils {
    auto isInt = [](Median number) -> bool {
        return std::holds_alternative<int>(number);
    };

    auto printMedianVariant = [](const Median number) -> void {
        if (isInt(number)) {
            std::cout << std::get<int>(number);
        } else {
            std::cout << std::get<double>(number);
        }
    };

    auto insertValues = [](IntArray &array, ArraySize size) -> void {
        for (ArraySize i = 0; i < size; ++i) {
            std::cin >> array->at(i);
        }
    };

    auto newIntArray = [](ArraySize size) -> IntArray {
        return std::make_unique<std::vector<int>>(size);
    };

    enum class ArraySplit {
        FIRST_HALF,
        SECOND_HALF,
    };
}

namespace Algorithm {
    int findMedianOfASortedArray(const IntArray &array) {
        ArraySize size = array->size();
        if (size % 2 == 0) {
            return (array->at(size / 2 - 1) + array->at(size / 2)) / 2;
        } else {
            return array->at(size / 2);
        }
    }

    IntArray splitArray(const IntArray &array, Utils::ArraySplit split) {
        ArraySize oldSize = array->size();
        ArraySize newSize = oldSize / 2;
        IntArray newArray = Utils::newIntArray(newSize);
        for (ArraySize i = 0; i < newSize; ++i) {
            if (split == Utils::ArraySplit::FIRST_HALF) {
                newArray->at(i) = array->at(i);
            } else {
                newArray->at(i) = array->at((oldSize / 2) + oldSize % 2 + i);
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
            return findMedian(splitArray(firstArray, Utils::ArraySplit::SECOND_HALF),
                              splitArray(secondArray, Utils::ArraySplit::FIRST_HALF));
        } else {
            return findMedian(splitArray(firstArray, Utils::ArraySplit::FIRST_HALF),
                              splitArray(secondArray, Utils::ArraySplit::SECOND_HALF));
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

        firstArray = Utils::newIntArray(firstArraySize);
        Utils::insertValues(firstArray, firstArraySize);

        secondArray = Utils::newIntArray(secondArraySize);
        Utils::insertValues(secondArray, secondArraySize);
    }

    void findMedian() {
        median = Algorithm::findMedian(firstArray, secondArray);
    }

    void printMedian() {
        Utils::printMedianVariant(median);
    }
};

int main() {
    Solution solution;
    return 0;
}
