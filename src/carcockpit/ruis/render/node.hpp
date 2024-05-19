#pragma once

#include <variant>

#include <r4/quaternion.hpp>
#include <r4/vector.hpp>
#include <papki/file.hpp>
#include <ruis/config.hpp>

#include "mesh.hpp"

namespace ruis::render{

class node{
public:
    std::string name;

    // TODO: add extras as JSON?

    utki::shared_ref<mesh> mesh_v;

    std::vector<utki::shared_ref<node>> children;

    struct trs
    {
        ruis::vec3 translation;
        ruis::quaternion rotation;
        ruis::vec3 scale;
    };

    std::variant<ruis::mat4, trs> transformation;

};

utki::shared_ref<node> read_gltf(const papki::file fi);

}