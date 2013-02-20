<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Exception;

/**
 * Application Exception - Module operation exception
 *
 * @package Daw
 * @subpackage Exception
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class OperationArgumentException extends OperationException {

    /**
     * @var argName name of the offending argument
     */
    protected $argName = null;

    /**
     * @var argValue value of the offending argument
     */
    protected $argValue = null;


    /**
     * Constructor
     *
     * @param string $operation operation
     * @param string argName name of the offending argument
     * @param string $message exception message
     * @param object value of the offending argument
     */
    public function __construct($operation, $argName, $message, $argValue = null) {
        parent::__construct($operation, $message, 302);

        $this->argName = $argName;
        $this->argValue = $argValue;
    }

    /**
     * Return exception data: type, operation, message, argument name, argument value
     *
     * @return array exception data
     */
    public function getData() {
        return array(
            'type' => get_class($this),
            'operation' => get_class($this->operation),
            'message' => $this->getMessage(),
            'name' => $this->argName,
            'value' => $this->argValue
        );
    }
}
