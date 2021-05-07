#pragma once
#include <vector>

#include "Object.h"
#include "Ray.h"

// A bit weird to call the world an object, maybe should fix?
class World : public Object
{
public:
	World() = default;
	~World() = default;
	
	void AddObject(std::shared_ptr<Object> object)
	{
		m_objects.push_back(object);
	}
	void Clear()
	{
		m_objects.clear();
	}

	CastResults Intersects(Ray& ray) const override
	{
		CastResults results;
		results.intersects = false;
		results.distance = std::numeric_limits<double>::infinity();

		for (const auto& object : m_objects)
		{
			const CastResults newResults = object->Intersects(ray);
			if (newResults.intersects && newResults.distance < results.distance)
			{
				results = newResults;
			}
		}

		return results;
	}

private:
	std::vector<std::shared_ptr<Object>> m_objects;
};

