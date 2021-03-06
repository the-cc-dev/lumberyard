/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#if defined(EMOTIONFXANIMATION_EDITOR)
#include <AzCore/Serialization/SerializeContext.h>
#include <MCore/Source/MCoreSystem.h>
#include <Integration/System/PipelineComponent.h>
#include <EMotionFX/Source/EMotionFXManager.h>
#include <EMotionFX/CommandSystem/Source/CommandManager.h>


namespace EMotionFX
{
    namespace Pipeline
    {
        PipelineComponent::PipelineComponent()
            : m_EMotionFXInited(false)
        {

        }

        void PipelineComponent::Activate()
        {
            if (!m_EMotionFXInited)
            {
                MCore::Initializer::InitSettings coreSettings;
                coreSettings.mNumThreads = 0;

                if (!MCore::Initializer::Init(&coreSettings))
                {
                    AZ_Error("EMotionFX", false, "Failed to initialize EMotion FX SDK Core");
                    return;
                }

                // Initialize EMotion FX runtime.
                EMotionFX::Initializer::InitSettings emfxSettings;
                emfxSettings.mUnitType = MCore::Distance::UNITTYPE_METERS;

                if (!EMotionFX::Initializer::Init(&emfxSettings))
                {
                    AZ_Error("EMotionFX", false, "Failed to initialize EMotion FX SDK Runtime");
                    return;
                }

                // Initialize the EMotionFX command system.
                m_commandManager = AZStd::make_unique<CommandSystem::CommandManager>();
                m_EMotionFXInited = true;
            }
        }

        void PipelineComponent::Deactivate()
        {
            if (m_EMotionFXInited)
            {
                m_EMotionFXInited = false;
                m_commandManager.reset();
                EMotionFX::Initializer::Shutdown();
                MCore::Initializer::Shutdown();
            }
        }

        void PipelineComponent::Reflect(AZ::ReflectContext* context)
        {
            AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
            if (serializeContext)
            {
                serializeContext->Class<PipelineComponent>()->Version(1);
            }
        }
    } // Pipeline
} // EMotionFX
#endif