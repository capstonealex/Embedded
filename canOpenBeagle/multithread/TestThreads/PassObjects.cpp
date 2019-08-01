//
// Created by William Campbell on 2019-08-01.
//

#include <iostream>
#include <thread>

class Exmaple {
private:
    int counter;

public:
    Exmaple() {
        counter = 0;
    }

    void doSomthing(){
        counter++;
    }

    void print() {
        std::cout << "value from A: " << counter << std::endl;
    }

};

// notice that the object is passed by reference
void thread_task(Exmaple& o) {
    o.doSomthing();
    o.print();
}

int main()
{
    Exmaple b;
    for(int i =0; i < 10; i++) {
        std::thread t1(thread_task, std::ref(b));
        t1.join();
    }
    return 0;
}