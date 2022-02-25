#include "Achievements.h"

Achievements::Achievements(Observable *conditionAchievement) : conditionAchievement(conditionAchievement), killNumber(0), gold(0), lifetime(600), kill(false), gainGold(false), CanDraw(false) {
    conditionAchievement->addObserver(this);
    sprite.setPosition(800, 0);
}

void Achievements::update(float _killNumber, float _gold) {
    killNumber = _killNumber;
    gold = _gold;
    if (killNumber == 3) {
        unlockAchievement(Event::Kill);
    }
    if (gold >= 10) {
        unlockAchievement(Event::Gold);
    }
}

void Achievements::render(sf::RenderWindow &window) {
    if (CanDraw) {
        window.draw(sprite);
    }
}

void Achievements::updateLifetime(float dt) {
    if (lifetime > 0.f) {
        //Update the lifetime
        lifetime -= 100.f * dt;
    }
    if (isExpired()) {
        CanDraw = false;
        lifetime = 600.f;
    }
}

Achievements::~Achievements() {
    conditionAchievement->removeObserver(this);
}

void Achievements::unlockAchievement(Event event) {
    switch (event) {
        case Event::Kill: {
            if (!kill) {
                texture.loadFromFile("Resources/killAchievement.png");
                sprite.setTexture(texture);
                CanDraw = true;
                kill = true;
            }
        }
            break;
        case Event::Gold: {
            if (!gainGold) {
                gainGold = true;
                texture.loadFromFile("Resources/goldAchiev.png");
                sprite.setTexture(texture);
                CanDraw = true;
            }
        }
    }
}

bool Achievements::getKill() const {
    return kill;
}

bool Achievements::getGainGold() const {
    return gainGold;
}

bool Achievements::isExpired() const {
    return lifetime <= 0.f;
}

bool Achievements::getExpired() const {
    return CanDraw;
}





