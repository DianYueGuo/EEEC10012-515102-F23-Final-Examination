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
    std::string get_valid_reservation_string_sorted(int valid_reservation_sorted_order_number) const;
    std::string get_room_name_sorted(int reservation_sorted_order_number) const;
    std::string get_roomer_name_sorted(int reservation_sorted_order_number) const;
    void process_reservation_validity();
    int get_total_number_of_reservations() const;
    int get_total_number_of_valid_reservations() const;
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
    int* valid_reservation_order_number_list_index_list;
    int total_number_of_reservations;
    int number_of_reservations_added;
    int number_of_valid_reservations;
    void sort_ordered_reservation_order_number_list() const;
    bool is_reservation_valid(int reservation_sorted_order_number) const;
    bool do_reservation_have_overlap(Reservation &reservation_1, Reservation &reservation_2) const;
};

#endif
