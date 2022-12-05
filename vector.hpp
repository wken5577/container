#ifndef vector
#define vector

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
    private:
        T                                       value_type;
        Allocator                               allocator_type;
        std::sizet                              size_type;
        std::ptrdiff_t                          difference_type;
        value_type&                             reference;
        const value_type&                       const_reference;
        Allocator::pointer                      pointer;
        Allocator::const_pointer                const_pointer;
        value_type::iterator                    iterator;
        const value_type::iterator              const_iterator;
        std::reverse_iterator<iterator>         reverse_iterator;
        std::reverse_iterator<const_iterator>   const_reverse_iterator;

        
        public:
            vector()
            :size_type(0), difference_type(0), reference(0), const_reference(0),\
             pointer(0), const_pointer(0), iterator(0), const_iterator(0), reverse_iterator(0), const_reverse_iterator(0)
            {
                allocator_type = Allocator<value_type>();
            }
            
            explicit vector(const Allocator& alloc)
            :size_type(0), difference_type(0), reference(0), const_reference(0),\
             pointer(0), const_pointer(0), iterator(0), const_iterator(0), reverse_iterator(0), const_reverse_iterator(0)
            {
                allocator_type = alloc;
            }

            vector(size_type count, const T& value, const Allocator& alloc = Allocator())
            {
                allocator_type = alloc;
                size_type = count;
                difference_type = count;
                reference = value;
                const_reference = value;
                pointer = allocator_type.allocate(count);
                const_pointer = pointer;
                iterator = pointer;
                const_iterator = pointer;
                reverse_iterator = std::reverse_iterator<iterator>(pointer);
                const_reverse_iterator = std::reverse_iterator<const_iterator>(pointer);
            }
       
            template <class InputIt>
            vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
            vector(const vector& other);
            vector(const vector& other, const Allocator& alloc);
            vector(vector&& other);
            vector(vector&& other, const Allocator& alloc);
            vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());

            ~vector();
    };
}

#endif