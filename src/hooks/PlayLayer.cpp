#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    CheckpointObject* createCheckpoint() {
        CheckpointObject* checkpoint = PlayLayer::createCheckpoint();

        if (m_isPlatformer) // platformer mode wont and will never work properly
            return checkpoint;

        auto percent = this->getCurrentPercent();
        auto percentString = fmt::format("{:.0f}%", floor(percent));

        auto percentLabel = CCLabelBMFont::create(percentString.c_str(), "bigFont.fnt");
        auto physicalCheckpointObj = checkpoint->m_physicalCheckpointObject;
        auto contentSize = physicalCheckpointObj->getContentSize();

        percentLabel->setScale(0.5f);
        percentLabel->setAnchorPoint({ 0.5f, 0.5f });
        percentLabel->setPosition(contentSize / 2);
        percentLabel->setID("checkpoint-label"_spr);

        physicalCheckpointObj->m_addToNodeContainer = true;
        physicalCheckpointObj->addChild(percentLabel);
        
        return checkpoint;
    }
};