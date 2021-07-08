#include <iostream>    
#include <chrono>
#include <vector>
#include <unordered_map>
#include <random> 
#include <ctime>

using namespace std::chrono;

int main() 
{
    std::vector<int> vect;
    std::unordered_map<int, int> un_map;

    // mersenne twister
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(0, 1);

    // standard 
    srand(time(0));

    system_clock::time_point start_vect, start_un_map, end_vect, end_un_map;

    int temp, index_of_one;
    bool un_map_lower = false;
    while (true) 
        {
        // generate random 
        //temp = uid(gen);
        temp = rand() % 2;
        
        start_vect = system_clock::now();
        vect.push_back(temp);
        end_vect = system_clock::now();

        // check if random is 1 and count time for insert
        if (temp)
            {
            index_of_one = vect.size();
            start_un_map = system_clock::now();
            un_map.insert({ index_of_one, temp });
            end_un_map = system_clock::now();
            }

        auto end1 = end_un_map - start_un_map, end2 = end_vect - start_vect;
        if (end1 > end2)
            {
            un_map_lower = true;
            }

        else if ((end2 > end1) && un_map_lower)
            {
            break;
            }
        }


    std::cout << "size of vector: " << vect.size() << "\t" << "capacity of vector: " << vect.capacity() << std::endl;
    std::cout << "size of un_map: " << un_map.size() << std::endl;
    std::cout << "percentage " << static_cast<double>(un_map.size()) / vect.size() << std::endl;

    std::cin.get();
    return 0;
}
