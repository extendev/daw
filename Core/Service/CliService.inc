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
use \Daw\Core\Service\Cli\CliServiceRequest;
use \Daw\Core\Service\Cli\CliServiceResponse;

/**
 * Command Line Service
 *
 * Entry point where all command line calls in are dispatched to.
 * Responses for this service are returned to client in indented text format.
 *
 * @package Daw
 * @subpackage Service
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class CliService extends Service {

    const RESPONSE_FORMAT =  'TextIndent';

    /**
     * Return user request for the CLI service
     *
     * @return CliServiceRequest
     */
    public function getRequest() {
        return new CliServiceRequest();
    }

    /**
     * Build response to be passed to user
     *
     * @return CliServiceResponse
     */
    public function buildResponse() {
        return new CliServiceResponse();
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
