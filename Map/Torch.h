//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_TORCH_H
#define MAIN_CPP_TORCH_H


#include "Items.h"

class Torch
        : public Object
{
public:

    /**
     * Default Constructor.
     */
    Torch();

    /**
     * Updates the brightness of the torch.
     * @param timeDelta The time that has passed since the last update.
     */
    virtual void Update(float timeDelta) override;

    /**
     * Gets the brightness modifier of the torch. This is used to create flicker.
     * @return The brightness of the torch.
     */
    float GetBrightness();

private:

    /**
     * The brightness modifier of the torch. This is used to denote flicker.
     */
    float m_brightness;
};


#endif //MAIN_CPP_TORCH_H
