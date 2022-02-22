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
    void Update(float timeDelta) override;



private:

};


#endif //MAIN_CPP_TORCH_H
