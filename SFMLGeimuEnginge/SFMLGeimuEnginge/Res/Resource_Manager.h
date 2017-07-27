#pragma once

#include <iostream>
#include <map>

template<typename Enum, typename Resource>
class Resource_Manager
{
public:
	const Resource& get(Enum name) const
	{
		return m_resources.at(name);
	}


protected:
	void addResource(Enum name, const std::string& fileName)
	{
		Resource res;
		if (!res.loadFromFile(fileName))
		{
			std::cout << "FAILED TO LOAD: " << fileName << " CHECK PATH!" << std::endl;
		}

		m_resources.insert(std::make_pair(name, res));
	}


private:
	std::map<Enum, Resource> m_resources;

};