#include "animator.hpp"
#include "gltf_loader.hxx"

using namespace ruis::render;

animator::animator(utki::shared_ref<ruis::render::animation> anim, float weight_coeff, bool loop)
	: animation(std::move(anim))
	, weight(weight_coeff)
	, looping(loop)
	, time(0)
{
}

template <typename T>
static T interpolate(const T& start, const T& end, float d, animation_sampler::interpolation mode)
{
	switch (mode) {
		case animation_sampler::interpolation::step:
		default: // shouldn't get here, but keep it safe
			return start;
		case animation_sampler::interpolation::linear:
		case animation_sampler::interpolation::cubic_spline: // TODO: implement properly
			return start + (end - start) * d;
	}
}

bool animator::update(uint32_t dt)
{
	time += double(dt) * 0.0001;

	for (auto& channel : animation.get().channels) {
		const auto& input = channel.sampler.get()->input.get();
		const auto& output = channel.sampler.get()->output.get();

		const auto& times = std::get<std::vector<float>>(input->data);
		if (times.size() == 0)
			continue;

		// TODO: optimize this
		double t = time;
		size_t start_index, end_index;
		for (;;) {
			start_index = 0;
			if (t <= times[0]) {
				start_index = 0;
				end_index = 0;
				break;
			}

			bool found = false;
			for (end_index = 1; end_index < times.size(); ++end_index) {
				if (t <= times[end_index]) {
					start_index = end_index - 1;
					found = true;
					break;
				}
			}
			if (found)
				break;

			t -= times[times.size() - 1];
		}

		float start_time = times[start_index];
		float end_time = times[end_index];
		float delta = (t - start_time) / (end_time - start_time);
		if (delta < 0.0f)
			delta = 0.0f;
		if (delta > 1.0f)
			delta = 1.0f;

		switch (channel.target_path) {
			case animation_channel::path::translation: {
				const auto& data = std::get<std::vector<ruis::vec3>>(output->data);
				ruis::vec3 start = data[start_index];
				ruis::vec3 end = data[end_index];
				ruis::vec3 value = interpolate(start, end, delta, channel.sampler.get()->interpolation_v);
				if (auto* tr = std::get_if<trs_transformation>(&channel.target_node.get()->transformation)) {
					tr->translation = value;
					printf("%.2f %.2f %.2f %.2f (%.2f %.2f %.2f)\n", t, start_time, end_time, delta, value.x(), value.y(), value.z());
				} else if (auto* tr = std::get_if<ruis::mat4>(&channel.target_node.get()->transformation)) {
					// TODO
				}
				// TODO
				break;
			}

			case animation_channel::path::rotation: {
				const auto& data = std::get<std::vector<ruis::vec4>>(output->data);
				ruis::vec4 start = data[start_index];
				ruis::vec4 end = data[end_index];
				ruis::vec4 value = interpolate(start, end, delta, channel.sampler.get()->interpolation_v);
				//printf("%.2f %.2f %.2f %.2f (%.2f %.2f %.2f %.2f)\n", t, start_time, end_time, delta, value.x(), value.y(), value.z(), value.w());
				// TODO
				break;
			}

			case animation_channel::path::scale: {
				const auto& data = std::get<std::vector<ruis::vec3>>(output->data);
				ruis::vec3 start = data[start_index];
				ruis::vec3 end = data[end_index];
				ruis::vec3 value = interpolate(start, end, delta, channel.sampler.get()->interpolation_v);
				printf("%.2f %.2f %.2f %.2f (%.2f %.2f %.2f)\n", t, start_time, end_time, delta, value.x(), value.y(), value.z());
				// TODO
				break;
			}

			case animation_channel::path::weights: {
				const auto& data = std::get<std::vector<float>>(output->data);
				float start = data[start_index];
				float end = data[end_index];
				float value = interpolate(start, end, delta, channel.sampler.get()->interpolation_v);
				break;
			}
		}
	}

	return true;
}
