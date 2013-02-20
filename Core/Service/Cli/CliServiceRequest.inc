<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Service\Cli;

use \Daw\Core\Service\ServiceRequest;

/**
 * Service request default class for CLI service
 *
 * @package Daw
 * @subpackage Service
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class CliServiceRequest extends ServiceRequest {

    /**
     * Return properties collected with request
     * For API service, properties are filled with $_SERVER array
     *
     * @return array service properties
     */
    public function getProperties() {
        return $_SERVER;
    }

    /**
     * Return list of arguments passed to the service and to be used by the module call
     * For CLI service, following arguments are being provided:
     *  - OBJECT name of the object requested
     *  - OPERATION name of the operation requested
     *  - PARAMS list of arguments collected from command line
     *
     * @return array
     */
    public function getArgs() {
        $args = array();
        $nbArgs =  $_SERVER['argc'];

    /*
        if ($nbArgs > 1) {
            $args['OBJECT'] = $_SERVER['argv'][1];
        }
        if ($nbArgs > 2) {
            $args['OPERATION'] = $_SERVER['argv'][2];
        }
     */

    if ($nbArgs > 2) {
      $args[ 'request'] = $_SERVER['argv'][1].".".$_SERVER['argv'][2];
    } elseif ($nbArgs > 1) {
      $args[ 'request'] = $_SERVER['argv'][1];
    } else {
      $args[ 'request'] = '';
    }

        $args['PARAMS'] = array();
        if ($nbArgs > 3) {
            foreach (array_slice($_SERVER['argv'], 2) as $arg) {
                if (strpos($arg, '=') === false) {
                    $args['PARAMS'][$arg] = true;
                } else {
                    $args['PARAMS'][substr($arg, 0, strpos($arg, '='))] = substr($arg, strpos($arg, '=') + 1);
                }
            }
        }
        
        return $args;
    }

    /**
     * Provides information related to the user authentication
     *
     * For CLI service, tokens are the following:
     *  - username: extracted from $_SERVER['DAW_USERNAME']
     *  - password: extracted from $_SERVER['DAW_PASSWORD']
     *
     * @return array
     */
    public function getAuthenticationToken() {
        $token = array();
        if (isset($_SERVER['DAW_USERNAME'])) {
            $token['username'] = $_SERVER['DAW_USERNAME'];
        }
        if (isset($_SERVER['DAW_PASSWORD'])) {
            $token['password'] = $_SERVER['DAW_PASSWORD'];
        }

        return $token;
    }
}
