#include "Component/MapGenerator.hpp"

MapGenerator::MapGenerator()
{
	srand(time(NULL));
	GenerateMap(4);
}

MapGenerator::MapGenerator(int squares, int doors, bool glass_doors)
{
	srand(time(NULL));
	GenerateMap(squares);
}

void MapGenerator::GenerateMap(int n)
{
	MapElement element(glm::vec2(0, 0));
	map.insert(std::pair<glm::vec2, MapElement>(element.Position, element));
	for (int i = 0; i < n-1; i++)
	{
		glm::vec2 pos = map[map.rbegin()->first].Position;
		float move_first, move_second;
		move_first = GetDirection();
		move_second = GetDirection(move_first == 0);
		MapElement element(pos + glm::vec2(move_first, move_second));
		map.insert(std::pair<glm::vec2, MapElement>(element.Position, element));
	}
}

float MapGenerator::GetDirection(bool canBeZero = true)
{
	float result = 0;
	while(result != 0 || !canBeZero)
		result = (float)(rand() % 2 + (-1));
	return result;
}

void MapGenerator::CheckFroWallsNDoors()
{
	for (std::map<glm::vec2, MapElement>::iterator it = map.begin(); it != map.end(); ++it)
	{
		std::vector<glm::vec2> neighbours = it->second.GetNeighbours();
		for (std::vector<glm::vec2>::iterator neighbour = neighbours.begin(); neighbour != neighbours.end(); neighbour++)
		{
			if (map.find(*neighbour) == map.end())
				it->second.SetWall(it->second.Position - *neighbour);
			else
				it->second.SetDoor(it->second.Position - *neighbour);
		}
	}
}
