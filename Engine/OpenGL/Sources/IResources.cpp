#include <IResources.h>

namespace Resources
{
	void IResources::setIResourceId(unsigned id)
	{
		ResourceId = id;
	}

	unsigned IResources::getIResourceId() const
	{
		return ResourceId;
	}

	void IResources::setIResourcePath(const std::string& path)
	{
		ResourcePath = path;
	}

	std::string IResources::getIResourcePath() const
	{
		return ResourcePath;
	}
}