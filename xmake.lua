set_project("texplr")
set_version("0.0.1")

set_xmakever("2.9.5")

add_requires("glfw 3.4")
add_requires("glm 1.0.1")
add_requires("eventpp 0.1.3")
add_requires("conan::rapidyaml/0.7.1", { 
    alias = "rapidyaml",
    configs = { 
        settings = { "compiler.cppstd=20" }
    } 
})

target("engine")
    set_kind("static")
    set_languages("c++20")

    add_defines("GLFW_INCLUDE_NONE")
    add_files("engine/src/**.cpp")
    add_includedirs("engine/include", { public = true })

    add_headerfiles("engine/include/(**.h)")

    add_packages("glfw", "rapidyaml")
    add_packages("glm", "eventpp", { public = true })

target_end()

target("game")
    set_kind("binary")
    set_languages("c++20")

    add_files("game/src/**.cpp")
    add_includedirs("game/include")

    add_deps("engine")

target_end()
