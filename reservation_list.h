#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <string>
#include <functional>
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
    std::string get_total_reservation_information_string(const RoomList &room_list, bool is_sorted_by_id = false, bool does_include_only_valid_reservation_and_calculate_total_cost = false) const;
    std::string get_roomer_names(const std::string room_name, bool does_include_only_valid_roomers) const;
    int get_room_earnings(const std::string room_name, const RoomList &room_list) const;
    void process_reservation_validity();
    int get_total_number_of_reservations() const;
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
    bool is_reservation_valid(const Reservation &reservation_in_question) const;
    bool do_reservations_have_overlap(const Reservation &reservation_1, const Reservation &reservation_2) const;
    std::string get_reservation_string(int reservation_order_number, const RoomList &room_list, bool does_calculate_total_cost = false) const;
    void for_each_reservation(std::function<void(Reservation &reservation)> do_function, bool is_sorted_by_id = false, bool does_include_valid_reservation_only = false) const;
};

#endif
