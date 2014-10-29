/** @file GameObject.h
 *  @brief File containing the GameObject class.
 *
 *  The purpose of this file is to implement a class that
 *  represents a displayed game object in the application. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <managers/TextureManager.h>

/** @brief Creates a GameObject.
 *  GameObject is a class that creates all objects seen in the
 *  application. Each GameObject instance creates a sprite at 
 *  a specified position. GameObjects can then be drawn to the 
 *  render window.
 */
class GameObject {
  public:
    GameObject();
    virtual ~GameObject() {}

    /** @brief Loads a texture using the TextureManager class and creates
      *   a sprite.
      *   @param file_name The file name of the texture that is being loaded.
      *   @return Void.
      */
    virtual void load(std::string file_name);

    /** @brief Draws a sprite to the render window if the GameObject instance
      *   has previously been loaded. 
      *   @param window A reference to the main render window of the application.
      *   @return Void.
      */
    virtual void draw(sf::RenderWindow& window);


    /** @brief Sets the initial draw position of a GameObject instance. 
      *   @param x X-coordinate of the position.
      *   @return Void.
      */
    virtual void setPosition(float x, float y);
	sf::Vector2f getPosition() const;
	std::string getFileName() const;
	sf::FloatRect getSpriteBounds() const;

  protected:
    /** @brief The Sprite instance of the GameObject. 
     */
    sf::Sprite sprite;

    /** @brief The file name of the sprite's texture. 
     */
    std::string file_name;

    /** @brief Boolean indicating whether or not a sprite has been created. 
      *   The purpose of this bool is to ensure that the sprite exists before
      *   the class attempts to draw the GameObject.
      */
    bool isSpriteCreated;
};