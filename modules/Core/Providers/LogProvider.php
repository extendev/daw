<?php

namespace Daw\Modules\Core\Providers;

class LogProvider extends \Daw\Core\Provider\Log\LogProvider {

	public function __construct($core, $module = null) {
		parent::__construct($core, $module);
		date_default_timezone_set("UTC");
	}

	protected function getCallerClass() {
		$stack = debug_backtrace();

		return $stack[3]['class'];
	}

	/**
	 * Check which facilities shall be used to store the log
	 *
	 * If no levels could be found, the application will verify the default facility
	 * The function may return more than one facilities or false if no facilities could be found
	 *
	 * @return array
	 */
	protected function isLogEnabled($callerClass, $level = null) {
		$config = $this->core->config('log');
		if (!$config) {
			return false;
		}

		// List of facilities to use
		$facilities = array();

		foreach ($config['levels'] as $info) {
			$token = explode(' ', $info);
			$facilityClass = $token[0];
			if (strpos($callerClass, $facilityClass) === 0) {
				$facilityLevel = \Daw\Core\Provider\Log\Level::parseValue($token[1]);
				$facilityName = $token[2];
				if ($facilityLevel >= $level) {
					$facilities[$facilityName] = true;
				}
			}
		}

		if (count($facilities) === 0) {
			$facilityName = $config['defaultFacility'];
			$requiredLevel = \Daw\Core\Provider\Log\Level::parseValue($config['defaultLevel']);
			if ($requiredLevel >= $level) {
				$facilities[$facilityName] = true;
			}
		}

		return count($facilities) > 0 ? array_keys($facilities) : false;
	}

	protected function getFacility($name) {
		$config = $this->core->config('log');
		if (isset($config['facilities'][$name])) {
			return explode(' ', $config['facilities'][$name]);
		}

		return false;
	}

	public function log($message, $level = \Daw\Core\Provider\Log\Level::INFO) {
		$callerClass = $this->getCallerClass();
		$facilities = $this->isLogEnabled($callerClass, $level);
		if ($facilities === false) {
			return;
		}

		// Format message
		$message = "[" . date('Y-m-d H:i:s.u') . "][$level][$callerClass]:: " . __NAMESPACE__ . ' ' . $message;

		foreach ($facilities as $facilityName) {
			$facility = $this->getFacility($facilityName);
			switch ($facility[0]) {
				case 'syslog':
					syslog(LOG_INFO, $message);
					break;
				case 'errorlog':
					error_log($message . "\n", isset($facility[1]) ? $facility[1] : null, isset($facility[2]) ? $facility[2] : null);
					break;
				case 'file':
					error_log($message . "\n", 3, $facility[1]);
					break;
			}
		}
	}
}