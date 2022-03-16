#ifndef SET_HPP
# define SET_HPP

#include "RBtree.hpp"
#include "ft_map_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include <memory>
#include "utils.hpp"

namespace ft
{
    template <class Key, class Compare = ft::less<Key>, class Allocator = std::allocator<Key> >
    class set
    {
        public:
            typedef Key key_type;
            typedef Key value_type;
            typedef std::size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef Compare key_compare;
            typedef Compare value_compare;
            typedef Allocator allocator_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef typename Allocator::pointer pointer;
            typedef typename Allocator::const_pointer const_pointer;
            
            typedef ft::map_iterator<const value_type> iterator;
            typedef ft::map_iterator<const value_type> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

            typedef typename Allocator::template rebind<Node<value_type> >::other node_alloc;
            typedef RBtree<value_type, Node<value_type>, value_compare, node_alloc> tree_type;
            typedef Node<value_type>* node_ptr;

        private:
            allocator_type _allocator;
            tree_type _tree;
            size_type _size;
            key_compare _key_comp;
            value_compare _value_comp;

        public:
            /* constructors */
            set(): _allocator(Allocator()), _tree(tree_type()), _size(0), _key_comp(key_compare()), _value_comp(value_compare()) {};
            
            explicit set(const Compare& comp, const Allocator& alloc = Allocator()): _allocator(alloc), _tree(tree_type()), _size(0), _key_comp(comp), _value_comp(comp) {};

            template <class InputIt>
            set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _allocator(alloc), _tree(tree_type()), _size(0), _key_comp(comp), _value_comp(comp)
            {
                insert(first, last);
            };

            set(const set& other): _allocator(other._allocator), _tree(tree_type()), _size(0), _key_comp(other._key_comp), _value_comp(other._value_comp)
            {
                clear();
                insert(other.begin(), other.end());
            };

            set& operator=(const set& other)
            {
                if (this == &other)
                    return *this;
                clear();
                this->_allocator = other._allocator;
                this->_key_comp = other._key_comp;
                this->_value_comp = other._value_comp;
                insert(other.begin(), other.end());
                return *this;
            };

            ~set()
            {
                this->_tree.clear(this->_tree.getRoot());
                this->_tree.makeRootNull();
            };

            /* methods */
            allocator_type get_allocator() const
            {
                return this->_allocator;
            };

            /* iterators */
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

            /* capacity */
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

            /* modifiers */

            void clear()
            {
                this->_tree.clear(this->_tree.getRoot());
                this->_tree.makeRootNull();
                this->_size = 0;
            };

            ft::pair<iterator, bool> insert(const value_type& val)
            {
                bool res = this->_tree.insert(this->_tree.createNode(val));
                this->_size += res;
                return ft::pair<iterator, bool>(iterator(this->_tree.find(val, this->_tree.getRoot()), this->_tree.getRoot()), res);
            };

            iterator insert(iterator, const value_type& val)
            {
                this->_size += this->_tree.insert(this->_tree.createNode(val));
                return iterator(this->_tree.find(val, this->_tree.getRoot()), this->_tree.getRoot());
            };

            template <class InputIt>
            void insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
            {
                for (; first != last; ++first)
                    this->_size += this->_tree.insert(this->_tree.createNode(*first));
            };

            void erase(iterator pos)
            {
                iterator it = begin();
                while (it != pos)
                    it++;
                node_ptr node = this->_tree.find(*it, this->_tree.getRoot());
                this->_size -= this->_tree.deleteNode(node);
            };

            void erase(iterator first, iterator last)
            {
                while (first != last)
                    erase(first++);
            };

            size_type erase(const Key& key)
            {
                node_ptr node = this->_tree.find(key, this->_tree.getRoot());
                size_t res = this->_tree.deleteNode(node);
                this->_size -= res;
                return res;
            };

            void swap(set& x)
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

            /* look up */
            size_type count(const Key& key) const
            {
                if (this->_tree.find(key, this->_tree.getRoot()))
                    return 1;
                return 0;
            };

            iterator find(const Key& key)
            {
                return iterator(this->_tree.find(key, this->_tree.getRoot()), this->_tree.getRoot());
            };
	
            const_iterator find(const Key& key) const
            {
                return const_iterator(this->_tree.find(key, this->_tree.getRoot()), this->_tree.getRoot());
            };

            ft::pair<iterator, iterator> equal_range(const Key& key)
            {
                return ft::make_pair(lower_bound(key), upper_bound(key));
            };

            ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
            {
                return ft::make_pair(lower_bound(key), upper_bound(key));
            };

            iterator lower_bound(const Key& key)
            {
                return iterator(this->_tree.lower(this->_tree.getRoot(), key), this->_tree.getRoot());
            };
	
            const_iterator lower_bound(const Key& key) const
            {
                return const_iterator(this->_tree.lower(this->_tree.getRoot(), key), this->_tree.getRoot());
            };

            iterator upper_bound(const Key& key)
            {
                return iterator(this->_tree.upper(this->_tree.getRoot(), key), this->_tree.getRoot());            
            };
	
            const_iterator upper_bound(const Key& key) const
            {
                return const_iterator(this->_tree.upper(this->_tree.getRoot(), key), this->_tree.getRoot());
            };

            /* observers */
            key_compare key_comp() const
            {
                return this->_key_comp;
            };

            value_compare value_comp() const
            {
                return this->_value_comp;
            };
    };

    /* operators */
    template< class Key, class Compare, class Alloc >
    bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin() ) && ft::equal(rhs.begin(), rhs.end(), lhs.begin());
    };
    
    template< class Key, class Compare, class Alloc >
    bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return !(lhs == rhs);
    };
    
    template< class Key, class Compare, class Alloc >
    bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());        
    };
    
    template< class Key, class Compare, class Alloc >
    bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return !(lhs > rhs);
    };
    
    template< class Key, class Compare, class Alloc >
    bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return (rhs < lhs);
    };
    
    template< class Key, class Compare, class Alloc >
    bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
    {
        return !(lhs < rhs);
    };
}

#endif