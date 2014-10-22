/** @file AnimationHandler.h
 *  @brief File containing the AnimationHandler class.
 *
 *  The purpose of this file is to implement a class that
 *  handles animations in the application. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utils/Animation.h>

/** @brief Handles animations.
 */
class AnimationHandler {
  public:
    /** @brief Current section of the texture to be displayed.
     */
    sf::IntRect bounding_rect;

    /** @brief Pixel dimensions of each animation frame.
     */
    sf::IntRect frame_size;

    /** @brief AnimationHandler constructor.
     */
    AnimationHandler() : current_time(0.0f), current_animation(-1) {}

    /** @brief Overloading AnimationHandler constructor with frame size.
     */
    AnimationHandler(const sf::IntRect& frame_size) 
    : frame_size(frame_size), current_time(0.0f), current_animation(-1) {}

    /** @brief Add a new animation.
     *  @return Void.
     */
    void addAnimation(Animation& animation);

    /** @brief Updates the current frame of animation.
     *  @param delta_time Time since the update was last called 
     *  (i.e. time for one frame to be executed).
     *  @return Void.
     */
    void update(const float delta_time);

    /** @brief Changes the animation.
     *  @param animation_index Index of new animation.
     *  @return Void.
     */
    void changeAnimation(unsigned int animation_index);

  private:
    /** @brief Array of animations.
     */
    std::vector<Animation> animations;

    /** @brief Time since the animation loop started.
     */
    float current_time;

    /** @brief Current animation displayed.
     */
    float current_animation;
};