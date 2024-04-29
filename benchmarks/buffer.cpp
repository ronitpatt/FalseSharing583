#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <optional>
#include <functional>
#include <atomic>

// single producer single consumer
// atomics
int numIterations = 5000000;
class simplebuf
{    
public:
    int buf[8];
    // char pad[32];
    int head {0};
    // char pad1[60];
    int tail {0};
    // char pad2[60];
    std::atomic<int> size {0};
    // char pad3[60];


    bool add(int val) {
        if (size == 8) {
            return false;
        }
        buf[tail] = val;
        size++;
        tail = (tail + 1) & 7;
        return true;
    }

    std::optional<int> pop() {
        if (size == 0) {
            return {};
        }
        int val = buf[head];
        head = (head + 1 )& 7;
        size--;
        return val;
    }

};

void* producer(void* b) {
    simplebuf* buffer = (simplebuf*)b;
    for (int i = 0; i < numIterations; ++i) {
        while (!buffer->add(i));
    }
    return nullptr;
}

void* consumer(void* b) {
    simplebuf* buffer = (simplebuf*)b;
    for (int i = 0; i < numIterations; ++i) {
        int val = 0;
        while (true) {
            auto res = buffer->pop();
            if (res.has_value()) {
                val = res.value();
                //printf("%d\n", val);
                break;
            }
        }

    }
    return nullptr;
}

int main () {


    // Creating the thread
    simplebuf buffer;
    printf("%p\n", &buffer.head);
    printf("%p\n", &buffer.tail);
    printf("%p\n", &buffer.size);
    pthread_t ptid1, ptid2; 
    pthread_create(&ptid1, NULL, &producer, (void*) &buffer); 
    pthread_create(&ptid2, NULL, &consumer, (void*) &buffer); 

    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);

}
// 0x7fff8b7783f0
// 0x7fff8b778430
// 0x7fff8b778470