macro (cmpIncludePath RootPath)
	set(root_dir ${RootPath})
	file(GLOB children RELATIVE ${root_dir} ${root_dir}/*)

	foreach(child ${children})
		if(IS_DIRECTORY ${root_dir}/${child}/Public)
			#message(STATUS "include path " ${root_dir}/${child}/Public)
			list(APPEND AllEngineIncludePath ${root_dir}/${child})
		endif()
	endforeach()
endmacro (cmpIncludePath RootPath)

macro (cmpLibraryPath RootPath)
	set(lib_dir ${RootPath})
	file(GLOB children RELATIVE ${lib_dir} ${lib_dir}/*)
	foreach(child ${children})
		if (IS_DIRECTORY ${lib_dir}/${child}/Lib)
			list(APPEND AllEngineLinkPath ${lib_dir}/${child}/Lib)
		endif()
	endforeach()
	list(APPEND AllEngineIncludePath ${lib_dir})
endmacro (cmpLibraryPath RootPath)

macro (cmpDirectoryFiles RootPath IncludeFiles SourceFiles)
		if(IS_DIRECTORY ${RootPath}/Public)
			file(GLOB inc ${RootPath}/Public/*)
			list(APPEND ${IncludeFiles} ${inc})
		endif()
		if (IS_DIRECTORY ${RootPath}/Private)
			file(GLOB src ${RootPath}/Private/*)
			list(APPEND ${SourceFiles} ${src})
		endif()
endmacro (cmpDirectoryFiles RootPath IncludeFiles SourceFiles)


