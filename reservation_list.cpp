#include "reservation_list.h"

#include <sstream>
#include <algorithm>

ReservationList::ReservationList(int number_of_reservations) {
    reservation_list = new Reservation[number_of_reservations];
    ordered_reservation_order_number_list = new int[number_of_reservations];
    total_number_of_reservations = number_of_reservations;
    number_of_reservations_added = 0;
}

ReservationList::~ReservationList() {
    delete[] reservation_list;
    delete[] ordered_reservation_order_number_list;
}

void ReservationList::add_reservation(
        int id,
        std::string &name,
        std::string &reserved_room_name,
        int start_time,
        int end_time
) {
    reservation_list[number_of_reservations_added].id = id;
    reservation_list[number_of_reservations_added].name = name;
    reservation_list[number_of_reservations_added].reserved_room_name = reserved_room_name;
    reservation_list[number_of_reservations_added].start_time = start_time;
    reservation_list[number_of_reservations_added].end_time = end_time;

    ordered_reservation_order_number_list[number_of_reservations_added] = number_of_reservations_added + 1;

    number_of_reservations_added++;
}

int ReservationList::get_total_number_of_reservations() const {
    return total_number_of_reservations;
}

std::string ReservationList::get_reservation_string(int reservation_order_number) const {
    std::ostringstream output_string_stream;

    output_string_stream << "Id: " << reservation_list[reservation_order_number - 1].id << ", "
                         << "Name: " << reservation_list[reservation_order_number - 1].name << ", "
                         << "Room: " << reservation_list[reservation_order_number - 1].reserved_room_name << ", "
                         << "Start: " << reservation_list[reservation_order_number - 1].start_time << ", "
                         << "End: " << reservation_list[reservation_order_number - 1].end_time << ", "
                         << "Duration: "
                         << (reservation_list[reservation_order_number - 1].end_time - reservation_list[reservation_order_number - 1].start_time)
                         << "hr, "
                         << "Total Cost: " << 0;

    return output_string_stream.str();
}

void ReservationList::sort_ordered_reservation_order_number_list() const {
    std::sort(
        ordered_reservation_order_number_list,
        ordered_reservation_order_number_list + number_of_reservations_added,
        [this](const int &first_reservation_order_number, const int &second_reservation_order_number) {
            return reservation_list[first_reservation_order_number - 1].id < reservation_list[second_reservation_order_number - 1].id;
        }
    );
}

std::string ReservationList::get_reservation_string_sorted(int reservation_sorted_order_number) const {
    sort_ordered_reservation_order_number_list();

    return get_reservation_string(ordered_reservation_order_number_list[reservation_sorted_order_number - 1]);
}

std::string ReservationList::get_room_name_sorted(int reservation_sorted_order_number) const {
    sort_ordered_reservation_order_number_list();

    return reservation_list[ordered_reservation_order_number_list[reservation_sorted_order_number - 1] - 1].reserved_room_name;
}

std::string ReservationList::get_roomer_name_sorted(int reservation_sorted_order_number) const {
    sort_ordered_reservation_order_number_list();

    return reservation_list[ordered_reservation_order_number_list[reservation_sorted_order_number - 1] - 1].name;
}
