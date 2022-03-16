#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

#include "ft_iterator.hpp"
#include "ft_iterator_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        private:

            Iterator _it;

        public:

            //typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;

            /*constuctor*/
            reverse_iterator(): _it(Iterator()) {};

            explicit reverse_iterator (Iterator const & it): _it(it) {};

            reverse_iterator(reverse_iterator const & copy)
            {
                this->_it = copy.base();
            };


            template <class Type>
            operator reverse_iterator<Type>() const
            {
                return reverse_iterator<Type>(this->_it);
            };

            /*operator = */
            template <class Type>
            reverse_iterator& operator=(reverse_iterator<Type> const & source)
            {
                if (*this == source)
                    return *this;
                this->_it = source.base();
                return *this;
            }

            /*destructor*/ // ???
            ~reverse_iterator() {};

            /*operators*/
            Iterator base() const
            {
                return this->_it;
            };

            reference operator*() const
            {
                Iterator tmp = this->_it;
                tmp--;
                return *tmp;
            };

            reverse_iterator operator+(difference_type n) const
            {
                return reverse_iterator(base() - n);
            };

            reverse_iterator& operator++()
            {
                --this->_it;
                return *this;
            };

            reverse_iterator  operator++(int)
            {
                reverse_iterator temp = *this;
                --this->_it;
                return temp;
            };

            reverse_iterator& operator+= (difference_type n)
            {
                this->_it -= n;
                return *this;
            };


            reverse_iterator operator- (difference_type n) const
            {
                return reverse_iterator(base() + n);
            };

            reverse_iterator& operator--()
            {
                ++this->_it;
                return *this;
            };
            
            reverse_iterator  operator--(int)
            {
                reverse_iterator temp = *this;
                ++this->_it;
                return temp;
            };

            reverse_iterator& operator-= (difference_type n)
            {
                this->_it += n;
                return *this;
            };

            pointer operator->() const
            {
                return &(operator*());
            };

            reference operator[] (difference_type n) const
            {
                return this->_it[ -n - 1];
            };
    };

    template <class Iter1, class Iter2>
    bool operator==(reverse_iterator<Iter1> const & left, reverse_iterator<Iter2> const & right)    
    {
        return left.base() == right.base();
    };
    
    template <class Iter1, class Iter2>
    bool operator!=(reverse_iterator<Iter1> const & left, reverse_iterator<Iter2> const & right)       
    {
        return !(left == right);
    };
    
    template <class Iter1, class Iter2>
    bool operator<=(reverse_iterator<Iter1> const & left, reverse_iterator<Iter2> const & right)
    {
        return !(left.base() > right.base());
    };
    
    template <class Iter1, class Iter2>
    bool operator>=(reverse_iterator<Iter1> const & left, reverse_iterator<Iter2> const & right)      
    {
        return !(left.base() < right.base());
    };
    
    template <class Iter1, class Iter2>
    bool operator<(reverse_iterator<Iter1> const & left, reverse_iterator<Iter2> const & right)        
    {
        return left.base() < right.base();
    };
    
    template <class Iter1, class Iter2>
    bool operator>(reverse_iterator<Iter1> const & left, reverse_iterator<Iter2> const & right)        
    {
        return left.base() > right.base();
    };

    template <class Iterator>
    reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) {
        return reverse_iterator<Iterator>(it + n);
    }

    template <class Iterator1, class Iterator2>
    typename reverse_iterator<Iterator1>::difference_type	operator-(const reverse_iterator<Iterator1>& first, const reverse_iterator<Iterator2>& second) {
        return second.base() - first.base();
    }

}

#endif