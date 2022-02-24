#ifndef MAIN_CPP_ITEMS_H
#define MAIN_CPP_ITEMS_H

#include <sstream>
#include <fstream>
#include "Object.h"

class Items : public Object {
private:
    ITEM type;
    int goldValue;
    int hpPotionValue;
public:
    /**
     * Default constructor.
     */
    explicit Items(ITEM itemType);

    /**
     * Gets the item type.
     * @return The item type.
     */
    ITEM GetType() const;
    int GetValue() const;
    void Update(float _timeDelta) override;
};

#endif //MAIN_CPP_ITEMS_H
