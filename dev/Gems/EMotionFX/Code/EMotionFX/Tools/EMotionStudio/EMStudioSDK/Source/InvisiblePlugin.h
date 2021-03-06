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

#ifndef __EMSTUDIO_INVISIBLEPLUGIN_H
#define __EMSTUDIO_INVISIBLEPLUGIN_H

// include MCore
#include <MCore/Source/StandardHeaders.h>
#include <MCore/Source/UnicodeString.h>
#include "EMStudioConfig.h"
#include "EMStudioPlugin.h"


namespace EMStudio
{
    /**
     *
     *
     */
    class EMSTUDIO_API InvisiblePlugin
        : public EMStudioPlugin
    {
        MCORE_MEMORYOBJECTCATEGORY(InvisiblePlugin, MCore::MCORE_DEFAULT_ALIGNMENT, MEMCATEGORY_EMSTUDIOSDK)
    public:
        InvisiblePlugin();
        virtual ~InvisiblePlugin();

        EMStudioPlugin::EPluginType GetPluginType() const override              { return EMStudioPlugin::PLUGINTYPE_INVISIBLE; }

        bool Init() override { return true; }   // for this type of plugin, perform the init inside the constructor
        virtual bool GetHasWindowWithObjectName(const MCore::String& objectName) override { MCORE_UNUSED(objectName); return false; }
        virtual QString GetObjectName() const override                          { return objectName(); }
        virtual void SetObjectName(const QString& objectName) override          { setObjectName(objectName); }
        virtual void CreateBaseInterface(const char* objectName) override       { MCORE_UNUSED(objectName); }
    };
}   // namespace EMStudio

#endif
