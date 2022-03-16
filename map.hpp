#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include "ft_map_iterator.hpp"
#include "RBtree.hpp"
#include "ft_reverse_iterator.hpp"
#include "utils.hpp"

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            typedef Key key_type;	
            typedef T mapped_type;
            typedef ft::pair<const Key, T> value_type;
            typedef Compare key_compare;

        private:
            class pair_compare
            {
                key_compare _compare;

                public:
                    pair_compare(const key_compare & compare = key_compare()) : _compare(compare) {}

                    bool operator()(const value_type & x, const value_type & y) const{
                        return (_compare(x.first, y.first));
                    }
            };

        public:

            typedef pair_compare value_compare;
            typedef Alloc allocator_type;
            typedef ft::map_iterator<value_type> iterator;
            typedef ft::map_iterator<const value_type> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;	
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;	
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

            typedef typename Alloc::template rebind<Node<value_type> >::other node_alloc;
            typedef RBtree<value_type, Node<value_type>, pair_compare, node_alloc> tree_type;
            typedef Node<value_type>* node_ptr;

        private:

            tree_type _tree;
            size_type _size;

            allocator_type _allocator;
            key_compare _key_comp;
            value_compare _value_comp;

        public:
            /*constructors*/
            //default = empty
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
             _tree(tree_type()), _size(0), _allocator(alloc), _key_comp(comp), _value_comp(pair_compare(_key_comp)) {};

            
            //range 	
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(tree_type()), _size(0), _allocator(alloc), _key_comp(comp), _value_comp(pair_compare(_key_comp))
            {
                insert(first, last);
            };
            
            //copy	
            map (const map& x): _tree(tree_type()), _size(0), _allocator(x._allocator), _key_comp(x._key_comp), _value_comp(x._value_comp)
            {
                clear();
                insert(x.begin(), x.end());
            };

            /*destructor*/
            ~map()
            {
                this->_tree.clear(this->_tree.getRoot());
                this->_tree.makeRootNull();
            };

            map& operator=(map const & source)
            {
                if (this == &source)
                    return *this;
                clear();
                this->_allocator = source._allocator;
                this->_key_comp = source._key_comp;
                this->_value_comp = source._value_comp;
                insert(source.begin(), source.end());
                return *this;
            };

            /*iterators*/
            iterator begin()
            {               
                return iterator(this->_tree.min(this->_tree.getRoot()), this->_tree.getRoot());
            };

            const_iterator begin() const
            {
                return const_iterator(this->_tree.min(this->_tree.getRoot()), this->_tree.getRoot());
            };

            iterator end()
            {
                return iterator(NULL, this->_tree.getRoot());
            };

            const_iterator end() const
            {
                return const_iterator(NULL, this->_tree.getRoot());
            };

            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            };

            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            };

            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            };

            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
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
                return this->_tree.max_size();
            };

            /*element access*/
            mapped_type& operator[] (const key_type& k)
            {
                return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
            };

            /*modifiers*/
            
            ft::pair<iterator, bool> insert (const value_type& val)
            {
                bool res = this->_tree.insert(this->_tree.createNode(val));
                this->_size += res;
                return ft::pair<iterator, bool>(iterator(this->_tree.find(val, this->_tree.getRoot()), this->_tree.getRoot()), res);
            };

            
            //with hint
            iterator insert (iterator, const value_type& val)
            {
                this->_size += this->_tree.insert(this->_tree.createNode(val));
                return iterator(this->_tree.find(val, this->_tree.getRoot()), this->_tree.getRoot());
            };
            
            //range
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
            {
                for (; first != last; ++first)
                    this->_size += this->_tree.insert(this->_tree.createNode(*first));
            };

            void erase (iterator position)
            {
                iterator it = begin();
                while (it != position)
                    it++;
                node_ptr node = this->_tree.find(*it, this->_tree.getRoot());
                this->_size -= this->_tree.deleteNode(node);
            };

            size_type erase (const key_type& k)
            {
                node_ptr node = this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot());
                size_t res = this->_tree.deleteNode(node);
                this->_size -= res;
                return res;
            };

            void erase (iterator first, iterator last)
            {
                while (first != last)
                    erase(first++);                    
            };

            void swap (map& x)
            {
                tree_type tree = this->_tree;
                size_type size = this->_size;
                allocator_type alloc = this->_allocator;
                key_compare k_comp = this->_key_comp;
                value_compare val_comp = this->_value_comp;

                this->_tree = x._tree;
                this->_size = x._size;
                this->_allocator = x._allocator;
                this->_key_comp = x._key_comp;
                this->_value_comp = x._value_comp;

                x._tree = tree;
                x._size = size;
                x._allocator = alloc;
                x._key_comp = k_comp;
                x._value_comp = val_comp;
            };

            void clear()
            {
                this->_tree.clear(this->_tree.getRoot());
                this->_tree.makeRootNull();
                this->_size = 0;
            };

            /*observers*/
            key_compare key_comp() const
            {
                return this->_key_comp;
            };

            value_compare value_comp() const
            {
                return this->_value_comp;
            };

            /*operations*/
            iterator find (const key_type& k)
            {
                return iterator(this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot()), this->_tree.getRoot());
            };

            const_iterator find (const key_type& k) const
            {
                return const_iterator(this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot()), this->_tree.getRoot());
            };

            size_type count (const key_type& k) const
            {
                if (this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot()))
                    return 1;
                return 0;
            };

            iterator lower_bound (const key_type& k)
            {
                return iterator(this->_tree.lower(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree.getRoot());
            };

            const_iterator lower_bound (const key_type& k) const
            {
                return const_iterator(this->_tree.lower(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree.getRoot());
            };

            iterator upper_bound (const key_type& k)
            {
                return iterator(this->_tree.upper(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree.getRoot());
            };
            
            const_iterator upper_bound (const key_type& k) const
            {
                return const_iterator(this->_tree.upper(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree.getRoot());
            };

            pair<iterator, iterator> equal_range (const key_type& k)
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            };
            

            pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            };

            /*allocator*/
            allocator_type get_allocator() const
            {
                return this->_allocator;
            };
    };

    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin() ) && ft::equal(rhs.begin(), rhs.end(), lhs.begin());
    };
    
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return !(lhs == rhs);
    };
    
    template< class Key, class T, class Compare, class Alloc >
    bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());        
    };
    
    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return !(lhs > rhs);
    };
    
    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return (rhs < lhs);
    };
    
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
    {
        return !(lhs < rhs);
    };
}

#endif