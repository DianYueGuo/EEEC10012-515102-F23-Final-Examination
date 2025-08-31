#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <string>

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
    std::string get_reservation_string(int reservation_order_number) const;
    std::string get_reservation_string_sorted(int reservation_sorted_order_number) const;
    std::string get_room_name_sorted(int reservation_sorted_order_number) const;
    std::string get_roomer_name_sorted(int reservation_sorted_order_number) const;
    int get_total_number_of_reservations() const;
private:
    struct Reservation {
        int id;
        std::string name;
        std::string reserved_room_name;
        int start_time;
        int end_time;
    };
    Reservation* reservation_list;
    int* ordered_reservation_order_number_list;
    int total_number_of_reservations;
    int number_of_reservations_added;
    void sort_ordered_reservation_order_number_list() const;
};

#endif
