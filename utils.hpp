#ifndef UTILS_HPP
# define UTILS_HPP

#include <memory>

namespace ft
{
    template <class T>
    struct less
    {
        typedef T first_argument_type;
        typedef T second_argument_type;
        typedef bool result_type;

        first_argument_type first;
        second_argument_type second;
        result_type res;

        bool operator() (const T& x, const T& y) const { return x < y; }
    };

    template<bool Cond, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template<class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant type;

        operator value_type() const
        {
            return value;
        }
    };

    template<class T>
    struct is_const: ft::integral_constant<bool, false> {};

    template<class T>
    struct is_const<const T>: ft::integral_constant<bool, true> {};

    template <class>
    struct is_integral : public ft::integral_constant<bool, false> {};

    template<> struct is_integral<bool> :                       public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char> :                       public ft::integral_constant<bool, true> {};
    template<> struct is_integral<wchar_t> :                    public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned char> :              public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned short int> :         public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned int> :               public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long int> :          public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long long int> :     public ft::integral_constant<bool, true> {};

    template<> struct is_integral<signed char> :                public ft::integral_constant<bool, true> {};
    template<> struct is_integral<short int> :                  public ft::integral_constant<bool, true> {};
    template<> struct is_integral<int> :                        public ft::integral_constant<bool, true> {};
    template<> struct is_integral<long int> :                   public ft::integral_constant<bool, true> {};
    template<> struct is_integral<long long int> :              public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char16_t> :                  public ft::integral_constant<bool, true> {};

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1) return false;
            else if (*first1<*first2) return true;
            ++first1; ++first2;
        }
        return (first2!=last2);
    };

    template<class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!(*first1 == *first2)) {
                return false;
            }
        }
        return true;
    };

    /*pair*/
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        //default contructor
        pair(): first(first_type()), second(second_type()) {};

        //copy constructor
        //template<class U, class V>
        //pair (const pair<U, V> &pr) : first(static_cast<T1>(pr.first)), second(static_cast<T2>(pr.second)) {};
        
        template<class K, class V>
        pair (const pair<K, V> &pr) : first(static_cast<T1>(pr.first)), second(static_cast<T2>(pr.second)) {}; // ?? pair(const pair & pr) : first(pr.first), second(pr.second) {}


        //initialization constructor
        pair (const first_type& a, const second_type& b): first(a), second(b) {};

        template <class T>
        typename ft::enable_if<!ft::is_const<T>::value, pair&>::type
        operator= (const pair& pr)
        {
            // if (*this == pr)
            //     return *this;
            this->first = pr.first;
            this->second = pr.second;
            return (*this);
        };
    };

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs == rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs < lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs < lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs < rhs); }

    template <class T1,class T2>
    ft::pair<T1, T2> make_pair (T1 x, T2 y)
    {
        return ft::pair<T1, T2>(x, y);
    }

}

#endif