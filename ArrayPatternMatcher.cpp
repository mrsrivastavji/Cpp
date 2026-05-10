#include <iostream>
#include <string>

using namespace std;

class ArrayPatternMatcher {
public:

    static bool containsPattern(string array1[], int size1,
                                string array2[], int size2) {

        // Empty pattern is always found
        if (size2 == 0) {
            return true;
        }

        // Pattern cannot be larger than main array
        if (size1 < size2) {
            return false;
        }

        // Check every possible starting position
        for (int i = 0; i <= size1 - size2; i++) {

            bool match = true;

            // Compare elements one by one
            for (int j = 0; j < size2; j++) {

                if (array1[i + j] != array2[j]) {
                    match = false;
                    break;
                }
            }

            // If complete pattern matched
            if (match) {
                return true;
            }
        }

        return false;
    }
};

int main() {

    // Example 1
    string str1[] = {"1", "2", "3", "4", "5", "6", "7"};
    string str2[] = {"3", "4", "5"};

    cout << boolalpha
         << ArrayPatternMatcher::containsPattern(str1, 7, str2, 3)
         << endl;

    // Example 2
    string str3[] = {"5", "6", "7", "8", "9"};
    string str4[] = {"6", "8"};

    cout << boolalpha
         << ArrayPatternMatcher::containsPattern(str3, 5, str4, 2)
         << endl;

    // Example 3
    string str5[] = {"a", "b", "c", "d"};
    string str6[] = {"b", "c"};

    cout << boolalpha
         << ArrayPatternMatcher::containsPattern(str5, 4, str6, 2)
         << endl;

    return 0;
}