/*
carcockpit - Car cockpit example GUI project

Copyright (C) 2024-2025 Gagistech Oy <gagisechoy@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* ================ LICENSE END ================ */

#include "gltf.hpp"

using namespace ruis::render;

void gltf::play_animation(const std::string& name, float weight, bool loop)
{
	for (const auto& it : this->animations) {
		if (it.get().name == name) {
			auto animator = utki::make_shared<ruis::render::animator>(it, weight, loop);
			this->animators.emplace_back(std::move(animator));
			return;
		}
	}
}

void gltf::update(uint32_t dt)
{
	time += dt;

	for (auto it = this->animators.begin(); it != this->animators.end(); ) {
		auto& animator = it->get();
		if (animator.update(dt))
			++it;
		else
			it = this->animators.erase(it);
	}
}
