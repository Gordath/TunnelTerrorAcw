#ifndef AUDIO_H_
#define AUDIO_H_
#include <GL/GLM/mat4x2.hpp>

bool init_audio();
void destroy_audio();

void set_audio_listener(const glm::mat4 &xform);

#endif  // AUDIO_H_
