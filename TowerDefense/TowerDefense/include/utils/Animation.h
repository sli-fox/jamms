/** @file Animation.h
 *  @brief File containing the Animation class.
 *
 *  The purpose of this file is to implement a class that
 *  represents an animation in the application. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>

/** @brief Represents an animation in the game.
 */
class Animation {
  public:
    /** @brief Index of start frame in the sprite sheet.
     */
    unsigned int start_frame;

    /** @brief Index of end frame in the sprite sheet.
     */
    unsigned int end_frame;

    /** @brief Amount of time one frame of the animation should last for.
     */
    float duration;

    /** @brief Animation constructor
     *  @param start_frame Start frame index
     *  @param end_fram End frame index
     *  @param duration How long one frame of the animation lasts
     */
    Animation (unsigned int start_frame, unsigned int end_frame, float duration) {
      this->start_frame = start_frame;
      this->end_frame = end_frame;
      this->duration = duration;
    }

    /** @brief Returns the length of the animation 
     *  @param Unsigned int representing the length of animation in frames
     */
    unsigned int getLength() {
      return end_frame - start_frame + 1;
    }
};