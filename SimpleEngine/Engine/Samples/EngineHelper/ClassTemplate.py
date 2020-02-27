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

def create_class_template(project, cls_name):
	project_path = os.path.join(PROJECT_ROOT, project)
	if not os.path.exists(project_path):
		os.makedirs(project_path)

	if not cls_name.startswith("S"):
		cls_name = "S" + cls_name
	header_path = os.path.join(PROJECT_ROOT, project, "Public")
	cpp_path = os.path.join(PROJECT_ROOT, project, "Private")
	if not os.path.exists(header_path):
		os.makedirs(header_path)
	if not os.path.exists(cpp_path):
		os.makedirs(cpp_path)

	cmake_dst_path = os.path.join(PROJECT_ROOT, project, "CMakeLists.txt")
	if not os.path.exists(cmake_dst_path):
		cmake_src_path = os.path.join(SAMPLE_PATH, "CMakeLists_template.txt")
		shutil.copy(cmake_src_path, cmake_dst_path)

	header_path = os.path.join(PROJECT_ROOT, project, "Public/%s.h" % (cls_name, ))
	src_header_path = os.path.join(SAMPLE_PATH, "SampleClass.h")
	cpp_path = os.path.join(PROJECT_ROOT, project, "Private/%s.cpp" % (cls_name, ))
	src_cpp_path = os.path.join(SAMPLE_PATH, "SampleClass.cpp")

	shutil.copy(src_header_path, header_path)
	shutil.copy(src_cpp_path, cpp_path)
	logging.debug("create class %s of project %s" % (cls_name, project))

if __name__ == "__main__":
	parser = argparse.ArgumentParser(prog="ClsTemplate")
	parser.add_argument("-args", metavar="The project and the class name", default="")
	args = parser.parse_args()

	if not args.args:
		logger.error("Error input: (%s-%s)" % (args.project, args.cls_name))
	else:
		project, cls_name = args.args.split(",")
		create_class_template(project, cls_name)





