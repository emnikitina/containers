#include <iostream>

#include <map>
#include <stack>
#include <vector>
#include <list>
#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "ft_iterator.hpp"
#include "ft_map_iterator.hpp"
#include "ft_reverse_iterator.hpp"

#include <stdlib.h>
#include <string>
#include <sys/time.h>

template <typename T>
void print_vector(std::vector<T> vect)
{
    std::cout << "printing vector\n";
    for (size_t i = 0; i < vect.size(); i++)
        std::cout << i << " : |" << vect[i] << "| ";
    std::cout << std::endl;
};

int main()
{
    std::cout << "MAIN TESTING STD CONTAINERS\n"; 

    std::cout << "\n----------TESTING VECTORS----------\n";
    std::cout << "CREATING VECTORS\n";
    std::vector<int> my_vect1;

    std::cout << "capacity: " << my_vect1.capacity() << std::endl;
    std::cout << "    size: " << my_vect1.size() << std::endl;

    my_vect1.push_back(17);
    my_vect1.push_back(13);
    for (int i = 0; i < 8; i++)
        my_vect1.push_back(i);    

    print_vector(my_vect1);
    std::cout << "capacity after fill vector: " << my_vect1.capacity() << std::endl;
    std::cout << "    size after fill vector: " << my_vect1.size() << std::endl;

    std::cout << "\nTEST POP BACK\n";
    std::cout << "After pop back:\n";
    my_vect1.pop_back();
    print_vector(my_vect1);

    std::cout << "First element: " << my_vect1.front() << std::endl;
    std::cout << "Last element: " << my_vect1.back() << std::endl;
    std::cout << "Data: " << my_vect1.data() << std::endl;
    if (my_vect1.empty())
        std::cout << "Vector is empty\n";
    else
        std::cout << "Vector is not empty\n";
    std::cout << "Max size: " << my_vect1.max_size() << std::endl;

    std::cout << "\nTEST REVERSE AND RESIZE\n";
    std::cout << "Reserve to 10\n";
    my_vect1.reserve(10);
    std::cout << "now capacity: " << my_vect1.capacity() << std::endl;
    std::cout << "    now size: " << my_vect1.size() << std::endl;

    std::cout << "Resize to 12\n";
    my_vect1.resize(12);
    std::cout << "now capacity: " << my_vect1.capacity() << std::endl;
    std::cout << "    now size: " << my_vect1.size() << std::endl;
    print_vector(my_vect1);

    std::cout << "Reize to 7\n";
    my_vect1.resize(7);
    std::cout << "now capacity: " << my_vect1.capacity() << std::endl;
    std::cout << "    now size: " << my_vect1.size() << std::endl;
    print_vector(my_vect1);


    std::cout << "\nTEST AT\n";
    std::cout << "the 4th element is: " << my_vect1.at(4) << std::endl;

    std::cout << "\nTEST ERASE\n";
    std::cout << "test erase, one element\nvector: \n";
    print_vector(my_vect1);
    my_vect1.erase(my_vect1.begin() + 3);
    std::cout << "vector after delete 3rd element: \n";
    print_vector(my_vect1);

    std::cout << "test erase, range\nvector: \n";
    print_vector(my_vect1);
    my_vect1.erase(my_vect1.begin(), my_vect1.begin() + 2);
    std::cout << "vector after delete 3rd element: \n";
    print_vector(my_vect1);


    //iterators
    std::vector<int>::iterator it = my_vect1.begin();
    std::vector<int>::iterator ite = my_vect1.end();

    std::cout << "\nTEST ITERATORS\n";
    while (it != ite)
    {
        std::cout << *it << std::endl;
        it++;
    }

    //copy constructor and = operator
    std::vector<int> copy(my_vect1);
    std::vector<int> vect_copy = my_vect1;

    std::cout << "\nTEST COPY CONSTUCTOR AND ASSING OPERATOR\n";
    std::cout << "Vector1 creted by copy constructor:\n";
    print_vector(copy);
    std::cout << "Vector2 creted by overloaded assignment operator:\n";
    print_vector(vect_copy);

    
    std::cout << "\nTEST INSERT\n";
    std::cout << "Insert vector1\n";
    my_vect1.insert(my_vect1.begin() + 2, 40);
    print_vector(my_vect1);

    std::cout << "Insert vector2\n";
    vect_copy.insert(vect_copy.begin(), 5, 77);
    print_vector(vect_copy);

    std::cout << "Insert vector3\n";
    my_vect1.insert(my_vect1.begin(), vect_copy.begin() + 1, vect_copy.begin() + 4);
    print_vector(my_vect1);

    std::cout << "\nTEST ASSIGN\n";
    std::cout << "assign value\n";
    copy.assign(5, 20);
    print_vector(copy);

    std::cout << "assign range\n";
    copy.assign(my_vect1.begin(), my_vect1.begin() + 3);
    print_vector(copy);


    std::cout << "\nTEST SWAP\n";
    std::cout << "Swap vectors\nvect1:\n";
    print_vector(copy);
    std::cout << "vect2:\n";
    print_vector(vect_copy);
    std::cout << "swap\n";
    copy.swap(vect_copy);
    std::cout << "Now vect1:\n";
    print_vector(copy);
    std::cout << "Now vect2:\n";
    print_vector(vect_copy);

    // relationship

    std::cout << "\nTEST RELATIONSHIP\n";
    std::cout << "equal:\n";
    if (copy == vect_copy)
        std::cout << "vectors are equal\n";
    else
        std::cout << "vectors are not equal\n";
    
    std::cout << "not equal:\n";
    if (copy != my_vect1)
        std::cout << "vectors are not equal\n";
    else
        std::cout << "vectors are equal\n";

    std::cout << "less:\n";
    if (copy < my_vect1)
        std::cout << "vectors are less\n";
    else
        std::cout << "vectors are not less\n";

    std::cout << "less or equal:\n";
    if (copy <= my_vect1)
        std::cout << "vectors are less or equal\n";
    else
        std::cout << "vectors are not less or equal\n";

    std::cout << "more:\n";
    if (copy > my_vect1)
        std::cout << "vectors are more\n";
    else
        std::cout << "vectors are not more\n";

    std::cout << "more or equal:\n";
    if (copy > my_vect1)
        std::cout << "vectors are more or equal\n";
    else
        std::cout << "vectors are not more or equal\n";


    std::cout << "\nCLEAR\n";
    my_vect1.clear();
    std::cout << "now capacity: " << my_vect1.capacity() << std::endl;
    std::cout << "    now size: " << my_vect1.size() << std::endl;

    std::cout << "\nCRETING VECTORS WITH DIFFERENT TYPE\n";
    std::vector<std::string> str_vect;
    str_vect.push_back("hello");
    str_vect.push_back("it");
    str_vect.push_back("is");
    str_vect.push_back("vector");
    print_vector(str_vect);

    std::cout << "\n--------END TESTING VECTORS--------\n";

    std::cout << "\n----------TESTING STACK----------\n";

    std::cout << "Creating stack and fill it by push\n";
    std::stack<int> my_stack;
    for (size_t i = 10; i < 15; i++)
        my_stack.push(i);
    
    std::cout << "\nsize: ";
    std::cout << my_stack.size() << std::endl;
    if (my_stack.empty())
        std::cout << "Stack is empty\n";
    else
        std::cout << "Stack is not empty\n";

    std::cout << "\ntest top and pop\n";
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << "top: " << my_stack.top() << std::endl;
        my_stack.pop();
    }

    std::cout << "\nrelationship\n";
    std::stack<int> copy_stack;
    for (size_t i = 0; i < 5; i++)
        copy_stack.push(i);
    std::cout << "equal:\n";
    if (my_stack == copy_stack)
        std::cout << "stack are equal\n";
    if (my_stack != copy_stack)
        std::cout << "stack are not equal\n";
    if (my_stack < copy_stack)
        std::cout << "less\n";
    else
        std::cout << "not less\n";
    if (my_stack <= copy_stack)
        std::cout << "less or equal\n";
    else
        std::cout << "not less or less\n";
    if (my_stack > copy_stack)
        std::cout << "more\n";
    else
        std::cout << "not more\n";
    if (my_stack >= copy_stack)
        std::cout << "more or equal\n";
    else
        std::cout << "not more or equal\n";

    std::cout << "\n--------END TESTING STACK--------\n";

    std::cout << "\n----------TESTING MAP----------\n";
    std::map<int, int> my_map;
    if (my_map.empty())
        std::cout << "Stack is empty\n";
    else
        std::cout << "Stack is not empty\n";
    
    std::cout << "\nTEST INSERT\n";
    my_map.insert(std::make_pair(7, 7));
    my_map.insert(std::make_pair(9, 9));
    for (size_t i = 0; i < 5; i++)
        my_map.insert(std::make_pair(1 + i, 11 + i));
    std::cout << "size: " << my_map.size() << std::endl;
    
    std::cout << "\nTEST FIND\n";
    std::cout << "find: [" << my_map.find(3)->first << "; " << my_map.find(3)->second << "]\n";

    std::map<int, int>::iterator mit = my_map.begin();
    std::map<int, int>::iterator mite = my_map.end();
    std::cout << "\nprint map\n";
    for (; mit != mite; mit++)
        std::cout << "[" << mit->first << "; " << mit->second << "]\n";

    std::cout << "\nTEST COPY\n";
    std::map<int, int> copy_map(my_map);
    std::cout << "print map copy\n";
    for (size_t i = 0; i < copy_map.size(); i++)
        std::cout << "[" << copy_map[i] << "]\n";

    std::cout << "\nTEST ERASE\n";
    my_map.erase(7);
    std::map<int, int>::iterator m = my_map.begin();
    std::map<int, int>::iterator me = my_map.end();
    std::cout << "\nprint map\n";
    for (; m != me; m++)
        std::cout << "[" << m->first << "; " << m->second << "]\n";

    std::cout << "\n--------END TESTING MAP--------\n";

    return 0;
}