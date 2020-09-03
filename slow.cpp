#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
            : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
              page_rating(MAX_PAGE_COUNT + 1, 0){}

    void Read(int user_id, int page_count) {
        page_rating[page_count] ++;
        page_rating[user_page_counts_[user_id]]--;
        user_page_counts_[user_id] = page_count;

    }

    double Cheer(int user_id) const {
        if (user_page_counts_[user_id] == 0) {
            return 0;
        }
        const int user_count = -page_rating[0];
        if (user_count == 1) {
            return 1;
        }
        const int page_count = user_page_counts_[user_id];

        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Простой способ сделать это — умножить его на 1.0.
        int sum = accumulate(page_rating.begin() + 1, page_rating.begin() + page_count, 0);
        return sum * 1.0/ (user_count - 1);
    }

private:

    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT = 1000;

    vector<int> user_page_counts_;
    vector<int> page_rating;

};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}