#include <iostream>
#include <Loader.hh>

int main(int argc, char** argv) {

    Loader* loader = new Loader(argc,argv);
    delete loader;

    return 0;
}