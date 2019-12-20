#include "tilemap.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

bool TileMap::load (const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{

if (!m_tileset.loadFromFile(tileset))
            return false;

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                int tileNumber = tiles[i + j * width];

                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                quad[0].position = sf::Vector2f(i * tileSize.x , j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y  );
                quad[3].position = sf::Vector2f(i * tileSize.x  , (j + 1) * tileSize.y );

                quad[0].texCoords = sf::Vector2f(tu * tileSize.x + tu + 1, tv  * tileSize.y + tv +1);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x + tu + 1, tv * tileSize.y + tv +1);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x + tu + 1, (tv + 1) * tileSize.y + tv +1);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x + tu + 1, (tv + 1) * tileSize.y + tv +1 );
            }

        return true;
}

void TileMap::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
        
    states.texture = &m_tileset;

    target.draw(m_vertices, states);
}
