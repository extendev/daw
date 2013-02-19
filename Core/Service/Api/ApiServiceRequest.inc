<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Service\Api;

use \Daw\Core\Service\ServiceRequest;

/**
 * Service request default class for HTTP service
 *
 * @package Daw
 * @subpackage Service
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class ApiServiceRequest extends ServiceRequest {

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
     * For API service, following arguments are being provided:
     *  - OBJECT name of the object requested
     *  - OPERATION name of the operation requested
     *  - GET list of arguments specified in the _GET variable, if request performed using GET method
     *  - POST list of arguments specified in the _GET variable, if request performed using GET method
     *
     * @return array
     */
    public function getArgs() {
        $args = array();
        $request = $_SERVER['PATH_INFO'];

        $requestTokens = explode('/', $request);
        $cntTokens = count($requestTokens);

/*
        if ($cntTokens >= 2) {
            $args['OBJECT'] = $requestTokens[1];
        }
        if ($cntTokens >= 3) {
            $args['OPERATION'] = $requestTokens[2];
        }
*/

    if ($cntTokens > 2) {
      $args[ 'request'] = $requestTokens[1].".".$requestTokens[2];
    } elseif ($cntTokens > 1) {
      $args[ 'request'] = $requestTokens[1];
    } else {
      $args[ 'request'] = '';
    }

        switch ($_SERVER['REQUEST_METHOD']) {
            case 'GET':
                $args['PARAMS'] = &$_GET;
                break;
            case 'POST':
                $args['PARAMS'] = &$_POST;
                break;
        }

        return $args;
    }

    /**
     * Provides information related to the user authentication
     *
     * For API service, tokens are requested to the user using HTTP basic authentication:
     *  - username: extracted from $_SERVER['PHP_AUTH_USER']
     *  - password: extracted from $_SERVER['PHP_AUTH_PW']
     *
     * @return array
     */
    public function getAuthenticationToken() {
        $token = array();
        if (isset($_SERVER['PHP_AUTH_USER'])) {
            $token['username'] = $_SERVER['PHP_AUTH_USER'];
        }
        if (isset($_SERVER['PHP_AUTH_PW'])) {
            $token['password'] = $_SERVER['PHP_AUTH_PW'];
        }

        return $token;
    }
}
