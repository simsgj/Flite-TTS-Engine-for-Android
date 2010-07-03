// Standard headers
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "tts/tts.h"

#include <android/log.h>
#define LOG_TAG "FliteEngine"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

static android_tts_synth_cb_t ttsSynthDoneCBPointer;
static android_tts_engine_funcs_t functable;
static android_tts_engine_t engine;

android_tts_result_t init(void* engine, android_tts_synth_cb_t synthDoneCBPtr, const char *engineConfig)
{
  LOGI("TtsEngine::init start");
  return ANDROID_TTS_SUCCESS;    
};

android_tts_result_t shutdown(void* engine )
{
  LOGI("TtsEngine::shutdown");
  return ANDROID_TTS_SUCCESS;
}

android_tts_result_t loadLanguage(void* engine, const char *lang, const char *country, const char *variant)
{
  LOGI("TtsEngine::loadLanguage: lang=%s, country=%s, variant=%s", lang, country, variant);
  return ANDROID_TTS_SUCCESS;
}

android_tts_result_t setLanguage( void* engine, const char * lang, const char * country, const char * variant )
{
  LOGI("TtsEngine::setLanguage: lang=%s, country=%s, variant=%s", lang, country, variant);
  return ANDROID_TTS_SUCCESS;
}

android_tts_support_result_t isLanguageAvailable(void* engine, const char *lang, const char *country,
						 const char *variant)
{
  LOGI("TtsEngine::isLanguageAvailable: lang=%s, country=%s, variant=%s", lang, country, variant);
  return ANDROID_TTS_LANG_COUNTRY_VAR_AVAILABLE;
}

android_tts_result_t getLanguage(void* engine, char *language, char *country, char *variant)
{
  LOGI("TtsEngine::getLanguage");
  return ANDROID_TTS_SUCCESS;
}

android_tts_result_t setAudioFormat(void* engine, android_tts_audio_format_t* encoding, uint32_t* rate,
				    int* channels)
{
  LOGI("TtsEngine::setAudioFormat");
  return ANDROID_TTS_FAILURE;
}

android_tts_result_t setProperty(void* engine, const char *property, const char *value,
				 const size_t size)
{
  LOGW("TtsEngine::setProperty is unimplemented");
  return ANDROID_TTS_PROPERTY_UNSUPPORTED; 
}

android_tts_result_t getProperty(void* engine, const char *property, char *value, size_t *iosize)
{
  LOGW("TtsEngine::getProperty is unimplemented");
  return ANDROID_TTS_PROPERTY_UNSUPPORTED;
}

android_tts_result_t stop(void* engine)
{
  LOGI("TtsEngine::stop");
  return ANDROID_TTS_SUCCESS;
}

android_tts_result_t synthesizeText( void* engine, const char * text, int8_t * buffer, size_t bufferSize, void * userdata )
{
  LOGI("TtsEngine::synthesizeText: text=%s, bufferSize=%lu", text, (unsigned long) bufferSize);
  return ANDROID_TTS_FAILURE;
}

android_tts_engine_t *android_getTtsEngine()
{
  LOGD("TtsEngine::getTtsEngine not called here!");

  functable.init = init;
  functable.shutdown = shutdown;
  functable.stop = stop;
  functable.isLanguageAvailable = isLanguageAvailable;
  functable.loadLanguage = loadLanguage;
  functable.setLanguage = setLanguage;
  functable.getLanguage = getLanguage;
  functable.setAudioFormat = setAudioFormat;
  functable.setProperty = setProperty;
  functable.getProperty = getProperty;
  functable.synthesizeText = synthesizeText;
  
  engine.funcs = &functable;

  return &engine;
}

namespace android 
{
  android_tts_engine_t* getTtsEngine()
  {
    
    LOGD("TtsEngine::getTtsEngine is called here!");
    return android_getTtsEngine();
  }
}
