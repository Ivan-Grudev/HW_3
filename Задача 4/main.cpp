#include <iostream>
#include <vector>
#include <clocale>
#include <sstream>
#include <stdlib.h>

int N = 3000;
const char* ar[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s",
        "t", "u", "v", "w", "x", "y", "z" };

void run(std::vector <size_t> hashes)
{
        for (int k = 11; k < N; k++) {
        std::vector <size_t> dub;
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

        std::cout << "N = " << k + 1 << "; collisions amount = " << count << std::endl;
    }
}

unsigned int RSHash(const char* str, unsigned int length)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a = a * b;
    }

    return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits =
        (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
            (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}

int main()
{
    std::vector <std::string> strings(N);
    for (size_t j = 0; j < strings.size(); j++)
    {
        for (size_t i = 0; i < 6; i++)
        {
            strings[j] += ar[rand() % 25];
        }
    }
    //for (size_t j = 0; j < strings.size(); j++)
    //{
    //    cout << strings[j] << endl;
    //}

    std::vector <size_t> hashes(N);
    /* for (size_t j = 0; j < strings.size(); j++)
     {
         hashes[j] = RSHash(strings[j].c_str(), N);
     }
     run(hashes);
     std::cout << std::endl;*/

     //for (size_t j = 0; j < strings.size(); j++)
     //{
     //    hashes[j] = JSHash(strings[j].c_str(), N);
     //}
     //run(hashes);
     //std::cout << std::endl;

     //for (size_t j = 0; j < strings.size(); j++)
     //{
     //    hashes[j] = PJWHash(strings[j].c_str(), N);
     //}
     //run(hashes);
     //std::cout << std::endl;

     /*for (size_t j = 0; j < strings.size(); j++)
     {
         hashes[j] = ELFHash(strings[j].c_str(), N);
     }
     run(hashes);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < strings.size(); j++)
     {
         hashes[j] = BKDRHash(strings[j].c_str(), N);
     }
     run(hashes);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < strings.size(); j++)
     {
         hashes[j] = SDBMHash(strings[j].c_str(), N);
     }
     run(hashes);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < strings.size(); j++)
     {
         hashes[j] = DJBHash(strings[j].c_str(), N);
     }
     run(hashes);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < strings.size(); j++)
     {
         hashes[j] = DEKHash(strings[j].c_str(), N);
     }
     run(hashes);
     std::cout << std::endl;*/

    for (size_t j = 0; j < strings.size(); j++)
    {
        hashes[j] = APHash(strings[j].c_str(), N);
    }
    run(hashes);
    std::cout << std::endl;

    system("pause");
    return 0;
}
