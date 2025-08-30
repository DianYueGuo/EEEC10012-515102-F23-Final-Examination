#include <iostream>
#include <string>

void process_cli_arguments(
    const char* const argv[],
    std::string &input_file_name,
    std::string &task1_out_file_name,
    std::string &task2_out_file_name,
    std::string &task3_out_file_name
);

int main(int argc, char *argv[]) {

    std::string input_file_name;
    std::string task1_out_file_name;
    std::string task2_out_file_name;
    std::string task3_out_file_name;

    if (argc != 1 + 4) {
        std::cout << "Exception: should have 4 arguments instead of " << (argc - 1) << std::endl;
        return 0;
    }

    process_cli_arguments(argv, input_file_name, task1_out_file_name, task2_out_file_name, task3_out_file_name);

    return 0;
}

void process_cli_arguments(
    const char* const argv[],
    std::string &input_file_name,
    std::string &task1_out_file_name,
    std::string &task2_out_file_name,
    std::string &task3_out_file_name
) {
    input_file_name.assign(argv[1]);
    task1_out_file_name.assign(argv[2]);
    task2_out_file_name.assign(argv[3]);
    task3_out_file_name.assign(argv[4]);
}
