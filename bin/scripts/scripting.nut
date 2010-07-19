// $Id$

function OnInitEngine() {
	EngineRoot.DebugPhysics = true;
}

function OnTeardownEngine() {
	print("Au revoir.");
}

function OnInitSoundState() {
	print("Initialisiere SoundState ...");
	SoundState.setDistanceModel(SoundDistanceModel.Exponent);
}

function OnInitSoundEmitter(emitter) {
	emitter.setGain(2.0);
	emitter.setMinGain(0.0);
	emitter.setMaxGain(1.0);
	emitter.setMaxDistance(5.0);
	emitter.setRolloffFactor(2.0);
	emitter.setReferenceDistance(2.0);
}

function OnPause() {
	print("Pause begonnen.");

	local color = EngineRoot.getClearColor();
	color.set(255, 255*frand(), 255*frand(), 255*frand());
	EngineRoot.setClearColor(color);

	local world = Physics.getWorld(0);
	local mass = world.getObject(1).Mass;
	local force = Vector(0, mass, 0);
	world.getObject(1).LinearVelocity = force;
	world.getObject(1).poke();

	world.getObject(3).Gravity = Vector(0, 0, 0);

	getSoundEmitter(1).setGain(10);
	getSoundEmitter(0).mask(); // Stummschalten
}

function OnUnpause() {
	print("Pause beendet.");

	getSoundEmitter(1).setGain(1);
	getSoundEmitter(0).unmask(); // Wieder lebendig schalten
}