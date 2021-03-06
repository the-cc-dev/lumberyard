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

#pragma once

// include required files
#include "StandardHeaders.h"
#include "MultiThreadManager.h"


namespace MCore
{
    /**
     * The reference counter class.
     */
    class MCORE_API MemoryObject
    {
    public:
        /**
         * The constructor.
         * Sets the initial reference count to 1.
         */
        MemoryObject();

        /**
         * The destructor.
         */
        virtual ~MemoryObject();

        /**
         * Increase the reference count by one.
         */
        void IncreaseReferenceCount();

        /**
         * Decrease the reference count.
         * The Destroy method already calls this.
         */
        void DecreaseReferenceCount();

        /**
         * Destroy the object, like you would delete it.
         * This internally decreases the reference count. It will only really delete once the reference count reaches zero.
         */
        void Destroy();

        /**
         * Get the current reference count on this object.
         * @return The reference count, which indicates how many objects reference this one.
         */
        uint32 GetReferenceCount() const;

    protected:
        virtual void Delete();

    private:
        AtomicUInt32    mReferenceCount;
    };



    /**
     * A little helper to destroy a given memory object.
     * Internally this just checks if the object is nullptr or not, and only calls Destroy on the object if it is not nullptr.
     * This does NOT set the object to nullptr afterwards!
     * @param object The object to be destroyed.
     */
    MCORE_API void Destroy(MemoryObject* object);
}   // namespace MCore
