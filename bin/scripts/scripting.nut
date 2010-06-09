// $Id$

function OnPause() {
	print("Pause begonnen.");

	local color = EngineRoot.getClearColor();
	color.set(255, 255*frand(), 255*frand(), 255*frand());
	EngineRoot.setClearColor(color);
}

function OnUnpause() {
	print("Pause beendet.");
	print("weiter geht's mit ~"+FPS+" FPS");
}