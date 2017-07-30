#pragma once

//Menadzer zasobow bazujacy na mapach STL, typ enumeracyjny ID tekstury, dzwieku itd.

#include <iostream>
#include <map>

//Template dla menadzera "czegos"
template<typename Enum, typename Resource>
class Resource_Manager
{
public:

	//Zwraca cos
	const Resource& get(Enum name) const
	{
		return m_resources.at(name);
	}


protected:

	//Dodaje jakies cos po wybranej nazwie, filePath to sciezka do zasobu
	void addResource(Enum name, const std::string& filePath)
	{
		Resource res;

		if (!res.loadFromFile(filePath))
		{
			std::cout << "FAILED TO LOAD: " << filePath << " CHECK PATH!" << std::endl;
		}

		//Wrzuc do mapy
		m_resources.insert(std::make_pair(name, res));
	}


private:
	std::map<Enum, Resource> m_resources;

};