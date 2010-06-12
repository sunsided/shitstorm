// $Id$

function OnInitEngine() {
	EngineRoot.DebugPhysics = true;
}

function OnTeardownEngine() {
	print("Au revoir.");
}

function OnPause() {
	print("Pause begonnen.");

	local color = EngineRoot.getClearColor();
	color.set(255, 255*frand(), 255*frand(), 255*frand());
	EngineRoot.setClearColor(color);

	local world = Physics.getWorld(0);
	print(world.getGravity());
	print("Anzahl der Physikwelten: " + Physics.WorldCount);
	print("Anzahl der Objekte in Welt 1: " + world.ObjectCount);

	local mass = world.getObject(1).Mass;
	print("Masse des Objektes: " + mass);
	local force = Vector(0, mass, 0);
	print("Setze Geschwindigkeit des Objektes auf: " + force + " m/s");
	world.getObject(1).LinearVelocity = force;
	world.getObject(1).poke();
}

function OnUnpause() {
	print("Pause beendet.");
	print("weiter geht's mit ~"+FPS+" FPS");

	print("Alter Zustand: Simulation aktiv f. Objekt #3: " + World.getObject(3).PhysicsEnabled);
	World.getObject(3).Physics.SimulationEnabled = !World.getObject(3).Physics.SimulationEnabled;
	print("Neuer Zustand: Simulation aktiviert f. Objekt 3: " + World.getObject(3).Physics.SimulationEnabled);
	print("Neuer Zustand: Activation state von Objekt 3: " + World.getObject(3).Physics.getActivationStateString());
}