/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

/// @file
/// @brief Class template thor::EventSystem

#ifndef THOR_EVENTSYSTEM_HPP
#define THOR_EVENTSYSTEM_HPP

#include <Thor/Tools/NonCopyable.hpp>
#include <Thor/Detail/EventListener.hpp>


namespace thor
{

/// @addtogroup Events
/// @{

/// @brief Class for object-oriented handling of user-defined events.
/// @tparam Event The event type. For example, this can be a class or enum.
/// @tparam EventIdentifier The type that distinguishes different events. This isn't necessarily the event type itself.
///  Consider SFML: The event type would be sf::Event, but the identifier is sf::Event::EventType. When you use custom
///  events where @a EventIdentifier and @a Event are distinct types, you have to provide a global function
///  <b>EventIdentifier ExtractEventIdentifier(const Event&)</b> in the namespace of the @a Event type definition. Besides, the
///  event system requires less-than operator < for @a EventIdentifier (enums can use the implicit conversion to int).
template <typename Event, typename EventIdentifier = Event>
class EventSystem : private NonCopyable
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public types
	public:
		/// @brief Function type of listeners associated with Event
		///
		typedef std::tr1::function< void(const Event&) >					Listener;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Default constructor
		/// @details Sets up an EventSystem where @a Event and @a EventIdentifier are the same types.
									EventSystem();
			
		/// @brief Fires an event.
		/// @details Calls all listener functions that are currently associated with @a event.
		void						TriggerEvent(const Event& event);
	
		/// @brief Connects an event to the specified listener.
		/// @details Duplicates are allowed (thus, the listener is invoked multiple times).
		/// @param trigger The event you want to associate with a listener function.
		/// @param listener The function that is invoked when a @a trigger event is fired.
		/// @return A connection which can be used to remove the listener.
		///  If you don't need this functionality, just ignore the return value.
		Connection					Connect(const EventIdentifier& trigger, const Listener& listener);
		
		/// @brief Disconnects listeners associated with a given event type.
		/// @param identifier The event type identifier of which you want to remove all connected listeners.
		void						ClearConnections(EventIdentifier identifier);

		/// @brief Disconnects all listeners.
		/// @details Removes all event-listener connections, independently of the event type.
		void						ClearAllConnections();


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		// Container type
		typedef detail::ListenerMap<EventIdentifier, const Event&>	EventListenerMap;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		EventListenerMap			mListeners;
};

/// @}

} // namespace thor

#include <Thor/Detail/EventSystem.inl>
#endif // THOR_EVENTSYSTEM_HPP
