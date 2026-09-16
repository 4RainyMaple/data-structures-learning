template<typename Iterator, typename Object>
Iterator find ( Iterator start, Iterator end, const Object & x )
{
    for ( auto itr = start; itr != end; ++itr )
    {
        if ( *itr == x )
            return itr;
    }
    return end;
}
