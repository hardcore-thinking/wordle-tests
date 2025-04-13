add_requires("snitch")

set_languages("cxx20")
set_warnings("error")

add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

target("wordle")
    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("inc/*.hpp")
    add_extrafiles("xmake.lua")
    
    add_includedirs("inc")

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/resources")
    add_configfiles("resources/*")
target_end()

target("wordle-test")
    set_kind("binary")
    add_packages("snitch")

    add_files("src/WordComparator.cpp")
    add_files("src/WordGenerator.cpp")
    add_files("src/WordleGame.cpp")
    add_files("tests/*.cpp")
    add_headerfiles("inc/*.hpp")
    add_extrafiles("xmake.lua")

    add_includedirs("inc")

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/resources")
    add_configfiles("resources/*")
    add_configfiles("resources/tests/*")
target_end()

target("WordComparatorTest")
    set_kind("binary")
    set_default(false)
    
    add_packages("snitch")

    set_runargs("-v", "full", "*")

    add_files("tests/WordComparator.test.cpp")
    add_files("src/WordComparator.cpp")
    add_headerfiles("inc/WordComparator.hpp")
    add_tests("test")

    add_includedirs("inc")

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)/resources")
    add_configfiles("resources/tests/words.test.txt", { prefixdir = "tests" })
target_end()