#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

constexpr int CORE_NUMBER = 2;

//int endPos;

using namespace std;

void init_array(vector<long long>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i] = i + 1;
	}
}

/*void put_sum(vector<long long>& arr, int start_index, int end_index) {
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
*/

int calculate_step(int size) {
	return size > 1 ? size / (log(size) / log(CORE_NUMBER)) : 1;
}

int main()
{
	cout << "Enter the array size: ";
	int array_size;
	cin >> array_size;
	vector<long long> arr(array_size);
	init_array(arr);
	int endPos = array_size;
	int midPos = endPos / 2 + endPos % 2;
	long long sum = 0;
	//int step = calculate_step(midPos);
	int wave_count = array_size > 1 ? ceil(log(array_size) / log(2)) : 1;
	for (int w = 0; w < wave_count; w++)
	{
//#pragma omp parallel
		{
			//printf("Threads: %d\n\n", omp_get_num_threads());
#pragma omp parallel for 
			for (int i = 0; i <= midPos; i++)
			{
				//printf("W: %d\tT: %d\ti: %d\n", w,  omp_get_thread_num(), i);
				int right_index = endPos - i - 1;
				if (i < right_index)
				{
//#pragma omp single
					arr[i] += arr[right_index];
				}
			}
		}
		endPos = midPos;
		midPos = endPos / 2 + endPos % 2;
		//step = calculate_step(midPos);
	}
	cout << "Sum: " << arr[0] << endl;
	return 0;
}