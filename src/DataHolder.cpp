//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "DataHolder.hpp"

namespace data
{

DataHolder::DataHolder() {
}


void DataHolder::SetSeatsWidth(const uint32_t size) {
    mSeats.resize(size);
}

void DataHolder::SetSeatsHeight(const uint32_t size) {
    for (auto& row : mSeats) {
        row.resize(size, SeatType::Unavailable);
    }
}

void DataHolder::SetSeats(const std::vector<std::string>& words) {
    SetSeatsWidth(std::stoi(words.at(1)));
    SetSeatsHeight(std::stoi(words.at(0)));

    for (int row_index = 0; row_index < mSeats.size(); ++row_index) {
        for (int column_index = 0; column_index < mSeats[row_index].size(); ++column_index) {
            SetSeat(row_index, column_index, words.at(row_index + 2).at(column_index));
        }
    }
}

void DataHolder::SetSeat(uint32_t width, uint32_t height, const char val) {
    switch (val)
    {
        case '_':
            mSeats[width][height] = SeatType::Developer;
            break;
        case 'M':
            mSeats[width][height] = SeatType::Manager;
            break;
        default:
            mSeats[width][height] = SeatType::Unavailable;
    }
}

}
