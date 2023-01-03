#pragma once
#include <filesystem>
#include <map>
#include <IResources.h>

namespace Resources
{
    class ResourcesManager
    {
    private:
        std::map<std::string, IResources*> myResources;

    public:
        ResourcesManager() {}
        virtual ~ResourcesManager() {}

        template <typename T>
        T* CreateResource(const std::string& name, const std::string& path)
        {
            T* resource = new T();
            resource->setIResourcePath(path);
            resource->setIResourceId(myResources.size());
            resource->loadOBJ(path);

            myResources.insert(std::pair<std::string, IResources*>(name, resource));

            return resource;
        }

        template <typename T>
        T* GetResource(const std::string& name)
        {
            return dynamic_cast<T*>(myResources.find(name)->second);
        }

        void DeleteResource(const std::string& name);

        static ResourcesManager& getInstance();
        static ResourcesManager* getInstancePtr();


    };
}