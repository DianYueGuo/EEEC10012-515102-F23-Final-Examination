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
    std::string get_room_string(int room_order_number, const ReservationList &reservation_list) const;
    int get_price_per_hour(const std::string room_name) const;
private:
    struct Room {
        std::string room_name;
        int price_per_hour;
    };
    Room* room_list;
    int total_number_of_rooms;
    int number_of_rooms_added;
};

#endif
