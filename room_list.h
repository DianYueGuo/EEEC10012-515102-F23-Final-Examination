#ifndef ROOM_LIST_H
#define ROOM_LIST_H

#include <string>

class RoomList {
public:
    RoomList(int number_of_rooms);
    ~RoomList();
    void add_room(const std::string &room_name, int price_per_hour);
    int get_total_number_of_rooms() const;
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
