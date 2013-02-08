<?php

/**
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

/**
 * Web Service API
 *
 * Entry point where all calls to web service are dispatched to.
 * Responses for this service are returned to client in JSON format.
 *
 * @package Daw
 * @subpackage Service
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class ApiService extends Service {

    const RESPONSE_FORMAT =  'Json';

    /**
     * Return user request for the API service
     *
     * @return ApiServiceRequest
     */
    public function getRequest() {
        return new ApiServiceRequest();
    }

    /**
     * Build response to be passed to user
     *
     * @return ApiServiceResponse
     */
    public function buildResponse() {
        return new ApiServiceResponse();
    }

    /**
     * Return default response format expected for this service
     *
     * @return string
     */
    public function getResponseFormat() {
        return self::RESPONSE_FORMAT;
    }
}
