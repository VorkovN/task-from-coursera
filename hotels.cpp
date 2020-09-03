#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <gtest/gtest.h>

using namespace std;

struct Reservation {

    Reservation(const int64_t time, const int64_t client_id, const int64_t room_count): time(time), client_id(client_id), room_count(room_count) {};

    const int64_t time;
    const uint64_t client_id;
    const uint64_t room_count;
};

class Hotels_Manager {
public:

    void book(const int64_t reservation_time, const string& hotel_name, const int64_t client_id, const int64_t room_count){
        hotels[hotel_name] += room_count;
        hotelsR[hotel_name].emplace_back(reservation_time, client_id, room_count);
        hotel_client_count[hotel_name][client_id]++;
        time = reservation_time;
    }

    int64_t countClients(const string& hotel_name) {

        deleteOldBooking(hotel_name);

        return hotel_client_count[hotel_name].size();
    }

    int64_t countRooms(const string& hotel_name){

        deleteOldBooking(hotel_name);

        return hotels[hotel_name];
    }

public:
    int64_t time = 0;
    map<string, int> hotels;
    map<string, deque<Reservation>> hotelsR;
    map<string, map<int, int>> hotel_client_count;

    void deleteOldBooking(const string& hotel_name){

        while (!hotelsR[hotel_name].empty() && hotelsR[hotel_name].front().time <= time - 86400) {
            hotel_client_count[hotel_name][hotelsR[hotel_name].front().client_id]--;
            if (hotel_client_count[hotel_name][hotelsR[hotel_name].front().client_id] == 0) hotel_client_count[hotel_name].erase(hotelsR[hotel_name].front().client_id);
            hotels[hotel_name] -= hotelsR[hotel_name].front().room_count;
            if (hotels[hotel_name] == 0) hotels.erase(hotel_name);
            hotelsR[hotel_name].pop_front();
            if (hotelsR[hotel_name].empty()) hotelsR.erase(hotel_name);

        }
    }
};


TEST(countClients_test, countC){

    Hotels_Manager hm;

    hm.book(3, "hotel1", 4, 5);
    hm.book(3, "hotel1", 4, 5);
    hm.book(9, "hotel2", 6, 2);
    hm.book(86404, "hotel2", 8, 1);
    hm.book(86405, "hotel3", 6, 2);

    EXPECT_EQ(hm.countClients("hotel1"), 0);
    EXPECT_EQ(hm.countClients("hotel2"), 2);
    EXPECT_EQ(hm.countClients("hotel3"), 1);
}

TEST(countRooms_test, countR){

    Hotels_Manager hm;

    hm.book(3, "hotel1", 4, 5);
    hm.book(3, "hotel1", 4, 5);
    hm.book(9, "hotel2", 6, 2);
    hm.book(9, "hotel2", 6, 2);
    hm.book(86404, "hotel2", 8, 1);
    hm.book(86405, "hotel3", 6, 2);

    EXPECT_EQ(hm.countRooms("hotel1"), 0);
    EXPECT_EQ(hm.countRooms("hotel2"), 5);
    EXPECT_EQ(hm.countRooms("hotel3"), 2);
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    testing::InitGoogleTest();
    cout << RUN_ALL_TESTS() << endl;


    Hotels_Manager manager;

    int64_t query_count;
    cin >> query_count;

    for (int64_t query_id = 0; query_id < query_count; ++query_id) {

        string query_type;
        cin >> query_type;

        if (query_type == "BOOK"){

            int64_t time;
            string hotel_name;
            int64_t client_id;
            int64_t room_count;

            cin >> time >> hotel_name >> client_id >> room_count;
            manager.book(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS"){
            string hotel_name;

            cin >> hotel_name;
            cout << manager.countClients(hotel_name) << endl;
        }
        else if (query_type == "ROOMS"){
            string hotel_name;

            cin >> hotel_name;
            cout << manager.countRooms(hotel_name) << endl;
        }
    }

    return 0;
}
