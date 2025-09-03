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

void ReservationList::for_each_reservation(std::function<void(Reservation &reservation)> do_function, bool is_sorted_by_id, bool does_include_valid_reservation_only) const {
    if (!is_sorted_by_id) {
        for (int reservation_order_number = 1; reservation_order_number <= total_number_of_reservations; reservation_order_number++) {
            do_function(reservation_list[reservation_order_number - 1]);
        }
        return;
    }

    sort_ordered_reservation_order_number_list();

    if (!does_include_valid_reservation_only) {
        for (
            int reservation_sorted_order_number = 1;
            reservation_sorted_order_number <= total_number_of_reservations;
            reservation_sorted_order_number++
        ) {
            do_function(*ordered_reservation_list[reservation_sorted_order_number - 1]);
        }
        return;
    }

    for (
        int valid_reservation_sorted_order_number = 1;
        valid_reservation_sorted_order_number <= number_of_valid_reservations;
        valid_reservation_sorted_order_number++
    ) {
        do_function(*valid_reservation_list[valid_reservation_sorted_order_number - 1]);
    }
    return;
}

std::string ReservationList::get_total_reservation_information_string(const RoomList &room_list, bool is_sorted_by_id, bool does_include_only_valid_reservation_and_calculate_total_cost) const {
    std::ostringstream output_string_stream;

    for_each_reservation(
        [&](Reservation &reservation) {
            output_string_stream << get_reservation_string(
                reservation.order_number,
                room_list,
                does_include_only_valid_reservation_and_calculate_total_cost
            ) << std::endl;
        },
        is_sorted_by_id,
        does_include_only_valid_reservation_and_calculate_total_cost
    );

    return output_string_stream.str();
}

void ReservationList::process_reservation_validity() {
    for_each_reservation(
        [&](Reservation &reservation) {
            if (is_reservation_valid(reservation)) {
                valid_reservation_list[number_of_valid_reservations] = &reservation;
                number_of_valid_reservations++;
            }
        },
        true
    );
}

bool ReservationList::is_reservation_valid(const Reservation &reservation_in_question) const {
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

bool ReservationList::do_reservations_have_overlap(const Reservation &reservation_1, const Reservation &reservation_2) const {
    if (reservation_1.start_time < reservation_2.start_time && reservation_1.end_time < reservation_2.start_time ) {
        return false;
    }

    if (reservation_2.start_time < reservation_1.start_time && reservation_2.end_time < reservation_1.start_time ) {
        return false;
    }

    return true;
}

std::string ReservationList::get_roomer_names(const std::string room_name, bool does_include_only_valid_roomers) const {
    std::ostringstream output_string_stream;

    for_each_reservation(
        [&](Reservation &reservation) {
            if (room_name.compare(
                    reservation.reserved_room_name
                ) == 0
            ) {
                output_string_stream << " " << reservation.name;
            }
        },
        true,
        does_include_only_valid_roomers
    );

    return output_string_stream.str();
}

int ReservationList::get_room_earnings(const std::string room_name, const RoomList &room_list) const {
    int earnings = 0;

    for_each_reservation(
        [&](Reservation &reservation) {
            if (room_name.compare(
                    reservation.reserved_room_name
                ) == 0
            ) {
                int duration = reservation.end_time - reservation.start_time;
                earnings += duration * room_list.get_price_per_hour(reservation.reserved_room_name);
            }
        },
        true,
        true
    );

    return earnings;
}
