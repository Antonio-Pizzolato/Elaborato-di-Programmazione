#ifndef MAIN_CPP_ITEMS_H
#define MAIN_CPP_ITEMS_H


#include <sstream>
#include <fstream>
#include "Object.h"

class Items : public Object
{
public:
    /**
     * Default constructor.
     */
    Items();

    /**
     * Gets the item type.
     * @return The item type.
     */
    ITEM GetType() const;

protected:

public:

    /**
     * The type of item.
     */
    ITEM m_type;
};


#endif //MAIN_CPP_ITEMS_H
