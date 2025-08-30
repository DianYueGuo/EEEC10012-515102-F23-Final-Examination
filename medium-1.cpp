#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class RoomList {
public:
    RoomList(int number_of_rooms);
    ~RoomList();
    void add_room(const std::string &room_name, int price_per_hour);
private:
    struct Room {
        std::string room_name;
        int price_per_hour;
    };
    Room* room_list;
    int number_of_rooms_added;
};

class ReservationList {
public:
    ReservationList(int number_of_reservations);
    ~ReservationList();
    void add_reservation(
        int id,
        std::string &name,
        std::string &reserved_room_name,
        int start_time,
        int end_time
    );
private:
    struct Reservation {
        int id;
        std::string name;
        std::string reserved_room_name;
        int start_time;
        int end_time;
    };
    Reservation* reservation_list;
    int number_of_reservations_added;
};

void read_line_clean(std::ifstream &input_file_stream, std::string &read_line);

RoomList read_room_data(std::ifstream &input_file_stream);
ReservationList read_reservation_data(std::ifstream &input_file_stream);

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

    RoomList room_list = read_room_data(input_file_stream);

    ReservationList reservation_list = read_reservation_data(input_file_stream);

    input_file_stream.close();

    return 0;
}

RoomList read_room_data(std::ifstream &input_file_stream) {
    std::string read_line;
    read_line_clean(input_file_stream, read_line);

    std::istringstream input_string_stream(read_line);
    int number_of_rooms = 0;
    input_string_stream >> number_of_rooms;

    RoomList room_list(number_of_rooms);

    for (int room_number = 1; room_number <= number_of_rooms; room_number++) {
        read_line_clean(input_file_stream, read_line);
        input_string_stream.str(read_line);

        std::string room_name;
        int price_per_hour;

        input_string_stream >> room_name >> price_per_hour;

        room_list.add_room(room_name, price_per_hour);
    }

    return room_list;
}

ReservationList read_reservation_data(std::ifstream &input_file_stream) {
    std::string read_line;
    read_line_clean(input_file_stream, read_line);

    std::istringstream input_string_stream(read_line);
    int number_of_reservations = 0;
    input_string_stream >> number_of_reservations;

    ReservationList reservation_list(number_of_reservations);

    for (int reservation_number = 1; reservation_number <= number_of_reservations; reservation_number++) {
        read_line_clean(input_file_stream, read_line);
        input_string_stream.str(read_line);

        int id;
        std::string name;
        std::string reserved_room_name;
        int start_time;
        int end_time;

        input_string_stream >> id >> name >> reserved_room_name >> start_time >> end_time;

        reservation_list.add_reservation(id, name, reserved_room_name, start_time, end_time);
    }

    return reservation_list;
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

RoomList::RoomList(int number_of_rooms) {
    room_list = new Room[number_of_rooms];
    number_of_rooms_added = 0;
}

RoomList::~RoomList() {
    delete[] room_list;
}

void RoomList::add_room(const std::string &room_name, int price_per_hour) {
    room_list[number_of_rooms_added].room_name = room_name;
    room_list[number_of_rooms_added].price_per_hour = price_per_hour;

    number_of_rooms_added++;
}

ReservationList::ReservationList(int number_of_reservations) {
    reservation_list = new Reservation[number_of_reservations];
    number_of_reservations_added = 0;
}

ReservationList::~ReservationList() {
    delete[] reservation_list;
}

void ReservationList::add_reservation(
        int id,
        std::string &name,
        std::string &reserved_room_name,
        int start_time,
        int end_time
) {
    reservation_list[number_of_reservations_added].id = id;
    reservation_list[number_of_reservations_added].name = name;
    reservation_list[number_of_reservations_added].reserved_room_name = reserved_room_name;
    reservation_list[number_of_reservations_added].start_time = start_time;
    reservation_list[number_of_reservations_added].end_time = end_time;

    number_of_reservations_added++;
}
