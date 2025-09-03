#ifndef ROOM_LIST_H
#define ROOM_LIST_H

#include <string>
#include "reservation_list.h"

class ReservationList;

class RoomList {
public:
    RoomList(int number_of_rooms);
    ~RoomList();
    void add_room(const std::string &room_name, int price_per_hour);
    int get_total_number_of_rooms() const;
    int get_price_per_hour(const std::string room_name) const;
    std::string get_total_room_information_string(const ReservationList &reservation_list, bool does_calculate_earnings_and_include_only_valid_roomers = false) const;
private:
    struct Room {
        std::string room_name;
        int price_per_hour;
    };
    Room* room_list;
    int total_number_of_rooms;
    int number_of_rooms_added;
    std::string get_room_string(const Room &room, const ReservationList &reservation_list, bool does_calculate_earnings_and_include_only_valid_roomers = false) const;
};

#endif
