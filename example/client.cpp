#include "interface_proxy.h"    
#include <iostream>


int main()
{
    std::cout << "Hello world from client \n";
    active_object::Proxy client_proxy;
    auto result_future = client_proxy.GetPrediction("Some Input");
    auto result = result_future.get();
    std::cout << "Result = " << result.data << '\n';
    return 0;
}
