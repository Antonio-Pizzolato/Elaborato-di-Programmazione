#include "Torch.h"
// Default constructor.
Torch::Torch()
{
    // Set sprite.
    int textureID = TextureManager::AddTexture("Resources/spr_torch.png");
    SetSprite(TextureManager::GetTexture(textureID), false, 5, 12);
}

// Update the brightness of the torch.
void Torch::Update(float timeDelta)
{

}

