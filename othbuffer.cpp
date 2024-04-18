#include <stdint.h>
#include <thread>
#include <iostream>
int  queue_pop(_Atomic uint32_t *queue, int exp);
void queue_pop_commit(_Atomic uint32_t *queue);

int  queue_push(_Atomic uint32_t *queue, int exp);
void queue_push_commit(_Atomic uint32_t *queue);
#define EXP 3  // note; 2**6 == 64

int slots[1<<EXP];
struct queue {
    _Atomic uint64_t head;
    _Atomic uint64_t tail;
};
struct queue buf;
int mask = (1u << EXP) - 1;
int numIterations = 500000;

_Atomic uint32_t  q = 0;
int queue_pop(_Atomic uint32_t *q, int exp)
{
    
    int head = buf.head  & mask;
    int tail = buf.tail  & mask;
    if (head == tail) {
        return -1;
    }
    if (tail & 0x8000) {  // avoid overflow on commit
        buf.tail &= ~0x8000;
    }
    return tail;
}
void queue_pop_commit(_Atomic uint32_t *q)
{
    buf.tail += 1;  // consider "release"
}

int queue_push(_Atomic uint32_t *q, int exp)
{
    int head = buf.head     & mask;
    int tail = buf.tail & mask;
    int next = (head + 1u) & mask;
    if (next == tail) {
        return -1;
    }
    if (head & 0x8000) {  // avoid overflow on commit
        buf.head &= ~0x8000;
    }
    return head;
}
void queue_push_commit(_Atomic uint32_t *q)
{
    buf.head += 1;  // consider "release"
}


void producer() {
    for (int val = 0; val < numIterations; ++val) {
    int i;
    do {
        i = queue_push(&q, EXP);
    } while (i < 0);  // note: busy-wait while full
    slots[i] = val;
    queue_push_commit(&q);
    }
}


void consumer () {
    for (int val = 0; val < numIterations; ++val) {
    int i;
    do {
        i = queue_pop(&q, EXP);
    } while (i < 0);  // note: busy-wait while empty
    int job = slots[i];
    queue_pop_commit(&q);
    //std::cout << job << std::endl;

}
}


int main () {


    // Creating the thread
    memset(&buf, 0, sizeof(queue));
    std::thread t1 (producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}