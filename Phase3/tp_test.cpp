#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"
using namespace std;

int f(int x){
  cout<<"hello"<<x<<endl;
  return x;
}
int main()
{

    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                return f(i);
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    return 0;
}
