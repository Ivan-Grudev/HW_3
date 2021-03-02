#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>

unsigned int hash(double d)
{
	auto h = 0U;
	h = fmod(d, 17) * pow(d, 3);
	return fmod(h, 128);
}

const int N = 1000;

int main(int argc, char ** argv)
{
    //Проверка времени работы
    auto now = std::chrono::system_clock::now();
	std::cout << hash(52.489) << std::endl;
	auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - now);
    std::cout << "Hash-function work time (in microseconds): " << elapsed.count() << std::endl;

    std::vector <int> hashes(N);
    std::vector <double> v(N);
    int r = 0;
    for (int i = 0; i < N; i++)
    {
        srand(time(0) * r++ * 17);
        v[i] = rand() % 700 + (rand() % 100) / (double)100;
        hashes[i] = hash(v[i]);
//        std::cout << v[i] << std::endl;
    }
    std::cout << std::endl;

    std::string outFile_1 = "out.dat";
    std::ofstream out_1(outFile_1);

    if (!out_1.is_open()) {
        std::cerr << "Can not open: " << outFile_1 << std::endl;
        return EXIT_FAILURE;
    }

    for (auto i = 0U; i < N; i++) {
        out_1 << v[i] << "\t" << hash(v[i]) << "\n";
    }

    out_1.close();

    std::string outFile_2 = "collision.dat";
    std::ofstream out_2(outFile_2);

    if (!out_2.is_open()) {
        std::cerr << "Can not open: " << outFile_2 << std::endl;
        return EXIT_FAILURE;
    }

for (int k = 1; k < N; k++) {
        std::vector <size_t> Rep;
        int count = 0;

        for (size_t i = 0; i < k - 1; i++)
        {
            bool t = true;

            for (size_t j = 0; j < Rep.size(); j++)
            {
                if (Rep[j] == hashes[i])
                {
                    t = false;
                    break;
                }
            }

            if (t == true)
            {
                Rep.push_back(hashes[i]);

                for (size_t j = i + 1; j < k; j++)
                {
                    if (hashes[j] == hashes[i])
                    {
                        count++;
                    }
                }
            }
        }

        out_2 << k + 1 << "\t" << count << "\n";
    }
    out_2.close();
	return 0;
}
