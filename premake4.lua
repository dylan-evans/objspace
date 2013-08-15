
solution "ObjSpace"
    configurations { "Debug", "Test", "Production" }

    project "objectspace"
        kind "ConsoleApp"
        language "C"
        files { "src/*.h", "src/*.c" }
        includedirs { "src" }

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols", "ExtraWarnings", "FatalWarnings" }

        configuration "Production"
            flags { "OptimizeSpeed" }
        
    project "test"
        kind "ConsoleApp"
        language "C"
        files { "tests/*.c", "src/*.h", "src/*.c"  }
        includedirs { "src" }
        links { "cunit" }
        configuration "Test"
            libdirs { os.findlib("cunit") }
            defines { "DEBUG" }
            flags { "Symbols", "ExtraWarnings", "FatalWarnings" }

