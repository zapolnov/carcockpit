#pragma once

#include <ruis/widget.hpp>
#include <ruis/widgets/base/blending_widget.hpp>
#include <ruis/widgets/base/fraction_widget.hpp>
#include <ruis/res/image.hpp>

#include <utki/math.hpp>

namespace ruis{
class gauge :
		public ruis::blending_widget,
		public ruis::fraction_widget,
		virtual public ruis::widget
{
public:
	struct parameters{
		utki::shared_ref<ruis::res::image> arrow;
		std::shared_ptr<ruis::res::image> shadow;
		
		real arm_fraction = 1;
		
		real start_angle_rad = utki::deg_to_rad(real(200));
		real end_angle_rad = utki::deg_to_rad(real(-20));
	};

	struct all_parameters{
		ruis::widget::parameters widget_params;
		ruis::blending_widget::parameters blending_params;
		parameters params;
	};
private:
	parameters params;

	std::shared_ptr<const ruis::res::image::texture> arrow_tex;
	std::shared_ptr<const ruis::res::image::texture> shadow_tex;
public:
	gauge(utki::shared_ref<ruis::context> c, all_parameters params);

	void on_lay_out()override;
	
	void render(const ruis::matrix4& matrix) const override;
};

namespace make{
inline utki::shared_ref<ruis::gauge> gauge(utki::shared_ref<ruis::context> c, ruis::gauge::all_parameters params){
	return utki::make_shared<ruis::gauge>(std::move(c), std::move(params));
}
}

}
