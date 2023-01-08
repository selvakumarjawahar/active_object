# active_object

This repository has the example code for implementing the Active Object architecture design pattern. This example is a companion code for my cppindia talk on the Active objects.
The slides used in the cppindia talk are here <slide url>

This example needs C++17 compliant compiler to build. There are no other external dependencies for building this example. If you want to run clangformat and clang-tidy, you will need to
install clangformat and clang tidy. 

## Building the project        
```bash
git clone <url>                
cd active_objects
mkdir build && cd build
cmake..
make 
make clangformat # Needs clang-format installed
make clang-tidy-check # Needs clang-tidy installed.
```

The code in the repository is a sample code demonstrating the Active Object Pattern. One can take inspiration from this code base and adapt it for production needs.
