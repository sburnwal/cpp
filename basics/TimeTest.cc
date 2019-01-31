#include <iostream>
#include <chrono>
#include <ctime>

int main()
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::time_t startTime = std::chrono::system_clock::to_time_t(start);
    std::cout	<< "started at " << startTime << std::endl
    			<< "finished computation at " << std::ctime(&end_time)
    			<< "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
