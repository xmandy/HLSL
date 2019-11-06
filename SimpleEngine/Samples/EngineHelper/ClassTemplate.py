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
	if not cls_name.startswith("S"):
		cls_name = "S" + cls_name
	if os.path.exists(os.path.join(PROJECT_ROOT, "Public")) or \
		os.path.exists(os.path.join(PROJECT_ROOT, "Private")):
		logger.error("not project path")
		return

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





