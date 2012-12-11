<?php

namespace Daw\Core\Provider\Log;

use \Daw\Core\Provider\Log\Level;

abstract class LogProvider extends \Daw\Core\Provider\Provider {

	/**
	 * Return TRUE if this provider serves the specified feature
	 *
	 * @param string $feature
	 */
	public function isProviderFor($feature) {
		return $feature === 'log';
	}

	public abstract function log($message, $level = \Daw\Core\Provider\Log\Level::INFO);

	public function fatal($message) {
		$this->log($message, \Daw\Core\Provider\Log\Level::FATAL);
	}
	public function error($message) {
		$this->log($message, \Daw\Core\Provider\Log\Level::ERROR);
	}
	public function warn($message) {
		$this->log($message, \Daw\Core\Provider\Log\Level::WARN);
	}
	public function notice($message) {
		$this->log($message, \Daw\Core\Provider\Log\Level::NOTICE);
	}
	public function info($message) {
		$this->log($message, \Daw\Core\Provider\Log\Level::INFO);
	}
	public function debug($message) {
		$this->log($message, \Daw\Core\Provider\Log\Level::DEBUG);
	}
	public function trace($message) {
		$this->log($message, \Daw\Core\Provider\Log\Level::TRACE);
	}
}

