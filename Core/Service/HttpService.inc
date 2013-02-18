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

/**
 * HTTP Service
 *
 * Entry point where all HTTP requests are dispatched to.
 * Responses for this service are returned to client in JSON format.
 *
 * @package Daw
 * @subpackage Service
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class HttpService extends Service {

    const RESPONSE_FORMAT =  'Json';

    /**
     * Return user request for the HTTP service
     *
     * @return HttpServiceRequest
     */
    public function getRequest() {
        return new HttpServiceRequest();
    }

    /**
     * Build response to be passed to user
     *
     * @return HttpServiceResponse
     */
    public function buildResponse() {
        return new HttpServiceResponse();
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
