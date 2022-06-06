#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <termios.h>
#include <unistd.h>

#include "utils.hpp"

#define PI 3.14159

struct UtilsSystem {
   bool initialize() {return utils::initialize();}
   ~UtilsSystem() {
      utils::deinitialize();
   }
};

// Type: short
class NoiseMaker {
public:
   typedef double(*UserCallback)(double /*time*/);
   
   ~NoiseMaker() {
      SDL_CloseAudio();
   }

   void pause() {
      SDL_PauseAudio(1);
   }
   void play() {
      SDL_PauseAudio(0);
   }

   void setUserCallback(UserCallback callback) {m_callback = callback;}

   static std::shared_ptr<NoiseMaker> Make(unsigned sampleRate, unsigned amplitude) {
      NoiseMaker* noiseMaker = new NoiseMaker(sampleRate, amplitude);
      SDL_AudioSpec spec{0};
      spec.freq = sampleRate; // Hertz
      spec.format = AUDIO_S16SYS;
      spec.channels = 1;
      spec.samples = 2048;
      spec.callback = &NoiseMaker::audio_callback;
      spec.userdata = reinterpret_cast<void*>(noiseMaker);

      if(SDL_OpenAudio(&spec, nullptr) != 0) {
         SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
         return nullptr;
      }

      return std::shared_ptr<NoiseMaker>(noiseMaker);
   }
private:
   NoiseMaker(unsigned sampleRate, unsigned amplitude) :
      m_globalTime(0.0),
      m_callback(nullptr),
      m_sampleRate(sampleRate),
      m_amplitude(amplitude) {}

   static void audio_callback(void* userdata, Uint8* stream, int len) {
      NoiseMaker* self = reinterpret_cast<NoiseMaker*>(userdata);
      Sint16* buf = (Sint16*)stream;

      double timeStep = 1.0 / self->m_sampleRate;
      for(int i = 0; i < len / sizeof(Sint16); ++i) {
         self->m_globalTime += timeStep;
         if(self->m_callback != nullptr)
           buf[i] = (Sint16)(self->m_callback(self->m_globalTime) * (double)self->m_amplitude);
         else
            buf[i] = 0;
      }
   }
   
   UserCallback m_callback;
   double m_globalTime;
   unsigned m_sampleRate;
   unsigned m_amplitude;
};

double g_frecuency = 400.0;

double make_noise(double time) {
   return std::sin(2.0 * PI * g_frecuency * time);
}

int main() {
   UtilsSystem utilsSys;
   if(SDL_Init(SDL_INIT_AUDIO) < 0) {
      SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
      return 1;
   }
   if(!utilsSys.initialize()) {
      perror("UtilsSystem initializion failed");
      return 1;
   }

   auto noiseMaker = NoiseMaker::Make(44010, 28000);
   if(!noiseMaker) {
      perror("Failed creating NoiseMaker");
      return 1;
   }

   noiseMaker->setUserCallback(make_noise);
   noiseMaker->play();

   double d12thRootOf2 = std::pow(2.0, 1.0/12.0);

   // Pitch Standard => 440 Hz
   while(!utils::is_key_press_by_keycode(utils::kKeyEsc)) {
      bool isKeyPressed = false;
      for(int k = 0; k < 16; ++k) {
         if(utils::is_key_press_by_vk("ZSXCFVGBNJMK,l."[k])) {
            g_frecuency = 440.0 * std::pow(d12thRootOf2, k);
            isKeyPressed = true;
         }
      }

      if(!isKeyPressed)
         g_frecuency = 0.0;
   }
   noiseMaker->pause();

   return 0;
}