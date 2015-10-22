#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <vector>

#include "Interface.h"
#include "Options.h"
#include "Vector2.h"
#include "Sprite.h"
#include "Character.h"
#include "Button.h"

class UserInterface{
    public:
        UserInterface(Interface* Inter);
        ~UserInterface();

        void ToggleOptions();
        void ToggleInventory();
        void ToggleAllUI();
        std::vector<Sprite*> GetUISprites();
        void Update(Character Actor);

    protected:
        Options Option;

        bool InventoryOpen;
        Vector2 InventoryPosition;
        Sprite* InventoryOverlay;
        //std::vector<Sprite*> InventoryRenders;

        bool OptionsOpen;
        Vector2 OptionsPosition;
        Sprite* OptionsOverlay;

        bool SpellListOpen;
        Vector2 SpellListPosition;
        Sprite* SpellsOverlay;

        bool HealthBool, ManaBool;
        Vector2 HealthSize, ManaSize;
        Sprite* HealthSprite;
        Sprite* ManaSprite;
        Sprite* HealthBar;
        Sprite* ManaBar;
};

#endif // USERINTERFACE_H
