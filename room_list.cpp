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

std::string RoomList::get_room_string(int room_order_number, const ReservationList &reservation_list) const {
    std::ostringstream output_string_stream;

    output_string_stream << "Room " << room_list[room_order_number - 1].room_name << ": "
                         << "Price " << room_list[room_order_number - 1].price_per_hour << ", "
                         << "Earnings: " << 0 << ", ";

    output_string_stream << "Roomer:";
    for (
        int reservation_sorted_order_number = 1;
        reservation_sorted_order_number <= reservation_list.get_total_number_of_reservations();
        reservation_sorted_order_number++
    ) {
        if (room_list[room_order_number - 1].room_name
            .compare(
                reservation_list.get_room_name_sorted(reservation_sorted_order_number)
            ) == 0
        ) {
            output_string_stream << " " << reservation_list.get_roomer_name_sorted(reservation_sorted_order_number);
        }
    }

    return output_string_stream.str();
}
