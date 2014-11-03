#include <utils/Waypoint.h>

void Waypoint::draw(sf::RenderWindow& game_window) {
  sf::CircleShape waypoint;
  waypoint.setRadius(5);
  waypoint.setOrigin(2.5, 2.5);
  waypoint.setOutlineColor(sf::Color::Red);
  waypoint.setFillColor(sf::Color::Transparent);
  waypoint.setOutlineThickness(3);
  waypoint.setPosition(position);
  game_window.draw(waypoint);

  sf::Vertex line[2];
  if (next_waypoint) {
    line[0] = sf::Vertex(position, sf::Color::Red);
    line[1] = sf::Vertex(next_waypoint->position, sf::Color::Red);
    game_window.draw(line, 2, sf::Lines);
  }
}