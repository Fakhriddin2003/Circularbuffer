// here's an implementation of a circular buffer class with the push, pop, and size methods in C++.
#include <stdexcept>
#include <vector>

class CircularBuffer {
public:
    CircularBuffer(int capacity) : capacity_(capacity), buffer_(capacity), head_(0), tail_(0), count_(0), empty_(true) {}

    void push(int element) {
        if (count_ == capacity_) {
            throw std::out_of_range("Buffer is full");
        }
        buffer_[tail_] = element;
        tail_ = (tail_ + 1) % capacity_;
        count_++;
        empty_ = false;
    }

    int pop() {
        if (count_ == 0) {
            throw std::out_of_range("Buffer is empty");
        }
        int element = buffer_[head_];
        buffer_[head_] = 0;
        head_ = (head_ + 1) % capacity_;
        count_--;
        if (count_ == 0) {
            empty_ = true;
        }
        return element;
    }

    int size() const {
        return count_;
    }

    bool empty() const {
        return empty_;
    }

private:
    int capacity_;
    std::vector<int> buffer_;
    int head_;
    int tail_;
    int count_;
    bool empty_;
};



//And here are some unit tests to check the implementation:

    #include <cassert>

int main() {
    // Test creating a buffer with capacity 3
    CircularBuffer buffer(3);
    assert(buffer.size() == 0);
    assert(buffer.empty() == true);

    // Test pushing elements onto the buffer
    buffer.push(1);
    assert(buffer.size() == 1);
    assert(buffer.empty() == false);
    buffer.push(2);
    assert(buffer.size() == 2);
    buffer.push(3);
    assert(buffer.size() == 3);
    assert(buffer.empty() == false);

    // Test pushing onto a full buffer
    try {
        buffer.push(4);
    }
    catch (const std::out_of_range& e) {
        assert(e.what() == std::string("Buffer is full"));
    }

    // Test popping elements from the buffer
    assert(buffer.pop() == 1);
    assert(buffer.size() == 2);
    assert(buffer.empty() == false);
    assert(buffer.pop() == 2);
    assert(buffer.size() == 1);
    assert(buffer.empty() == false);
    assert(buffer.pop() == 3);
    assert(buffer.size() == 0);
    assert(buffer.empty() == true);

    // Test popping from an empty buffer
    try {
        buffer.pop();
    }
    catch (const std::out_of_range& e) {
        assert(e.what() == std::string("Buffer is empty"));
    }

    // Test pushing and popping elements repeatedly
    buffer.push(1);
    buffer.pop();
    buffer.push(2);
    buffer.pop();
    buffer.push(3);
    buffer.pop();
    assert(buffer.size() == 0);
    assert(buffer.empty() == true);

    return 0;
}