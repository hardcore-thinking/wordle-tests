add_requires("snitch")

set_languages("cxx20")
set_warnings("error")

add_rules("mode.debug", "mode.release", "mode.coverage")
add_rules("plugin.vsxmake.autoupdate")

target("WordleGame")
    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("inc/*.hpp")
    add_extrafiles("xmake.lua")
    
    add_includedirs("inc")

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/resources")
    add_configfiles("resources/*")
target_end()

target("WordComparatorTest")
    set_kind("binary")
    set_default(false)
    add_deps("WordleGame")

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
    add_deps("WordleGame")

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