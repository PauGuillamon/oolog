
#include <mutex>

class Lock {
	public:
		explicit Lock(std::mutex& mutexToLock) : mutex(mutexToLock) {
			mutex.lock();
		}

		~Lock() {
			mutex.unlock();
		}

	private:
		std::mutex& mutex;
};