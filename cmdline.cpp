#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include "cmdline.h"
#include<iostream>

void use_arguments(int argc, char* argv[]){
    // std::cout << argc << std::endl;
    bool testCmdSeen = false;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i],"--help") == 0){
            std::cout << "Allowed Arguments: --test --help" << std::endl;
            exit(0);
        } else if(strcmp(argv[i],"--test") == 0 ){
            if(!testCmdSeen){
                testCmdSeen = true;
                if(Catch::Session().run(1, argv) !=0){
                    exit(1);
                }

            } else{
                std::cerr << "Test command already seen!!" << std::endl;
                exit(1);
            }
        } else{
            std::cerr << "Enter valid argument!!!" << std::endl;
            exit(1);
        }
    }
    
    
}