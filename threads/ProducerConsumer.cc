#include <iostream>
#include <thread>
#include <list>

int MAX_SIZE = 5;
std::mutex gMutex;
std::condition_variable gCV;

class Producer {
private:
	std::list<int>& numbers;

public:
	Producer(std::list<int>& l): numbers(l) {
		std::cout << std::this_thread::get_id() << " Constructor Producer" << std::endl;
	}

	~Producer() {
		std::cout << std::this_thread::get_id() << " Destructor Producer" << std::endl;
	}

public:
	void start() {
		//generate 100 random numbers and add to queue for consumer
		for (int i = 0; i < 100; i++) {
			//wait if queue full
			std::unique_lock<std::mutex> lock(gMutex);
			std::cout << std::this_thread::get_id() << " Producer lock" << std::endl;
			gCV.wait(lock, [this]{
				return this->numbers.size() < MAX_SIZE;
			});

			int num = std::rand() % 1000;
			std::cout << std::this_thread::get_id() << " Produced " << num << std::endl;
			numbers.push_back(num);
			//notify waiting threads
			std::cout << std::this_thread::get_id() << " Producer notify" << std::endl;
			gCV.notify_all();
		}
	}
};

class Consumer {
private:
	std::list<int>& numbers;

public:
	Consumer(std::list<int>& l): numbers(l) {
		std::cout << std::this_thread::get_id() << " Constructor Consumer" << std::endl;
	}

	~Consumer() {
		std::cout << std::this_thread::get_id() << " Destructor Consumer" << std::endl;
	}

public:
	void start() {
		for(int i = 0; i < 100; i++) {
			std::unique_lock<std::mutex> lock(gMutex);
			std::cout << std::this_thread::get_id() << " Consumer lock" << std::endl;
			//wait if queue is empty
			gCV.wait(lock, [this]{
				return this->numbers.size() > 0 ;
			});

			int num = numbers.front();
			numbers.pop_front();
			std::cout << std::this_thread::get_id() << " Consumed " << num << std::endl;
			//notify waiting threads
			std::cout << std::this_thread::get_id() << " Consumer notify" << std::endl;
			gCV.notify_all();
		}
	}
};


int main(int argc, char* argv[]) {
	std::list<int> buffer;
	Producer p(std::ref(buffer));
	std::thread pThread(&Producer::start, &p);

	Consumer c(std::ref(buffer));
	std::thread cThread(&Consumer::start, &c);

	pThread.join();
	cThread.join();
}
