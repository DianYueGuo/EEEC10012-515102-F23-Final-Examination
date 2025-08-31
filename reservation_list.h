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
    int total_number_of_reservations;
    int number_of_reservations_added;
};

#endif
