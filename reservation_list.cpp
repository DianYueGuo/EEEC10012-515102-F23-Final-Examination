#include "reservation_list.h"

#include <sstream>
#include <algorithm>

ReservationList::ReservationList(int number_of_reservations) {
    reservation_list = new Reservation[number_of_reservations];
    ordered_reservation_list = new Reservation*[number_of_reservations];
    valid_reservation_list = new Reservation*[number_of_reservations];
    total_number_of_reservations = number_of_reservations;
    number_of_reservations_added = 0;
    number_of_valid_reservations = 0;
}

ReservationList::~ReservationList() {
    delete[] reservation_list;
    delete[] ordered_reservation_list;
    delete[] valid_reservation_list;
}

void ReservationList::add_reservation(
        int order_number,
        int id,
        std::string &name,
        std::string &reserved_room_name,
        int start_time,
        int end_time
) {
    reservation_list[number_of_reservations_added].order_number = order_number;
    reservation_list[number_of_reservations_added].id = id;
    reservation_list[number_of_reservations_added].name = name;
    reservation_list[number_of_reservations_added].reserved_room_name = reserved_room_name;
    reservation_list[number_of_reservations_added].start_time = start_time;
    reservation_list[number_of_reservations_added].end_time = end_time;

    ordered_reservation_list[number_of_reservations_added] = &reservation_list[number_of_reservations_added];

    number_of_reservations_added++;
}

int ReservationList::get_total_number_of_reservations() const {
    return total_number_of_reservations;
}

std::string ReservationList::get_reservation_string(int reservation_order_number, const RoomList &room_list, bool does_calculate_total_cost) const {
    std::ostringstream output_string_stream;

    int duration = reservation_list[reservation_order_number - 1].end_time - reservation_list[reservation_order_number - 1].start_time;

    output_string_stream << "Id: " << reservation_list[reservation_order_number - 1].id << ", "
                         << "Name: " << reservation_list[reservation_order_number - 1].name << ", "
                         << "Room: " << reservation_list[reservation_order_number - 1].reserved_room_name << ", "
                         << "Start: " << reservation_list[reservation_order_number - 1].start_time << ", "
                         << "End: " << reservation_list[reservation_order_number - 1].end_time << ", "
                         << "Duration: " << duration << "hr, "
                         << "Total Cost: ";

    if (does_calculate_total_cost) {
        output_string_stream << duration * room_list.get_price_per_hour(reservation_list[reservation_order_number - 1].reserved_room_name);
    } else {
        output_string_stream << 0;
    }

    return output_string_stream.str();
}

void ReservationList::sort_ordered_reservation_order_number_list() const {
    std::sort(
        ordered_reservation_list,
        ordered_reservation_list + number_of_reservations_added,
        [](const Reservation* first_reservation, const Reservation* second_reservation) {
            return first_reservation->id < second_reservation->id;
        }
    );
}

std::string ReservationList::get_reservation_string_sorted(int reservation_sorted_order_number, const RoomList &room_list) const {
    sort_ordered_reservation_order_number_list();

    return get_reservation_string(ordered_reservation_list[reservation_sorted_order_number - 1]->order_number, room_list);
}

std::string ReservationList::get_valid_reservation_string_sorted(int valid_reservation_sorted_order_number, const RoomList &room_list) const {
    return get_reservation_string(valid_reservation_list[valid_reservation_sorted_order_number - 1]->order_number, room_list, true);
}

std::string ReservationList::get_room_name_sorted(int reservation_sorted_order_number) const {
    sort_ordered_reservation_order_number_list();

    return ordered_reservation_list[reservation_sorted_order_number - 1]->reserved_room_name;
}

std::string ReservationList::get_roomer_name_sorted(int reservation_sorted_order_number) const {
    sort_ordered_reservation_order_number_list();

    return ordered_reservation_list[reservation_sorted_order_number - 1]->name;
}

void ReservationList::process_reservation_validity() {
    for (
        int reservation_sorted_order_number = 1;
        reservation_sorted_order_number <= total_number_of_reservations;
        reservation_sorted_order_number++
    ) {
        if (is_reservation_valid(reservation_sorted_order_number)) {
            valid_reservation_list[number_of_valid_reservations] = ordered_reservation_list[reservation_sorted_order_number - 1];
            number_of_valid_reservations++;
        }
    }
}

bool ReservationList::is_reservation_valid(int reservation_sorted_order_number) const {
    Reservation &reservation_in_question = *ordered_reservation_list[reservation_sorted_order_number - 1];

    for (
        int valid_reservation_sorted_order_number = 1;
        valid_reservation_sorted_order_number <= number_of_valid_reservations;
        valid_reservation_sorted_order_number++
    ) {
        Reservation &already_valid_reservation = *valid_reservation_list[valid_reservation_sorted_order_number - 1];

        if (
            reservation_in_question.reserved_room_name.compare(
                already_valid_reservation.reserved_room_name
            ) != 0
        ) {
            continue;
        }

        if (do_reservations_have_overlap(reservation_in_question, reservation_in_question)) {
            return false;
        }
    }

    return true;
}

bool ReservationList::do_reservations_have_overlap(Reservation &reservation_1, Reservation &reservation_2) const {
    if (reservation_1.start_time < reservation_2.start_time && reservation_1.end_time < reservation_2.start_time ) {
        return false;
    }

    if (reservation_2.start_time < reservation_1.start_time && reservation_2.end_time < reservation_1.start_time ) {
        return false;
    }

    return true;
}

int ReservationList::get_total_number_of_valid_reservations() const {
    return number_of_valid_reservations;
}
