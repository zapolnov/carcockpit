#pragma once

#include <ruis/res/texture.hpp>
#include <ruis/updateable.hpp>
#include <ruis/widgets/widget.hpp>

namespace carcockpit {

class car_widget : public ruis::widget, public ruis::updateable
{
	std::shared_ptr<ruis::res::texture> tex;

	ruis::quaternion rot = ruis::quaternion().set_identity();

	std::shared_ptr<ruis::vertex_array> cube_vao;

	unsigned fps = 0;
	uint32_t fps_sec_counter = 0;

public:
	struct parameters {};

private:
	parameters params;

public:
	struct all_parameters {
		ruis::widget::parameters widget_params;
		parameters car_params;
	};

	car_widget(utki::shared_ref<ruis::context> context, all_parameters params);

	void render(const ruis::matrix4& matrix) const override;
	void update(uint32_t dt) override;
};

namespace make {
inline utki::shared_ref<car_widget> car_widget(utki::shared_ref<ruis::context> c, car_widget::all_parameters params)
{
	return utki::make_shared<carcockpit::car_widget>(std::move(c), std::move(params));
}
} // namespace make

} // namespace carcockpit
