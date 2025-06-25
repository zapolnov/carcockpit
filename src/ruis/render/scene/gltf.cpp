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

ruis::mat4 gltf::get_node_transformation_matrix(const node& n) const
{
	auto transformation = n.transformation;

	if (!this->animators.empty()) {
		// TODO: animation mixing
		const auto& tr = this->animators[0].get().node_transforms[n.index];

		if (tr.translation.has_value()) {
			if (auto* t = std::get_if<trs_transformation>(&transformation)) {
				t->translation = tr.translation.value();
			}
			else if (auto* t = std::get_if<ruis::mat4>(&transformation)) {
				// TODO
			}
		}

		if (tr.rotation.has_value()) {
			if (auto* t = std::get_if<trs_transformation>(&transformation)) {
				t->rotation = tr.rotation.value();
			}
			else if (auto* t = std::get_if<ruis::mat4>(&transformation)) {
				// TODO
			}
		}

		if (tr.scale.has_value()) {
			if (auto* t = std::get_if<trs_transformation>(&transformation)) {
				t->scale = tr.scale.value();
			}
			else if (auto* t = std::get_if<ruis::mat4>(&transformation)) {
				// TODO
			}
		}
	}

	if (std::holds_alternative<ruis::mat4>(transformation)) {
		return std::get<ruis::mat4>(transformation);
	} else {
		ASSERT(std::holds_alternative<trs_transformation>(transformation))

		const auto& trs = std::get<trs_transformation>(transformation);

		auto m = ruis::mat4().set_identity();
		m.translate(trs.translation);
		m.rotate(trs.rotation);
		m.scale(trs.scale);

		return m;
	}
}

void gltf::play_animation(utki::shared_ref<ruis::updater> updater, const std::string& name, float weight, bool loop)
{
	for (const auto& it : this->animations) {
		if (it.get().name == name) {
			auto animator = utki::make_shared<gltf_animator>(shared_from_this(), updater, it, weight, loop);
			animator.get().start();
			this->animators.emplace_back(std::move(animator));
			return;
		}
	}
}
