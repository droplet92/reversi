#pragma once
#include <chrono>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std::chrono;

namespace yothello
{
	static const char* logpath = "log";

	class Logger
	{
	public:
		~Logger() {}

		static Logger& instance()
		{
			static Logger* logger = new Logger();
			return *logger;
		}

		void write(std::string s)
		{
			printf("%s", s.data());
			s.push_back('\n');
			writer.write(s.data(), s.length());
			writer.flush();
		}

		void timestamp()
		{
			auto now = std::chrono::system_clock::now();
			auto now_time_t = std::chrono::system_clock::to_time_t(now);
			write(std::ctime(&now_time_t));
		}
		inline void begins()
		{
			write("###");
			timestamp();
		}
	private:
		Logger() :writer(logpath, std::ofstream::out | std::ofstream::app)
		{
		}
		std::ofstream writer;
	};
}