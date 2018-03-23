#pragma once
#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <vector>

//
#include "iUpdate.hpp"
#include "iRender.hpp"
#include "uniqueID.hpp"

namespace engine
{
	namespace core
	{
		class component;
		class gameObject : public iUpdate, public iRender, public uniqueID
		{
		public:
			// CTOR
			gameObject();
			~gameObject();

			// PUBLIC FUNCTIONS
			void attach_component(component*);
			void remove_component(component*);
			void add_child(gameObject*);
			void remove_child(gameObject*);
			void update(double deltaTime) override;
			void render() override;

			// GETTER FUNCTIONS
			std::vector<component*>get_components() const { return mComponents; }
			std::vector<gameObject*> get_children() const { return mChildren; }
			gameObject* get_parent() const { return mParent; }

			template<typename T>
			T* get_component()
			{
				// If no components have been attached then return nothing
				//
				if (mComponents.size() == 0) return nullptr;

				std::vector< component* >::iterator comp = mComponents.begin();
				for (; comp != mComponents.end(); ++comp)
				{
					T* theComponent = dynamic_cast<T*>(*comp);
					if (theComponent)
					{
						return theComponent;
					}
				}

				return nullptr;
			}
		protected:
			// MEMBERS
			std::vector<component*>	mComponents;
			std::vector<gameObject*> mChildren;
			gameObject* mParent;
		};

	}
}

#endif // !_GAMEOBJECT_HPP_