#include <iostream>
#include <fstream>
#include <optional>
#include <string>

class NumberLinesReader
{
public:
    NumberLinesReader(const std::string& fileName);
    struct NotANumber;
    struct FileOpeningFailer;
    std::optional<int> ReadNextNumber();
    ~NumberLinesReader()
        {
        Stream.close();
        }
private:
    std::ifstream Stream;
};

int main()
{
    NumberLinesReader reader;
    try 
        {
        reader.Open("numbers.txt");
        int sum = 0;
        while (const auto result = reader.ReadNextNumber())
            {
            sum += result.value();
            }
            std::cout << "sum = " << sum << std::endl;
            
            }
        }
    catch (std::exception const& e)
        {
        std::cerr << "couldn't open file" << std::endl;
        return EXIT_FAILURE;
        }

    catch (std::exception const& e)
        {
        std::cerr << "not a number found" << std::endl;
        return EXIT_FAILURE;
        }

   
   return EXIT_SUCCESS;
}