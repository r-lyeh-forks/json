#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP

#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <iosfwd>
#include <string>
#include <memory>
#include <limits>
#include <tuple>

#include <cstdint>
#include <cstring>

#include <core/type_traits.hpp>
#include <core/string.hpp>

namespace json {
inline namespace v1 {

template <class Alloc>
struct basic_string final {
  using difference_type = std::ptrdiff_t;
  using value_type = char;
  using size_type = std::uint32_t;

  using reference = core::add_lvalue_reference_t<core::add_const_t<value_type>>;
  using pointer = core::add_pointer_t<core::add_const_t<value_type>>;

  using const_reference = reference;
  using const_pointer = pointer;

  using const_iterator = pointer;
  using iterator = const_iterator;

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using reverse_iterator = const_reverse_iterator;

  using allocator_type = typename std::allocator_traits<
    Alloc
  >::template rebind_alloc<value_type>;

  using allocator_traits = typename std::allocator_traits<
    Alloc
  >::template rebind_traits<value_type>;

  using traits = std::char_traits<value_type>;

  static constexpr size_type npos = std::numeric_limits<size_type>::max();

  enum field { data, length, hash, allocator };

  explicit basic_string (allocator_type const& = allocator_type { });

  basic_string (
    size_type,
    value_type,
    allocator_type const& = allocator_type { }
  );

  basic_string (
    basic_string const&,
    size_type,
    size_type = npos,
    allocator_type const& = allocator_type { }
  );

  basic_string (
    const_pointer,
    size_type,
    allocator_type const& = allocator_type { }
  );

  basic_string (
    const_pointer,
    allocator_type const& = allocator_type { }
  );

  template <class InputIterator>
  basic_string (
    InputIterator first,
    InputIterator last,
    allocator_type const& = allocator_type { }
  );

  basic_string (
    std::initializer_list<value_type> ilist,
    allocator_type const& = allocator_type { }
  );

  basic_string (basic_string const&, allocator_type const&);
  basic_string (basic_string&&, allocator_type const&);

  basic_string (basic_string const&);
  basic_string (basic_string&&);

  ~basic_string ();

  basic_string& operator = (basic_string const&);
  basic_string& operator = (basic_string&&);

  operator core::string_ref () const noexcept;

  /* element access */
  reference operator [] (size_type) const noexcept;
  reference at (size_type) const noexcept;

  reference front () const noexcept;
  reference back () const noexcept;

  pointer c_str () const noexcept;
  pointer data () const noexcept;

  /* iterators */
  const_iterator cbegin () const noexcept;
  const_iterator begin () const noexcept;

  const_iterator cend () const noexcept;
  const_iterator end () const noexcept;

  const_reverse_iterator crbegin () const noexcept;
  const_reverse_iterator rbegin () const noexcept;

  const_reverse_iterator crend () const noexcept;
  const_reverse_iterator rend () const noexcept;

  /* capacity and hash */
  size_type max_size () const noexcept;
  size_type capacity () const noexcept;
  size_type length () const noexcept;
  size_type size () const noexcept;
  size_type hash () const noexcept;

  bool empty () const noexcept;

  /* operations */
  void clear ();

  int compare (
    size_type,
    size_type,
    basic_string const&,
    size_type,
    size_type
  ) const noexcept;
  int compare (size_type, size_type, basic_string const&) const noexcept;
  int compare (basic_string const&) const noexcept;

  int compare (size_type, size_type, const_pointer, size_type) const noexcept;
  int compare (size_type, size_type, const_pointer) const noexcept;
  int compare (const_pointer) const noexcept;

  basic_string substr (size_type = 0, size_type = npos) const;
  void swap (basic_string&) noexcept;

  /* search */
  size_type find (const_pointer, size_type, size_type) const noexcept;
  size_type find (basic_string const&, size_type = 0) const noexcept;
  size_type find (core::string_ref, size_type = 0) const noexcept;
  size_type find (const_pointer, size_type = 0) const noexcept;
  size_type find (value_type, size_type = 0) const noexcept;

  size_type rfind (const_pointer, size_type, size_type) const noexcept;
  size_type rfind (basic_string const&, size_type = 0) const noexcept;
  size_type rfind (core::string_ref, size_type = 0) const noexcept;
  size_type rfind (const_pointer, size_type = 0) const noexcept;
  size_type rfind (value_type, size_type = 0) const noexcept;

  size_type find_first_of (const_pointer, size_type, size_type) const noexcept;
  size_type find_first_of (basic_string const&, size_type = 0) const noexcept;
  size_type find_first_of (core::string_ref, size_type = 0) const noexcept;
  size_type find_first_of (const_pointer, size_type = 0) const noexcept;
  size_type find_first_of (value_type, size_type = 0) const noexcept;

  size_type find_last_of (const_pointer, size_type, size_type) const noexcept;
  size_type find_last_of (basic_string const&, size_type = 0) const noexcept;
  size_type find_last_of (core::string_ref, size_type = 0) const noexcept;
  size_type find_last_of (const_pointer, size_type = 0) const noexcept;
  size_type find_last_of (value_type, size_type = 0) const noexcept;

  size_type find_first_not_of (
    const_pointer,
    size_type,
    size_type
  ) const noexcept;

  size_type find_first_not_of (
    basic_string const&,
    size_type = 0
  ) const noexcept;

  size_type find_first_not_of (
    core::string_ref,
    size_type = 0
  ) const noexcept;

  size_type find_first_not_of (
    const_pointer,
    size_type = 0
  ) const noexcept;

  size_type find_first_not_of (
    value_type,
    size_type = 0
  ) const noexcept;

  size_type find_last_not_of (
    const_pointer,
    size_type,
    size_type
  ) const noexcept;

  size_type find_last_not_of (
    basic_string const&,
    size_type = 0
  ) const noexcept;

  size_type find_last_not_of (
    core::string_ref,
    size_type = 0
  ) const noexcept;

  size_type find_last_not_of (
    const_pointer,
    size_type = 0
  ) const noexcept;

  size_type find_last_not_of (
    value_type,
    size_type = 0
  ) const noexcept;


private:
  std::tuple<pointer, size_type, size_type, allocator_type> storage;
};

template <class A>
bool operator == (basic_string<A> const&, basic_string<A> const&);

template <class A>
bool operator != (basic_string<A> const&, basic_string<A> const&);

template <class A>
bool operator >= (basic_string<A> const&, basic_string<A> const&);

template <class A>
bool operator <= (basic_string<A> const&, basic_string<A> const&);

template <class A>
bool operator > (basic_string<A> const&, basic_string<A> const&);

template <class A>
bool operator < (basic_string<A> const&, basic_string<A> const&);

template <class A>
std::basic_ostream<char, std::char_traits<char>>& operator << (
  std::basic_ostream<char, std::char_traits<char>>& os,
  basic_string<A> const& str
) { return os << str.c_str(); }

}} /* namespace json::v1 */

namespace std {

template <class A>
void swap (
  json::v1::basic_string<A>& lhs,
  json::v1::basic_string<A>& rhs
) noexcept { return lhs.swap(rhs); }

} /* namespace std */

#endif /* JSON_STRING_HPP */
