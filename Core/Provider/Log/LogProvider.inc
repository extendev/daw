<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Provider\Log;

use \Daw\Core\Provider\Log\Level;

/**
 * Log Provider base abstract class
 * Extends this class if you wish to implement your own log provider
 *
 * @package Modules/Core
 * @subpackage Provider
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
abstract class LogProvider extends \Daw\Core\Provider\Provider {

    /**
     * Return TRUE if this provider serves the specified feature
     *
     * @param string $feature
     */
    public function isProviderFor($feature) {
        return $feature === 'log';
    }

    /**
     * Raise log message using specified leg level
     *
     * @param string $message associated message
     * @param int $level log level as available in Level class
     * @see \Daw\Core\Provider\Log\Level
     */
    public abstract function log($message, $level = \Daw\Core\Provider\Log\Level::INFO);

    /**
     * Raise log message using Level::FATAL level
     *
     * @param string $message associated message
     */
    public function fatal($message) {
        $this->log($message, \Daw\Core\Provider\Log\Level::FATAL);
    }

    /**
     * Raise log message using Level::ERROR level
     *
     * @param string $message associated message
     */
    public function error($message) {
        $this->log($message, \Daw\Core\Provider\Log\Level::ERROR);
    }

    /**
     * Raise log message using Level::WARN level
     *
     * @param string $message associated message
     */
    public function warn($message) {
        $this->log($message, \Daw\Core\Provider\Log\Level::WARN);
    }

    /**
     * Raise log message using Level::NOTICE level
     *
     * @param string $message associated message
     */
    public function notice($message) {
        $this->log($message, \Daw\Core\Provider\Log\Level::NOTICE);
    }

    /**
     * Raise log message using Level::INFO level
     *
     * @param string $message associated message
     */
    public function info($message) {
        $this->log($message, \Daw\Core\Provider\Log\Level::INFO);
    }

    /**
     * Raise log message using Level::DEBUG level
     *
     * @param string $message associated message
     */
    public function debug($message) {
        $this->log($message, \Daw\Core\Provider\Log\Level::DEBUG);
    }

    /**
     * Raise log message using Level::TRACE level
     *
     * @param string $message associated message
     */
    public function trace($message) {
        $this->log($message, \Daw\Core\Provider\Log\Level::TRACE);
    }
}

