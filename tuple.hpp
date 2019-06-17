//
// Created by Роман Агеев on 2019-06-14.
//

#ifndef TUPLE_TUPLE_HPP
#define TUPLE_TUPLE_HPP

namespace my {

template<typename First_, typename... Next_>
struct tuple;

namespace internal_ {
template<size_t n, typename First_, typename... Next_>
struct getter_size_t {
  static auto const &value(tuple<First_, Next_...> const &in) {
    return getter_size_t<n - 1, Next_...>::value(in.next_elements);
  }

  static auto &value(tuple<First_, Next_...> &in) {
    return getter_size_t<n - 1, Next_...>::value(in.next_elements);
  }
};

template<typename First_, typename... Next_>
struct getter_size_t<0, First_, Next_...> {
  static auto const &value(tuple<First_, Next_...> const &in) {
    return in.now_element;
  }

  static auto &value(tuple<First_, Next_...> &in) {
    return in.now_element;
  }
};

template<typename Need_, typename First_, typename... Next_>
struct getter_type {
  static Need_ const &value(tuple<First_, Next_...> const &in) {
    return getter_type<Need_, Next_...>::value(in.next_elements);
  }

  static Need_ &value(tuple<First_, Next_...> &in) {
    return getter_type<Need_, Next_...>::value(in.next_elements);
  }
};

template<typename Need_, typename... Next_>
struct getter_type<Need_, Need_, Next_...> {
  static Need_ const &value(tuple<Need_, Next_...> const &in) {
    return in.now_element;
  }

  static Need_ &value(tuple<Need_, Next_...> &in) {
    return in.now_element;
  }
};
}
template<typename Need_, typename First_, typename... Next_>
Need_ &getter(tuple<First_, Next_...> &in) {
  return internal_::getter_type<Need_, First_, Next_...>::value(in);
}

template<typename Need_, typename First_, typename... Next_>
Need_ const &getter(tuple<First_, Next_...> const &in) {
  return internal_::getter_type<Need_, First_, Next_...>::value(in);
}

template<size_t n, typename First_, typename... Next_>
auto &getter(tuple<First_, Next_...> &in) {
  return internal_::getter_size_t<n, First_, Next_...>::value(in);
}

template<size_t n, typename First_, typename... Next_>
auto const &getter(tuple<First_, Next_...> const &in) {
  return internal_::getter_size_t<n, First_, Next_...>::value(in);
}

template<typename First_, typename...Next_>
struct tuple {
  First_ now_element;
  tuple<Next_...> next_elements;

  explicit tuple(First_ &&first, Next_ &&...next)
      : now_element(std::forward<First_>(first)), next_elements(std::forward<Next_>(next)...) {}
  tuple() : now_element(), next_elements() {}

  tuple(tuple const &) = default;
  tuple(tuple &&) noexcept = default;

  ~tuple() = default;

  void swap(tuple &in) {
    std::swap(now_element, in.now_element);
    next_elements.swap(in.next_elements);
  };

  template<size_t n>
  auto const &get() const {
    return getter<n>(*this);
  }

  template<size_t n>
  auto &get() {
    return getter<n>(*this);
  }

  template<typename T>
  auto const &get() const {
    return getter<T>(*this);
  }

  template<typename T>
  auto &get() {
    return getter<T>(*this);
  }

  size_t size() {
    return next_elements.size + 1;
  }
};

template<typename First>
struct tuple<First> {
  explicit tuple(First &&first) : now_element(std::forward<First>(first)) {}
  tuple() : now_element() {}

  tuple(tuple const &) = default;
  tuple(tuple &&) noexcept = default;
  ~tuple() = default;

  void swap(tuple &in) {
    std::swap(now_element, in.now_element);
  };

  First now_element;

  constexpr size_t size() {
    return 1;
  }
  template<size_t n>
  auto const &get() const {
    return getter<n>(*this);
  }

  template<size_t n>
  auto &get() {
    return getter<n>(*this);
  }

  template<typename T>
  auto const &get() const {
    return getter<T>(*this);
  }

  template<typename T>
  auto &get() {
    return getter<T>(*this);
  }
};

template<typename...Next_>
tuple<Next_...> make_tuple(Next_ &&... in) {
  return tuple<Next_...>(std::forward<Next_>(in)...);
}

template<typename First>
void swap(my::tuple<First> &in1, my::tuple<First> &in2) {
  in1.swap(in2);
}

template<typename First_, typename...Next_>
void swap(std::tuple<First_, Next_...> &in1, std::tuple<First_, Next_...> &in2) {
  in1.swap(in2);
}
}

#endif //TUPLE_TUPLE_HPP
