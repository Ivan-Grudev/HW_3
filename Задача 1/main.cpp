#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;

int main()
{
    const auto size = 5000U;

	vector <int> v(size);
    array <int, size> a;
    set <int> set;

    int r = 0;

	for (size_t i = 0; i < size; i++)
	{
        srand(time(0) * r++ * 7);
        int k = rand() % 100;
		v[i] = k;
		a[i] = k;
    }

    auto now = std::chrono::system_clock::now();
    for (size_t i = 0; i < size; i++) {
        set.insert(v[i]);
    }
    auto end = std::chrono::system_clock::now();
	int elapsed_set = std::chrono::duration_cast<std::chrono::microseconds>(end - now).count();
	int elapsed = elapsed_set;
	string elapsed_str = "Set";

    now = std::chrono::system_clock::now();
	sort(v.begin(), v.end());
	end = std::chrono::system_clock::now();
	int elapsed_v = std::chrono::duration_cast<std::chrono::microseconds>(end - now).count();
	if (elapsed > elapsed_v)
    {
        elapsed = elapsed_v;
        elapsed_str = "Vector";
    }

    now = std::chrono::system_clock::now();
	sort(a.begin(), a.end());
	end = std::chrono::system_clock::now();
	int elapsed_a = std::chrono::duration_cast<std::chrono::microseconds>(end - now).count();
	if (elapsed > elapsed_a)
    {
        elapsed = elapsed_a;
        elapsed_str = "Array";
    }

    cout << "Results (in microseconds):" << endl <<
    "Vector sorting time is " << elapsed_v << endl <<
    "Array sorting time is " << elapsed_a << endl <<
    "Set sorting time is " << elapsed_set << endl;

    cout << endl << elapsed_str << " has the fastest sort"; 
    return 0;
}
