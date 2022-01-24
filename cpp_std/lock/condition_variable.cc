#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>


std::mutex mtx;
std::condition_variable cv;
std::string data;

bool ready{false};
bool processed{false};

void worker_thread() {
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait( lk, []{ return ready; } );

    std::cout << "Worker thread is processing data \n";

    data += " worker added ";
    processed = true;
    std::cout << "worker thread signals data processing completed \n";

    lk.unlock();
    cv.notify_one();
}


int main() {
    std::thread worker(worker_thread);
    data = "Example Data for Test";
    {   
        std::cout << "111111 \n";
        std::lock_guard<std::mutex> lk(mtx);
        ready = true;
        std::cout << " main() signals data ready for processing \n";
    }
    std::cout << " notify_one";
    cv.notify_one();

    {
        std::cout << "unique_lock";
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, []{ return processed; } );
    }

    std::cout << " back in main()\n data = " << data << " \n";
    worker.join();

    return 0;
}




