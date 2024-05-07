#include <queue>
#include <mutex>
#include <optional>

template <typename T>
class thread_safe_fifo {
	size_t			max_size;
	std::queue<T>		q;
	std::mutex		mutex;
public:
	thread_safe_fifo(size_t size):max_size(size) {
	}

	bool push(T v) {
		mutex.lock();
		if(q.size() <= max_size) {
			q.emplace(v);
			mutex.unlock();
			return true;
		}
		mutex.unlock();
		return false;
	}

	std::optional<T> pop() {
		mutex.lock();
		if(q.empty()) {
			mutex.unlock();
			return {};
		}
		T r(q.front());
		q.pop();
		mutex.unlock();
		return r;
	}

	size_t size() {
		mutex.lock();
		size_t r = q.size();
		mutex.unlock();
		return r;
	}
};