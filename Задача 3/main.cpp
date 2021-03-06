#include <iostream>
#include <iomanip>
#include <functional>
#include <vector>
#include <boost/functional/hash.hpp>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

int N = 700;

struct Human {
    unsigned int age;
    char name;
    friend size_t hash_value(const Human& h);
};

size_t hash_value(const Human& h){
  size_t seed = 0;
  boost::hash_combine(seed, h.age);
  boost::hash_combine(seed, h.name);
  return seed;
}

int main(int argc, char ** argv)
{
    vector <Human> humans(N);
    vector <size_t> hashes(N);
    unsigned int j = 20U;
    int k = 65;
    int r = 0;
    for (int i = 0; i < N; i++) {
        srand(time(0) * r++ * 7);
        humans[i] = {j + (rand() % 70), char(k + rand() % 36)};
        hashes[i] = hash_value(humans[i]);
    }

//    for (int i = 0; i < N; i++) {
//        std::cout << humans[i].age << " " << humans[i].name << std::endl;
//    }

    std::string outFile_1 = "out.dat";
    std::ofstream out_1(outFile_1);

    if (!out_1.is_open()) {
        std::cerr << "Can not open: " << outFile_1 << std::endl;
        return EXIT_FAILURE;
    }

    for (unsigned int k = 50; k < N; k++) {
        vector <size_t> dub;
        int count = 0;

        for (int i = 0; i < k - 1; i++) {
            bool fl = true;

            for (int j = 0; j < dub.size(); j++) {
                if (dub[j] == hashes[i]) {
                    fl = false;
                    break;
                }
            }

            if (fl == true) {
                dub.push_back(hashes[i]);

                for (int j = i + 1; j < k; j++) {
                    if (hashes[j] == hashes[i]) {
                        count++;
                    }
                }
            }
        }

        out_1 << k + 1 << "\t" << count << "\n";
    }

    out_1.close();
	return EXIT_SUCCESS;
}
