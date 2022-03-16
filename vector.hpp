#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <exception>
#include <memory>
#include <cstddef>
#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include <iterator>

#include "utils.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            /* Member types*/
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef ft::ftIterator<T*> iterator;
            typedef ft::ftIterator<const T*> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

        private:
            T* _array;
            size_type _size;
            size_type _capacity;
            allocator_type _allocator;

        public:
            /*constructors*/
            vector(): _array(0), _size(0), _capacity(0), _allocator(allocator_type()) {};

            explicit vector (const allocator_type& alloc): _array(0), _size(0), _capacity(0), _allocator(alloc) {};

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
            _array(0), _size(0), _capacity(0), _allocator(alloc)
            {
                insert(end(), n, val);
            };
            
            template<class InputIt>
            vector (InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0):
            _array(0), _size(0), _capacity(0), _allocator(alloc)
            {
                insert(end(), first, last);
            };

            vector (vector const & copy)
            {
                this->_size = copy._size;
                this->_capacity = copy._capacity;
                this->_allocator = copy._allocator;
                try
                {
                    this->_array = this->_allocator.allocate(this->_capacity);
                    for (size_t i = 0; i < this->_size; ++i)
                        this->_allocator.construct(this->_array + i, copy[i]);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
            };

            vector& operator=(const vector& source)
            {
                if (this == &source)
                    return *this;
                clear();
                this->_size = source._size;
                this->_allocator = source._allocator;
                this->_capacity = source._capacity;
                for (size_t i = 0; i < this->_size; i++)
                    this->_allocator.destroy(this->_array + i);
                this->_allocator.deallocate(this->_array, this->_capacity);
                try
                {
                    this->_array = this->_allocator.allocate(this->_capacity);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                for (size_t i = 0; i < this->_size; i++)
                    this->_allocator.construct(this->_array + i, source[i]);
                return (*this);
            };

            ~vector() 
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_allocator.destroy(this->_array + i);
                this->_allocator.deallocate(this->_array, this->_size);
                this->_size = 0;
                this->_capacity = 0;
            };

            void assign(size_type count, const T& value)
            {
                clear();
                insert(end(), count, value);
            };

            template<class InputIt>
            void assign(InputIt first, InputIt last)
            {
                clear();
                insert(end(), first, last);
            };

            allocator_type get_allocator() const
            {
                return this->_allocator;
            };

            /*element access*/
            reference at(size_type pos)
            {
                if (pos > this->_size)
                    throw std::out_of_range("Out of vector range");
                return (*(this->_array + pos));
            };

            const_reference at(size_type pos) const
            {
                if (pos >= this->_size || pos < 0)
                    throw std::out_of_range("Out of range of vector");
                return (*(this->_array + pos));
            };

            reference operator[](size_type pos)
            {
                return (*(this->_array + pos));
            };

            const_reference operator[]( size_type pos ) const
            {
                return (*(this->_array + pos));
            };

            reference front()
            {
                return (*this->_array);
            };

            const_reference front() const
            {
                return (*this->_array);
            };

            reference back()
            {
                return (*(this->_array + this->_size - 1));
            };

            const_reference back() const
            {
                return (*(this->_array + this->_size - 1));
            };

            T* data()
            {
                return this->_array;
            };

            const T* data() const
            {
                return this->_array;
            };

            /*iterators*/

            iterator begin()
            {
                return iterator(this->_array);
            };

            const_iterator begin() const
            {
                return const_iterator(this->_array);
            };
            
            iterator end()
            {
                return iterator(this->_array + this->_size);
            };

            const_iterator end() const
            {
                return const_iterator(this->_array + this->_size);
            };
            
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            };

            const_reverse_iterator rbegin() const
            {
                return const_reverse_iteraror(end());
            };
            
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            };

            const_reverse_iterator rend() const
            {
                return const_reverse_iteraror(begin());
            };
            

            /*capacity*/
            bool empty() const
            {
                return (this->_size == 0);
            };
            
            size_type size() const
            {
                return this->_size;
            };

            size_type max_size() const
            {
                return (this->_allocator.max_size());
            };

            void reserve(size_type n)
            {
                if (n > max_size() || n < 0)
                    throw std::length_error("Vector capacity error!");
                if (n <= this->_capacity)
                    return ;
                size_type newCap = 2 * this->_capacity + (this->_capacity == 0);
                if (n < newCap && newCap < max_size())
                    n = newCap;
                
                T* tmp = this->_allocator.allocate(n);
                for (size_t i = 0; i < this->_size; i++)
                    this->_allocator.construct(tmp + i, *(this->_array + i));
                for (size_t i = 0; i < this->_size; i++)
                    this->_allocator.destroy(this->_array + i);
                this->_allocator.deallocate(this->_array, this->_capacity);
                this->_array = tmp;
                this->_capacity = n;
            };

            size_type capacity() const
            {
                return this->_capacity;
            };

            /*modifiers*/

            void clear()
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_allocator.destroy(this->_array + i);
                this->_size = 0;
            };

            iterator insert(iterator pos, const value_type& value)
            {
                if (pos < begin() || pos > end())
                    throw std::out_of_range("Out of vector range\n");
                size_t dif = pos - begin();
                reserve(this->_size + 1);
                this->_size++;
                for (size_t i = this->_size; i > dif; i--)
                {
                    this->_allocator.construct(this->_array + i, *(this->_array + i - 1));
                    this->_allocator.destroy(this->_array + i - 1);
                }
                this->_allocator.construct(this->_array + dif, value);
                return iterator(begin() + dif);
            };

            void insert(iterator pos, size_type count, const T& value)
            {
                if (pos < begin() || pos > end())
                    throw std::out_of_range("Out of vector range\n");
                size_t dif = pos - this->begin();
                reserve(this->_size + count);
                this->_size += count;
                for (size_t i = this->_size; i >= dif + count; i--)
                {
                    this->_allocator.construct(this->_array + i, *(this->_array + i - count));
                    this->_allocator.destroy(this->_array + i - count);
                }
                for (size_t i = 0; i < count; ++i)
                    this->_allocator.construct(this->_array + dif + i, value);
                
            };
            
            template< class InputIt >
            void insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
            {
                if (pos < begin() || pos > end())
                    throw std::out_of_range("Out of vector range");
                size_t dif = pos - begin();
                size_type n = static_cast<size_type>(std::distance(first, last));
                pointer tmp = NULL;
                InputIt it_tmp = first;       
                try
                {
                    tmp = this->_allocator.allocate(n);
                    for (size_t i = 0; i < n; i++)
                    {
                        this->_allocator.construct(tmp + i, *it_tmp);
                        it_tmp++;
                    }
                }
                catch(...)
                {
                    for (size_t i = 0; tmp + i != NULL && i < n; i++)
                        this->_allocator.destroy(tmp + i);
                    this->_allocator.deallocate(tmp, n);
                    throw;
                }
                for (size_t i = 0; i < n; i++)
                    this->_allocator.destroy(tmp + i);
                this->_allocator.deallocate(tmp, n);

                reserve(this->_size + n);
                this->_size += n;
                for (size_t i = this->_size - 1; i >= dif + n; i--)
                {
                    this->_allocator.construct(this->_array + i, *(this->_array + i - n));
                    this->_allocator.destroy(this->_array + i - n);
                }
                for (size_t i = 0; i < n; i++)
                {
                    this->_allocator.construct(this->_array + dif + i, *first);
                    first++;
                }
            };

            iterator erase( iterator pos )
            {
                if (pos < begin() || pos > end())
                    throw std::out_of_range("out of vector range");
                size_t dif = pos - begin();
                this->_allocator.destroy(this->_array + dif);
                for (size_t i = dif; i < this->_size; ++i)
                {                    
                    this->_allocator.construct(this->_array + i, *(this->_array + i + 1));
                    this->_allocator.destroy(this->_array + i + 1);
                }
                this->_size--;
                return begin() + dif;
            };
            
            iterator erase( iterator first, iterator last )
            {
                if (begin() > first || last > end() || last < first)
                    throw std::out_of_range("out of vector range");
                size_type dif = first - begin();
                size_type n = last - first;
                for (size_t i = 0; i < n; i++)
                    this->_allocator.destroy(this->_array + dif + i);
                for (size_t i = 0; i < this->_size - dif - n; i++)
                {
                    this->_allocator.construct(this->_array + dif + i, *(this->_array + dif + n + i));
                    this->_allocator.destroy(this->_array + dif + n + i);
                }
                this->_size -= n;
                return begin() + dif;
            };

            void push_back(const T& value)
            {
                reserve(this->_size + 1);
                this->_allocator.construct(this->_array + this->_size, value);
                this->_size++;
            };

            void pop_back()
            {
                if (this->_size)
                {
                    this->_allocator.destroy(this->_array + this->_size - 1);
                    this->_size--;
                }
            };

            void resize(size_type n, value_type val = value_type())
            {
                if (n <= this->_size)
                {
                    for (size_t i = n; i < this->_size; i++)
                        this->_allocator.destroy(this->_array + i);
                }
                else
                    insert(this->end(), n - this->_size, val);
                this->_size = n;
            };

            void swap(vector& other)
            {
                T* array = this->_array;
                size_type size = this->_size;
                size_type capacity = this->_capacity;
                allocator_type allocator = this->_allocator;
                
                this->_array = other._array;
                this->_size = other._size;
                this->_capacity = other._capacity;
                this->_allocator = other._allocator;
                
                other._array = array;
                other._size = size;
                other._capacity = capacity;
                other._allocator = allocator;
            };

            
    };

    /*non member function*/

    template< class T, class Alloc >
    bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
    {
        return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    };

    template< class T, class Alloc >
    bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
    {
        return !(lhs == rhs);
    };

    template< class T, class Alloc >
    bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    };

    template< class T, class Alloc >
    bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
    {
        return !(lhs > rhs);
    };

    template< class T, class Alloc >
    bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
    {
        return (rhs < lhs);
    };

    template< class T, class Alloc >
    bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
    {
        return !(lhs < rhs);
    };
}

#endif