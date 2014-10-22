#include <utils/AnimationHandler.h> 

/** The update() function calculates and sets up the next frame for the animation.
 *  It also keeps track of elapsed time.
 */
void AnimationHandler::update(const float delta_time) {
  // Don't update id the current_animation doesn't exist in the animations arrays
  if (current_animation >= this->animations.size() || current_animation <0)
    return;

  // Cache the duration of the animation
  float duration = this->animations[current_animation].duration;

  // Check to see if the time has passed enough for the animation to progress to a new frame
  // and if yes, then change the image to the next frame.
  if (int((current_time + delta_time) / duration) > int(current_time / duration)) {
    //Calculate frame number
    int frame_number = int((current_time + delta_time) / duration);

    // Make sure animation loops back to start and not beyond the animation length
    frame_number %= this->animations[current_animation].getLength();

    // Set sprite to new frame
    sf::IntRect rect = this->frame_size;
    rect.left = rect.width * frame_number;
    rect.top = rect.height * this->current_animation;
    this->bounding_rect = rect;
  }

  // Increment elapsed time
  this->current_time += delta_time;

  // Reset elapsed time to zero if the frames advance past the duration of the animation
  if (this->current_time > duration * this->animations[current_animation].getLength()) {
    this->current_time = 0.0f;  // Set to zero to avoid modulus with floating point 
  }
}

void AnimationHandler::addAnimation(Animation& animation) {
  this->animations.push_back(animation);
}

/** The changeAnimation() function sets the current animation to the new animation if the 
 *  new animation is valid. If the new animation is set, elapsed time is reset.
 */
void AnimationHandler::changeAnimation(unsigned int animation_index) {
  // Do not change the animation if new animation is currently active or or if 
  // the new animation does not exist
  if (this->current_animation == animation_index || animation_index >= this->animations.size()
    || animation_index < 0) 
    return;

  //Set current animation to the one at the index given and reset time
  this->current_animation = animation_index;
  sf::IntRect rect = this->frame_size;
  rect.top = rect.height * animation_index;
  this->bounding_rect = rect;
  this->current_time = 0.0f;
}