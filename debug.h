#include <bits/stdc++.h>

namespace helper {
    template <class T>
    inline constexpr bool is_array_v = std::is_array<T>::value;

    template <bool B, class T = void>
    using enable_if_t = typename std::enable_if<B, T>::type;

    template <typename T>
    auto is_iterable_impl(int) -> decltype(
        begin(std::declval<T &>()) != end(std::declval<T &>()),   // begin/end and operator !=
        void(),                                                   // Handle evil operator ,
        ++std::declval<decltype(begin(std::declval<T &>())) &>(), // operator ++
        void(*begin(std::declval<T &>())),                        // operator*
        std::true_type{}
    );

    template <typename T>
    std::false_type is_iterable_impl(...);

    /* check if variable type is iterable */
    // https://stackoverflow.com/a/29634934
    template <typename T>
    using is_iterable = decltype(is_iterable_impl<T>(0));

    /* check if pointer is iterator */
    // https://stackoverflow.com/a/4336298
    template<class T, class Enable = void>
    struct is_iterator {
        static T makeT();

        typedef void* twoptrs[2];

        static twoptrs& test(...);

        template<class R>
        static typename R::iterator_category* test(R);

        template<class R>
        static void* test(R*);

        static const bool value = sizeof(test(makeT())) == sizeof(void*);
    };

    template<class T>
    struct is_iterator<T, typename helper::enable_if_t<is_array_v<T>>> {
        static const bool value = false;
    };
};

template <typename A, typename B>
std::string to_string(std::pair<A, B> p);

template <typename A, typename B, typename C>
std::string to_string(std::tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
std::string to_string(std::tuple<A, B, C, D> p);

template <typename T>
typename helper::enable_if_t<!helper::is_iterable<T>::value, std::string> to_string(T v);

template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
std::string to_string(std::priority_queue<T, Container, Compare> pq);

template <class T>
std::string to_string(std::queue<T> q);

template <class T>
std::string to_string(std::stack<T> s);

std::string to_string(const std::string& s) {
    return '"' + s + '"';
}

std::string to_string(const char* s) {
    return to_string((std::string) s);
}

std::string to_string(char* s) {
    return to_string((std::string) s);
}

std::string to_string(bool b) {
    return (b ? "true" : "false");
}

template <size_t N>
std::string to_string(std::bitset<N> v) {
    std::string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A, typename B>
std::string to_string(std::pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
std::string to_string(std::tuple<A, B, C> p) {
    return "(" + to_string(std::get<0>(p)) + ", " + to_string(std::get<1>(p)) + ", " + to_string(std::get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
std::string to_string(std::tuple<A, B, C, D> p) {
    return "(" + to_string(std::get<0>(p)) + ", " + to_string(std::get<1>(p)) + ", " + to_string(std::get<2>(p)) + ", " + to_string(std::get<3>(p)) + ")";
}

template <typename T>
typename helper::enable_if_t<!helper::is_iterable<T>::value, std::string>
to_string(T v) {
    std::ostringstream ss;
    ss << v;
    return ss.str();
}

template <class T, class Container, class Compare>
std::string to_string(std::priority_queue<T, Container, Compare> pq) {
    bool first = true;
    std::string res = "{";
    while (!pq.empty()) {
        if (!first) res += ", ";
        res += to_string(pq.top());
        first = false;
        pq.pop();
    }
    res += "}";
    return res;
}

template <class T>
std::string to_string(std::queue<T> q) {
    bool first = true;
    std::string res = "{";
    while (!q.empty()) {
        if (!first) res += ", ";
        res += to_string(q.front());
        first = false;
        q.pop();
    }
    res += "}";
    return res;
}

template <class T>
std::string to_string(std::stack<T> s) {
    bool first = true;
    std::string res = "{";
    while (!s.empty()) {
        if (!first) res += ", ";
        res += to_string(s.top());
        first = false;
        s.pop();
    }
    res += "}";
    return res;
}

template <typename T>
std::string to_string(const std::vector<T>& v) {
    bool first = true;
    std::string res = "{";
    for (const T& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename T>
typename helper::enable_if_t<helper::is_iterable<T>::value, std::string>
to_string(T v) {
    bool first = true;
    std::string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << to_string(H);
    if (sizeof...(T))
        std::cerr << ", ";
    debug_out(T...);
}

#define debug(...) std::cerr << "LINE(" << __LINE__ << ") : [" << #__VA_ARGS__ << "] = ", debug_out(__VA_ARGS__)

/*
Usage:

#ifndef ONLINE_JUDGE
#include "algo/debug.h"
#else
#define debug(...) 42
#endif
*/