#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include "utils.hpp"

namespace ft
{
    enum RBTreeColors { Black, Red };

    template <class Pair>
    class Node
    {
        public:
            Pair pair;
            Node* left;
            Node* right;
            Node* parent;
            bool color;

        
            Node(): pair(Pair()), left(NULL), right(NULL), parent(NULL), color(Black) {};

            Node(Pair const & pair): pair(pair), left(NULL), right(NULL), parent(NULL), color(Black) {};
            
            Node(Node const & copy): pair(copy.pair), left(copy.left), right(copy.right), parent(copy.parent), color(copy.color) {};

            Node& operator=(Node const & source)
            {
                if (this == &source)
                    return *this;
                
                this->pair = source.pair;
                this->left = source.left;
                this->right = source.right;
                this->parent = source.parent;
                this->color = source.color;
                return *this;
            };

            ~Node() {};

    };

    template <class Pair, class Node, class Compare, class Allocator = std::allocator<Node> >
    class RBtree
    {
        public:
            typedef Allocator allocator_type;
            typedef typename allocator_type::pointer pointer;

        private:
            pointer _root;
            Allocator _allocator;
            Compare _comparator;

            pointer createNullNode()
            {
                pointer node = this->_allocator.allocate(1);
                this->_allocator.construct(node, Node());
                return node;
            };

        public:
            RBtree(): _root(NULL), _allocator(Allocator()) {};

            ~RBtree() {};

            /*methods*/

            pointer createNode(Pair value)
            {
                pointer node = this->_allocator.allocate(1);
                this->_allocator.construct(node, value);
                return node;
            };

            void destroyNode(pointer node)
            {
                if (!node)
                    return ;
                this->_allocator.destroy(node);
                this->_allocator.deallocate(node, 1);
            };

            pointer getRoot() const
            {
                return this->_root;
            }

            size_t max_size() const
            {
                return this->_allocator.max_size();
            }

            pointer min(pointer node) const
            {
                if (node)
                {
                    while (node->left)
                        node = node->left;
                }
                return node;
            };

            pointer max(pointer node) const
            {
                if (node)
                {
                    while (node->right)
                    node = node->right;
                }
                return node;
            };

            pointer find(Pair value, pointer node) const
            {                
                if (node)
                {
                    if (_comparator(node->pair, value))
                        return find(value, node->right);
                    else if (_comparator(value, node->pair)){
                        return find(value, node->left);
                    }
                }
                return node;
            };

            void leftRotate(pointer node)
            {
                pointer tmp = node->right;
                node->right = tmp->left;
                if (tmp->left)
                    tmp->left->parent = node;
                tmp->parent = node->parent;
                if (!node->parent)
                    this->_root = tmp;
                else if (node == node->parent->left)
                    node->parent->left = tmp;
                else
                    node->parent->right = tmp;
                tmp->left = node;
                node->parent = tmp;
            };

            void rightRotate(pointer node)
            {
                pointer tmp = node->left;
                node->left = tmp->right;
                if (tmp->right)
                    tmp->right->parent = node;
                tmp->parent = node->parent;
                if (!node->parent)
                    this->_root = tmp;
                else if (node == node->parent->right)
                    node->parent->right = tmp;
                else
                    node->parent->left = tmp;
                tmp->right = node;
                node->parent = tmp;
            };
            
            void insertBalance(pointer node)
            {
                pointer tmp = NULL;
                pointer parent = NULL;
                pointer grand = NULL;

                if (node)
                    parent = node->parent;
                if (parent)
                    grand = parent->parent;
                while (parent && grand && parent->color == Red)
                {
                    if (parent == grand->left)
                    {
                        tmp = grand->right;
                        if (tmp && tmp->color == Red)
                        {
                            parent->color = Black;
                            tmp->color = Black;
                            grand->color = Red;
                            node = grand;
                        }
                        else if (!tmp || tmp->color == Black)
                        {
                            if (node == parent->right)
                            {
                                node = parent;
                                leftRotate(node);
                            }
                            else
                            {
                                parent->color = Black;
                                grand->color = Red;
                                rightRotate(grand);
                            }
                            
                        }    
                    }
                    else
                    {
                        tmp = grand->left;
                        if (tmp && tmp->color == Red)
                        {
                            parent->color = Black;
                            tmp->color = Black;
                            grand->color = Red;
                            node = grand;
                        }
                        else if (!tmp || tmp->color == Black)
                        {
                            if (node == parent->left)
                            {
                                node = parent;
                                rightRotate(node);
                            }
                            else
                            {
                                parent->color = Black;
                                grand->color = Red;
                                leftRotate(grand);
                            }
                        }
                    }
                    if (node)
                        parent = node->parent;
                    else
                        parent = NULL;
                    if (parent)
                        grand = parent->parent;
                    else
                        grand = NULL;
                }
                this->_root->color = Black;
            };

            bool insert(pointer node)
            {
                if (!this->_root)
                    this->_root = node;
                else
                {
                    pointer tmp = this->_root;
                    while (tmp)
                    {
                        if (!this->_comparator(tmp->pair, node->pair) && !this->_comparator(node->pair, tmp->pair))
                        {
                            if (tmp != node)
                                destroyNode(node);
                            return false;
                        }
                        else if (this->_comparator(node->pair, tmp->pair))
                        {
                            if (tmp->left)
                                tmp = tmp->left;
                            else
                            {
                                tmp->left = node;
                                node->parent = tmp;
                                break;
                            }
                        }
                        else
                        {
                            if (tmp->right)
                                tmp = tmp->right;
                            else
                            {
                                tmp->right = node;
                                node->parent = tmp;
                                break;
                            }
                        }
                    }
                }
                node->color = Red;
                insertBalance(node);
                return true;
            };

            void clear(pointer node)
            {
                if (!node)
                    return ;
                clear(node->left);
                node->left = NULL;
                clear(node->right);
                node->right = NULL;
                if (node->parent && node == node->parent->left)
                    node->parent->left = NULL;
                else if (node->parent && node == node->parent->right)
                    node->parent->right = NULL;
                destroyNode(node);
            };

            void makeRootNull()
            {
                this->_root = NULL;
            }

            void transplant(pointer u, pointer v)
            {
                if (u && !u->parent)
                    this->_root = v;
                else if (u && u->parent && u == u->parent->left)
                    u->parent->left = v;
                else if (u && u->parent && u == u->parent->right)
                    u->parent->right = v;
                if (!v)
                    return ;
                v->parent = u->parent;
            };

            void deleteBalance(pointer node, bool *flag)
            {
                pointer tmp = NULL;
                pointer x = node;
                while (node != this->_root && node->color == Black)
                {
                    if (node == node->parent->left)
                    {
                        tmp = node->parent->right;
                        if (tmp && tmp->color == Red)
                        {
                            
                            tmp->color = Black;
                            node->parent->color = Red;
                            leftRotate(node->parent);
                            tmp = node->parent->right;
                        }
                        if ((!tmp->left || tmp->left->color == Black) && (!tmp->right || tmp->right->color == Black))
                        {
                            tmp->color = Red;
                            
                            x = node;
                            node = node->parent;
                            
                            if (*flag)
                            {
                                if (x == node->right)
                                    node->right = NULL;
                                else if (x == node->left)
                                    node->left = NULL;
                                destroyNode(x);
                                *flag = false;
                            }
                        }
                        else
                        {
                            if (!tmp->right || tmp->right->color == Black)
                            {
                                tmp->left->color = Black;
                                tmp->color = Red;
                                rightRotate(tmp);
                                tmp = node->parent->right;
                                x = node;
                                if (*flag)
                                {
                                    if (x == node->parent->right)
                                        node->parent->right = NULL;
                                    else if (x == node->parent->left)
                                        node->parent->left = NULL;
                                    destroyNode(x);
                                    *flag = false;
                                }
                            }
                            tmp->color = node->parent->color;
                            node->parent->color = Black;
                            tmp->right->color = Black;
                            leftRotate(node->parent);
                            node = this->_root;
                        }
                    }
                    else
                    {
                        tmp = node->parent->left;
                        if (tmp && tmp->color == Red)
                        {
                            tmp->color = Black;
                            node->parent->color = Red;
                            rightRotate(node->parent);
                            tmp = node->parent->left;
                        }
                        if ((!tmp->right || tmp->right->color == Black)
                            && (!tmp->left || tmp->left->color == Black))
                        {
                            tmp->color = Red;
                            x = node;
                            node = node->parent;

                            if (*flag)
                            {
                                if (x == node->right)
                                    node->right = NULL;
                                else if (x == node->left)
                                    node->left = NULL;
                                destroyNode(x);
                                *flag = false;
                            }
                        }
                        else
                        {
                            if (!tmp->left || tmp->left->color == Black)
                            {
                                tmp->right->color = Black;
                                tmp->color = Red;
                                leftRotate(tmp);
                                tmp = node->parent->left;

                                x = node;
                                if (*flag)
                                {
                                    if (x == node->parent->right)
                                        node->parent->right = NULL;
                                    else if (x == node->parent->left)
                                        node->parent->left = NULL;
                                    destroyNode(x);
                                    *flag = false;
                                }
                            }
                            tmp->color = node->parent->color;
                            node->parent->color = Black;
                            tmp->left->color = Black;
                            rightRotate(node->parent);
                            node = this->_root;
                            
                        }
                    }
                }
                node->color = Black;
            };

            bool deleteNode(pointer node)
            {
                
                bool flag = false;
                if (!node)
                    return false;
                pointer tmp = node;
                pointer x = NULL;
                int tmpTrueColor = tmp->color;        

                if (!node->left)
                {
                    x = node->right;
                    if (!x)                             
                    {
                        x = createNullNode();
                        flag = true;
                    }
                    transplant(node, x);                                                         
                }
                else if (!node->right)
                {
                    x = node->left;
                    if (!x)                             
                    {
                        x = createNullNode();
                        flag = true;
                    }
                    transplant(node, x);                    
                }
                else
                {
                    tmp = min(node->right);

                    tmpTrueColor = tmp->color;
                    x = tmp->right;

                    if (!x)
                    {
                        x = createNullNode();
                        flag = true;
                    }
                    if (tmp->parent == node) 
                        x->parent = tmp;
                    else
                    {
                        transplant(tmp, tmp->right);
                        tmp->right = node->right;
                        tmp->right->parent = tmp;
                    }
                    transplant(node, tmp);
                    tmp->left = node->left;
                    tmp->left->parent = tmp;
                    tmp->color = node->color;
                }
                if (tmpTrueColor == Black)
                    deleteBalance(x, &flag);
                if (flag)
                {
                    
                    if (x == this->_root)
                        this->_root = NULL;
                    else if (node->parent && x == node->parent->right)
                        node->parent->right = NULL;
                    else if (node->parent && x == node->parent->left)
                        node->parent->left = NULL;
                    destroyNode(x);
                }
                destroyNode(node);
                return true;
            };

        pointer lower(pointer node, Pair const & pair) const
        {
            pointer tmp = NULL;
            while (node)
            {
                if (this->_comparator(node->pair, pair))
                    node = node->right;
                else
                {
                    
                    if (node->left)
                    {
                        tmp = lower(node->left, pair);
                        if (tmp)
                            node = tmp;
                        break ;
                    }
                    else
                        break ;
                }
            }
            return node;
        }

        pointer upper(pointer node, Pair const & pair) const
        {
            pointer tmp = NULL;
            while (node)
            {
                if (!this->_comparator(pair, node->pair))
                    node = node->right;
                else
                {
                    
                    if (node->left)
                    {
                        tmp = upper(node->left, pair);
                        if (tmp)
                            node = tmp;
                        break ;
                    }
                    else
                        break ;
                }
            }
            return node;
        }

    };
}


#endif