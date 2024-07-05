#include <cassert>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

#include "race.h"

void check_properties() {
    Race::StepperBlob blob;
    blob.step();
    assert(blob.total_steps() == 2);

    static_assert(!std::is_default_constructible_v<Race::Blob>);
    static_assert(std::is_destructible_v<Race::Blob>);
    static_assert(!std::is_copy_constructible_v<Race::Blob>);
    static_assert(!std::is_copy_assignable_v<Race::Blob>);
    static_assert(!std::is_move_constructible_v<Race::Blob>);
    static_assert(!std::is_move_assignable_v<Race::Blob>);
    static_assert(std::has_virtual_destructor_v<Race::Blob>);

    Race::RandomBlob random_blob([]() { return 0; },
                                 [](auto gen) { return gen(); });
    random_blob.step();
    assert(random_blob.total_steps() == 0);
}

int main() {
    check_properties();
    auto blobs = Race::create_blobs(8);
    Race::race(blobs);
}
