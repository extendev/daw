<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Exception;

/**
 * Operation validation exception
 *
 * This exception is raised when validation on an operation parameter fails.
 *
 * @package Daw
 * @subpackage Exception
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class ValidationException extends Exception {

    /**
     * @var string Associated operation where the exception has been triggered
     */
    protected $operation = null;


    /**
     * Constructor
     *
     * @param string $message exception message
     * @param mixed $code exception code
     */
    public function __construct($message, $code = -1) {
        parent::__construct($message, $code);
    }

    /**
     * Return exception associated data
     *
     * Return validation exception message and the offending value
     */
    public function getData() {
        return array(
                'message' => $this->getMessage(),
                'value' => isset($this->argValue) ? $this->argValue : null
        );
    }

}
