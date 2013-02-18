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
 * Application Exception base class
 *
 * All exceptions raised by the application and modules
 * shall extend this exception to be properly formatted
 * by the different services
 *
 * @package Daw
 * @subpackage Exception
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Exception extends \Exception {

    /**
     * Return exception associated data
     *
     * This returns following information
     *   type: type of exception
     *   message: exception message
     *
     * @return array exception data
     */
    public function getData() {
        return array(
            'type' => get_class($this),
            'message' => $this->getMessage()
        );
    }

}
