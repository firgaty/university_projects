// #ifndef MODEL_UTIL_TUPLEITERATION_HPP_
// #define MODEL_UTIL_TUPLEITERATION_HPP_

// namespace TupleIteration
// {
// // based on http://stackoverflow.com/a/17426611/410767 by Xeo

// template <size_t... Ints>
// struct index_sequence {
//     using type       = index_sequence;
//     using value_type = size_t;
//     static constexpr std::size_t size() noexcept { return sizeof...(Ints); }
// };

// // --------------------------------------------------------------

// template <class Sequence1, class Sequence2>
// struct _merge_and_renumber;

// template <size_t... I1, size_t... I2>
// struct _merge_and_renumber<index_sequence<I1...>, index_sequence<I2...>>
//     : index_sequence<I1..., (sizeof...(I1) + I2)...> {
// };

// // --------------------------------------------------------------

// template <size_t N>
// struct make_index_sequence
//     : _merge_and_renumber<typename make_index_sequence<N / 2>::type,
//                           typename make_index_sequence<N - N / 2>::type> {
// };

// template <>
// struct make_index_sequence<0> : index_sequence<> {
// };
// template <>
// struct make_index_sequence<1> : index_sequence<0> {
// };

// // // tuple_iteration
// // template <class... Fs>
// // void do_in_order(Fs &&... fs)
// // {
// //     int unused[] = {0, ((void)std::forward<Fs>(fs)(), 0)...}(
// //         void)unused; // blocks warnings
// // }

// // template <class T>
// // constexpr make_index_sequence<std::tuple_size<T>::value> get_indexes(T const &)
// // {
// //     return {};
// // }

// // template <size_t... Is, class Tuple, class F>
// // void for_each(std::index_sequence<Is...>, Tuple &&tup, F &&f)
// // {
// //     using std::get;
// //     do_in_order([&] { f(get<Is>(std::forward<Tuple>(tup))); }...);
// // }

// // template <class Tuple, class F>
// // void for_each(Tuple &&tup, F &&f)
// // {
// //     auto indexes = get_indexes(tup);
// //     for_each(indexes, std::forward<Tuple>(tup), std::forward<F>(f));
// // }

// } // namespace std

// #endif // !MODEL_UTIL_TUPLEITERATION_HPP_