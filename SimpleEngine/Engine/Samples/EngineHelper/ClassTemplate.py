# -*- coding: UTF-8 -*-

import argparse
import os
import shutil
import logging
from logger_manager import logger_manager

logger = logger_manager.create_logger("EngineHelper", "log.txt")
logger.setLevel(logging.DEBUG)


SAMPLE_PATH = "../"
PROJECT_ROOT = "../../"

def create_class_template(project, cls_name, group=None):
	project_path = os.path.join(PROJECT_ROOT, project)
	if group:
		cls_path = os.path.join(PROJECT_ROOT, project, group)
	else:
		cls_path = project_path
	if not os.path.exists(project_path):
		os.makedirs(project_path)

	if not cls_name.startswith("S"):
		cls_name = "S" + cls_name
	header_path = os.path.join(cls_path, "Public")
	cpp_path = os.path.join(cls_path, "Private")
	if not os.path.exists(header_path):
		os.makedirs(header_path)
	if not os.path.exists(cpp_path):
		os.makedirs(cpp_path)

	cmake_dst_path = os.path.join(project_path, "CMakeLists.txt")
	if not os.path.exists(cmake_dst_path):
		cmake_src_path = os.path.join(SAMPLE_PATH, "CMakeLists_template.txt")
		shutil.copy(cmake_src_path, cmake_dst_path)

	header_file_path = os.path.join(header_path, "%s.h" % (cls_name, ))
	src_header_path = os.path.join(SAMPLE_PATH, "SampleClass.h")
	cpp_file_path = os.path.join(cpp_path, "%s.cpp" % (cls_name, ))
	src_cpp_path = os.path.join(SAMPLE_PATH, "SampleClass.cpp")

	shutil.copy(src_header_path, header_file_path)
	shutil.copy(src_cpp_path, cpp_file_path)
	logging.debug("create class %s of project %s" % (cls_name, project))

if __name__ == "__main__":
	parser = argparse.ArgumentParser(prog="ClsTemplate")
	parser.add_argument("-args", metavar="The project and the class name", default="")
	args = parser.parse_args()

	if not args.args:
		logger.error("Error input: (%s-%s)" % (args.project, args.cls_name))
	else:
		arg_list = args.args.split(",")
		if len(arg_list) == 2:
			project, cls_name = arg_list
		elif len(arg_list) == 3:
			project, group, cls_name = arg_list
		else:
			logger.error("Error input: (%s-%s)" % (args.project, args.cls_name))
		create_class_template(project, cls_name, group)





