// Bullet Test.cpp : Defines the entry point for the console application.
// $Id$

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Bullet Test" << endl;

	//#####################################################################################################
	// Initialisierung
	//#####################################################################################################

	// Broadphase
	// Sortiert nicht kollidierende Elemente aus
    auto_ptr<btBroadphaseInterface> broadphase(new btDbvtBroadphase());

    // Kollisionskonfiguration und Dispatcher
    auto_ptr<btDefaultCollisionConfiguration> collisionConfiguration(new btDefaultCollisionConfiguration());
	auto_ptr<btCollisionDispatcher> dispatcher(new btCollisionDispatcher(collisionConfiguration.get()));
	
	// Der eigentliche Solver
    auto_ptr<btSequentialImpulseConstraintSolver> solver(new btSequentialImpulseConstraintSolver());

    // Die Simulationswelt
    auto_ptr<btDiscreteDynamicsWorld> dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get()));
    dynamicsWorld->setGravity(btVector3(0,-9.81f,0));

	//#####################################################################################################
	// Collision Shapes
	//#####################################################################################################

	// Shape für Boden
	auto_ptr<btCollisionShape> groundShape(new btStaticPlaneShape(btVector3(0,1,0), 1));

	// Shape für Kugel
	auto_ptr<btCollisionShape> fallShape(new btSphereShape(1));

	//#####################################################################################################
	// Unbeweglicher Festkörper: Boden
	//#####################################################################################################

	// Motion State des Bodens - gibt die Position an.
	auto_ptr<btDefaultMotionState> groundMotionState(new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,-1,0))));

	// Boden konstruieren
	// Eine Masse von null macht das Objekt unbeweglich
	const btScalar massGround = 0.0f;
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(massGround, groundMotionState.get(), groundShape.get(), btVector3(0,0,0));
    auto_ptr<btRigidBody> groundRigidBody(new btRigidBody(groundRigidBodyCI));

	// Boden zur Welt hinzufügen
	dynamicsWorld->addRigidBody(groundRigidBody.get());

	//#####################################################################################################
	// Beweglicher Festkörper: Kugel
	//#####################################################################################################

	// Motion State der Kugel
	auto_ptr<btDefaultMotionState> fallMotionState(new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,50,0))));

	// Masse setzen und Trägheit der Kugel berechnen lassen
	btScalar mass = 1.0f;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass, fallInertia);

	// Kugel konstruieren
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState.get(), fallShape.get(), fallInertia);
    auto_ptr<btRigidBody> fallRigidBody(new btRigidBody(fallRigidBodyCI));

	// Kugel zur Welt hinzufügen
    dynamicsWorld->addRigidBody(fallRigidBody.get());

	//#####################################################################################################
	// Eigentliche Simulation
	//#####################################################################################################

	for (int i=0 ; i<300; ++i) {

		// Simulation steppen
		// 1/60 Sekunde, 10 Substeps
		dynamicsWorld->stepSimulation(1/60.f, 10);
 
		// Aktuelle Transformation der Kugel ermitteln
        btTransform trans;
        fallRigidBody->getMotionState()->getWorldTransform(trans);
 
		// Höhe ausgeben
        cout << "Höhe der Kugel: " << trans.getOrigin().getY() << endl;
	}

	//#####################################################################################################
	// Aufräumen.
	// Die Elemente müssen entfernt werden, den Rest macht der auto_ptr<>
	//#####################################################################################################
	dynamicsWorld->removeRigidBody(fallRigidBody.get());
	dynamicsWorld->removeRigidBody(groundRigidBody.get());

	cout << "Enter zum Beenden." << endl;
	getchar();

	return 0;
}

