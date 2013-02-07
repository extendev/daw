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

class ApiServiceRequest extends ServiceRequest {

    public function getProperties() {
        return $_SERVER;
    }

    public function getArgs() {
        $args = array();
        $request = $_SERVER['PATH_INFO'];

        $requestTokens = explode('/', $request);
        $cntTokens = count($requestTokens);

        if ($cntTokens >= 2) {
            $args['OBJECT'] = $requestTokens[1];
        }
        if ($cntTokens >= 3) {
            $args['OPERATION'] = $requestTokens[2];
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
