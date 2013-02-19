<?php

/**
 * This file is part of the Nbsdb package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this module source code.
 */

namespace Daw\Modules\Core\Providers;

/**
 * Log Provider basic implementation
 * Use PHP's errorlog, syslog or files to store logs.
 *
 * @package Modules/Core
 * @subpackage Providers
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class LogProvider extends \Daw\Core\Provider\Log\LogProvider {

    /**
     * Constructor
     *
     * @param Core $core daw instance
     * @param Module $module module owning the provider
     */
    public function __construct($core, $module = null) {
        parent::__construct($core, $module);
        date_default_timezone_set("UTC");
    }

    /**
     * Extract from current stacktrace the source class 
     * @return string class name
     */
    private function getCallerClass() {
        $stack = debug_backtrace();

        return $stack[3]['class'];
    }

    /**
     * Check which facilities shall be used to store the log
     *
     * If no levels could be found, the application will verify the default facility
     * The function may return more than one facilities or false if no facilities could be found
     *
     * @param string $callerClass the object class from where the exception is generated
     * @param int $level a \Daw\Core\Provider\Log\Level value
     * @return array
     */
    protected function getLogFacilities($callerClass, $level = null) {
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

    /**
     * Return facility definition with the given name, or FALSE if not found
     *
     * @param string $name
     * @return array the facility configuration as an array
     */
    protected function getFacility($name) {
        $config = $this->core->config('log');
        if (isset($config['facilities'][$name])) {
            return explode(' ', $config['facilities'][$name]);
        }

        return false;
    }

    /**
     * Raise log message using specified leg level
     *
     * @param string $message associated message
     * @param int $level log level as available in Level class
     * @see \Daw\Core\Provider\Log\Level
     */
    public function log($message, $level = \Daw\Core\Provider\Log\Level::INFO) {
        $callerClass = $this->getCallerClass();
        $facilities = $this->getLogFacilities($callerClass, $level);
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
                    $messageType = isset($facility[1]) ? $facility[1] : null;
                    $destination = isset($facility[2]) ? $facility[2] : null;
                    if ($messageType === 3 && !empty($destination) && $destination[0] !== '/') {
                        // We need to make the log path an absolute file
                        $destination = $this->core->path($destination);
                    }

                    error_log($message . "\n", $messageType, $destination);
                    break;

                case 'file':
                    $destination = isset($facility[1]) ? $facility[1] : null;
                    if (!empty($destination) && $destination[0] !== '/') {
                        // We need to make the log path an absolute file
                        $destination = $this->core->path($destination);
                    }
                    error_log($message . "\n", 3, $destination);
                    break;
            }
        }
    }
}
