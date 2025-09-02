#include "room_list.h"

#include <sstream>

RoomList::RoomList(int number_of_rooms) {
    room_list = new Room[number_of_rooms];
    total_number_of_rooms = number_of_rooms;
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

int RoomList::get_total_number_of_rooms() const{
    return total_number_of_rooms;
}

std::string RoomList::get_room_string(int room_order_number, const ReservationList &reservation_list, bool does_calculate_earnings_and_include_only_valid_roomers) const {
    std::ostringstream output_string_stream;

    output_string_stream << "Room " << room_list[room_order_number - 1].room_name << ": "
                         << "Price " << room_list[room_order_number - 1].price_per_hour << ", ";

    if (does_calculate_earnings_and_include_only_valid_roomers) {
        output_string_stream << "Earnings: " << reservation_list.get_room_earnings(room_list[room_order_number - 1].room_name, *this) << ", ";
    } else {
        output_string_stream << "Earnings: " << 0 << ", ";
    }

    output_string_stream << "Roomer:"
                         << reservation_list.get_roomer_names(room_list[room_order_number - 1].room_name, does_calculate_earnings_and_include_only_valid_roomers);

    return output_string_stream.str();
}

std::string RoomList::get_total_room_information_string(const ReservationList &reservation_list, bool does_calculate_earnings_and_include_only_valid_roomers) const {
    std::ostringstream output_string_stream;

    for (int room_order_number = 1; room_order_number <= total_number_of_rooms; room_order_number++) {
        output_string_stream << get_room_string(room_order_number, reservation_list, does_calculate_earnings_and_include_only_valid_roomers) << std::endl;
    }

    return output_string_stream.str();
}

int RoomList::get_price_per_hour(const std::string room_name) const {
    for (int room_list_index = 0; room_list_index < number_of_rooms_added; room_list_index++) {
        if (room_name.compare(room_list[room_list_index].room_name) == 0) {
            return room_list[room_list_index].price_per_hour;
        }
    }

    return 0;
}
