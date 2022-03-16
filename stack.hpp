#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:

            typedef Container container_type;
            typedef T value_type;
            typedef size_t size_type;
            typedef typename container_type::reference reference;
            typedef	typename container_type::const_reference const_reference;


            /*constructor*/
            explicit stack (const container_type& ctnr = container_type()): c(ctnr) {};

            stack( const stack& other ): c(other.c) {};
            
            /*destructor*/
            ~stack() {};
            
            stack& operator=( const stack& other )
            {
                if (this == &other)
                    return (*this);
                this->c = other.c;
                return (*this);
            };


            /*  methods  */
            value_type& top()
            {
                return this->c.back();
            };

            const value_type& top() const
            {
                return this->c.back();
            };

            bool empty() const
            {
                return this->c.empty();
            };

            size_type size() const
            {
                return this->c.size();
            };

            void push(const value_type& value)
            {
                this->c.push_back(value);
            };

            void pop()
            {
                this->c.pop_back();
            };

            friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs.c == rhs.c);
            };

            friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {
                return (lhs.c != rhs.c);
            };

            friend bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
            {
                return (lhs.c < rhs.c);
            };


            friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
            {
                return (lhs.c <= rhs.c);
            };

            friend bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
            {
                return (lhs.c > rhs.c);
            };

            friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
            {
                return (lhs.c >= rhs.c);
            };

        protected:
            container_type c;
    };
}

#endif