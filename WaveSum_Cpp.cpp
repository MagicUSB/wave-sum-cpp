#include <iostream>
#include <vector>
#include <cmath>

constexpr int CORE_NUMBER = 2;

int endPos;

using namespace std;

void init_array(vector<long long>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i] = i + 1;
	}
}

void put_sum(vector<long long>& arr, int start_index, int end_index) {
	int right_index;
	for (int i = start_index; i < end_index; i++)
	{
		right_index = endPos - i - 1;
		if (i < right_index)
		{
			arr[i] += arr[right_index];
		}
	}
}

int calculate_step(int size) {
	return size > 1 ? size / (log(size) / log(CORE_NUMBER)) : 1;
}

int main()
{
	cout << "Enter the array size: ";
	int arr_size;
	cin >> arr_size;
	vector<long long> arr(arr_size);
	init_array(arr);
	endPos = arr_size;
	int midPos = endPos / 2 + endPos % 2;
	long long sum = 0;
	int step = calculate_step(midPos);
	int i = 0;
	int wave_count = arr_size > 1 ? ceil(log(arr_size) / log(2)) : 1;
	for (int w = 0; w < wave_count; w++)
	{
		while (i <= midPos)
		{
			put_sum(arr, i, min(i + step, midPos));
			i += step;
		}
		endPos = midPos;
		midPos = endPos / 2 + endPos % 2;
		step = calculate_step(midPos);
		i = 0;
	}
	cout << "Sum: " << arr[0] << endl;
	return 0;
}