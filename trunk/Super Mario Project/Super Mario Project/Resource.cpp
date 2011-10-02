////////////////////////////////////////////////////////////////////////
// Resource.cpp
// Super Mario Project
// Copyright (C) 2011  
// Lionel Joseph lionel.r.joseph@gmail.com
// Olivier Guittonneau openmengine@gmail.com
////////////////////////////////////////////////////////////////////////

#include "Resource.hpp"
#include "ResourceManager.hpp"

namespace SuperMarioProject
{
    Resource::Resource(std::string name)
        : _name(name),
        _refCount(0)
    {
    }


    Resource::~Resource()
    {
    }

    const std::string &Resource::name() const
    {
        return _name;
    }

     void Resource::addRef()
     {
         _refCount++;
     }
       
     
     void Resource::release()
     {
         _refCount--;

         if(_refCount == 0)
             ResourceManager::remove(this);
     }
} // namespace