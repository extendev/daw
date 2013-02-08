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

/**
 * Service Abstract Class
 *
 * Any new service shall extend this class so that user calls
 * can be processed by the application
 *
 * @package Daw
 * @subpackage Service
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
abstract class Service {

    /**
     * Return user request
     *
     * @return ServiceRequest
     */
    public abstract function getRequest();

    /**
     * Build response to be passed to user
     *
     * @return ServiceResponse
     */
    public abstract function buildResponse();
}
