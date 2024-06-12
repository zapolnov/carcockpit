#include <papki/fs_file.hpp>
#include <ruis/render/null/factory.hpp>
#include <ruis/render/scene/scene.hpp>
#include <tst/check.hpp>
#include <tst/set.hpp>

namespace {
tst::set set("scene", [](tst::suite& suite) {
	suite.add("basic_read", []() {
		ruis::render::null::factory rf;

		auto sc = ruis::render::read_gltf(papki::fs_file("samples_gltf/kub.glb"), rf);

		tst::check(!sc.get().nodes.empty(), SL);
	});
});
} // namespace
