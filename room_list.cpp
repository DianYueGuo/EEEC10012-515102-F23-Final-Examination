#include "room_list.h"

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
