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

/**
 * Service response base class
 *
 * @package Daw
 * @subpackage Object
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class ServiceResponse {

    /**
     * @var ServiceRequest request associated to the response
     */
    protected $request = null;

    /**
     * @var boolean $success to be set to TRUE if operation completed successfully
     */
    public $success;

    /**
     * @var string $code if operation failed, may contain a code to help identifying error type
     */
    public $code;

    /**
     * @var string $message message associated to either the success or failure case
     */
    public $message;

    /**
     * @var object $contents associated contents provided with the response
     */
    public $contents;


    /**
     * Set associated request for which this response has been created
     *
     * @param ServiceRequest $request
     */
    public function setRequest($request) {
        $this->request = $request;
    }
}
