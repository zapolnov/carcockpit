#include "gltf_animator.hpp"
#include "gltf.hpp"
#include "gltf_loader.hxx"

using namespace ruis::render;

gltf_animator::gltf_animator(std::shared_ptr<gltf> gltf, utki::shared_ref<ruis::updater> updater, utki::shared_ref<gltf_animation> anim, float weight_coeff, bool loop)
	: ruis::animation(updater, uint32_t(anim.get().duration * 1000.0))
	, gltf_v(std::move(gltf))
	, animation(std::move(anim))
	, node_transforms(gltf_v.lock()->nodes.size())
	, weight(weight_coeff)
	, looping(loop)
{
}

template <typename T>
static T lerp(const T& start, const T& end, float d)
{
	return start + (end - start) * d;
}

template <typename T>
static T cubic_spline(const std::vector<T>& data, float start_time, float end_time, size_t start_index, size_t end_index, float d)
{
	if (start_index == end_index)
		return data[start_index * 3 + 1];

	T previous_output_tangent = data[start_index * 3 + 2];
	T previous_value = data[start_index * 3 + 1];
	T next_value = data[end_index * 3 + 1];
	T next_input_tangent = data[end_index * 3 + 0];

	float delta_time = end_time - start_time;
	T previous_tangent = delta_time * previous_output_tangent;
	T next_tangent = delta_time * next_input_tangent;

	// The mathematical function is described in the Appendix C of the glTF 2.0 specification
	float t = d;
	float t2 = t * t;
	float t3 = t2 * t;

	return  (2 * t3 - 3 * t2 + 1) * previous_value +
			(t3 - 2 * t2 + t) * previous_tangent +
			(-2 * t3 + 3 * t2) * next_value +
			(t3 - t2) * next_tangent;
}

template <typename T>
static T get_interpolated_value(const std::vector<T>& data, float start_time, float end_time, size_t start_index, size_t end_index, float delta, gltf_animation_sampler::interpolation mode)
{
	switch (mode) {
		case gltf_animation_sampler::interpolation::step:
		default: // shouldn't happen, but just in case
			return data[start_index];
			break;
		case gltf_animation_sampler::interpolation::linear:
			return lerp(data[start_index], data[end_index], delta); // TODO: should use slerp for rotation!
			break;
		case gltf_animation_sampler::interpolation::cubic_spline:
			return cubic_spline(data, start_time, end_time, start_index, end_index, delta);
			break;
	}
}

void gltf_animator::on_update(real factor)
{
	double time = factor * animation.get().duration;

	for (auto& it : node_transforms)
		it.reset();

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
			case gltf_animation_channel::path::translation: {
				const auto& data = std::get<std::vector<ruis::vec3>>(output->data);
				ruis::vec3 value = get_interpolated_value(data, start_time, end_time, start_index, end_index, delta, channel.sampler.get()->interpolation_v);
				node_transforms[channel.target_node.get()->index].translation = value;
				break;
			}

			case gltf_animation_channel::path::rotation: {
				const auto& data = std::get<std::vector<ruis::vec4>>(output->data);
				ruis::vec4 value = get_interpolated_value(data, start_time, end_time, start_index, end_index, delta, channel.sampler.get()->interpolation_v);
				node_transforms[channel.target_node.get()->index].rotation = ruis::quaternion(value);
				break;
			}

			case gltf_animation_channel::path::scale: {
				const auto& data = std::get<std::vector<ruis::vec3>>(output->data);
				ruis::vec3 value = get_interpolated_value(data, start_time, end_time, start_index, end_index, delta, channel.sampler.get()->interpolation_v);
				node_transforms[channel.target_node.get()->index].scale = value;
				break;
			}

			case gltf_animation_channel::path::weights: {
				const auto& data = std::get<std::vector<float>>(output->data);
				float value = get_interpolated_value(data, start_time, end_time, start_index, end_index, delta, channel.sampler.get()->interpolation_v);
				// TODO
				break;
			}
		}
	}
}

void gltf_animator::on_end(uint32_t dt)
{
	if (looping) {
		// TODO: this is wrong
		rewind();
		start();
		return;
	}

	auto gltf = this->gltf_v.lock();
	if (gltf) {
		for (auto it = gltf->animators.begin(); it != gltf->animators.end(); ++it) {
			if (&it->get() == this) {
				gltf->animators.erase(it);
				break;
			}
		}
	}
}
