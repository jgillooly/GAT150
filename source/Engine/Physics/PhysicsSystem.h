#pragma once
#include "Framework/Singleton.h"
#include "box2d/b2_world.h"
#include "box2d/box2d.h"
#include "Core/Vector2.h"
#include "ContactListener.h"
#include <memory>
#define VEC2_TO_B2VEC2(vec) (*(b2Vec2*)(&vec))
#define B2VEC2_TO_VEC2(vec) (*(antares::Vector2*)(&vec))

namespace antares {
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);
		friend class Singleton;


	public:
		struct RigidBodyData
		{
			float gravityScale = 1;
			float damping = 0;
			float angularDamping = 0;
			bool constrainAngle = false;
			bool isDynamic = true;
		};

		struct CollisionData
		{
			vec2 size;
			vec2 offset;
			float density = 1;
			float friction = 1;
			float restitution = 0.3f;
			bool isTrigger = false;
		};
	private:
		PhysicsSystem() = default;
		float m_pixelsPerUnit = 48.0f;
	private:
		std::unique_ptr<b2World> m_world;
		std::unique_ptr<ContactListener> contactListener;
	public:
		b2Body* CreateBody(const vec2& position, float angle, const RigidBodyData& data);
		void DestroyBody(b2Body* body);

		void SetCollisionBox(b2Body* body, const CollisionData& data, class Actor* actor = nullptr);
		void SetCollisionBoxStatic(b2Body* body, const CollisionData& data, class Actor* actor = nullptr);

		vec2 WorldToScreen(const vec2& world) { return world * m_pixelsPerUnit; }
		vec2 ScreenToWorld(const vec2& screen) { return screen * (1.0f / m_pixelsPerUnit); }
	};
}