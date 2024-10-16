set_project("texplr")
set_version("0.0.1")

set_xmakever("2.9.5")
set_languages("c++20")

add_rules("mode.debug", "mode.release")

add_requires("glfw 3.4")
add_requires("glm 1.0.1")
add_requires("eventpp 0.1.3")
add_requires("vulkansdk")
add_requires("conan::rapidyaml/0.7.1", { 
    alias = "rapidyaml",
    configs = {
        settings = { "compiler.cppstd=20" }
    } 
})

target("engine")
    set_kind("static")

    add_defines("GLFW_INCLUDE_VULKAN")
    add_files("engine/src/**.cpp")
    add_includedirs("engine/include", { public = true })

    add_headerfiles("engine/include/(**.h)")

    add_packages("glfw", "rapidyaml")
    add_packages("glm", "eventpp", "vulkansdk", { public = true })

    after_build(function (target)
        print("compiling shaders...")
        for _, file in ipairs(os.files("shaders/**")) do
            local output_name = "assets/" .. path.directory(file) .. "/" .. path.basename(file) .. ".spv"
            os.exec("mkdir -p %s", path.directory(output_name))

            print("compiling %s to %s...", file, output_name)
            os.exec("glslc %s -o %s", file, output_name)
        end

        print("copying assets...")
        os.exec("cp -r assets %s", target:targetdir())
    end)

target_end()

target("game")
    set_kind("binary")

    add_files("game/src/**.cpp")
    add_includedirs("game/include")

    add_deps("engine")

target_end()
