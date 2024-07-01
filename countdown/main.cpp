#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>

void duration_to_end_of_year() {
    // C++17 for CTAD
    std::chrono::time_point now = std::chrono::system_clock::now();

    const auto ymd =
        std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(now));
    auto this_year = ymd.year();
    auto new_years_eve = this_year / std::chrono::December / 31;

    // convert date to time_point
    auto event = std::chrono::sys_days(new_years_eve);
    std::chrono::duration dur = event - now;

    // C++20 - chrono operator<<
    std::cout << duration_cast<std::chrono::days>(dur)
              << " until end of year\n";

    /* using cent = std::chrono::duration< */
    /*     long long, std::ratio_multiply<std::chrono::years::period,
     * std::hecto>>; */
    /* std::cout << "Century: " << cent(1) << " seconds: " */
    /*           << std::chrono::duration_cast<std::chrono::seconds>(cent(1)) */
    /*           << std::endl; */
}

void last_friday_of_month() {
    using namespace std::chrono;

    time_point now = system_clock::now();
    const auto ymd = year_month_day(floor<days>(now));
    auto pay_day =
        ymd.year() / ymd.month() / std::chrono::Friday[std::chrono::last];
    auto event = sys_days(pay_day);
    duration dur = event - now;

    std::cout << duration_cast<days>(dur) << " until last Friday of month\n";
}

constexpr std::chrono::system_clock::duration
countdown(std::chrono::system_clock::time_point start) {
    using namespace std::chrono;

    auto days_only = floor<days>(start);
    const auto ymd = year_month_day{days_only};
    auto this_year = ymd.year();
    auto new_years_eve = this_year / December / last;
    auto event = sys_days(new_years_eve);
    return event - start;
}

void check_properties() {
    using namespace std::chrono;
    constexpr auto new_years_eve = 2022y / December / last;
    constexpr auto one_day_away = sys_days{new_years_eve} - 24h;
    constexpr auto result = countdown(one_day_away);
    static_assert(duration_cast<days>(result) == days{1});
}

int main() {
    check_properties();
    duration_to_end_of_year();
    last_friday_of_month();

    using namespace std::chrono;
    for (int i = 0; i < 5; i++) {
        std::this_thread::sleep_for(5000ms);
        auto dur = countdown(system_clock::now());
        std::cout << duration_cast<seconds>(dur) << " until event" << std::endl;
    }
}
