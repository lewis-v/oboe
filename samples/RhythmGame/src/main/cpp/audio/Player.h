/*
 * Copyright 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RHYTHMGAME_SOUNDRECORDING_H
#define RHYTHMGAME_SOUNDRECORDING_H

#include <cstdint>
#include <array>

#include <chrono>
#include <memory>
#include <atomic>

#include <android/asset_manager.h>

#include "RenderableAudio.h"
#include "DataSource.h"

class Player : public RenderableAudio{

public:
    /**
     * Construct a new SoundPlayer from the given source data.
     *
     * @param sourceData
     * @param numFrames
     */

    // maybe use shared_ptr
    // Player
    //Player(SoundSource)
    Player(DataSource *source)
        : mSource(source)
        , mChannelCount(source->getChannelCount())
    {};

    /*Player(const int16_t *sourceData, int32_t numFrames)
            : mData(sourceData)
            , mTotalFrames(numFrames)
    {};*/

    void renderAudio(int16_t *targetData, int32_t numFrames);
    void resetPlayHead() { mReadFrameIndex = 0; };
    void setPlaying(bool isPlaying) { mIsPlaying = isPlaying; resetPlayHead(); };
    void setLooping(bool isLooping) { mIsLooping = isLooping; };

private:
    int32_t mReadFrameIndex = 0;
    //const int16_t* mData = nullptr;
    //int32_t mTotalFrames = 0;
    std::atomic<bool> mIsPlaying { false };
    std::atomic<bool> mIsLooping { false };

    DataSource *mSource;
    int32_t mChannelCount;

};

#endif //RHYTHMGAME_SOUNDRECORDING_H