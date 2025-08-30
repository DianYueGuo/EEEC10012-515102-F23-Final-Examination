#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    if (argc != 1 + 4) {
        std::cout << "Exception: should have 4 arguments instead of " << (argc - 1) << std::endl;
        return 0;
    }

    std::string input_file_name(argv[1]);
    std::string task1_out_file_name(argv[2]);
    std::string task2_out_file_name(argv[3]);
    std::string task3_out_file_name(argv[4]);

    return 0;
}
