//
// Created by void on 6/14/24.
//

#ifndef ENI_ITERATOR_H
#define ENI_ITERATOR_H

#include <fmt/core.h>
#include <functional>

namespace eni {

template<typename FromT, typename ToT>
class TransformIterator {
public:
    using value_type = ToT;
    using source_type = FromT;
    using difference_type = std::ptrdiff_t;
    using transform_fun = std::function<ToT(const FromT &)>;

    TransformIterator(source_type *ptr, const transform_fun transform) : _ptr(ptr), _transform(transform) {}

    value_type operator*() const { return _transform(*_ptr); }
    TransformIterator &operator++() {
        ++_ptr;
        return *this;
    }
    TransformIterator operator++(int) {
        TransformIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend bool operator==(const TransformIterator &a, const TransformIterator &b) {
        return a._ptr == b._ptr;
    }
    friend bool operator!=(const TransformIterator &a, const TransformIterator &b) {
        return a._ptr != b._ptr;
    }

private:
    source_type *_ptr;
    transform_fun _transform{};
};

template<typename PtrT>
class DereferenceIterator : public TransformIterator<PtrT, typename PtrT::element_type &> {
public:
    using typename TransformIterator<PtrT, typename PtrT::element_type &>::source_type;
    using typename TransformIterator<PtrT, typename PtrT::element_type &>::value_type;
    using typename TransformIterator<PtrT, typename PtrT::element_type &>::difference_type;

private:
    static value_type &_transform(const PtrT &ptr) {
        return *ptr;
    }

public:
    explicit DereferenceIterator(PtrT *ptr) : TransformIterator<source_type, value_type>(ptr, _transform) {
    }
};

template<typename IteratorT>
struct Range {
public:
    using iterator = IteratorT;

private:
    iterator _begin, _end;

public:
    Range(iterator begin, iterator end)
        : _begin(std::move(begin)),
          _end(std::move(end)) {}

    iterator begin() const {
        return _begin;
    }

    iterator end() const {
        return _end;
    }
};

template<typename IteratorT>
Range<IteratorT> make_range(IteratorT begin, IteratorT end) {
    return Range<IteratorT>(std::move(begin), std::move(end));
}

}// namespace eni

#endif//ENI_ITERATOR_H
