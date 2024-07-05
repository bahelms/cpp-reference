#include <memory>
#include <vector>

namespace Race {
class Blob {
  public:
    virtual ~Blob() = default; // adding a destructor blocks the implicit
                               // inclusion of the move special member functions

    Blob() = default;
    Blob(Blob const &) = delete;
    Blob &operator=(Blob const &) = delete;

    virtual void step() = 0;
    virtual int total_steps() const = 0;
};

class StepperBlob final : public Blob {
    int y = 0;

  public:
    void step() override { y += 2; }
    int total_steps() const override { return y; }
};

template <std::invocable<> T, typename U> class RandomBlob final : public Blob {
    int y = 0;
    T generator;
    U distribution;

  public:
    RandomBlob(T gen, U dis) : generator(gen), distribution(dis) {}

    void step() override { y += static_cast<int>(distribution(generator)); }
    int total_steps() const override { return y; }
};

std::vector<std::unique_ptr<Blob>> create_blobs(int number);
void draw_blobs(const std::vector<std::unique_ptr<Blob>> &blobs);
void move_blobs(std::vector<std::unique_ptr<Blob>> &blobs);
void race(std::vector<std::unique_ptr<Blob>> &blobs);
} // namespace Race
