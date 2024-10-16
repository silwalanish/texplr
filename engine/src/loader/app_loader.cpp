#include <texplr/loader/app_loader.h>

#include <fstream>
#include <ryml.hpp>
#include <ryml_std.hpp>

namespace texplr {

ApplicationSpecification AppLoader::loadSpecs(const std::string& path)
{
    std::ifstream ifs(path);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    ApplicationSpecification specs {};
    ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(content));

    tree["name"] >> specs.name;
    tree["width"] >> specs.width;
    tree["height"] >> specs.height;

    bool hasIsResizable = tree.has_child(tree.root_id(), "isResizable");
    if (hasIsResizable) {
        tree["isResizable"] >> specs.isResizable;
    } else {
        specs.isResizable = false;
    }

    return specs;
}

} // namespace texplr
