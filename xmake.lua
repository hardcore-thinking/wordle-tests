add_requires("snitch")

set_languages("cxx20")
set_warnings("error")

add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

target("WordleGame")
    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("inc/*.hpp")
    add_extrafiles("xmake.lua")
    
    add_includedirs("inc")

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/resources")
    add_configfiles("resources/*")

    if is_plat("windows") then
        set_toolchains("msvc", { vs = "2022" })
    elseif is_plat("linux") then
        set_toolchains("gcc", { gcc = "13" })
        add_cxxflags("gcc::-fprofile-arcs", { force = true })
        add_cxxflags("gcc::-ftest-coverage")
        add_links("gcov")
    else
        set_toolchains("xcode", { clang = "19" })
    end
target_end()

target("WordComparatorTest")
    set_kind("binary")
    set_default(false)
    
    add_packages("snitch")

    set_runargs("-v", "full", "*")

    add_files("tests/WordComparator.test.cpp")
    add_files("src/WordComparator.cpp")
    add_headerfiles("inc/WordComparator.hpp")
    add_tests("test-comparator")

    add_includedirs("inc")

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/resources")
    add_configfiles("resources/tests/words.test.txt", { prefixdir = "tests" })
target_end()

target("WordGeneratorTest")
    set_kind("binary")
    set_default(false)
    
    add_packages("snitch")

    set_runargs("-v", "full", "*")

    add_files("tests/WordGenerator.test.cpp")
    add_files("src/WordGenerator.cpp")
    add_headerfiles("inc/WordGenerator.hpp")
    add_tests("test-generator")

    add_includedirs("inc")

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/resources")
    add_configfiles("resources/tests/words.test.txt", { prefixdir = "tests" })
target_end()