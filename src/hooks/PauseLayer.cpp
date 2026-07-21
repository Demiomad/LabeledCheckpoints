#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class $modify(PauseLayer) {
    void customSetup() {    
        PauseLayer::customSetup();

        auto settingsSprite = CircleButtonSprite::createWithSprite(
            "labeledCheckpoint.png"_spr,
            0.85f,
            CircleBaseColor::Green,
            CircleBaseSize::Medium
        );

        auto settingsButton = CCMenuItemExt::createSpriteExtra(
            settingsSprite,
            [this](CCMenuItemSpriteExtra*) {
                geode::openSettingsPopup(Mod::get(), false);
            }
        );

        settingsButton->setID("settings-button"_spr);

        auto menu = this->getChildByID("left-button-menu");
        menu->addChild(settingsButton);
        menu->updateLayout();
    }
    
    void onModSettings(CCObject*) {
        openSettingsPopup(Mod::get(), false);
    }
};