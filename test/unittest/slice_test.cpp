#if defined(GO_UNITTEST)
#if defined(GO_UNITTEST_ALL) || defined(GO_UNITTEST_SLICE)
#include <go/slice.hpp>
#include <gtest/gtest.h>

TEST(slice, from_array) {
    constexpr std::size_t N = 10;
    auto buf = std::shared_ptr<int>(new int[N], [](int *p) { delete[] p; });
    for (int i = 0; i < static_cast<int>(N); i++)
        buf.get()[i] = i;

    auto slice = go::slice<int>{buf.get(), 0, N};
    for (std::size_t index = 0; index < N * 2; index++) {
        for (std::size_t count = 0; count < N * 2; count++) {
            auto item = go::slice<int>{slice, index, count};
            std::size_t index_ = index;
            std::size_t count_ = count;
            if (index >= N) {
                index_ = 0;
                count_ = 0;
            } else {
                if (index_ + count >= N)
                    count_ = N - index_;
            }
            ASSERT_EQ(count_, item.size());
            for (const auto &val : item) {
                ASSERT_EQ(buf.get()[index_++], val);
            }
        }
    }
}

#endif
#endif