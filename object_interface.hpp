#ifndef OMPRM_OBJECT_INTERFACE_HPP
#define OMPRM_OBJECT_INTERFACE_HPP

#include <cstdint>

class object_interface{
public:
    virtual float distance_to_surface(float x, float y, float z) = 0;
    virtual uint32_t get_color() = 0;
};

#endif
