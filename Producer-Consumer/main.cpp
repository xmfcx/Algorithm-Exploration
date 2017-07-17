
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <condition_variable>

std::mutex mx;
std::condition_variable cv;
std::queue<unsigned long> q;

bool finished = false;

void producer(unsigned long n) {
  for (unsigned long i = 0; i < n; ++i) {
    {
      std::lock_guard<std::mutex> lk(mx);
      q.push(i);
      std::cout << "pushing " << i << std::endl;
    }
    cv.notify_all();
  }
  {
    std::lock_guard<std::mutex> lk(mx);
    finished = true;
  }
  cv.notify_all();
}

void consumer() {
  while (true) {
    std::unique_lock<std::mutex> lk(mx);
    cv.wait(lk, [] { return finished || !q.empty(); });
    while (!q.empty()) {
      std::cout << "consuming " << q.front() << std::endl;
      q.pop();
    }
    if (finished) break;
  }
}

int main() {
  std::thread t1(producer, 9999999999);
  std::thread t2(consumer);
  t1.join();
  t2.join();
  std::cout << "finished!" << std::endl;
}