/** 
 * Project Vector
 * Sound-Bindings
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "SoundBindings.h"
#include "Sound/SoundEmitter.h"
#include "Sound/SoundState.h"
#include "Sound/RoamingSoundListener.h"
#include "Sound/ContextBoundSoundListener.h"
#include "Sound/SoundDevice.h"
#include "Sound/SoundDeviceManager.h"
#include "Sound/SoundContext.h"
#include "Sound/SingleSoundBuffer.h"
#include "Sound/StreamingSoundBuffer.h"
#include "Sound/StreamingAudioSource.h"
#include "Sound/OggVorbisAudioSource.h"

using namespace Sqrat;
using namespace irr;
using namespace irr::core;
using namespace pv::sound;

namespace pv {
namespace scripting {

	//! Ermittelt einen Emitter von Device 0
	SoundEmitter* getEmitterFromContext(irr::u32 contextId, irr::u32 emitterId) {
		SoundDevice* dev = SoundDeviceManager::get()->getDevice(0);
		if (!dev) return NULL;

		SoundContext* con = dev->getContext(contextId);
		if (!con) return NULL;

		return con->getEmitter(emitterId);
	}

	//! Ermittelt einen Emitter vom aktiven Kontext des Device 0
	SoundEmitter* getEmitterFromCurrentContext(irr::u32 emitterId) {
		SoundDevice* dev = SoundDeviceManager::get()->getDevice(0);
		if (!dev) return NULL;

		SoundContext* con = dev->getActiveContext();
		if (!con) return NULL;

		return con->getEmitter(emitterId);
	}

	//! Bindet die Klasse
	void SoundBindings::scriptingBind(HSQUIRRELVM& vm) {

		RootTable(vm).Func(_SC("getSoundEmitter"), getEmitterFromCurrentContext);
		RootTable(vm).Func(_SC("getSoundEmitterEx"), getEmitterFromContext);

		ConstTable(vm).Enum(
			_SC("SoundDistanceModel"),
			Enumeration(vm)
				.Const(_SC("None"), SDM_NONE)
				.Const(_SC("Inverse"), SDM_INVERSE_DISTANCE)
				.Const(_SC("InverseClamped"), SDM_INVERSE_DISTANCE_CLAMPED)
				.Const(_SC("Linear"), SDM_LINEAR_DISTANCE)
				.Const(_SC("LinearClamped"), SDM_LINEAR_DISTANCE_CLAMPED)
				.Const(_SC("Exponent"), SDM_EXPONENT_DISTANCE)
				.Const(_SC("ExponentClamped"), SDM_EXPONENT_DISTANCE_CLAMPED)
			);

		RootTable(vm).Bind(
			_SC("SoundState"),
			Class<SoundState, NoConstructor>(vm)
				.Func(_SC("setDopplerFactor"), &SoundState::setDopplerFactor)
				.Func(_SC("setSpeedOfSound"), &SoundState::setSpeedOfSound)
				.Func(_SC("setDistanceModel"), &SoundState::setDistanceModelU32)
			);

		RootTable(vm).Bind(
			_SC("PositionalAudioObject"),
			Class<PositionalAudioObject, NoConstructor>(vm)
				.Func<vector3df(PositionalAudioObject::*)()const>(_SC("getVelocity"), &PositionalAudioObject::getVelocity)
				.Func<vector3df(PositionalAudioObject::*)()const>(_SC("getPosition"), &PositionalAudioObject::getPosition)
				.Func<void(PositionalAudioObject::*)(vector3df&)const>(_SC("setVelocity"), &PositionalAudioObject::setVelocity)
				.Func<void(PositionalAudioObject::*)(vector3df&)const>(_SC("setPosition"), &PositionalAudioObject::setPosition)
				.Prop(_SC("Gain"), &PositionalAudioObject::getGain)
				.Func(_SC("setGain"), &PositionalAudioObject::setGain)
				.Func(_SC("getGain"), &PositionalAudioObject::getGain)
			);

		RootTable(vm).Bind(
			_SC("SoundEmitter"),
			DerivedClass<SoundEmitter, PositionalAudioObject, NoConstructor>(vm)
				.Prop(_SC("IsPlaying"), &SoundEmitter::isPlaying)
				.Prop(_SC("IsPaused"), &SoundEmitter::isPaused)
				.Prop(_SC("IsMasked"), &SoundEmitter::systemPreventsPlaying)
				.Prop(_SC("State"), &SoundEmitter::getState)
				.Prop(_SC("Id"), &SoundEmitter::getEmitterId)
				.Prop(_SC("IsLooping"), &SoundEmitter::isLooping)
				.Prop(_SC("OpenALSourceId"), &SoundEmitter::getOpenALSource)
				.Prop(_SC("Context"), &SoundEmitter::getParentContext)
				.Func(_SC("play"), &SoundEmitter::play)
				.Func(_SC("pause"), &SoundEmitter::pause)
				.Func(_SC("stop"), &SoundEmitter::stop)
				.Func(_SC("mask"), &SoundEmitter::pauseBySystem)
				.Func(_SC("unmask"), &SoundEmitter::unpauseBySystem)
				.Func(_SC("rewind"), &SoundEmitter::rewind)
				.Func(_SC("setLooping"), &SoundEmitter::setLooping)
				.Func(_SC("setMaxGain"), &SoundEmitter::setMaxGain)
				.Func(_SC("setMinGain"), &SoundEmitter::setMinGain)
				.Prop(_SC("MaxGain"), &SoundEmitter::getMaxGain)
				.Prop(_SC("MinGain"), &SoundEmitter::getMinGain)
				.Prop(_SC("MaxDistance"), &SoundEmitter::getMaxDistance)
				.Func(_SC("setMaxDistance"), &SoundEmitter::setMaxDistance)
				.Func(_SC("setReferenceDistance"), &SoundEmitter::setReferenceDistance)
				.Func<void(SoundEmitter::*)(vector3df&)const>(_SC("setOrientation"), &SoundEmitter::setOrientation)
				.Func<vector3df(SoundEmitter::*)()const>(_SC("getOrientation"), &SoundEmitter::getOrientation)
				.Func(_SC("resetOrientation"), &SoundEmitter::resetOrientation)
				.Func(_SC("setRelative"), &SoundEmitter::setRelative)
				.Func(_SC("makeAmbient"), &SoundEmitter::makeAmbient)
				.Func(_SC("setRolloffFactor"), &SoundEmitter::setRolloffFactor)
				.Prop(_SC("IsStreaming"), &SoundEmitter::isStreamingEmitter)
			);

		RootTable(vm).Bind(
			_SC("SoundListener"),
			DerivedClass<SoundListener, PositionalAudioObject, NoConstructor>(vm)
				.Func<void(SoundListener::*)(vector3df&,vector3df&)const>(_SC("setOrientation"), &SoundListener::setOrientation)
			);

		RootTable(vm).Bind(
			_SC("RoamingSoundListener"),
			DerivedClass<RoamingSoundListener, SoundListener, NoConstructor>(vm)
			);

		RootTable(vm).Bind(
			_SC("ContextBoundSoundListener"),
			DerivedClass<ContextBoundSoundListener, SoundListener, NoConstructor>(vm)
				.Prop(_SC("Context"), &ContextBoundSoundListener::getContext)
			);

		RootTable(vm).Bind(
			_SC("SoundDevice"),
			Class<SoundDevice, NoConstructor>(vm)
				.Prop(_SC("IsActive"), &SoundDevice::isActiveDevice)
				.Prop(_SC("BufferCount"), &SoundDevice::getBufferCount)
				.Prop(_SC("ActiveContext"), &SoundDevice::getActiveContext)
				.Prop(_SC("ContextCount"), &SoundDevice::getContextCount)
				.Func(_SC("createContext"), &SoundDevice::createContext)
				.Func(_SC("getContext"), &SoundDevice::getContext)
				.Func(_SC("getActiveContext"), &SoundDevice::getActiveContext)
				.Func<SoundContext*(SoundDevice::*)(SoundContext*)>(_SC("setActiveContext"), &SoundDevice::setActiveContext)
				.Func(_SC("createBuffer"), &SoundDevice::createSingleBuffer)
				.Func(_SC("createStreamingBuffer"), &SoundDevice::createStreamingBuffer)
				.Func<void(SoundDevice::*)()>(_SC("updateStreamingAudio"), &SoundDevice::updateStreamingAudio)
			);

		RootTable(vm).Bind(
			_SC("SoundContext"),
			Class<SoundContext, NoConstructor>(vm)
				.Prop(_SC("Id"), &SoundContext::getContextId)
				.Prop(_SC("IsActive"), &SoundContext::isActiveContext)
				.Prop(_SC("IsSuspended"), &SoundContext::isSuspended)
				.Func(_SC("getBoundListener"), &SoundContext::getContextSwitchingListener)
				.Func(_SC("makeActive"), &SoundContext::makeActiveContext)
				.Func(_SC("unsetActive"), &SoundContext::unsetActiveContext)
				.Func(_SC("suspend"), &SoundContext::suspend)
				.Func(_SC("process"), &SoundContext::process)
				.Func(_SC("createEmitter"), &SoundContext::createSoundEmitter)
				.Func(_SC("getEmitter"), &SoundContext::getEmitter)
			);

		RootTable(vm).Bind(
			_SC("SoundBuffer"),
			Class<SoundBuffer, NoConstructor>(vm)
				.Prop(_SC("Count"), &SoundBuffer::getBufferCount)
				.Func(_SC("getSize"), &SoundBuffer::getSize)
				.Func(_SC("getBitrate"), &SoundBuffer::getBitrate)
				.Func(_SC("getFrequency"), &SoundBuffer::getFrequency)
				.Func(_SC("getChannels"), &SoundBuffer::getChannels)
			);

		RootTable(vm).Bind(
			_SC("SingleSoundBuffer"),
			DerivedClass<SingleSoundBuffer, SoundBuffer, NoConstructor>(vm)
				.Prop(_SC("Size"), &SingleSoundBuffer::getSize)
				.Prop(_SC("Bitrate"), &SingleSoundBuffer::getBitrate)
				.Prop(_SC("Frequency"), &SingleSoundBuffer::getFrequency)
				.Prop(_SC("Channels"), &SingleSoundBuffer::getChannels)
			);

		RootTable(vm).Bind(
			_SC("StreamingSoundBuffer"),
			DerivedClass<StreamingSoundBuffer, SoundBuffer, NoConstructor>(vm)
				.Prop(_SC("BufferSize"), &StreamingSoundBuffer::getBufferSize)
				.Func(_SC("update"), &StreamingSoundBuffer::updateStreamingAudio)
				.Func(_SC("detachSource"), &StreamingSoundBuffer::detachStreamingSource)
				.Func(_SC("getAttachedSource"), &StreamingSoundBuffer::getAttachedStreamingSource)
			);

		RootTable(vm).Bind(
			_SC("StreamingAudioSource"),
			Class<StreamingAudioSource, NoConstructor>(vm)
				.Prop(_SC("IsAttached"), &StreamingAudioSource::isAttachedToBuffer)
				.Func(_SC("initializeStreaming"), &StreamingAudioSource::initializeStreaming)
				.Func(_SC("update"), &StreamingAudioSource::updateStreamingAudio)
				.Func(_SC("detach"), &StreamingAudioSource::detachFromStreamingBuffer)
				.Func(_SC("rewind"), &StreamingAudioSource::rewindStreaming)
			);

		RootTable(vm).Bind(
			_SC("OggVorbisAudioSource"),
			DerivedClass<OggVorbisAudioSource, StreamingAudioSource>(vm)
				.Prop(_SC("Format"), &OggVorbisAudioSource::getFormat)
				.Prop(_SC("IsOpen"), &OggVorbisAudioSource::isOpen)
				.Func(_SC("openFile"), &OggVorbisAudioSource::openFile)
				.Func(_SC("loadToBuffer"), &OggVorbisAudioSource::loadToBuffer)
				.Func(_SC("closeFile"), &OggVorbisAudioSource::closeFile)
				.Func(_SC("getUncompressedPCMSize"), &OggVorbisAudioSource::getUncompressedPCMSize)
			);
	}

}}
