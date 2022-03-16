#ifndef FT_MAP_ITERATOR_HPP
# define FT_MAP_ITERATOR_HPP

#include "ft_iterator_traits.hpp"
#include "RBtree.hpp"


//map iterator is a Bidirectional iterator
namespace ft
{

    template<class T> struct remove_const { typedef T type; };

    template<class T> struct remove_const <const T> { typedef T type; };


    template <class Pair, typename traits = ft::iterator_traits<Pair*> >
    class map_iterator
    {
        public:
            typedef std::bidirectional_iterator_tag     iterator_category;
            typedef typename traits::difference_type    difference_type;
            typedef typename traits::value_type         value_type;
            typedef typename traits::pointer            pointer;
            typedef typename traits::reference          reference;
            //typedef ft::Node<Pair>* node_ptr;
            typedef ft::Node<typename ft::remove_const<Pair>::type >* node_ptr;

        private:
            node_ptr _ptr;
            node_ptr _root;

        public:
            map_iterator(): _ptr(NULL), _root(NULL) {};

            explicit map_iterator(node_ptr const & node, node_ptr const & root): _ptr(node), _root(root) {};

            map_iterator(map_iterator const & copy): _ptr(copy._ptr), _root(copy._root) {};

            map_iterator& operator=(map_iterator const & source)
            {
                if (this == &source)
                    return *this;
                this->_ptr = source._ptr;
                this->_root = source._root;
                return *this;
            };

            ~map_iterator() {};

            template <class Type>
            operator map_iterator<const Type>() const
            {
                return map_iterator<const Type>(_ptr, _root);
            };

            /*operators*/

            //*iter
            reference operator*() const
            {
                return this->_ptr->pair;
            };

            // it->
            pointer operator->() const
            {
                return &(this->_ptr->pair);
            };

            // *iter = tmp; 
            /*operator map_iterator*()
            {
                return this->_ptr->pair->first;
            };*/

            //it++
            map_iterator operator++(int)
            {
                map_iterator<Pair> tmp = *this;
                if (!this->_ptr)
                    return tmp;
                if (this->_ptr->right)
                {
                    node_ptr copy = this->_ptr->right;
                    while (copy && copy->left)
                        copy = copy->left;
                    this->_ptr = copy;
                    
                }
                else if (this->_ptr == find_max_all_tree(this->_ptr))
                    this->_ptr = NULL;
                else
                {
                    node_ptr parent = this->_ptr->parent;
                    while (parent && this->_ptr == parent->right)
                    {
                        this->_ptr = parent;
                        parent = this->_ptr->parent;
                    }
                    this->_ptr = parent;
                }
                return tmp;
            };

            // void print_nodes(node_ptr root, size_t i)
            // {
            //     if (!root)
            //         return ;
            //     print_nodes(root->left, i + 1);                
            //     std::cout << i + 1 << "[ " << root->pair.second << " ; " << root->pair.second << " ; ";
            //     if (root->color == Black)
            //         std::cout << "Black ]\n";
            //     else
            //         std::cout << "Red ]\n";
            //     print_nodes(root->right, i + 1);
            // }

            node_ptr find_max_all_tree(node_ptr node)
            {
                while (node && node->parent)
                    node = node->parent;
                while (node && node->right)
                    node = node->right;
                return node;
            };

            //++iter
            map_iterator& operator++()
            {
                if (!this->_ptr)
                    return *this;
                if (this->_ptr->right)
                {
                    node_ptr copy = this->_ptr->right;
                    while (copy->left)
                        copy = copy->left;
                    this->_ptr = copy;
                }
                else if (this->_ptr == find_max_all_tree(this->_ptr))
                    this->_ptr = NULL;
                else
                {
                    node_ptr parent = this->_ptr->parent;
                    while (parent && this->_ptr == parent->right)
                    {
                        this->_ptr = parent;
                        parent = this->_ptr->parent;
                    }
                    this->_ptr = parent;
                }
                return *this;
            };
            
            //it--
            map_iterator operator--(int)
            {
                map_iterator<Pair> tmp(*this);
                // --(*this);
                if (!this->_ptr)
                {
                    this->_ptr = find_max_all_tree(this->_root);
                    return tmp;
                }
                if (this->_ptr->left)
                {
                    node_ptr copy = this->_ptr->left;
                    while (copy->right)
                        copy = copy->right;
                    this->_ptr = copy;
                }
                else
                {
                    node_ptr parent = this->_ptr->parent;
                    while (parent && this->_ptr == parent->left)
                    {
                        this->_ptr = parent;
                        parent = parent->parent;
                    }
                    this->_ptr = parent;
                }
                return tmp;
            };

            //--iter
            map_iterator& operator--()
            {
                if (!this->_ptr)
                {
                    this->_ptr = find_max_all_tree(this->_root);
                    return *this;
                }
                if (this->_ptr && this->_ptr->left)
                {
                    node_ptr copy = this->_ptr->left;
                    while (copy->right)
                        copy = copy->right;
                    this->_ptr = copy;
                }
                else
                {
                    node_ptr parent = this->_ptr->parent;
                    while (parent && this->_ptr == parent->left)
                    {
                        this->_ptr = parent;
                        parent = parent->parent;
                    }
                    this->_ptr = parent;
                }
                return *this;
            };

            /*relationship*/
            template <class Iter1, class Iter2>
            friend bool	operator==(const map_iterator<Iter1>& left, const map_iterator<Iter2>& right);
            
            template <class Iter1, class Iter2>
            friend bool	operator!=(const map_iterator<Iter1>& left, const map_iterator<Iter2>& right);
    };

    template <class Iter1, class Iter2>
    bool	operator==(const map_iterator<Iter1>& left, const map_iterator<Iter2>& right)
    {
        return (left._ptr == right._ptr);
    };

    template <class Iter1, class Iter2>
    bool	operator!=(const map_iterator<Iter1>& left, const map_iterator<Iter2>& right)
    {
        return !(left == right);
    };
}

#endif