<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Object;

/**
 * Operation object
 *
 * @package Daw
 * @subpackage Object
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Operation {

    private $name = null;
    private $info = array();

    public function __construct($name, $info = array()) {
        $this->name = $name;
        $this->info = $info;
    }

    /**
     * Return operation name in parent module
     */
    public function getName() {
        return $this->name;
    }

    /**
    * Return module information
    */
    public function info($value = null) {
        if ($value === null) {
            return $this->info;
        }

        return $this->info[$value];
    }
}
