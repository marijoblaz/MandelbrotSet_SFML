#include <iostream>
#include <vector>
#include "merge_sort.h"

std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> result;
    while ((int)left.size() > 0 || (int)right.size() > 0) {
        if ((int)left.size() > 0 && (int)right.size() > 0) {
            if ((int)left.front() <= (int)right.front()) {
                result.push_back((int)left.front());
                left.erase(left.begin());
            }
            else {
                result.push_back((int)right.front());
                right.erase(right.begin());
            }
        }
        else if ((int)left.size() > 0) {
            for (int i = 0; i < (int)left.size(); i++)
                result.push_back(left[i]);
            break;
        }
        else if ((int)right.size() > 0) {
            for (int i = 0; i < (int)right.size(); i++)
                result.push_back(right[i]);
            break;
        }
    }
    return result;
}

std::vector<int> merge_sort(std::vector<int> m)
{
	if (m.size() <= 1)
		return m;

	std::vector<int> left, right, result;
	int middle = ((int)m.size() + 1) / 2;

	for (int i = 0; i < middle; i++) {
		left.push_back(m[i]);
	}

	for (int i = middle; i < (int)m.size(); i++) {
		right.push_back(m[i]);
	}

	left = merge_sort(left);
	right = merge_sort(right);
	result = merge(left, right);

	return result;
}