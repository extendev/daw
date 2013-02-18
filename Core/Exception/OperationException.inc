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
 * Module operation exception
 *
 * This exception is raised whenever a module operation fails
 * to process in its business logic.
 *
 * It is expected to extend this exception to provide more
 * meaningful information to the developer, like OperationArgumentException
 *
 * @package Daw
 * @subpackage Exception
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class OperationException extends Exception {

    /**
     * @var string Associated operation where the exception has been triggered
     */
    protected $operation = null;


    /**
     * Constructor
     *
     * @param string $operation operation
     * @param string $message exception message
     * @param mixed $code exception code
     */
    public function __construct($operation, $message, $code = -1) {
        $this->operation = $operation;

        parent::__construct($message, $code);
    }

    /**
     * Return exception data: type, message, operation, argument name, argument value, operation args
     *
     * @return array exception data
     */
    public function getData() {
        return array(
                'type' => get_class($this),
                'message' => $this->getMessage(),
                'operation' => get_class($this->operation),
                'name' => isset($this->argName) ? $this->argName : null,
                'value' => isset($this->argValue) ? $this->argValue : null,
                'args' => print_r($this->operation->getArgs(), true)
        );
    }

}
