#include "car_widget.hpp"

#include <ratio>

using namespace carcockpit;

car_widget::car_widget(utki::shared_ref<ruis::context> context, all_parameters params) :
	ruis::widget(std::move(context), {.widget_params = std::move(params.widget_params)})
{
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
	std::array<ruis::vector3, 36> cube_pos = {
		{ruis::vector3(-1, -1, 1), ruis::vector3(1, -1, 1),   ruis::vector3(-1, 1, 1),   ruis::vector3(1, -1, 1),
		 ruis::vector3(1, 1, 1),   ruis::vector3(-1, 1, 1),   ruis::vector3(1, -1, 1),   ruis::vector3(1, -1, -1),
		 ruis::vector3(1, 1, 1),   ruis::vector3(1, -1, -1),  ruis::vector3(1, 1, -1),   ruis::vector3(1, 1, 1),
		 ruis::vector3(1, -1, -1), ruis::vector3(-1, -1, -1), ruis::vector3(1, 1, -1),   ruis::vector3(-1, -1, -1),
		 ruis::vector3(-1, 1, -1), ruis::vector3(1, 1, -1),   ruis::vector3(-1, -1, -1), ruis::vector3(-1, -1, 1),
		 ruis::vector3(-1, 1, -1), ruis::vector3(-1, -1, 1),  ruis::vector3(-1, 1, 1),   ruis::vector3(-1, 1, -1),
		 ruis::vector3(-1, 1, -1), ruis::vector3(-1, 1, 1),   ruis::vector3(1, 1, -1),   ruis::vector3(-1, 1, 1),
		 ruis::vector3(1, 1, 1),   ruis::vector3(1, 1, -1),   ruis::vector3(-1, -1, -1), ruis::vector3(1, -1, -1),
		 ruis::vector3(-1, -1, 1), ruis::vector3(-1, -1, 1),  ruis::vector3(1, -1, -1),  ruis::vector3(1, -1, 1)}
	};

	auto pos_vbo = this->context.get().renderer.get().factory->create_vertex_buffer(utki::make_span(cube_pos));

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
	std::array<ruis::vector2, 36> cube_tex = {
		{ruis::vector2(0, 0), ruis::vector2(1, 0), ruis::vector2(0, 1), ruis::vector2(1, 0), ruis::vector2(1, 1),
		 ruis::vector2(0, 1), ruis::vector2(0, 0), ruis::vector2(1, 0), ruis::vector2(0, 1), ruis::vector2(1, 0),
		 ruis::vector2(1, 1), ruis::vector2(0, 1), ruis::vector2(0, 0), ruis::vector2(1, 0), ruis::vector2(0, 1),
		 ruis::vector2(1, 0), ruis::vector2(1, 1), ruis::vector2(0, 1), ruis::vector2(0, 0), ruis::vector2(1, 0),
		 ruis::vector2(0, 1), ruis::vector2(1, 0), ruis::vector2(1, 1), ruis::vector2(0, 1), ruis::vector2(0, 0),
		 ruis::vector2(1, 0), ruis::vector2(0, 1), ruis::vector2(1, 0), ruis::vector2(1, 1), ruis::vector2(0, 1),
		 ruis::vector2(0, 0), ruis::vector2(1, 0), ruis::vector2(0, 1), ruis::vector2(1, 0), ruis::vector2(1, 1),
		 ruis::vector2(0, 1)}
	};

	auto tex_vbo = this->context.get().renderer.get().factory->create_vertex_buffer(utki::make_span(cube_tex));

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
	std::array<uint16_t, 36> indices = {
		{// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
		 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
		}
	};

	auto cube_indices = this->context.get().renderer.get().factory->create_index_buffer(utki::make_span(indices));

	this->cube_vao =
		this->context.get()
			.renderer.get()
			.factory->create_vertex_array({pos_vbo, tex_vbo}, cube_indices, ruis::vertex_array::mode::triangles)
			.to_shared_ptr();

	this->tex = this->context.get().loader.load<ruis::res::texture>("tex_sample").to_shared_ptr();
	this->rot.set_identity();


}

void car_widget::update(uint32_t dt)
{
	this->fps_sec_counter += dt;
	++this->fps;
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
	this->rot *=
		ruis::quaternion().set_rotation(r4::vector3<float>(1, 2, 1).normalize(), 1.5f * (float(dt) / std::milli::den));
	if (this->fps_sec_counter >= std::milli::den) {
		std::cout << "fps = " << std::dec << fps << std::endl;
		this->fps_sec_counter = 0;
		this->fps = 0;
	}
	this->clear_cache();
}

void car_widget::render(const ruis::matrix4& matrix) const
{
	this->widget::render(matrix);

	ruis::matrix4 matr(matrix);
	matr.scale(this->rect().d / 2);
	matr.translate(1, 1);
	matr.scale(1, -1);
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
	matr.frustum(-2, 2, -1.5, 1.5, 2, 100);
	matr.translate(0, 0, -4);
	matr.rotate(this->rot);

	//		glEnable(GL_CULL_FACE);

	this->context.get().renderer.get().shader->pos_tex->render(matr, *this->cube_vao, this->tex->tex());

	//		glDisable(GL_CULL_FACE);
}
