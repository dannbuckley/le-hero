/*
 * QuestLoaderQueue.cpp
 * Copyright (c) 2020 Daniel Buckley
 */

#include "QuestLoaderQueue.h"

namespace le_hero {
	namespace lua {
		void QuestLoaderQueue::push(const quest::Quest& data, uint8_t index)
		{
			// create a <quest::Quest, uint8_t> pair and push to the back of the queue
			this->container->emplace_back(data, index);
		}

		std::vector<quest::Quest> QuestLoaderQueue::export_to_vector()
		{
			size_t n = this->size();
			if (n == 0) {
				// no quests in queue -> no transformation necessary
				return std::vector<quest::Quest>();
			}

			// sort quests by index
			this->heapsort();

			// create vector for Quest objects
			std::vector<quest::Quest> quests;
			// make the vector the same size as the queue's container
			quests.reserve(n);

			// push each Quest data object into the quests vector
			for (size_t i = 0; i < n; i++) {
				quests.push_back(this->container->at(i).first);
			}
			return quests;
		}

		void QuestLoaderQueue::construct_heap(size_t n)
		{
			size_t nh = n / 2;
			for (size_t i = 1; i < (nh + 1); i++) {
				size_t k = nh - i + 1;
				std::pair<quest::Quest, uint8_t> v = this->container->at(k - 1);
				bool heap = false;
				while (!heap && (2 * k) <= n) {
					size_t j = 2 * k;
					if (j < n) {
						// there are two children
						if (this->container->at(j - 1).second < this->container->at(j).second) {
							j++;
						}
					}

					if (v.second >= this->container->at(j - 1).second) {
						heap = true;
					}
					else {
						this->container->at(k - 1) = this->container->at(j - 1);
						k = j;
					}
				}
				this->container->at(k - 1) = v;
			}
		}

		void QuestLoaderQueue::heapsort()
		{
			size_t n = this->size();
			if (n == 0) {
				return;
			}

			// construct a heap using the queue's container
			this->construct_heap(n);

			// apply the root-deletion operation n-1 times to the remaining heap
			for (size_t i = 0; i < (n - 1); i++) {
				// exchange the root's key with the last key k of the heap
				std::swap(this->container->front(), this->container->at(n - 1 - i));
				// verify parental dominance for k
				this->construct_heap(n - 1 - i);
			}
		}
	}
}
