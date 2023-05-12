#pragma once
#include <iostream>
#include <chrono>

class SimpleTimer 
{
public:
	SimpleTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~SimpleTimer()
	{
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		
		std::cout << "complited in: " << std::fixed << duration.count() << " s";
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};