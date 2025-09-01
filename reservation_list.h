#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <string>
#include "room_list.h"

class RoomList;

class ReservationList {
public:
    ReservationList(int number_of_reservations);
    ~ReservationList();
    void add_reservation(
        int order_number,
        int id,
        std::string &name,
        std::string &reserved_room_name,
        int start_time,
        int end_time
    );
    std::string get_reservation_string(int reservation_order_number, const RoomList &room_list, bool does_calculate_total_cost = false) const;
    std::string get_reservation_string_sorted(int reservation_sorted_order_number, const RoomList &room_list) const;
    std::string get_valid_reservation_string_sorted(int valid_reservation_sorted_order_number, const RoomList &room_list) const;
    std::string get_room_name_sorted(int reservation_sorted_order_number) const;
    std::string get_roomer_name_sorted(int reservation_sorted_order_number) const;
    std::string get_valid_reservation_room_name_sorted(int valid_reservation_sorted_order_number) const;
    std::string get_valid_reservation_roomer_name_sorted(int valid_reservation_sorted_order_number) const;
    int get_valid_sorted_reservation_total_cost(int valid_reservation_sorted_order_number, const RoomList &room_list) const;
    void process_reservation_validity();
    int get_total_number_of_reservations() const;
    int get_total_number_of_valid_reservations() const;
private:
    struct Reservation {
        int order_number;
        int id;
        std::string name;
        std::string reserved_room_name;
        int start_time;
        int end_time;
    };
    Reservation* reservation_list;
    Reservation** ordered_reservation_list;
    Reservation** valid_reservation_list;
    int total_number_of_reservations;
    int number_of_reservations_added;
    int number_of_valid_reservations;
    void sort_ordered_reservation_order_number_list() const;
    bool is_reservation_valid(int reservation_sorted_order_number) const;
    bool do_reservations_have_overlap(Reservation &reservation_1, Reservation &reservation_2) const;
};

#endif
