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

#include "scene.hpp"

#include <chrono>

using namespace ruis::render;

std::shared_ptr<light> scene::get_primary_light()
{
	if (this->lights.size() >= 1)
		return lights[0].to_shared_ptr();

	return nullptr;
}

std::shared_ptr<light> scene::get_secondary_light()
{
	if (this->lights.size() >= 2)
		return lights[1].to_shared_ptr();

	return nullptr;
}

void scene::play_animation(const std::string& name, float weight, bool loop)
{
	for (const auto& it : this->animations) {
		if (it.get().name == name) {
			auto animator = utki::make_shared<ruis::render::animator>(it, weight, loop);
			this->animators.emplace_back(std::move(animator));
			return;
		}
	}
}

void scene::update(uint32_t dt)
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

ruis::mat4 camera::get_projection_matrix(ruis::real aspect_ratio)
{
	auto projection = ruis::mat4().set_identity();
	projection.set_perspective(
		fovy, //
		aspect_ratio,
		near,
		far
	);
	return projection;
}

ruis::mat4 camera::get_view_matrix()
{
	auto view = ruis::mat4().set_identity();
	view.set_look_at(
		pos, //
		target,
		up
	);
	return view;
}

ruis::vec3 camera::to_view_coords(ruis::vec3 vec)
{
	return get_view_matrix() * vec;
}

light::light(
	ruis::vec4 pos, //
	ruis::vec3 intensity
) :
	pos(pos),
	intensity(intensity)
{}
