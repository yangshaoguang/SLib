#ifndef CHECKHEADER_SLIB_MEDIA_AUDIO_FORMAT
#define CHECKHEADER_SLIB_MEDIA_AUDIO_FORMAT

#include "definition.h"

SLIB_MEDIA_NAMESPACE_BEGIN

enum class AudioSampleType
{
	Int8 = 1,
	Uint8 = 2,
	
	Int16 = 8,
	Uint16 = 9,
	Int16LE = 12,
	Uint16LE = 13,
	Int16BE = 14,
	Uint16BE = 15,
	
	Float = 32,
	FloatLE = 33,
	FloatBE = 34
};

/*
	Format Bits Description
 
 0~7: audio sample type
 8~15: bits per sample
 16~23: channels count
 24: is non-interleaved
 
*/

#define SLIB_DEFINE_AUDIO_FORMAT(sampleType, bitsPerSample, nChannels, isNonInterleaved) \
	((sl_uint32)(sampleType) | (bitsPerSample << 8) | (nChannels << 16) | (isNonInterleaved << 24))

enum class AudioFormat
{
	None = 0,
	
	Int8_Mono =							SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int8, 8, 1, 0),
	Int8_Stereo =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int8, 8, 2, 0),
	Int8_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int8, 8, 2, 1),
	
	Uint8_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint8, 8, 1, 0),
	Uint8_Stereo =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint8, 8, 2, 0),
	Uint8_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint8, 8, 2, 1),
	
	Int16_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16, 16, 1, 0),
	Int16_Stereo =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16, 16, 2, 0),
	Int16_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16, 16, 2, 1),
	
	Uint16_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16, 16, 1, 0),
	Uint16_Stereo =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16, 16, 2, 0),
	Uint16_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16, 16, 2, 1),
	
	Int16LE_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16LE, 16, 1, 0),
	Int16LE_Stereo =					SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16LE, 16, 2, 0),
	Int16LE_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16LE, 16, 2, 1),
	
	Uint16LE_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16LE, 16, 1, 0),
	Uint16LE_Stereo =					SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16LE, 16, 2, 0),
	Uint16LE_Stereo_NonInterleaved =	SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16LE, 16, 2, 1),
	
	Int16BE_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16BE, 16, 1, 0),
	Int16BE_Stereo =					SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16BE, 16, 2, 0),
	Int16BE_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Int16BE, 16, 2, 1),
	
	Uint16BE_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16BE, 16, 1, 0),
	Uint16BE_Stereo =					SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16BE, 16, 2, 0),
	Uint16BE_Stereo_NonInterleaved =	SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Uint16BE, 16, 2, 1),
	
	Float_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Float, 32, 1, 0),
	Float_Stereo =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Float, 32, 2, 0),
	Float_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::Float, 32, 2, 1),
	
	FloatLE_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::FloatLE, 32, 1, 0),
	FloatLE_Stereo =					SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::FloatLE, 32, 2, 0),
	FloatLE_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::FloatLE, 32, 2, 1),
	
	FloatBE_Mono =						SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::FloatBE, 32, 1, 0),
	FloatBE_Stereo =					SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::FloatBE, 32, 2, 0),
	FloatBE_Stereo_NonInterleaved =		SLIB_DEFINE_AUDIO_FORMAT(AudioSampleType::FloatBE, 32, 2, 1)

};


class SLIB_EXPORT AudioFormats
{
public:
	static AudioSampleType getSampleType(AudioFormat format);
	
	static sl_uint32 getBitsPerSample(AudioFormat format);
	
	static sl_uint32 getBytesPerSample(AudioFormat format);
	
	static sl_uint32 getChannelsCount(AudioFormat format);
	
	static sl_bool isNonInterleaved(AudioFormat format);
	
	static sl_bool isFloat(AudioFormat format);

};

SLIB_MEDIA_NAMESPACE_END

#endif
