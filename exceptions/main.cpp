#include <iostream>
#include <fstream>
#include <string>

class NumberLinesReader
{
public:
    enum class ReadResult
    {
        OK,
        EndOfFile,
        NotANumber
    };
    void Open(const std::string& fileName) 
        {
        Stream.open(fileName);
        Stream.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        };
    ReadResult ReadNextNumber(int& number) 
        {
        return ReadResult::OK;
        };

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
    int sum = 0;
    try 
        {
        reader.Open("numbers.txt");
        int number = 0;
        while (true)
            {
            const auto result = reader.ReadNextNumber(number);
            try {
                if (result == NumberLinesReader::ReadResult::NotANumber)
                    throw;

                sum += number;
                }
            catch (...)
                {
                std::cerr << "not a number found" << std::endl;
                reader.~NumberLinesReader();
                return EXIT_FAILURE;
                }
            }
        }
    catch (std::exception const& e)
        {
        std::cerr << "could not open file" << std::endl;
        return EXIT_FAILURE;
        }

   std::cout<< "sum = " << sum << std::endl;
   return EXIT_SUCCESS;
}