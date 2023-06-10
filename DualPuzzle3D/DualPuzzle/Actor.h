#pragma once
#include <vector>
#include "Vector2.h"
#include <SDL_stdinc.h>
#include "Matrix4.h"
using std::vector;

class Game;
class Component;

class Actor
{
public:

	enum class ActorState
	{
		Active,
		Paused,
		Accomplished,
		Out,
		Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector3 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const Quaternion getRotation() const { return rotation; }
	const Matrix4& getWorldTransform() const { return worldTransform;  }

	virtual void setPosition(Vector3 positionP);
	void setScale(float scaleP);
	void setRotation(Quaternion rotationP);
	void setState(ActorState stateP);

	void setAngle(const Vector3& axis, float angle);
	void rotate(const Vector3& axis, float angle);
	Vector3 getForward() const;
	Vector3 getRight() const;
	void computeWorldTransform();

	void processInput(const struct InputState& inputState);
	virtual void actorInput(const struct InputState& inputState);
	void update(float dt);
	virtual void updateActor(float dt);

	inline vector<Component*> getComponents() { return components; }

	template <typename T>
	T* getComponent();

	void updateComponents(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

protected:
	Game& game;
	ActorState state;
	Vector3 position;
	float scale;
	Quaternion rotation;
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform;

	vector<Component*> components;
};
