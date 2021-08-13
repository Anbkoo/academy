#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <numeric>
#include <iterator>

#pragma optimize("", off)

template<typename It, typename T>
T parallel_accumulate_func(It begin, It end, T init,
    std::function<T(T)>& func,
    std::size_t threads_number = std::thread::hardware_concurrency())
    {
    const std::size_t elements_number = std::distance(begin, end);
    const std::size_t elements_per_thread =
        static_cast<size_t>(std::ceil(static_cast<double>(elements_number) / threads_number));

    const std::size_t used_threads_number = 
        static_cast<size_t>(std::ceil(static_cast<double>(elements_number) / elements_per_thread));

    std::vector<std::thread> threads(used_threads_number);
    std::vector<T> sums(used_threads_number, 0);

    It cur_begin = begin;
    It cur_end = begin;

    for (auto i = 0; i < used_threads_number; ++i)
        {
        if (i == used_threads_number - 1)
            {
            cur_end = end;
            }
        else 
            {
            std::advance(cur_end, elements_per_thread);
            }

        threads[i] = std::thread(
            [cur_begin, cur_end, &func, &sums, i]()
            {
            T sum = 0;
            for (It it = cur_begin; it < cur_end; ++it)
                {
                sum += func(*it);
                }
            sums[i] = sum;
            });

        cur_begin = cur_end;
        }

    for (auto i = 0; i < used_threads_number; ++i)
        threads[i].join();

    return std::accumulate(sums.begin(), sums.end(), init);
    }

template <typename T>
T parallel_accumulate_cycle(const std::vector<T>& values, 
    std::function<T(T)>& func,
    std::size_t threads_number = std::thread::hardware_concurrency())
    {
    if (threads_number > values.size())
        threads_number = values.size();

    std::vector<std::thread> threads(threads_number);
    std::vector<T> sums(threads_number, 0);

    for (auto i = 0; i < threads_number; ++i)
        {
        threads[i] = std::thread([&values, func, &sums, i, threads_number]
            {
            T sum = 0;
            for (size_t j = i; j < values.size(); j += threads_number)
                sum += func(values[j]);

            sums[i] = sum;
            });
        }

    for (auto i = 0; i < threads_number; ++i)
        threads[i].join();

    return std::accumulate(sums.begin(), sums.end(), 0);
    }

int main()
{
    const std::size_t size = 100'000'000;
    std::vector<double>values(size, std::rand());

    for (auto v : values)
        {
        v = std::rand();
        }
        

    std::function<double(double)> func = [](double value)
        {
        const std::size_t sqrt_number = 10;
        for (auto i = 0; i < sqrt_number; ++i)
            value = sqrt(value);
        return value;
        };

    // sequen exec;
    auto start = std::chrono::system_clock::now();
    double seq_num = 0; 
    for (auto i = 0; i < size; ++i)
        seq_num += func(values[i]);

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << seq_num << std::endl;
    std::cout << duration.count() << std::endl;

    // parralel exec;
    start = std::chrono::system_clock::now();
    double parallel_sum =
        parallel_accumulate_func(
            values.begin(), values.end(), 0.0, func, 8);

    end = std::chrono::system_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << parallel_sum << std::endl;
    std::cout << duration2.count() << std::endl;


    // parralel cycle exec;
    start = std::chrono::system_clock::now();
    double parallel_sum_cycle =
        parallel_accumulate_cycle(
            values, func, 8);

    end = std::chrono::system_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << parallel_sum << std::endl;
    std::cout << duration3.count() << std::endl;

    std::cout << "speed up : " << (double)duration.count() / duration2.count() << std::endl;
    std::cout << "speed up cycle: " << (double)duration.count() / duration3.count() << std::endl;

    std::cin.get();
    return EXIT_SUCCESS;
}