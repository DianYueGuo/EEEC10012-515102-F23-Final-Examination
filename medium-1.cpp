#include <iostream>
#include <fstream>
#include <sstream>

#include "room_list.h"
#include "reservation_list.h"

void read_line_clean(std::ifstream &input_file_stream, std::string &read_line);

void read_number_of_rooms(std::ifstream &input_file_stream, int &number_of_rooms);
void read_room_data(std::ifstream &input_file_stream, RoomList &room_list);
void read_number_of_reservations(std::ifstream &input_file_stream, int &number_of_reservations);
void read_reservation_data(std::ifstream &input_file_stream, ReservationList &reservation_list);

void output_task1_file(const std::string &task1_out_file_name, const ReservationList &reservation_list, const RoomList &room_list);
void output_task2_file(const std::string &task2_out_file_name, const ReservationList &reservation_list, const RoomList &room_list);

int main(int argc, char *argv[]) {

    if (argc != 1 + 4) {
        std::cout << "Exception: should have 4 arguments instead of " << (argc - 1) << std::endl;
        return 0;
    }

    std::string input_file_name(argv[1]);
    std::string task1_out_file_name(argv[2]);
    std::string task2_out_file_name(argv[3]);
    std::string task3_out_file_name(argv[4]);

    std::ifstream input_file_stream;
    input_file_stream.open(input_file_name);

    int number_of_rooms = 0;
    read_number_of_rooms(input_file_stream, number_of_rooms);

    RoomList room_list(number_of_rooms);

    read_room_data(input_file_stream, room_list);

    int number_of_reservations = 0;
    read_number_of_reservations(input_file_stream, number_of_reservations);

    ReservationList reservation_list(number_of_reservations);

    read_reservation_data(input_file_stream, reservation_list);

    input_file_stream.close();

    output_task1_file(task1_out_file_name, reservation_list, room_list);

    output_task2_file(task2_out_file_name, reservation_list, room_list);

    std::ofstream output_file_stream;
    output_file_stream.open(task3_out_file_name);

    output_file_stream << "Reservation Information: " << std::endl;

    reservation_list.process_reservation_validity();

    for (
        int valid_reservation_sorted_order_number = 1;
        valid_reservation_sorted_order_number <= reservation_list.get_total_number_of_valid_reservations();
        valid_reservation_sorted_order_number++
    ) {
        output_file_stream << reservation_list.get_valid_reservation_string_sorted(valid_reservation_sorted_order_number, room_list) << std::endl;
    }

    output_file_stream << "Room Information: " << std::endl;

    for (int room_order_number = 1; room_order_number <= room_list.get_total_number_of_rooms(); room_order_number++) {
        output_file_stream << room_list.get_room_string(room_order_number, reservation_list, true) << std::endl;
    }

    output_file_stream.close();

    return 0;
}

void output_task1_file(const std::string &task1_out_file_name, const ReservationList &reservation_list, const RoomList &room_list) {
    std::ofstream output_file_stream;
    output_file_stream.open(task1_out_file_name);

    output_file_stream << "Reservation Information: " << std::endl;

    for (int reservation_order_number = 1; reservation_order_number <= reservation_list.get_total_number_of_reservations(); reservation_order_number++) {
        output_file_stream << reservation_list.get_reservation_string(reservation_order_number, room_list) << std::endl;
    }

    output_file_stream.close();
}

void output_task2_file(const std::string &task2_out_file_name, const ReservationList &reservation_list, const RoomList &room_list) {
    std::ofstream output_file_stream;
    output_file_stream.open(task2_out_file_name);

    output_file_stream << "Reservation Information: " << std::endl;

    for (
        int reservation_sorted_order_number = 1;
        reservation_sorted_order_number <= reservation_list.get_total_number_of_reservations();
        reservation_sorted_order_number++
    ) {
        output_file_stream << reservation_list.get_reservation_string_sorted(reservation_sorted_order_number, room_list) << std::endl;
    }

    output_file_stream << "Room Information: " << std::endl;

    for (int room_order_number = 1; room_order_number <= room_list.get_total_number_of_rooms(); room_order_number++) {
        output_file_stream << room_list.get_room_string(room_order_number, reservation_list) << std::endl;
    }

    output_file_stream.close();
}

void read_number_of_rooms(std::ifstream &input_file_stream, int &number_of_rooms) {
    std::string read_line;
    read_line_clean(input_file_stream, read_line);

    std::istringstream input_string_stream(read_line);
    input_string_stream >> number_of_rooms;
}

void read_room_data(std::ifstream &input_file_stream, RoomList &room_list) {
    for (int room_order_number = 1; room_order_number <= room_list.get_total_number_of_rooms(); room_order_number++) {
        std::string read_line;
        read_line_clean(input_file_stream, read_line);
        std::istringstream input_string_stream(read_line);

        std::string room_name;
        int price_per_hour;

        input_string_stream >> room_name >> price_per_hour;

        room_list.add_room(room_name, price_per_hour);
    }
}

void read_number_of_reservations(std::ifstream &input_file_stream, int &number_of_reservations) {
    std::string read_line;
    read_line_clean(input_file_stream, read_line);

    std::istringstream input_string_stream(read_line);
    input_string_stream >> number_of_reservations;
}

void read_reservation_data(std::ifstream &input_file_stream, ReservationList &reservation_list) {
    for (int reservation_order_number = 1; reservation_order_number <= reservation_list.get_total_number_of_reservations(); reservation_order_number++) {
        std::string read_line;
        read_line_clean(input_file_stream, read_line);
        std::istringstream input_string_stream(read_line);

        int id;
        std::string name;
        std::string reserved_room_name;
        int start_time;
        int end_time;

        input_string_stream >> id >> name >> reserved_room_name >> start_time >> end_time;

        reservation_list.add_reservation(reservation_order_number, id, name, reserved_room_name, start_time, end_time);
    }
}

void read_line_clean(std::ifstream &input_file_stream, std::string &read_line) {
    std::getline(input_file_stream, read_line);

    size_t first_not_of_space = read_line.find_first_not_of(" ");
    if (first_not_of_space != std::string::npos)
        read_line.erase(0, first_not_of_space);
    else
        read_line.clear();

    size_t index_of_double_slash = read_line.find("//");
    if (index_of_double_slash != std::string::npos)
        read_line.erase(index_of_double_slash);

    size_t last_not_of_space = read_line.find_last_not_of(" ");
    if (last_not_of_space != std::string::npos)
        read_line.erase(last_not_of_space + 1);
    else
        read_line.clear();
}
