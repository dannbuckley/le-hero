/*
 * QuestLoaderQueue.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <deque>
#include <memory>
#include <utility>
#include <vector>
#include "Quest.h"

namespace le_hero {
	namespace lua {
		class QuestLoaderQueue
		{
		public:
			/* default constructor */
			QuestLoaderQueue() {
				container = std::make_unique<std::deque<std::pair<quest::Quest, uint8_t>>>();
			}

			/* copy constructor */
			QuestLoaderQueue(const QuestLoaderQueue& old) {
				container = std::make_unique<std::deque<std::pair<quest::Quest, uint8_t>>>(old.container->begin(), old.container->end());
			}

			/* destructor */
			virtual ~QuestLoaderQueue() {}

			/* size getter function, necessary for LuaQuestHandler::construct_quests_queue */
			size_t size() {
				return this->container->size();
			}
			void push(const quest::Quest& data, uint8_t index);
			std::vector<quest::Quest> export_to_vector();

		private:
			void construct_heap(size_t n);
			void heapsort();

			std::unique_ptr<std::deque<std::pair<quest::Quest, uint8_t>>> container;
		};
	}
}