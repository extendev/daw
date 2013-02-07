<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Service;

use \Daw\Core\Service\Service;
use \Daw\Core\Service\Http\HttpServiceRequest;
use \Daw\Core\Service\Http\HttpServiceResponse;

class HttpService extends Service {

    const RESPONSE_FORMAT =  'Json';

    public function getRequest() {
        return new HttpServiceRequest();
    }

    public function buildResponse() {
        return new HttpServiceResponse();
    }

    public function getResponseFormat() {
        return self::RESPONSE_FORMAT;
    }
}
