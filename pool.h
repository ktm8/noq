#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class Pool {
public:
	Pool(std::size_t);
	~Pool();

	template<typename F, typename... Args>
	void add_task(F f, Args... args)
	{
		this->real_add_task(std::bind(f, args...));
	}

private:
	void loop(void);
	void real_add_task(std::function<void()> task);

	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks;

	std::mutex mutex;
	std::condition_variable cond;
	bool done;
};
