#include <iostream>
#include <Loader.hh>

// v0.4

int main(int argc, char** argv) {

    Loader* loader = new Loader(argc,argv);
    delete loader;

    return 0;
}