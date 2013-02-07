<?php

namespace Daw\Core\Provider\Log;

class Level {
    const FATAL = 0;
    const ERROR = 10;
    const WARN = 20;
    const NOTICE = 100;
    const INFO = 150;
    const DEBUG = 200;
    const TRACE = 255;

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
    }
}
