// #include <array>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
// single producer single consumer
// is there a better construct for single way communication
int numIterations = 500000;
char pad6[64 - sizeof(numIterations)];

class simplebuf
{
private:
    std::mutex lock;
    char pad[64 - sizeof(lock)];

    int buf[8];
    char pad3[64 - sizeof(buf)];

    int head = 0;
    char pad2[64 - sizeof(head)];

    int size = 0;
    char pad1[64 - sizeof(size)];

    std::condition_variable producer_cv;
    char pad_gay[64 - sizeof(producer_cv)];
    
    std::condition_variable consumer_cv;
    char pad_gay2[64 - sizeof(consumer_cv)];

public:
    void add(int val) {
    
        std::unique_lock<std::mutex> lk(lock);

        while (size == 8) {
            producer_cv.wait(lk);
        }
        
        buf[getTail()] = val;
        
        size++;

        consumer_cv.notify_all(); // is there a functional difference between notify one and all here
    }

    int pop() {
        std::unique_lock<std::mutex> lk(lock);

        while (!size) {
            consumer_cv.wait(lk);
        }
        size--;
        int prevhead = head++;        
        head = head & 7;
        producer_cv.notify_all();
        return buf[prevhead];
    }

    int getTail() {
        //std::cout << "tail " << ((head + size) & 7) <<std::endl;
        return (head + size) & 7;
    }
};

simplebuf buffer;

void producer() {
    for (int i = 0; i < numIterations; ++i) {
        buffer.add(i);
    }
}

void consumer() {
    for (int i = 0; i < numIterations; ++i) {
        buffer.pop();
    }
}

int main () {


    std::thread t1 (producer);
    char pad4[64 - sizeof(t1)];

    std::thread t2(consumer);
    char pad5[64 - sizeof(t2)];

    t1.join();
    t2.join();
    printf("%d\n", sizeof(simplebuf));
}