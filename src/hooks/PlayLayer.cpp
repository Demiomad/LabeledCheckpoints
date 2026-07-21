#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    std::string getCustomFntFile() {
        auto mod = Mod::get();
        auto customFontEnabled = mod->getSettingValue<bool>("use-custom-font");
        if (!customFontEnabled)
            return "bigFont.fnt";
        
        auto customFont = mod->getSettingValue<std::filesystem::path>("font-file");
        return string::pathToString(customFont);
    }

    std::string getFntFileFromIndex(int index) {
        switch (index) {
            case -3: {
                return "bigFont.fnt";
            }

            case -2: {
                return "goldFont.fnt";
            }

            case -1: {
                return "chatFont.fnt";
            }

            case 0: {
                auto fntFile = this->m_attemptLabel->getFntFile();
                return fntFile;
            }

            default: {
                auto fntName = fmt::format("gjFont{:02d}.fnt", index);
                return fntName;
            }
        }
    }
    
    CheckpointObject* createCheckpoint() {
        CheckpointObject* checkpoint = PlayLayer::createCheckpoint();

        if (m_isPlatformer) // platformer mode wont and will never work properly
            return checkpoint;

        auto mod = Mod::get();
        auto customFontEnabled = mod->getSettingValue<bool>("use-custom-font");
        auto precision = mod->getSettingValue<int>("percentage-precision");
        auto scale = mod->getSettingValue<float>("label-size");
        auto opacity = mod->getSettingValue<float>("label-opacity");
        auto fontIndex = mod->getSettingValue<int>("label-font");
        auto color = mod->getSettingValue<ccColor3B>("label-color");

        auto percent = this->getCurrentPercent();
        auto percentString = fmt::format("{:.{}f}%", percent, precision);

        std::string font = customFontEnabled ? getCustomFntFile() : getFntFileFromIndex(fontIndex);
        log::debug("Font file: {}", font);

        auto percentLabel = CCLabelBMFont::create(percentString.c_str(), font.c_str());
        auto physicalCheckpointObj = checkpoint->m_physicalCheckpointObject;
        auto contentSize = physicalCheckpointObj->getContentSize();

        percentLabel->setColor(color);
        percentLabel->setOpacity(opacity * 255);
        percentLabel->setScale(scale);
        percentLabel->setAnchorPoint({ 0.5f, 0.5f });
        percentLabel->setPosition(contentSize / 2);
        percentLabel->setID("checkpoint-label"_spr);

        physicalCheckpointObj->m_addToNodeContainer = true;
        physicalCheckpointObj->addChild(percentLabel);
        
        return checkpoint;
    }
};