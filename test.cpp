#include <cstdio>
#include <thread>
#include <chrono>
#include <cstdlib>

static long count = 0;

int main(){
    printf("hello c plus plus----> %ld\n", count);
    count++;

    int size = 102400;
    while(1) {
        //int* a = new int();
        int* a = (int*) malloc(sizeof(int) * size);
        for(int i = 0; i < size; i++){
            *a = i;
            a++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    //return main();
    return 0;
}