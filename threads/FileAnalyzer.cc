#include <iostream>
#include <fstream>
#include <unordered_map>
#include <thread>
#include <chrono>

std::mutex gMutex;
std::condition_variable gCV;
bool gProcessingDone = false;

class WordProcessor {
private:
	std::string filePath;
	std::unordered_map<std::string, int>& wordCounts;		//use hash map

public:
	WordProcessor(std::string file, std::unordered_map<std::string, int>& counts) : filePath(file), wordCounts(counts) {
		std::cout << std::this_thread::get_id() << " Constructor WordProcessor for file " << filePath << std::endl;
	}

	~WordProcessor() {
		std::cout << std::this_thread::get_id() << " Destructor WordProcessor" << std::endl;
	}

public:
	std::string& getFilePath() {
		return filePath;
	}

public:
	//thread functor
	void operator()() {
		auto start = std::chrono::system_clock::now();
		std::ifstream instream(filePath, std::ios::in);
		if (instream.is_open()) {
			std::string line;
			while(!std::getline(instream, line).eof()) {
				if (instream.bad() || instream.fail()) {
					std::cout << std::this_thread::get_id() << " File stream error occurred" << std::endl;
					return;
				}

				std::string word;
				for (int i = 0; i < line.size(); i++) {
					if (std::isalpha(line.at(i))) {
						word += line.at(i);	//append the char. word.append(1, line.at(i)) also ok
					} else {
						//no possible word to process
						if (word.size() <= 0) {
							continue;
						}

						std::unordered_map<std::string, int>::iterator itr = wordCounts.find(word);
						if (itr != wordCounts.end()) {
							std::cout << std::this_thread::get_id() << " Found existing word " << word << std::endl;
							++itr->second;
						} else {
							std::cout << std::this_thread::get_id() << " Adding new word " << word << std::endl;
							wordCounts.insert(std::make_pair(word, 1));
						}
						word.clear();
					}
				}
			}
		} else {
			std::cout << std::this_thread::get_id() << " Could not open file " << filePath << std::endl;
		}

		//notify any condition variable waiting on the lock
		gProcessingDone = true;
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> dura = end - start;
		std::cout << std::this_thread::get_id() << " Time taken to find all the words " << dura.count() << std::endl;

		std::cout << std::this_thread::get_id() << " Notifying results are available..." << std::endl;
		gCV.notify_one();
	}
};

class ResultDisplayer {
private:
	std::unordered_map<std::string, int>& wordCounts;

public:
	ResultDisplayer(std::unordered_map<std::string, int>& c): wordCounts(c) {
		std::cout << std::this_thread::get_id() << " Constructor ResultsDisplayer" << std::endl;
	}

	~ResultDisplayer() {
		std::cout << std::this_thread::get_id() << " Destructor ResultsDisplayer" << std::endl;
	}

public:
	void operator()() {
		//Wait till the results are available
		std::unique_lock<std::mutex> lock(gMutex);
		std::cout << std::this_thread::get_id() << " Waiting for results..." << std::endl;
		gCV.wait(lock, []{
				return gProcessingDone;
		});
		std::cout << std::this_thread::get_id() << " ---- Word Count Result ----" << std::endl;
		for (auto itr = wordCounts.begin(); itr != wordCounts.end(); itr++) {
			std::cout << std::this_thread::get_id() << " " << itr->first << "\t" << itr->second << std::endl;
		}
	}
};

int main(int argc, char* argv[]) {
	std::cout << std::this_thread::get_id() << " Running File Analyzer..." << std::endl;
	std::unordered_map<std::string, int> wordCounts;

	//start the worker and displayer threads
	WordProcessor processor("/Users/sburnwal/Projects/ACI/temp/tests.log", wordCounts);
	std::thread processorThread(std::ref(processor));	//important to pass as reference, else they are copied

	ResultDisplayer displayer(wordCounts);
	std::thread displayThread(std::ref(displayer));

	//wait for the threads to finish
	processorThread.join();
	displayThread.join();
}
