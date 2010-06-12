/** 
 * Project Vector
 *
 * (c) 2010, Markus Mayer <code@defx.de>
 * $Id$
 */

#define _DEFINES_BINDING
#include "EngineBase.h"
#include "Scripting/Scripting.h"

namespace pv {
	
	//! Bindet die ObjectClass-Klasse
	void EngineBase::bindToScriptingVM() {

		using namespace Sqrat;
		using namespace scripting;
		using namespace irr::core;

		// VM holen
		HSQUIRRELVM vm = DefaultVM::Get();

		// Timer binden
		RootTable(vm).Bind(
			_SC("GameTimer"),
			Class<GameTimer, NoConstructor>(vm)
				.Func(_SC("pause"), &GameTimer::pause)
				.Func(_SC("unpause"), &GameTimer::unpause)
				.Func(_SC("isPaused"), &GameTimer::isPaused)
				.Func(_SC("getLastFrameTime"), &GameTimer::getLastFrameTime)
			);

		// Engine binden
		RootTable(vm).Bind(
			_SC("EngineBase"),
			Class<EngineBase, NoConstructor>(vm)
				.Func(_SC("isPaused"), &EngineBase::isPaused)
				.Func(_SC("pause"), &EngineBase::pause)
				.Func(_SC("unpause"), &EngineBase::unpause)
				.Func(_SC("shouldPause"), &EngineBase::shouldPause)
				.Func(_SC("shouldUnpause"), &EngineBase::shouldUnpause)
				.Func(_SC("getFps"), &EngineBase::getFps)
				.Func(_SC("getTimer"), &EngineBase::getTimer)
				.Func(_SC("getClearColor"), &EngineBase::getClearColor)
				.Func(_SC("setClearColor"), &EngineBase::setClearColor)
				.Prop(_SC("DebugPhysics"), &EngineBase::physicsDebuggingEnabled, &EngineBase::setPhysicsDebuggingEnabled)
				.Var(_SC("PhysicsFixedTimestep"), &EngineBase::physicsFixedTimestep)
				.Var(_SC("PhysicsMaxSubsteps"), &EngineBase::physicsMaxSubsteps)
				.Var(_SC("PhysicsUpdateFactor"), &EngineBase::physicsUpdateFactor)
			);

		// Slot für die Engine erzeugen
		RootTable(vm).SetValue<EngineBase*>(_SC("EngineRoot"), this);
		RootTable(vm).SetValue<physics::PhysicsManager*>(_SC("Physics"), getPhysics());
		RootTable(vm).SetValue<world::WorldManager*>(_SC("World"), getWorld());

		// Konstanten setzen
		ConstTable(vm).Const(_SC("PhysicsFixedTimestepDefault"), PHYSICS_MAX_SUBSTEPS_DEFAULT);
		ConstTable(vm).Const(_SC("PhysicsMaxSubstepsDefault"), PHYSICS_FIXED_TIMESTEP_DEFAULT);
	}
	
}
