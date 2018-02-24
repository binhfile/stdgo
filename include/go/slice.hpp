#ifndef GO_SLICE_H
#define GO_SLICE_H
/**
 * @author binhfile
 * @brief Slice data
 */

#include <memory>

namespace go {

template <typename T>
class slice {
  public:
    slice() : raw_data_{nullptr}, index_{0}, count_{0} {}
    slice(std::size_t _count)
        : data_{std::shared_ptr<T>(new T[_count], [](T *p) { delete[] p; })},
          raw_data_{data_.get()}, index_{0}, count_{_count} {}
    slice(T *_data, std::size_t _index, std::size_t _count)
        : data_{std::shared_ptr<T>(_data)}, raw_data_{nullptr}, index_{_index}, count_{_count} {
        if (data_)
            raw_data_ = data_.get();
    }
    slice(const slice &_source, std::size_t _index, std::size_t _count)
        : data_{_source.data_}, raw_data_{nullptr}, index_{_source.index_ + _index}, count_{
                                                                                         _count} {
        if (_count == 0) {
            index_ = 0;
            count_ = 0;
        }
        if (_index >= _source.count_) {
            index_ = 0;
            count_ = 0;
        }
        if (count_ + index_ >= _source.index_ + _source.count_) {
            count_ = _source.index_ + _source.count_ - index_;
        }
        if (count_ == 0) {
            data_ = nullptr;
            raw_data_ = nullptr;
        }
        if (data_)
            raw_data_ = data_.get();
    }

    virtual ~slice() = default;

    std::size_t size() const { return count_; }
    T *data() const { return &(raw_data_[index_]); }
    T &operator[](std::size_t index) const { return raw_data_[index]; }

    class iterator {
      public:
        virtual ~iterator() = default;
        iterator(T *_data, std::size_t _index) : raw_data_{_data}, index_{_index} {}

        iterator operator++() {
            ++index_;
            return *this;
        }
        bool operator!=(const iterator &rhs) { return index_ != rhs.index_; }
        const T &operator*() const { return raw_data_[index_]; }

      protected:
        T *raw_data_;
        std::size_t index_;
    };

    iterator begin() const { return iterator{data_.get(), index_}; }
    iterator end() const { return iterator{data_.get(), index_ + count_}; }

  protected:
    std::shared_ptr<T> data_;
    T *raw_data_;
    std::size_t index_;
    std::size_t count_;
};

} // namespace go

#endif // GO_SLICE_H