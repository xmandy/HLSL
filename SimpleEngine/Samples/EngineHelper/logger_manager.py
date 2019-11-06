import logging

class LoggerManager(object):

	def __init__(self):
		_logging_level = logging.DEBUG
		_format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
		logging.basicConfig(level=_logging_level, format=_format)

		self.file_handler = logging.FileHandler("log.txt", mode="w")
		self.file_handler.setLevel(_logging_level)
		_formater = logging.Formatter(_format)
		self.file_handler.setFormatter(_formater)

		# self.console_handler = logging.StreamHandler()
		# self.console_handler.setLevel(_logging_level)
		self.loggers = {}

	def create_logger(self, name, log_name=None):
		if name not in self.loggers:
			logger = logging.getLogger(name)
			if not log_name:
				file_handler = self.file_handler
			else:
				file_handler = logging.FileHandler(log_name, mode="w")
			# logger.addHandler(self.console_handler)
			logger.addHandler(file_handler)
			self.loggers[name] = logger

		return self.loggers[name]


logger_manager = LoggerManager()
