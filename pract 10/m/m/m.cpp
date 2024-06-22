#include <iostream>
#include <vector>
#include <thread>
using namespace std;

class ParallelMergeSort {
public:
    void sort(vector<int>& array) {
        if (array.size() > 1) {
            auto mid = array.size() / 2;
            vector<int> left(array.begin(), array.begin() + mid);
            vector<int> right(array.begin() + mid, array.end());

            thread left_thread([this, &left]() { sort(left); });
            thread right_thread([this, &right]() { sort(right); });

            left_thread.join();
            right_thread.join();

            merge(array, left, right);
        }
    }

private:
    void merge(vector<int>& array, const vector<int>& left, const vector<int>& right) {
        size_t left_index = 0, right_index = 0, merged_index = 0;

        while (left_index < left.size() && right_index < right.size()) {
            if (left[left_index] <= right[right_index]) {
                array[merged_index++] = left[left_index++];
            }
            else {
                array[merged_index++] = right[right_index++];
            }
        }

        while (left_index < left.size()) {
            array[merged_index++] = left[left_index++];
        }

        while (right_index < right.size()) {
            array[merged_index++] = right[right_index++];
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> array(10);
    cout << "Введите 10 целых чисел: ";
    for (int& num : array) {
        cin >> num;
    }

    ParallelMergeSort sorter;

    thread sort_thread([&sorter, &array]() { sorter.sort(array); });
    sort_thread.join();

    cout << "Отсортированный массив: ";
    for (const int& num : array) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
