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

/**
 * Log level class
 * This class provides all allowed log level values to be used with log provider
 *
 * @package Daw
 * @subpackage Provider
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class Level {

    const FATAL = 0;
    const ERROR = 10;
    const WARN = 20;
    const NOTICE = 100;
    const INFO = 150;
    const DEBUG = 200;
    const TRACE = 255;

    /**
     * Return Level constant based on string representation
     *
     * @param string $value string log level to parse
     * @return the log value if found, NULL otherwise
     */
    public static function parseValue($value) {
        switch ($value) {
            case 'FATAL':
                return self::FATAL;
                break;
            case 'ERROR':
                return self::ERROR;
                break;
            case 'WARN':
                return self::WARN;
                break;
            case 'NOTICE':
                return self::NOTICE;
                break;
            case 'INFO':
                return self::INFO;
                break;
            case 'DEBUG':
                return self::DEBUG;
                break;
            case 'TRACE':
                return self::TRACE;
                break;
        }

        return null;
    }
}
