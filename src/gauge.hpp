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
		std::shared_ptr<ruis::res::image> arrow;
		std::shared_ptr<ruis::res::image> shadow;
		
		real arm_fraction = 1;
		
		real start_angle_rad = utki::deg_to_rad(real(200));
		real end_angle_rad = utki::deg_to_rad(real(-20));
	};
private:
	parameters params;

	std::shared_ptr<const ruis::res::image::texture> arrow_tex;
	std::shared_ptr<const ruis::res::image::texture> shadow_tex;
public:
	gauge(const utki::shared_ref<ruis::context>& c, const tml::forest& desc);
	
	void on_lay_out()override;
	
	void render(const ruis::matrix4& matrix) const override;
};

namespace make{

struct gauge_parameters{

};

}

}
