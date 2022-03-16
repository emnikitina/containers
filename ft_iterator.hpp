#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include "ft_iterator_traits.hpp"

namespace ft
{
    template <class T, typename traits = std::iterator_traits<T> >
    class ftIterator
    {
        private:
            T ptr;

        public:
            typedef std::random_access_iterator_tag     iterator_category;
            typedef typename traits::difference_type    difference_type;
            typedef typename traits::value_type         value_type;
            typedef typename traits::pointer            pointer;
            typedef typename traits::reference          reference;

            ftIterator(): ptr(NULL) {};

            explicit ftIterator(pointer ptr): ptr(ptr) {};

            ftIterator(ftIterator const &copy): ptr(copy.ptr) {};
            
            ~ftIterator() {};

            template <class Iter>
            ftIterator& operator=(ftIterator<Iter> const & source)
            {
                if (*this == source)
                    return *this;
                this->ptr = source.getPtr();
                return *this;
            };

            pointer getPtr() const
            {
                return this->ptr;
            }

            template <class Type>
            operator ftIterator<Type>() const
            {
                return ftIterator<Type>(this->ptr);
            };

            //*iter
            reference operator*()
            {
                return *this->ptr;
            };

            //->
            pointer operator->()
            {
                return this->ptr;
            };

            // *iter = tmp;
            operator ftIterator*()
            {
                return *this->ptr;
            };

            //it++
            ftIterator operator++(int)
            {
                ftIterator tmp(*this);
                ++this->ptr;
                return tmp;
            };

            //++iter
            ftIterator& operator++()
            {
                ++this->ptr;
                return *this;
            };
            
            //it--
            ftIterator operator--(int)
            {
                ftIterator tmp(*this);
                --this->ptr;
                return tmp;
            };

            //--iter
            ftIterator& operator--()
            {
                --this->ptr;
                return *this;
            };
            
            //iter + n
            ftIterator operator+(difference_type const & n) const
            {
                return ftIterator(this->ptr + n);
            };

            //iter - n
            ftIterator operator-(difference_type const & n) const
            {
                return ftIterator(this->ptr - n);
            };

            // iter += n
            ftIterator& operator+=(difference_type const & n)
            {
                this->ptr += n;
                return *this;
            };

            // iter -= n
            ftIterator& operator-=(difference_type const & n)
            {
                this->ptr -= n;
                return *this;
            };

            //iter[]
            reference operator[](size_t n) const
            {
                return *(this->ptr + n);
            };

            template <class Iter1, class Iter2>
            friend bool operator==(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right);
            
            template <class Iter1, class Iter2>
            friend bool operator!=(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right);
            
            template <class Iter1, class Iter2>
            friend bool operator<=(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right);
            
            template <class Iter1, class Iter2>
            friend bool operator>=(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right);
            
            template <class Iter1, class Iter2>
            friend bool operator<(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right);
            
            template <class Iter1, class Iter2>
            friend bool operator>(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right);

            template <class Iterator>
            friend typename ftIterator<Iterator>::difference_type	operator-(const ftIterator<Iterator>& A, const ftIterator<Iterator>& B);

            template <class Iterator1, class Iterator2>
            friend typename ftIterator<Iterator1>::difference_type	operator-(const ftIterator<Iterator1>& A, const ftIterator<Iterator2>& B);
                    
    };

    template <class Iter1, class Iter2>
    bool operator==(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right)    
    {
        return left.ptr == right.ptr;
    };
    
    template <class Iter1, class Iter2>
    bool operator!=(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right)       
    {
        return !(left.ptr == right.ptr);
    };
    
    template <class Iter1, class Iter2>
    bool operator<=(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right)
    {
        return !(left.ptr > right.ptr);
    };
    
    template <class Iter1, class Iter2>
    bool operator>=(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right)      
    {
        return !(left.ptr < right.ptr);
    };
    
    template <class Iter1, class Iter2>
    bool operator<(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right)        
    {
        return left.ptr < right.ptr;
    };
    
    template <class Iter1, class Iter2>
    bool operator>(ftIterator<Iter1> const & left, ftIterator<Iter2> const & right)        
    {
        return left.ptr > right.ptr;
    };

    template <class Iterator>
    ftIterator<Iterator>	operator+(typename ftIterator<Iterator>::difference_type n, const ftIterator<Iterator>& it)
    {
        return ftIterator<Iterator>(it + n);
    };

    template <class Iterator>
    typename ftIterator<Iterator>::difference_type	operator-(const ftIterator<Iterator>& A, const ftIterator<Iterator>& B)
    {
        return A.ptr - B.ptr;
    };

    template <class Iterator1, class Iterator2>
    typename ftIterator<Iterator1>::difference_type	operator-(const ftIterator<Iterator1>& A, const ftIterator<Iterator2>& B)
    {
        return A.ptr - B.ptr;
    };
}

#endif