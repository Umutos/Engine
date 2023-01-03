#include <ResourcesManager.h>
#include <stdio.h>

namespace Resources
{
    void ResourcesManager::DeleteResource(const std::string& name)
    {
        if (remove(name.c_str()) != 0)
        {
            perror("Error deleting file");
        }
        else
        {
            puts("File successfully deleted");
        }
    }
}
