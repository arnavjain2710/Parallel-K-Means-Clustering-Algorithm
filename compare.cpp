#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <numeric> 
#include <iomanip> 
#include <string>  

using namespace std;

vector<double> readNumbersFromFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open file " + filePath);
    }

    vector<double> numbers;
    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        double num;
        while (stream >> num) {
            numbers.push_back(num);
        }
    }

    file.close();
    return numbers;
}

int main() {
    try {
        string file1Path = "centroid_output_dataset9.txt";

        vector<string> file2Paths = {
            "centroid_output_threads2_dataset9.txt",
            "centroid_output_threads4_dataset9.txt",
            "centroid_output_threads6_dataset9.txt",
            "centroid_output_threads8_dataset9.txt",
            "centroid_output_threads10_dataset9.txt",
            "centroid_output_threads12_dataset9.txt"
        };

        vector<double> numbers1 = readNumbersFromFile(file1Path);

        for (const string& file2Path : file2Paths) {
            vector<double> numbers2 = readNumbersFromFile(file2Path);

            if (numbers1.size() != numbers2.size()) {
                throw runtime_error("Error: The files " + file1Path + " and " + file2Path + " must contain the same number of numbers.");
            }

            vector<double> differences;
            for (size_t i = 0; i < numbers1.size(); ++i) {
                differences.push_back(numbers1[i] - numbers2[i]);
            }

            double sumOfDifferences = accumulate(differences.begin(), differences.end(), 0.0);
            double averageDifference = sumOfDifferences / differences.size();

            int precision = 10;
            cout << fixed << setprecision(precision);

            size_t threadsPos = file2Path.find("threads");
            string threadValue = (threadsPos != string::npos) ? file2Path.substr(threadsPos + 7) : "Unknown";

            cout << "File: " << file2Path << ", Threads: " << threadValue << endl;
            cout << "Average Difference: " << abs(averageDifference) << endl;
        }

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
