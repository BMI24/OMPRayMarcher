#ifndef OMPRM_UNION_OF_OBJECTS_H
#define OMPRM_UNION_OF_OBJECTS_H

#include "object_interface.hpp"

class union_of_objects : public object_interface {
private:
    object_interface *object_one, *object_two;
    uint8_t color_r, color_g, color_b;

public:
    float distance_to_surface(float x2, float y2, float z2) override;

    uint8_t get_color_r() override;

    uint8_t get_color_g() override;

    uint8_t get_color_b() override;

    union_of_objects(object_interface *object_one, object_interface *object_two);

};


#endif //OMPRM_UNION_OF_OBJECTS_H
