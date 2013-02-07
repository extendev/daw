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
use \Daw\Core\Service\Api\ApiServiceRequest;
use \Daw\Core\Service\Api\ApiServiceResponse;

class ApiService extends Service {

    const RESPONSE_FORMAT =  'Json';

    public function getRequest() {
        return new ApiServiceRequest();
    }

    public function buildResponse() {
        return new ApiServiceResponse();
    }

    public function getResponseFormat() {
        return self::RESPONSE_FORMAT;
    }
}
