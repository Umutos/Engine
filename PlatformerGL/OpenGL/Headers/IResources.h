#pragma once
#include <string>

namespace Resources
{
    class IResources
    {
    protected:
        unsigned ResourceId;
        std::string ResourcePath;

    public:

        virtual void loadOBJ(const std::string& path) = 0;
        virtual void unloadOBJ() = 0;

        void setIResourceId(unsigned id);
        unsigned getIResourceId() const;

        void setIResourcePath(const std::string& path);
        std::string getIResourcePath() const;


    };
}
